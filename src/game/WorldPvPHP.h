/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef WORLD_PVP_HP
#define WORLD_PVP_HP

#include "Language.h"

const uint32 HP_LANG_LOOSE_A[3] = {LANG_OPVP_HP_LOOSE_OVERLOOK_A, LANG_OPVP_HP_LOOSE_STADIUM_A, LANG_OPVP_HP_LOOSE_BROKENHILL_A};
const uint32 HP_LANG_LOOSE_H[3] = {LANG_OPVP_HP_LOOSE_OVERLOOK_H, LANG_OPVP_HP_LOOSE_STADIUM_H, LANG_OPVP_HP_LOOSE_BROKENHILL_H};
const uint32 HP_LANG_CAPTURE_A[3] = {LANG_OPVP_HP_CAPTURE_OVERLOOK_A, LANG_OPVP_HP_CAPTURE_STADIUM_A, LANG_OPVP_HP_CAPTURE_BROKENHILL_A};
const uint32 HP_LANG_CAPTURE_H[3] = {LANG_OPVP_HP_CAPTURE_OVERLOOK_H, LANG_OPVP_HP_CAPTURE_STADIUM_H, LANG_OPVP_HP_CAPTURE_BROKENHILL_H};

enum
{
    MAX_HP_TOWERS                           = 3,

    TYPE_OVERLOOK_STATE                     = 0,
    TYPE_STADIUM_STATE                      = 1,
    TYPE_BROKEN_HILL_STATE                  = 2,

    // tower ids
    // they are used in the process event functions
    TOWER_ID_OVERLOOK                       = 0,
    TOWER_ID_STADIUM                        = 1,
    TOWER_ID_BROKEN_HILL                    = 2,

    // spells
    SPELL_HELLFIRE_TOWER_TOKEN_ALY          = 32155,
    SPELL_HELLFIRE_TOWER_TOKEN_HORDE        = 32158,
    SPELL_HELLFIRE_SUPERIORITY_ALY          = 32071,
    SPELL_HELLFIRE_SUPERIORITY_HORDE        = 32049,

    // zone ids
    ZONE_ID_HELLFIRE_PENINSULA              = 3483,
    ZONE_ID_HELLFIRE_CITADEL                = 3563,
    ZONE_ID_HELLFIRE_RAMPARTS               = 3562,
    ZONE_ID_BLOOD_FURNACE                   = 3713,
    ZONE_ID_SHATTERED_HALLS                 = 3714,
    ZONE_ID_MAGTHERIDON_LAIR                = 3836,

    // npcs
    NPC_CAPTURE_CREDIT_OVERLOOK             = 19028,
    NPC_CAPTURE_CREDIT_STADIUM              = 19029,
    NPC_CAPTURE_CREDIT_BROKEN_HILL          = 19032,

    // gameobjects
    GO_TOWER_BANNER_OVERLOOK                = 182525,
    GO_TOWER_BANNER_STADIUM                 = 183515,
    GO_TOWER_BANNER_BRONEK_HILL             = 183514,

    // capture points
    GO_HELLFIRE_BANNER_OVERLOOK             = 182174,
    GO_HELLFIRE_BANNER_STADIUM              = 182173,
    GO_HELLFIRE_BANNER_BROKEN_HILL          = 182175,

    // events
    EVENT_OVERLOOK_WIN_ALLIANCE             = 11398,
    EVENT_OVERLOOK_WIN_HORDE                = 11397,
    EVENT_OVERLOOK_CONTEST_ALLIANCE         = 11392,
    EVENT_OVERLOOK_CONTEST_HORDE            = 11391,
    EVENT_OVERLOOK_PROGRESS_ALLIANCE        = 11396,
    EVENT_OVERLOOK_PROGRESS_HORDE           = 11395,
    EVENT_OVERLOOK_NEUTRAL_ALLIANCE         = 11394,
    EVENT_OVERLOOK_NEUTRAL_HORDE            = 11393,

    EVENT_STADIUM_WIN_ALLIANCE              = 11390,
    EVENT_STADIUM_WIN_HORDE                 = 11389,
    EVENT_STADIUM_CONTEST_ALLIANCE          = 11384,
    EVENT_STADIUM_CONTEST_HORDE             = 11383,
    EVENT_STADIUM_PROGRESS_ALLIANCE         = 11388,
    EVENT_STADIUM_PROGRESS_HORDE            = 11387,
    EVENT_STADIUM_NEUTRAL_ALLIANCE          = 11386,
    EVENT_STADIUM_NEUTRAL_HORDE             = 11385,

    EVENT_BROKEN_HILL_WIN_ALLIANCE          = 11406,
    EVENT_BROKEN_HILL_WIN_HORDE             = 11405,
    EVENT_BROKEN_HILL_CONTEST_ALLIANCE      = 11400,
    EVENT_BROKEN_HILL_CONTEST_HORDE         = 11399,
    EVENT_BROKEN_HILL_PROGRESS_ALLIANCE     = 11404,
    EVENT_BROKEN_HILL_PROGRESS_HORDE        = 11403,
    EVENT_BROKEN_HILL_NEUTRAL_ALLIANCE      = 11402,
    EVENT_BROKEN_HILL_NEUTRAL_HORDE         = 11401,

    // tower artkits
    GO_ARTKIT_BROKEN_HILL_ALY               = 65,
    GO_ARTKIT_BROKEN_HILL_HORDE             = 64,
    GO_ARTKIT_BROKEN_HILL_NEUTRAL           = 66,

