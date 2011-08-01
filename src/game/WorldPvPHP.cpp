/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Worldmap_outland
SD%Complete:
SDComment:
SDCategory: Outland
EndScriptData */

#include "WorldPvP.h"
#include "WorldPvPHP.h"

/*  Comments
 * This implements the basics of tower capturing in Eastern Plaguelands
 * When a player faction captures a capture point then it triggers some event (helpers + buff)
 * The tower states are processed by the capture point events
 */

WorldPvPHP::WorldPvPHP() : WorldPvP(),

    m_uiHPTowersAlly(0),
    m_uiHPTowersHorde(0)
{
    for (uint8 i=0; i<MAX_HP_TOWERS; i++)
    {
        m_uiHPWorldState[i] = WORLD_STATE_HP[i][1];
        m_uiHPController[i] = 50;
        m_uiHPState[i] = NEUTRAL;
        m_HPTowerBannerGuid[i].Clear();
        m_HPTowerPointGuid[i].Clear();
    }

    m_uiTypeId = WORLD_PVP_TYPE_HP;
}

bool WorldPvPHP::InitWorldPvPArea()
{
    RegisterZone(ZONE_ID_HELLFIRE_PENINSULA);
    RegisterZone(ZONE_ID_HELLFIRE_CITADEL);
    RegisterZone(ZONE_ID_HELLFIRE_RAMPARTS);
    RegisterZone(ZONE_ID_BLOOD_FURNACE);
    RegisterZone(ZONE_ID_SHATTERED_HALLS);
    RegisterZone(ZONE_ID_MAGTHERIDON_LAIR);

    return true;
}

void WorldPvPHP::FillInitialWorldStates(WorldPacket& data, uint32& count)
{
    FillInitialWorldState(data, count, 2489, 1);
    FillInitialWorldState(data, count, 2490, 1);

    FillInitialWorldState(data, count, 2473, 0);
    FillInitialWorldState(data, count, 2474, 0);
    FillInitialWorldState(data, count, 2475, 0);

    FillInitialWorldState(data, count, WORLD_STATE_HP_TOWER_COUNT_ALY,   m_uiHPTowersAlly);
    FillInitialWorldState(data, count, WORLD_STATE_HP_TOWER_COUNT_HORDE, m_uiHPTowersHorde);

    // towers
    for (uint8 i=0; i<MAX_HP_TOWERS; i++)
    {
        FillInitialWorldState(data, count, WORLD_STATE_HP[i][0], 
            (WORLD_STATE_HP[i][0]==m_uiHPWorldState[i])?1:0);
        FillInitialWorldState(data, count, WORLD_STATE_HP[i][1], 
            (WORLD_STATE_HP[i][1]==m_uiHPWorldState[i])?1:0);
        FillInitialWorldState(data, count, WORLD_STATE_HP[i][2], 
            (WORLD_STATE_HP[i][2]==m_uiHPWorldState[i])?1:0);
    }
}

void WorldPvPHP::SendRemoveWorldStates(Player* pPlayer)
{
    pPlayer->SendUpdateWorldState(2489, 0);
    pPlayer->SendUpdateWorldState(2490, 0);

    // slider
    pPlayer->SendUpdateWorldState(2473, 0);
    pPlayer->SendUpdateWorldState(2474, 0);
    pPlayer->SendUpdateWorldState(2475, 0);

    pPlayer->SendUpdateWorldState(WORLD_STATE_HP_TOWER_COUNT_ALY,      0);
    pPlayer->SendUpdateWorldState(WORLD_STATE_HP_TOWER_COUNT_HORDE,    0);

    // towers
    for (uint8 i=0; i<MAX_HP_TOWERS; i++)
    {
        pPlayer->SendUpdateWorldState(WORLD_STATE_HP[i][0], 0);
        pPlayer->SendUpdateWorldState(WORLD_STATE_HP[i][1], 0);
        pPlayer->SendUpdateWorldState(WORLD_STATE_HP[i][2], 0);
    }
}

void WorldPvPHP::UpdateWorldState()
{
    // update only tower count; tower states is updated in the process event
    SendUpdateWorldState(WORLD_STATE_HP_TOWER_COUNT_ALY,   m_uiHPTowersAlly);
    SendUpdateWorldState(WORLD_STATE_HP_TOWER_COUNT_HORDE, m_uiHPTowersHorde);
}

