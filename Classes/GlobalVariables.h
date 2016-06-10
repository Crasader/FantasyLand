﻿#pragma once
#include "cocos2d.h"
#include "Helper.h"

void gv_init();

extern float FXZorder;
extern float CelLine;
extern std::string BossTaunt;
extern AnimationCache * animationCache ;
extern Layer * currentLayer;


extern struct RECTS_d RECTS;
extern struct G_d G;
extern struct BGM_RES_d BGM_RES;
extern struct AUDIO_ID_d AUDIO_ID;
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



struct RECTS_d
{
	Rect iceBolt = SpriteFrameCache::getInstance()->getSpriteFrameByName("icebolt.png")->getRect();
	Rect iceSpike = SpriteFrameCache::getInstance()->getSpriteFrameByName("iceSpike1.png")->getRect();
	Rect fireBall = SpriteFrameCache::getInstance()->getSpriteFrameByName("fireball1.png")->getRect();
	Rect thunderBall = SpriteFrameCache::getInstance()->getSpriteFrameByName("thunderball.png")->getRect();
};

struct G_d
{
	Size winSize = Director::getInstance()->getWinSize();
	float bloodPercentDropSpeed = 2;

	struct activearea
	{
		int left = -2800;
		int right = 1000;
		int bottom = 100;
		int top = 700;
	}activearea;
};

struct BGM_RES_d
{
	std::string MAINMENUBGM = "audios/01 Beast Hunt.mp3";
	std::string MAINMENUSTART = "audios/effects/magical_3.mp3";
	std::string BATTLEFIELDBGM = "audios/The_Last_Encounter_Short_Loop.mp3";
	std::string CHOOSEROLESCENEBGM = "audios/Imminent Threat Beat B FULL Loop.mp3";
};

struct AUDIO_ID_d
{
	int MAINMENUBGM;
	int BATTLEFIELDBGM;
	int CHOOSEROLECHAPTERBGM;
	int KNIGHTNORMALATTACK;
	int KNIGHTSPECIALATTACK;
	int ARCHERATTACK;
};

struct ActorCommonValues_d
{
	float _aliveTime = 0,
		_curSpeed = 0;
	Animation * _curAnimation = NULL;
	Animation3D* _curAnimation3d = NULL;


	float _curFacing = 0;
	bool _isalive = true;
	float _AITimer = 0;
	bool _AIEnabled = false;
	float _attackTimer = 0;
	float _timeKnocked = 0;
	bool _cooldown = false;
	float _hp = 1000;
	bool _goRight = true;

	float _targetFacing = 0;

	Actor *_target = NULL;

	Vec2 _myPos = ccp(0, 0);

	float _angry = 0;
	float _angryMax = 500;
};

struct ActorDefaultValues_d
{
	enum EnumRaceType _racetype = HERO;
	//_statetype = nil;
	//_sprite3d = nil;

	float _radius = 50;
	float _mass = 100;
	float _shadowSize = 70;


	float _maxhp = 1000;
	float _defense = 100;
	float _specialAttackChance = 0;
	float _recoverTime = 0.8;

	float _speed = 500;
	float _turnSpeed = DEGREES_TO_RADIANS(225);
	float _acceleration = 750;
	float _decceleration = 750 * 1.7;

	float _AIFrequency = 1.0;
	float _attackFrequency = 0.01;
	float _searchDistance = 5000;

	float _attackRange = 100;

	struct _normalAttack
	{
		float minRange = 0;
		float maxRange = 130;
		float angle = DEGREES_TO_RADIANS(30);
		float knock = 50;
		float damage = 800;
		enum EnumRaceType mask = HERO;
		float duration = 0;
		float speed = 0;
		float criticalChance = 0;
	}_normalAttack;
};

struct KnightValues_d
{
	enum EnumRaceType _racetype = HERO;
	std::string _name = "Knight";
	float _radius = 50;
	float _mass = 1000;
	float _shadowSize = 70;

	float _hp = 1850;
	float _maxhp = 1850;
	float _defense = 180;
	float _attackFrequency = 2.2;
	float _recoverTime = 0.4;
	float _AIFrequency = 1.1;
	float _attackRange = 140;
	float _specialAttackChance = 0;
	float _specialSlowTime = 1;

