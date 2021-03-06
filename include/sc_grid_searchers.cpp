/* Copyright (C) 2006 - 2012 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#include "precompiled.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"

//return closest attackable Unit in grid, with range from pSource 
Unit* GetClosestAttackableUnit(Unit* pSource, float fMaxSearchRange) 
{ 
    Unit* pTarget = NULL; 
    MaNGOS::NearestAttackableUnitInObjectRangeCheck unit_check(pSource, fMaxSearchRange); 
    MaNGOS::UnitLastSearcher<MaNGOS::NearestAttackableUnitInObjectRangeCheck> searcher(pTarget, unit_check); 
    Cell::VisitAllObjects(pSource, searcher, fMaxSearchRange); 
    return pTarget; 
}

//return closest GO in grid, with range from pSource
GameObject* GetClosestGameObjectWithEntry(WorldObject* pSource, uint32 uiEntry, float fMaxSearchRange)
{
    GameObject* pGo = NULL;

    MaNGOS::NearestGameObjectEntryInObjectRangeCheck go_check(*pSource, uiEntry, fMaxSearchRange);
    MaNGOS::GameObjectLastSearcher<MaNGOS::NearestGameObjectEntryInObjectRangeCheck> searcher(pGo, go_check);

    Cell::VisitGridObjects(pSource, searcher, fMaxSearchRange);

    return pGo;
}

//return closest creature alive in grid, with range from pSource
Creature* GetClosestCreatureWithEntry(WorldObject* pSource, uint32 uiEntry, float fMaxSearchRange, bool bOnlyAlive/*=true*/, bool bOnlyDead/*=false*/)
{
    Creature* pCreature = NULL;

    MaNGOS::NearestCreatureEntryWithLiveStateInObjectRangeCheck creature_check(*pSource, uiEntry, bOnlyAlive, bOnlyDead, fMaxSearchRange);
    MaNGOS::CreatureLastSearcher<MaNGOS::NearestCreatureEntryWithLiveStateInObjectRangeCheck> searcher(pCreature, creature_check);

    Cell::VisitGridObjects(pSource, searcher, fMaxSearchRange);

    return pCreature;
}

void GetGameObjectListWithEntryInGrid(std::list<GameObject*>& lList , WorldObject* pSource, uint32 uiEntry, float fMaxSearchRange)
{
    MaNGOS::GameObjectEntryInPosRangeCheck check(*pSource, uiEntry, pSource->GetPositionX(), pSource->GetPositionY(), pSource->GetPositionZ(), fMaxSearchRange);
    MaNGOS::GameObjectListSearcher<MaNGOS::GameObjectEntryInPosRangeCheck> searcher(lList, check);

    Cell::VisitGridObjects(pSource, searcher, fMaxSearchRange);
}

void GetCreatureListWithEntryInGrid(std::list<Creature*>& lList, WorldObject* pSource, uint32 uiEntry, float fMaxSearchRange)
{
    MaNGOS::AllCreaturesOfEntryInRangeCheck check(pSource, uiEntry, fMaxSearchRange);
    MaNGOS::CreatureListSearcher<MaNGOS::AllCreaturesOfEntryInRangeCheck> searcher(lList, check);

    Cell::VisitGridObjects(pSource, searcher, fMaxSearchRange);
}
