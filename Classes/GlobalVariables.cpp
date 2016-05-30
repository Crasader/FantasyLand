#include "GlobalVariables.h"
#include "cocos2d.h"
#include "Helper.h"
USING_NS_CC;

float FXZorder = 1999;
float CelLine = 0.009;
std::string BossTaunt = "How dare you???";

AnimationCache * animationCache = AnimationCache::getInstance();

void init()
{
	Animation * hurtAnimation = Animation::create();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FX/FX.plist");
	hurtAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hit1.png"));
	hurtAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hit2.png"));
	hurtAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hit3.png"));
	hurtAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hit4.png"));
	hurtAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hit5.png"));
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("battlefieldUI/battleFieldUI.plist");
	hurtAnimation->setDelayPerUnit(0.1);
	animationCache->addAnimation(hurtAnimation, "hurtAnimation");

	Animation* fireBallAnim = Animation::create();
	fireBallAnim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireball2.png"));
	fireBallAnim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireball3.png"));
	fireBallAnim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireball4.png"));
	fireBallAnim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireball5.png"));
	fireBallAnim->setDelayPerUnit(0.1);
	animationCache->addAnimation(fireBallAnim, "fireBallAnim");
}

struct RECTS
{
	Rect iceBolt = SpriteFrameCache::getInstance()->getSpriteFrameByName("icebolt.png")->getRect();
	Rect iceSpike = SpriteFrameCache::getInstance()->getSpriteFrameByName("iceSpike1.png")->getRect();
	Rect fireBall = SpriteFrameCache::getInstance()->getSpriteFrameByName("fireball1.png")->getRect();
	Rect thunderBall = SpriteFrameCache::getInstance()->getSpriteFrameByName("thunderball.png")->getRect();
}RECTS;


struct G
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
}G;

struct BGM_RES
{
	std::string MAINMENUBGM = "audios/01 Beast Hunt.mp3";
	std::string MAINMENUSTART = "audios/effects/magical_3.mp3";
	std::string BATTLEFIELDBGM = "audios/The_Last_Encounter_Short_Loop.mp3";
	std::string CHOOSEROLESCENEBGM = "audios/Imminent Threat Beat B FULL Loop.mp3";
}BGM_RES;

enum AUDIO_ID
{
	MAINMENUBGM,
	BATTLEFIELDBGM,
	CHOOSEROLECHAPTERBGM,
	KNIGHTNORMALATTACK,
	KNIGHTSPECIALATTACK,
	ARCHERATTACK
}AUDIO_ID; 

//EnumRaceType =
//{
//	"HERO",  --only this
//	"MONSTER", --and this
//}
//EnumRaceType = CreateEnumTable(EnumRaceType)
//EnumStateType =
//{
//	"IDLE",
//	"WALKING",
//	"ATTACKING",
//	"DEFENDING",
//	"KNOCKING",
//	"DYING",
//	"DEAD"
//}
//EnumStateType = CreateEnumTable(EnumStateType)

struct ActorCommonValues
{
	float _aliveTime = 0,
	_curSpeed = 0;
	/*_curAnimation = nil;
	_curAnimation3d = nil;*/

		
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

	//_target = nil,

	Vec2 _myPos = ccp(0, 0);

	float _angry = 0;
	float _angryMax = 500;
}ActorCommonValues;

struct ActorDefaultValues 
{
	//_racetype = EnumRaceType.HERO;
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
		//mask = EnumRaceType.HERO
		float duration = 0;
		float speed = 0; 
		float criticalChance = 0;
	}_normalAttack;
}ActorDefaultValues;


struct KnightValues 
{
	//_racetype = EnumRaceType.HERO,
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
		//float mask = EnumRaceType.HERO,
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
		//mask = EnumRaceType.HERO;
		float duration = 0;
		float speed = 0;
		float criticalChance = 0.35;
	}_specialAttack;

}KnightValues;

struct MageValues
{
	//_racetype = EnumRaceType.HERO,
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
		//mask = EnumRaceType.HERO,
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
			//mask = EnumRaceType.HERO,
		float duration = 4.5;
		float speed = 0;
		float criticalChance = 0.05;
		float DOTTimer = 0.75;
		float curDOTTime = 0.75;
		bool DOTApplied = false;
	}_specialAttack;

}MageValues;