	struct _normalAttack
	{
		float minRange = 0;
		float maxRange = 130;
		float angle = DEGREES_TO_RADIANS(70);
		float knock = 60;
		float damage = 250;
		int mask = EnumRaceType::HERO;
		float duration = 0;
		float speed = 0;
		float criticalChance = 0.15;
	}_normalAttack;

	struct _specialAttack
	{
		float minRange = 0;
		float maxRange = 250;
		float angle = DEGREES_TO_RADIANS(160);
		float knock = 150;
		float damage = 350;
		int mask = EnumRaceType::HERO;
		float duration = 0;
		float speed = 0;
		float criticalChance = 0.35;
	}_specialAttack;

};

struct MageValues_d
{
	enum EnumRaceType _racetype = HERO;
	std::string _name = "Mage";
	float _radius = 50;
	float _mass = 800;
	float _shadowSize = 70;

	float _hp = 1100;
	float _maxhp = 1100;
	float _defense = 120;
	float _attackFrequency = 2.67;
	float _recoverTime = 0.8;
	float _AIFrequency = 1.33;
	float _attackRange = 400;
	float _specialAttackChance = 0;
	float _specialSlowTime = 0.67;

	struct _normalAttack
	{
		float minRange = 0;
		float maxRange = 50;
		float angle = DEGREES_TO_RADIANS(360);
		float knock = 10;
		float damage = 280;
		int mask = EnumRaceType::HERO;
		float duration = 2;
		float speed = 400;
		float criticalChance = 0.05;
	}_normalAttack;

	struct _specialAttack
	{
		float minRange = 0;
		float maxRange = 140;
		float angle = DEGREES_TO_RADIANS(360);
		float knock = 75;
		float damage = 250;
		int mask = EnumRaceType::HERO;
		float duration = 4.5;
		float speed = 0;
		float criticalChance = 0.05;
		float DOTTimer = 0.75;
		float curDOTTime = 0.75;
		bool DOTApplied = false;
	}_specialAttack;

};

struct ArcherValues_d
{
	enum EnumRaceType _racetype = HERO;
	std::string _name = "Archer";
	float _radius = 50;
	float _mass = 800;
	float _shadowSize = 70;

	float _hp = 1200;
	float _maxhp = 1200;
	float _defense = 130;
	float _attackFrequency = 2.5;
	float _recoverTime = 0.4;
	float _AIFrequency = 1.3;
	float _attackRange = 450;
	float _specialAttackChance = 0;
	float _specialSlowTime = 0.5;
	float _turnSpeed = DEGREES_TO_RADIANS(360);

	struct _normalAttack
	{
		float minRange = 0;
		float maxRange = 30;
		float angle = DEGREES_TO_RADIANS(360);
		float knock = 100;
		float damage = 200;
		int mask = EnumRaceType::HERO;
		float duration = 1.3;
		float speed = 900;
		float criticalChance = 0.33;
	}_normalAttack;

	struct _specialAttack
	{
		float minRange = 0;
		float maxRange = 75;
		float angle = DEGREES_TO_RADIANS(360);
		float knock = 100;
		float damage = 200;
		int mask = EnumRaceType::HERO;
		float duration = 1.5;
		float speed = 850;
		float criticalChance = 0.5;
		float DOTTimer = 0.3;
		float curDOTTime = 0.3;
		bool DOTApplied = false;
	}_specialAttack;

};

struct DragonValues_d
{
	enum EnumRaceType _racetype = MONSTER;
	std::string _name = "Dragon";
	float _radius = 50;
	float _mass = 100;
	float _shadowSize = 70;

	float _hp = 600;
	float _maxhp = 600;
	float _defense = 130;
	float _attackFrequency = 5.2;
	float _recoverTime = 0.8;
	float _AIFrequency = 1.337;
	float _attackRange = 350;

	float _speed = 300;
	float _acceleration = 250;
	float _decceleration = 750 * 1.7;
	float _turnSpeed = DEGREES_TO_RADIANS(180);

