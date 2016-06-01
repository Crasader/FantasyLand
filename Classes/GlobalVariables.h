#pragma once
#include <string>
#include "cocos2d.h"
#include "Helper.h"

extern float FXZorder;
extern float CelLine;
extern std::string BossTaunt;
extern AnimationCache * animationCache ;

void init();

extern struct RECTS_d RECTS;
extern struct G_d G;
extern struct BGM_RES_d BGM_RES;
extern enum AUDIO_ID_d AUDIO_ID;

//

extern struct ActorCommonValues_d ActorCommonValues;
extern struct ActorDefaultValues_d ActorDefaultValues;
extern struct KnightValues_d KnightValues;
extern struct MageValues_d MageValues;
extern struct ArcherValues_d ArcherValues;
extern struct DragonValues_d DragonValues;
extern struct SlimeValues_d SlimeValues;
extern struct PigletValues_d PigletValues;
extern struct RatValues_d  RatValues;
extern struct BossValues_d BossValues;
extern struct CommonAudios_d CommonAudios;
extern struct MonsterSlimeValues_d MonsterSlimeValues;
extern struct MonsterDragonValues_d MonsterDragonValues;
extern struct MonsterRatValues_d MonsterRatValues;
extern struct MonsterPigletValues_d MonsterPigletValues;
extern struct WarriorProperty_d WarriorProperty;
extern struct Archerproperty_d Archerproperty;
extern struct MageProperty_d MageProperty;
extern struct ReSkin_d ReSkin;

