#include "GlobalVariables.h"
#include "GameMaster.h"

Layer * currentLayer;
//GameMaster *gameMaster;
class BattleFieldUI *uiLayer;

float FXZorder = 1999;
float CelLine = 0.009;
std::string BossTaunt = "How dare you???";
Size VisibleSize;
float resolutionRate; 
AnimationCache *animationCache;

struct RECTS_d RECTS;
struct G_d G;
struct BGM_RES_d BGM_RES;
struct AUDIO_ID_d AUDIO_ID;
struct ActorCommonValues_d ActorCommonValues;
struct ActorDefaultValues_d ActorDefaultValues;
struct KnightValues_d KnightValues;
struct MageValues_d MageValues;
struct ArcherValues_d ArcherValues;
struct DragonValues_d DragonValues;
struct SlimeValues_d SlimeVaules;
struct PigletValues_d PigletVaules;
struct RatValues_d RatVaules;
struct BossValues_d BossValues;
struct CommonAudios_d CommonAudios;
struct MonsterSlimeValues_d MonsterSlimeValues;
struct MonsterDragonValues_d MonsterDragonValues;
struct MonsterRatValues_d MonsterRatValues;
struct MonsterPigletValues_d MonsterPigletValues;
struct WarriorProperty_d WarriorProperty;
struct Archerproperty_d Archerproperty;
struct MageProperty_d MageProperty;
struct ReSkin_d ReSkin;



void init_globalvariables()
{
	camera = Camera::create();

	animationCache = AnimationCache::getInstance();
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

	RECTS.iceBolt = SpriteFrameCache::getInstance()->getSpriteFrameByName("icebolt.png")->getRect();
	RECTS.iceSpike = SpriteFrameCache::getInstance()->getSpriteFrameByName("iceSpike1.png")->getRect();
	RECTS.fireBall = SpriteFrameCache::getInstance()->getSpriteFrameByName("fireball1.png")->getRect();
	RECTS.thunderBall = SpriteFrameCache::getInstance()->getSpriteFrameByName("thunderball.png")->getRect();

	G.winSize = Director::getInstance()->getWinSize();

	VisibleSize = Director::getInstance()->getWinSize();
	resolutionRate = VisibleSize.width / VisibleSize.height;
	
}