	struct _normalAttack
	{
		float minRange = 0;
		float maxRange = 40;
		float angle = DEGREES_TO_RADIANS(360);
		float knock = 50;
		float damage = 400;
		enum EnumRaceType mask = HERO;
		float duration = 1;
		float speed = 350;
		float criticalChance = 0.15;
	}_normalAttack;

};

struct SlimeValues_d
{
	enum EnumRaceType _racetype = MONSTER;
	std::string _name = "Slime";
	float _radius = 35;
	float _mass = 20;
	float _shadowSize = 45;

	float _hp = 300;
	float _maxhp = 300;
	float _defense = 65;
	float _attackFrequency = 1.5;
	float _recoverTime = 0.7;
	float _AIFrequency = 3.3;
	float _AITimer = 2.0;
	float _attackRange = 50;

	float _speed = 150;
	float _acceleration = 9999;
	float _decceleration = 9999;

	struct _normalAttack
	{
		float minRange = 0;
		float maxRange = 50;
		float angle = DEGREES_TO_RADIANS(360);
		float knock = 0;
		float damage = 135;
		enum EnumRaceType mask = MONSTER;
		float duration = 0;
		float speed = 0;
		float criticalChance = 0.13;
	}_normalAttack;

};

struct PigletValues_d
{
	enum EnumRaceType _racetype = MONSTER;
	std::string _name = "Piglet";
	float _radius = 50;
	float _mass = 69;
	float _shadowSize = 60;

	float _hp = 400;
	float _maxhp = 400;
	float _defense = 65;
	float _attackFrequency = 4.73;
	float _recoverTime = 0.9;
	float _AIFrequency = 2.3;
	float _attackRange = 120;

	float _speed = 350;
	float _turnSpeed = DEGREES_TO_RADIANS(270);

	struct _normalAttack
	{
		float minRange = 0;
		float maxRange = 120;
		float angle = DEGREES_TO_RADIANS(50);
		float knock = 0;
		float damage = 150;
		int mask = EnumRaceType::MONSTER;
		float duration = 0;
		float speed = 0;
		float criticalChance = 0.15;
	}_normalAttack;

};

struct RatValues_d
{
	enum EnumRaceType _racetype = MONSTER;
	std::string _name = "Rat";
	float _radius = 70;
	float _mass = 990;
	float _shadowSize = 90;

	float _hp = 2800;
	float _maxhp = 2800;
	float _defense = 200;
	float _attackFrequency = 3.0;
	float _recoverTime = 0.4;
	float _AIFrequency = 5.3;
	float _attackRange = 150;

	float _speed = 400;
	float _turnSpeed = DEGREES_TO_RADIANS(180);
	float _acceleration = 200;
	float _decceleration = 750 * 17;

	struct _normalAttack
	{
		float minRange = 0;
		float maxRange = 150;
		float angle = DEGREES_TO_RADIANS(100);
		float knock = 250;
		float damage = 210;
		int mask = EnumRaceType::MONSTER;
		float duration = 0;
		float speed = 0;
		float criticalChance = 1;
	}_normalAttack;

};

struct BossValues_d
{
	enum EnumRaceType _racetype = MONSTER;
	std::string _name = "Boss";
	float _radius = 50;
	float _mass = 100;
	float _shadowSize = 65;

	float _hp = 400;
	float _maxhp = 450;
	float _defense = 170;
	float _attackFrequency = 3.7;
	float _recoverTime = 0.4;
	float _AIFrequency = 5.3;
	float _attackRange = 110;
	float _acceleration = 450;
	float _decceleration = 750 * 1.7;
	float _turnSpeed = DEGREES_TO_RADIANS(255);
	float _speed = 300;
	float _AITimer = 5.0;

	struct _normalAttack
	{
		float minRange = 0;
		float maxRange = 110;
		float angle = DEGREES_TO_RADIANS(100);
		float knock = 50;
		float damage = 200;
		enum EnumRaceType mask = MONSTER;
		float duration = 0;
		float speed = 0;
		float criticalChance = 0.15;
	}_normalAttack;

	struct nova
	{
		float minRange = 0;
		float maxRange = 250;
		float angle = DEGREES_TO_RADIANS(360);
		float knock = 120;
		float damage = 250;
		enum EnumRaceType mask = HERO;
		float duration = 0.5;
		float speed = 0;
		float criticalChance = 0.15;
		float DOTTimer = 0.3;
		float curDOTTime = 0.3;
		bool DOTApplied = false;
	}nova;

};