void WorldPvPHP::OnGameObjectCreate(GameObject* pGo)
{
    switch(pGo->GetEntry())
    {
        case GO_TOWER_BANNER_OVERLOOK:
            m_HPTowerBannerGuid[0] = pGo->GetObjectGuid();
            pGo->SetGoArtKit(GO_ARTKIT_HP[0][CaptureSt(m_uiHPState[0])]);
            break;
        case GO_TOWER_BANNER_STADIUM:
            m_HPTowerBannerGuid[1] = pGo->GetObjectGuid();
            pGo->SetGoArtKit(GO_ARTKIT_HP[1][CaptureSt(m_uiHPState[1])]);
            break;
        case GO_TOWER_BANNER_BRONEK_HILL:
            m_HPTowerBannerGuid[2] = pGo->GetObjectGuid();
            pGo->SetGoArtKit(GO_ARTKIT_HP[2][CaptureSt(m_uiHPState[2])]);
            break;
        case GO_HELLFIRE_BANNER_OVERLOOK:
            m_HPTowerPointGuid[0] = pGo->GetObjectGuid();
            pGo->SetCapture(m_uiHPController[0], CapturePointState(m_uiHPState[0]));
            pGo->SetGoArtKit(GO_ARTKIT_BANNER[CaptureSt(m_uiHPState[0])]);
            break;
        case GO_HELLFIRE_BANNER_STADIUM:
            m_HPTowerPointGuid[1] = pGo->GetObjectGuid();
            pGo->SetCapture(m_uiHPController[1], CapturePointState(m_uiHPState[1]));
            pGo->SetGoArtKit(GO_ARTKIT_BANNER[CaptureSt(m_uiHPState[1])]);
            break;
        case GO_HELLFIRE_BANNER_BROKEN_HILL:
            m_HPTowerPointGuid[2] = pGo->GetObjectGuid();
            pGo->SetCapture(m_uiHPController[2], CapturePointState(m_uiHPState[2]));
            pGo->SetGoArtKit(GO_ARTKIT_BANNER[CaptureSt(m_uiHPState[2])]);
            break;
        default:
            return;
    }
}

void WorldPvPHP::HandlePlayerEnterZone(Player* pPlayer)
{
    // cast buff the the player which enters the zone
    switch(pPlayer->GetTeam())
    {
        case ALLIANCE:
            if (m_uiHPTowersAlly == MAX_HP_TOWERS)
                pPlayer->CastSpell(pPlayer, SPELL_HELLFIRE_SUPERIORITY_ALY, false);
            break;
        case HORDE:
            if (m_uiHPTowersHorde == MAX_HP_TOWERS)
                pPlayer->CastSpell(pPlayer, SPELL_HELLFIRE_SUPERIORITY_HORDE, false);
            break;
    }

    WorldPvP::HandlePlayerEnterZone(pPlayer);
}

void WorldPvPHP::HandlePlayerLeaveZone(Player* pPlayer)
{
    if (pPlayer->HasAura(pPlayer->GetTeam() == ALLIANCE ? SPELL_HELLFIRE_SUPERIORITY_ALY : SPELL_HELLFIRE_SUPERIORITY_HORDE))
        pPlayer->RemoveAurasDueToSpell(pPlayer->GetTeam() == ALLIANCE ? SPELL_HELLFIRE_SUPERIORITY_ALY : SPELL_HELLFIRE_SUPERIORITY_HORDE);

    WorldPvP::HandlePlayerLeaveZone(pPlayer);
}

void WorldPvPHP::HandleObjectiveComplete(PlayerSet m_sPlayersSet, uint32 uiEventId)
{
    uint32 uiCredit = 0;

    switch(uiEventId)
    {
        case EVENT_OVERLOOK_PROGRESS_HORDE:
        case EVENT_OVERLOOK_PROGRESS_ALLIANCE:
            uiCredit = NPC_CAPTURE_CREDIT_OVERLOOK;
            break;
        case EVENT_STADIUM_PROGRESS_HORDE:
        case EVENT_STADIUM_PROGRESS_ALLIANCE:
            uiCredit = NPC_CAPTURE_CREDIT_STADIUM;
            break;
        case EVENT_BROKEN_HILL_PROGRESS_HORDE:
        case EVENT_BROKEN_HILL_PROGRESS_ALLIANCE:
            uiCredit = NPC_CAPTURE_CREDIT_BROKEN_HILL;
            break;
    }

    if (!uiCredit)
        return;

    for(PlayerSet::iterator itr = m_sPlayersSet.begin(); itr != m_sPlayersSet.end(); ++itr)
    {
        if (!(*itr))
            continue;

        (*itr)->KilledMonsterCredit(uiCredit);
    }
}