struct ArcherValues
{
	//_racetype = EnumRaceType.HERO,
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
		//mask = EnumRaceType.HERO,
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
		//mask = EnumRaceType.HERO,
		float duration = 1.5;
		float speed = 850;
		float criticalChance = 0.5;
		float DOTTimer = 0.3;
		float curDOTTime = 0.3;
		bool DOTApplied = false;
	}_specialAttack;

}ArcherValues;


struct DragonValues
{
	//_racetype = EnumRaceType.MONSTER,
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
	float _decceleration = 750*1.7;
	float _turnSpeed = DEGREES_TO_RADIANS(180);

	struct _normalAttack
	{
		float minRange = 0;
		float maxRange = 40;
		float angle = DEGREES_TO_RADIANS(360);
		float knock = 50;
		float damage = 400;
		//mask = EnumRaceType.HERO,
		float duration = 1;
		float speed = 350;
		float criticalChance = 0.15;
	}_normalAttack;

}DragonValues;


struct SlimeValues
{
	//_racetype = EnumRaceType.MONSTER,
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
		//mask = EnumRaceType.Monster,
		float duration = 0;
		float speed = 0;
		float criticalChance = 0.13;
	}_normalAttack;

}SlimeVaules;

struct PigletValues
{
	//_racetype = EnumRaceType.MONSTER,
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
		//mask = EnumRaceType.Monster,
		float duration = 0;
		float speed = 0;
		float criticalChance = 0.15;
	}_normalAttack;

}PigletVaules;


struct RatValues
{
	//_racetype = EnumRaceType.MONSTER,
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
		//mask = EnumRaceType.Monster,
		float duration = 0;
		float speed = 0;
		float criticalChance = 1;
	}_normalAttack;

}RatVaules;


struct BossValues
{
	//_racetype = EnumRaceType.HERO,
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
	float _decceleration = 750*1.7;
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
		//mask = EnumRaceType.MONSTER,
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
		//mask = EnumRaceType.HERO,
		float duration = 0.5;
		float speed = 0;
		float criticalChance = 0.15;
		float DOTTimer = 0.3;
		float curDOTTime = 0.3;
		bool DOTApplied = false;
	}nova;

}BossValues;

struct CommonAudios 
{
	std::string hit = "audios/effects/hit20.mp3";
}CommonAudios;

struct MonsterSlimeValues
{
	std::string fileNameNormal = "model/slime/slimeAnger.c3b";
	std::string fileNameAnger = "model/slime/slimeAnger.c3b";
}MonsterSlimeValues;


struct MonsterDragonValues
{
	std::string fileName = "model/dragon/dragon.c3b";
	std::string attack = "audios/effects/dragon/Fire.mp3";
	std::string fireHit = "audios/effects/dragon/fireHit.mp3";
	std::string wounded = "audios/effects/dragon/hurt.mp3";
	std::string dead = "audios/effects/dragon/dead.mp3";
}MonsterDragonValues;


struct MonsterRatValues 
{
	std::string fileName = "model/rat/rat.c3b";
	std::string attack = "audios/effects/rat/attack.mp3";
	std::string dead = "aduios/effects/rat/dead.mp3";
	std::string wounded = "audios/effects/rat/ratHurt.mp3";
}MonsterRatValues;


struct MonsterPigletValues
{
	std::string fileName = "model/piglet/piglet.c3b";
	std::string attack1 = "audios/effects/piglet/piglet1.mp3";
	std::string attack2 = "audios/effects/piglet/piglet2.mp3";
	std::string attack3 = "audios/effects/piglet/piglet3.mp3";
	std::string dead = "audios/effects/piglet/dead.mp3";
	std::string hurt = "audios/effects/piglet/hurt.mp3";
}MonsterPigletValues;


struct WarriorProperty
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
}WarriorProperty;


struct Archerproperty
{
	std::string attack1 = "audios/effects/archer/swish-3.mp3";
	std::string attack2 = "audios/effects/archer/swish-4.mp3";
	std::string iwillfight = "audios/effects/archer/iwillfight.mp3";
	std::string wounded = "audios/effects/archer/hurt.mp3";
	std::string normalAttackShout = "audios/effects/archer/normalAttackShout.mp3";
	std::string specialAttackShout = "audios/effects/archer/specialAttackShout.mp3";
	std::string dead = "audios/effects/archer/dead.mp3";
}Archerproperty;

struct MageProperty
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

}MageProperty;


struct ReSkin 
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