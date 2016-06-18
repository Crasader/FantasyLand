#pragma once
#include "Helper.h"
#include "AudioEngine.h"

class GameMaster;


void initGlobalVariables();
extern Layer *currentLayer;
extern class BattleFieldUI *uiLayer;

extern const float FXZorder;
extern AnimationCache *animationCache ;
extern float resolutionRate;
extern Size VisibleSize;

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


//attack collider info, it can be customized
//data for normal attack
struct attack_d{	float minRange;					float maxRange;					float angle;					float knock;					float damage;					enum EnumRaceType mask;			float duration;					float speed;					float criticalChance;	float DOTTimer;	float curDOTTime;	bool DOTApplied;};

enum EnumRaceType
{
	HERO, 
	MONSTER,
};

enum EnumStateType 
{
	IDLE,
	WALKING,
	ATTACKING,
	DEFENDING,
	KNOCKING,
	DYING,
	DEAD,
};

struct RECTS_d
{
	Rect iceBolt ;
	Rect iceSpike;
	Rect fireBall;
	Rect thunderBall;
};

struct G_d
{
	float bloodPercentDropSpeed = 2;

	struct activearea
	{
		int left = -2800;
		int right = 1000;
		int bottom = 100;
		int top = 700;
	}activearea;
};


//Audios
struct BGM_RES_d
{
	std::string MAINMENUBGM = "audios/01 Beast Hunt.mp3";
	std::string MAINMENUSTART = "audios/effects/magical_3.mp3";
	std::string BATTLEFIELDBGM = "audios/The_Last_Encounter_Short_Loop.mp3";
	std::string CHOOSEROLESCENEBGM = "audios/Imminent Threat Beat B FULL Loop.mp3";
};

//play2d id
struct AUDIO_ID_d
{
	int MAINMENUBGM;
	int BATTLEFIELDBGM;
	int CHOOSEROLECHAPTERBGM;
	int KNIGHTNORMALATTACK;
	int KNIGHTSPECIALATTACK;
	int ARCHERATTACK;
};

//common value is used to reset an actor
struct ActorCommonValues_d
{
	float _aliveTime = 0,                   //time the actor is alive in seconds
		_curSpeed = 0;                      //current speed the actor is traveling in units/seconds
	Animation * _curAnimation = NULL;       
	Animation3D* _curAnimation3d = NULL;

	//runtime modified values
	float _curFacing = 0;					//current direction the actor is facing, in radians, 0 is to the right
	bool _isalive = true;
	float _AITimer = 0;						//accumulated timer before AI will execute, in seconds
	bool _AIEnabled = false;				//if false, AI will not run
	float _attackTimer = 0;					//accumulated timer to decide when to attack, in seconds
	float _timeKnocked = 0;					//accumulated timer to recover from knock, in seconds
	bool _cooldown = false;					//if its true, then you are currently playing attacking animation,
	float _hp = 1000;						//current hit point
	bool _goRight = true;
	//target variables
	float _targetFacing = 0;				//direction the actor Wants to turn to

	Actor *_target = NULL;					//the enemy actor 

	Vec2 _myPos = ccp(0, 0);

	float _angry = 0;
	float _angryMax = 500;
};

struct ActorDefaultValues_d
{
	enum EnumRaceType _racetype = HERO;		//type of the actor
	enum EnumStateType _statetype ;			// AI state machine
	Sprite3D * _sprite3d = NULL;			//place to hold 3d model

	float _radius = 50;						//actor collider size
	float _mass = 100;						//weight of the role, it affects collision
	float _shadowSize = 70;					//the size of the shadow under the actor


	float _maxhp = 1000;
	float _defense = 100;
	float _specialAttackChance = 0;
	float _recoverTime = 0.8;				//time takes to recover from knock, in seconds

	float _speed = 500;						//actor maximum movement speed in units/seconds
	float _turnSpeed = DEGREES_TO_RADIANS(225);//actor turning speed in radians/seconds
	float _acceleration = 750;				//actor movement acceleration, in units/seconds
	float _decceleration = 750 * 1.7;		//actor movement decceleration, in units/seconds

	float _AIFrequency = 1.0;				//how often AI executes in seconds
	float _attackFrequency = 0.01;			//an attack move every few seconds
	float _searchDistance = 5000;			//distance which enemy can be found

	float _attackRange = 100;				//distance the actor will stop and commence attack

	struct attack_d _normalAttack = 
	{
		0 , 130 , DEGREES_TO_RADIANS(30),
		50 , 800 , HERO , 0 , 0 , 0
	};
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

	struct attack_d _normalAttack =
	{
		0 , 130 , DEGREES_TO_RADIANS(70) ,
		60 , 250 , HERO , 0 , 0 , 0.15f
	}; 

	struct attack_d _specialAttack =
	{
		0 , 250 , DEGREES_TO_RADIANS(160) ,
		150 , 350 , HERO , 0 , 0 , 0.35f
	};
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

	
	struct attack_d _normalAttack =
	{
		0 , 50 , DEGREES_TO_RADIANS(360) ,
		10 , 280 , HERO , 2 , 400 , 0.05f
	};

	struct attack_d _specialAttack =
	{
		0 , 140 , DEGREES_TO_RADIANS(360) ,
		75 , 250 , HERO , 4.5 , 0 , 0.05f,
		0.75f , 0.75f , false
	};
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

	struct attack_d _normalAttack =
	{
		0 , 30 , DEGREES_TO_RADIANS(360) ,
		100 , 200 , HERO , 1.3f , 900 , 0.33f
	};

	struct attack_d _specialAttack =
	{
		0 , 75 , DEGREES_TO_RADIANS(360) ,
		100 , 200 , HERO , 1.5f , 850 , 0.5f ,
		0.3f , 0.3f , false
	};
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

	struct attack_d _normalAttack =
	{
		0 , 40 , DEGREES_TO_RADIANS(360) ,
		50 , 400 , MONSTER , 1 , 350 , 0.15f
	};
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

	struct attack_d _normalAttack =
	{
		0 , 50 , DEGREES_TO_RADIANS(360) ,
		0 , 135 , MONSTER , 0 , 0 , 0.13f
	};
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

	struct attack_d _normalAttack =
	{
		0 , 120 , DEGREES_TO_RADIANS(50) ,
		0 , 150 , MONSTER , 0 , 0 , 0.15f
	};
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

	struct attack_d _normalAttack =
	{
		0 , 150 , DEGREES_TO_RADIANS(100) ,
		250 , 210 , MONSTER , 0 , 0 , 1
	};
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

	struct attack_d _normalAttack =
	{
		0 , 110 , DEGREES_TO_RADIANS(100) ,
		50 , 200 , MONSTER , 0 , 0 , 0.15f
	};

	struct attack_d nova =
	{
		0 , 250 , DEGREES_TO_RADIANS(360) ,
		120 , 250 , HERO , 0.5f , 0 , 0.15f ,
		0.3f , 0.3f , false
	};

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


struct MESSAGE_ANGRY_CHANGE
{
	std::string _name;
	float _angry;
	float _angryMax;
};

struct MESSAGE_BLOOD_MINUS
{
	std::string _name;
	float _maxhp;
	float _hp;
	ProgressTimer* _bloodBar;
	ProgressTimer* _bloodBarClone;
	Sprite* _avatar;
};

struct MESSAGE_SPECIAL_PERSPECTIVE
{
	float speed;
	Vec2 pos;
	float dur;
	Actor* target;
};