struct CommonAudios_d
{
	std::string hit = "audios/effects/hit20.mp3";
};

struct MonsterSlimeValues_d
{
	std::string fileNameNormal = "model/slime/slimeAnger.c3b";
	std::string fileNameAnger = "model/slime/slimeAnger.c3b";
};

struct MonsterDragonValues_d
{
	std::string fileName = "model/dragon/dragon.c3b";
	std::string attack = "audios/effects/dragon/Fire.mp3";
	std::string fireHit = "audios/effects/dragon/fireHit.mp3";
	std::string wounded = "audios/effects/dragon/hurt.mp3";
	std::string dead = "audios/effects/dragon/dead.mp3";
};

struct MonsterRatValues_d
{
	std::string fileName = "model/rat/rat.c3b";
	std::string attack = "audios/effects/rat/attack.mp3";
	std::string dead = "aduios/effects/rat/dead.mp3";
	std::string wounded = "audios/effects/rat/ratHurt.mp3";
};

struct MonsterPigletValues_d
{
	std::string fileName = "model/piglet/piglet.c3b";
	std::string attack1 = "audios/effects/piglet/piglet1.mp3";
	std::string attack2 = "audios/effects/piglet/piglet2.mp3";
	std::string attack3 = "audios/effects/piglet/piglet3.mp3";
	std::string dead = "audios/effects/piglet/dead.mp3";
	std::string hurt = "audios/effects/piglet/hurt.mp3";
};

struct WarriorProperty_d
{
	std::string normalAttack1 = "audios/effects/knight/swish-1.mp3";
	std::string normalAttack2 = "audios/effects/knight/swish-2.mp3";
	std::string	specialAttack1 = "audios/effects/knight/swish-3.mp3";
	std::string	specialAttack2 = "audios/effects/knight/swish-4.mp3";
	std::string	kickit = "audios/effects/knight/kickit.mp3";
	std::string	normalAttackShout = "audios/effects/knight/normalAttackShout.mp3";
	std::string	specialAttackShout = "audios/effects/knight/specialAttackShout.mp3";
	std::string	wounded = "audios/effects/knight/wounded.mp3";
	std::string	dead = "audios/effects/knight/dead.mp3";
};

struct Archerproperty_d
{
	std::string attack1 = "audios/effects/archer/swish-3.mp3";
	std::string attack2 = "audios/effects/archer/swish-4.mp3";
	std::string iwillfight = "audios/effects/archer/iwillfight.mp3";
	std::string wounded = "audios/effects/archer/hurt.mp3";
	std::string normalAttackShout = "audios/effects/archer/normalAttackShout.mp3";
	std::string specialAttackShout = "audios/effects/archer/specialAttackShout.mp3";
	std::string dead = "audios/effects/archer/dead.mp3";
};

struct MageProperty_d
{
	float blood = 1000;
	float attack = 100;
	float defense = 100;
	float speed = 50;
	float special_attack_chance = 0.33;
	std::string letstrade = "audios/effects/mage/letstrade.mp3";
	std::string ice_normal = "audios/effects/mage/ice_1.mp3";
	std::string ice_special = "audios/effects/mage/ice_2.mp3";
	std::string ice_normalAttackHit = "audios/effects/mage/ice_3.mp3";
	std::string ice_specialAttackHit = "audios/effects/mage/ice_4.mp3";
	std::string specialAttackShout = "audios/effects/mage/specialAttack.mp3";
	std::string normalAttackShout = "audios/effects/mage/normalAttack.mp3";
	std::string wounded = "audios/effects/mage/hurt.mp3";
	std::string dead = "audios/effects/mage/dead.mp3";

};

struct ReSkin_d
{
	struct knight
	{
		float weapon = 0;
		float armour = 0;
		float helmet = 0;
	}knight;

	struct archer
	{
		float weapon = 0;
		float armour = 0;
		float helmet = 0;
	}archer;

	struct mage
	{
		float weapon = 0;
		float armour = 0;
		float helmet = 0;
	}mage;
};