    GO_ARTKIT_OVERLOOK_ALY                  = 62,
    GO_ARTKIT_OVERLOOK_HORDE                = 61,
    GO_ARTKIT_OVERLOOK_NEUTRAL              = 63,

    GO_ARTKIT_STADIUM_ALY                   = 67,
    GO_ARTKIT_STADIUM_HORDE                 = 68,
    GO_ARTKIT_STADIUM_NEUTRAL               = 69,

    // world states
    WORLD_STATE_HP_TOWER_COUNT_ALY          = 0x9ac,
    WORLD_STATE_HP_TOWER_COUNT_HORDE        = 0x9ae,

    WORLD_STATE_BROKEN_HILL_ALY             = 0x9b3,
    WORLD_STATE_BROKEN_HILL_HORDE           = 0x9b4,
    WORLD_STATE_BROKEN_HILL_NEUTRAL         = 0x9b5,

    WORLD_STATE_OVERLOOK_ALY                = 0x9b0,
    WORLD_STATE_OVERLOOK_HORDE              = 0x9b1,
    WORLD_STATE_OVERLOOK_NEUTRAL            = 0x9b2,

    WORLD_STATE_STADIUM_ALY                 = 0x9a7,
    WORLD_STATE_STADIUM_HORDE               = 0x9a6,
    WORLD_STATE_STADIUM_NEUTRAL             = 0x9a8,
};

const uint32 HP_CAPTURE_CREDIT[3] = {NPC_CAPTURE_CREDIT_OVERLOOK, NPC_CAPTURE_CREDIT_STADIUM, NPC_CAPTURE_CREDIT_BROKEN_HILL};

const uint32 EVENT_HP[3][8] = {
    {EVENT_OVERLOOK_CONTEST_HORDE, EVENT_OVERLOOK_CONTEST_ALLIANCE, EVENT_OVERLOOK_NEUTRAL_HORDE, EVENT_OVERLOOK_NEUTRAL_ALLIANCE,
    EVENT_OVERLOOK_PROGRESS_HORDE, EVENT_OVERLOOK_PROGRESS_ALLIANCE, EVENT_OVERLOOK_WIN_HORDE, EVENT_OVERLOOK_WIN_ALLIANCE},
    {EVENT_STADIUM_CONTEST_HORDE, EVENT_STADIUM_CONTEST_ALLIANCE, EVENT_STADIUM_NEUTRAL_HORDE, EVENT_STADIUM_NEUTRAL_ALLIANCE,
    EVENT_STADIUM_PROGRESS_HORDE, EVENT_STADIUM_PROGRESS_ALLIANCE, EVENT_STADIUM_WIN_HORDE, EVENT_STADIUM_WIN_ALLIANCE},
    {EVENT_BROKEN_HILL_CONTEST_HORDE, EVENT_BROKEN_HILL_CONTEST_ALLIANCE, EVENT_BROKEN_HILL_NEUTRAL_HORDE, EVENT_BROKEN_HILL_NEUTRAL_ALLIANCE,
    EVENT_BROKEN_HILL_PROGRESS_HORDE, EVENT_BROKEN_HILL_PROGRESS_ALLIANCE, EVENT_BROKEN_HILL_WIN_HORDE, EVENT_BROKEN_HILL_WIN_ALLIANCE}};

const uint8 GO_ARTKIT_HP[3][3] = {{62, 63, 61}, {67, 69, 68}, {65, 66, 64}};

const uint8 GO_ARTKIT_BANNER[3] = {2, 21, 1};

const uint32 WORLD_STATE_HP[3][3] = {{WORLD_STATE_OVERLOOK_ALY, WORLD_STATE_OVERLOOK_NEUTRAL, WORLD_STATE_OVERLOOK_HORDE},
                                   {WORLD_STATE_STADIUM_ALY, WORLD_STATE_STADIUM_NEUTRAL, WORLD_STATE_STADIUM_HORDE},
                                   {WORLD_STATE_BROKEN_HILL_ALY, WORLD_STATE_BROKEN_HILL_NEUTRAL, WORLD_STATE_BROKEN_HILL_HORDE}};

class WorldPvPHP : public WorldPvP
{
    public:
        WorldPvPHP();


        bool InitWorldPvPArea();

        //void OnCreatureCreate(Creature* pCreature);
        void OnGameObjectCreate(GameObject* pGo);
        void ProcessEvent(GameObject* pGo, Player* pPlayer, uint32 uiEventId);

        void HandlePlayerEnterZone(Player* pPlayer);
        void HandlePlayerLeaveZone(Player* pPlayer);
        void HandleObjectiveComplete(PlayerSet m_sPlayersSet, uint32 uiEventId);

        void SetData(uint32 uiType, uint32 uiData);

        void FillInitialWorldStates(WorldPacket& data, uint32& count);
        void SendRemoveWorldStates(Player* pPlayer);
        void UpdateWorldState();

        void SetBannerArtKit(ObjectGuid BannerGuid, uint32 uiArtkit);

        uint8 CaptureSt(uint8 st)
        {
            if (st == NEUTRAL) return 1;
            if (st > NEUTRAL) return 0;
            return 2;
        }

    protected:

        uint32 m_uiHPController[3];
        uint32 m_uiHPState[3];
        uint32 m_uiHPWorldState[3];
        uint32 m_uiHPTowersAlly;
        uint32 m_uiHPTowersHorde;

        ObjectGuid m_HPTowerBannerGuid[3];
        ObjectGuid m_HPTowerPointGuid[3];
};

#endif