void WorldPvPHP::SetData(uint32 uiType, uint32 uiData)
{
    if (uiType<MAX_HP_TOWERS)
    {
        SendUpdateWorldState(m_uiHPWorldState[uiType], 0);

        if ((m_uiHPState[uiType]==NEUTRAL) && (uiData==PROGRESS_A))
        {
            m_uiHPWorldState[uiType] = WORLD_STATE_HP[uiType][0];
            ++m_uiHPTowersAlly;

            // set artkit
            SetBannerArtKit(m_HPTowerBannerGuid[uiType], GO_ARTKIT_HP[uiType][0]);
        } else
        if ((m_uiHPState[uiType]>NEUTRAL) && (uiData==NEUTRAL))
        {
            m_uiHPWorldState[uiType] = WORLD_STATE_HP[uiType][1];
            --m_uiHPTowersAlly;

            // set artkit
            SetBannerArtKit(m_HPTowerBannerGuid[uiType], GO_ARTKIT_HP[uiType][1]);
        } else 
        if ((m_uiHPState[uiType]==NEUTRAL) && (uiData==PROGRESS_H))
        {
            m_uiHPWorldState[uiType] = WORLD_STATE_HP[uiType][2];
            ++m_uiHPTowersHorde;

            // set artkit
            SetBannerArtKit(m_HPTowerBannerGuid[uiType], GO_ARTKIT_HP[uiType][2]);
        } else
        if ((m_uiHPState[uiType]<NEUTRAL) && (uiData==NEUTRAL))
        {
            m_uiHPWorldState[uiType] = WORLD_STATE_HP[uiType][1];
            --m_uiHPTowersHorde;

            // set artkit
            SetBannerArtKit(m_HPTowerBannerGuid[uiType], GO_ARTKIT_HP[uiType][1]);
        }

        SendUpdateWorldState(m_uiHPWorldState[uiType], 1);

        m_uiHPState[uiType] = uiData;
        m_uiHPController[uiType] = WorldPvP::GetGoTowerPos(m_HPTowerBannerGuid[uiType]);
    } else return;

    // buff alliance
    if (m_uiHPTowersAlly == MAX_HP_TOWERS)
        WorldPvP::DoProcessTeamBuff(ALLIANCE, SPELL_HELLFIRE_SUPERIORITY_ALY);
    // buff horde
    if (m_uiHPTowersHorde == MAX_HP_TOWERS)
        WorldPvP::DoProcessTeamBuff(HORDE, SPELL_HELLFIRE_SUPERIORITY_HORDE);

    // debuff players if towers == 0; spell to remove will be always the first
    if (m_uiHPTowersHorde < MAX_HP_TOWERS)
        WorldPvP::DoProcessTeamBuff(HORDE, SPELL_HELLFIRE_SUPERIORITY_HORDE, true);
    if (m_uiHPTowersAlly < MAX_HP_TOWERS)
        WorldPvP::DoProcessTeamBuff(ALLIANCE, SPELL_HELLFIRE_SUPERIORITY_ALY, true);

    // update states counters
    // the map tower states are updated in the ProcessCaptureEvent function
    SendUpdateWorldState(WORLD_STATE_HP_TOWER_COUNT_ALY, m_uiHPTowersAlly);
    SendUpdateWorldState(WORLD_STATE_HP_TOWER_COUNT_HORDE, m_uiHPTowersHorde);
}

void WorldPvPHP::SetBannerArtKit(ObjectGuid BannerGuid, uint32 uiArtKit)
{
    // neet to use a player as anchor for the map
    Player* pPlayer = GetPlayerInZone();
    if (!pPlayer)
        return;

    if (GameObject* pBanner = pPlayer->GetMap()->GetGameObject(BannerGuid))
        pBanner->SetGoArtKit(uiArtKit);
}

// process the capture events
void WorldPvPHP::ProcessEvent(GameObject* pGo, Player* pPlayer, uint32 uiEventId)
{
    uint8 tower;

    switch (pGo->GetEntry())
    {
        case GO_HELLFIRE_BANNER_OVERLOOK:       tower = 0; break;
        case GO_HELLFIRE_BANNER_STADIUM:        tower = 1; break;
        case GO_HELLFIRE_BANNER_BROKEN_HILL:    tower = 2; break;
        default: return;
    }

    if (uiEventId == EVENT_HP[tower][0])
        SetData(tower, CONTESTED_H);
    else if (uiEventId == EVENT_HP[tower][1])
        SetData(tower, CONTESTED_A);
    else if (uiEventId == EVENT_HP[tower][2])
    {
        SetData(tower, NEUTRAL);
        sWorld.SendZoneText(ZONE_ID_HELLFIRE_PENINSULA, sObjectMgr.GetMangosStringForDBCLocale(HP_LANG_LOOSE_H[tower]));
    } else if (uiEventId == EVENT_HP[tower][3])
    {
        SetData(tower, NEUTRAL);
        sWorld.SendZoneText(ZONE_ID_HELLFIRE_PENINSULA, sObjectMgr.GetMangosStringForDBCLocale(HP_LANG_LOOSE_A[tower]));
    } else if (uiEventId == EVENT_HP[tower][4])
    {
        SetData(tower, PROGRESS_H);
        sWorld.SendZoneText(ZONE_ID_HELLFIRE_PENINSULA, sObjectMgr.GetMangosStringForDBCLocale(HP_LANG_CAPTURE_H[tower]));
    } else if (uiEventId == EVENT_HP[tower][5])
    {
        SetData(tower, PROGRESS_A);
        sWorld.SendZoneText(ZONE_ID_HELLFIRE_PENINSULA, sObjectMgr.GetMangosStringForDBCLocale(HP_LANG_CAPTURE_A[tower]));
    } else if (uiEventId == EVENT_HP[tower][6])
        SetData(tower, WIN_H);
    else if (uiEventId == EVENT_HP[tower][7])
        SetData(tower, WIN_A);
}
