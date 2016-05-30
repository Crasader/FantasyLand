#pragma once
#include <string>
#include "cocos2d.h"
#include "Helper.h"

extern float FXZorder;
extern float CelLine;
extern std::string BossTaunt;
extern AnimationCache * animationCache ;

void init();

extern struct RECTS_ RECTS;
extern struct G G;
extern struct BGM_RES BGM_RES;
extern enum AUDIO_ID AUDIO_ID;

//

extern struct ActorCommonValues ActorCommonValues;
extern struct ActorDefaultValues ActorDefaultValues;
extern struct KnightValues KnightValues;
extern struct MageValues MageValues;
extern struct ArcherValues ArcherValues;
extern struct DragonValues DragonValues;
extern struct SlimeValues SlimeValues;
extern struct PigletValues PigletValues;
extern struct RatValues  RatValues;
extern struct BossValues BossValues;
extern struct CommonAudios CommonAudios;
extern struct MonsterSlimeValues MonsterSlimeValues;
extern struct MonsterDragonValues MonsterDragonValues;
extern struct MonsterRatValues MonsterRatValues;
extern struct MonsterPigletValues MonsterPigletValues;
extern struct WarriorProperty WarriorProperty;
extern struct Archerproperty Archerproperty;
extern struct MageProperty MageProperty;
extern struct ReSkin ReSkin;

