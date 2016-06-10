#include "Rat.h"

Rat::Rat()
{
	_AIEnabled = true;
	scheduleUpdateWithPriority(0.5);
}

bool Rat::init()
{
	//copyTable(ActorCommonValues, this);
	//copyTable(RatValues, this);
	init3D();
	initActions();
	return true;
}

void Rat::reset()
{
	//copyTable(ActorCommonValues, this);
	//copyTable(RatValues, this);
	walkMode();
	setPositionZ(0);
}

void Rat::update(float dt)
{
	baseUpdate(dt);
	stateMachineUpdate(dt);
	movementUpdate(dt);
}

void Rat::playDyingEffects()
{
	experimental::AudioEngine::play2d(MonsterRatValues.dead, false, 1);
}

void Rat::hurtSoundEffects()
{
	experimental::AudioEngine::play2d(MonsterRatValues.wounded, false, 1);
}

void Rat::normalAttackSoundEffects()
{
	experimental::AudioEngine::play2d(MonsterRatValues.attack, false, 1);
}

void Rat::init3D()
{
	initShadow();
	_sprite3d = Sprite3D::create(file);
	_sprite3d->setScale(20);
	//_sprite3d->addEffect(Vec3(0, 0, 0), CelLine, -1);
	addChild(_sprite3d);
	_sprite3d->setRotation3D(Vec3(90, 0, 0));
	_sprite3d->setRotation(-90);
}

void Rat::initActions()
{
	_action.insert("idle", createAnimation(file, 0, 23, 1));
	_action.insert("walk", createAnimation(file, 122, 142, 0.4));
	_action.insert("attack1", createAnimation(file, 81, 99, 0.7));
	_action.insert("attack2", createAnimation(file, 99, 117, 0.7));
	_action.insert("knocked", createAnimation(file, 30, 37, 0.5));
	_action.insert("dead", createAnimation(file, 41, 76, 0.2));
}

void Rat::dyingMode(Vec2 knockSource, int knockAmount)
{
	setStateType(EnumStateType::DYING);
	playAnimation("dead");
	playDyingEffects();

	std::vector<Actor*>::iterator it = std::find(MonsterManager.begin(), MonsterManager.end(), this);
	remove(HeroManager.begin(), HeroManager.end(), this);
	auto recycle = [&]() {
		removeFromParent();
		//if (gameMaster != NULL)
		//	gameMaster::showVictoryUI();
	};

	auto disableHeroAI = [&]() {
		if (HeroManager.size != 0) {
			for (auto var = HeroManager.begin(); var != HeroManager.end(); ++var) {
				//HeroManager(var)->setAIEnabled(false);
				//HeroManager(var)->idleMode();
				//HeroManager(var)->_goRight = false;
			}
		}
	};
	runAction(Sequence::create(DelayTime::create(3), CallFunc::create(disableHeroAI), MoveBy::create(1.0, Vec3(0, 0, -50)), CallFunc::create(recycle), NULL));
	
	if (knockAmount) {
		auto p = _myPos;
		auto angle = ccpToAngle(ccpSub(p, knockSource));
		auto newPos = ccpRotateByAngle(ccpAdd(Vec2(knockAmount, 0), p), p, angle);
		runAction(EaseCubicActionOut::create(MoveTo::create(_action.at("knocked")->getDuration() * 3, newPos)));
	}
	_AIEnabled = false;
}

int Rat::hurt(BasicCollider* collider, bool dirKnockMode)
{
	if (_isalive == true) {
		//TODO add sound effect
		auto damage = collider->getDamage();
		//calculate the real damage
		bool critical = false;
		auto knock = collider->getKnock();
		if (CCRANDOM_0_1() < collider->getCriticalChance()) {
			damage *= 1.5;
			critical = true;
			knock *= 2;
		}
		damage = damage + damage * CCRANDOM_MINUS1_1() * 0.15 - _defense;
		damage = floor(damage);
		if (damage <= 0) damage = 1;
		_hp -= damage;
		if (_hp > 0) {
			if (critical == true) {
				knockMode(collider, dirKnockMode);
				hurtSoundEffects();
			}
			else hurtSoundEffects();
		}
		else {
			_hp = 0;
			_isalive = false;
			dyingMode(getPosTable(collider), knock);
		}

		//three param judge if crit

		/* 这里需要修改 */
		/*Sprite* blood = _hpCounter->showBloodLossNum(damage, this, critical);
		setPositionZ(Director::getInstance()->getVisibleSize().height * 0.25);
		addEffect(blood);*/
		return damage;
	}
	return 0;
}