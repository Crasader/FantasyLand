#include "Actor.h"

bool Actor::init() 
{

};

void Actor::addEffect(Sprite3D* effect)
{

};

void Actor::initPuff()
{

};

void Actor::initShadow()
{

};

void Actor::playAnimation(std::string name, bool loop) 
{

};

//getter & setter
EnumRaceType Actor::getRaceType()
{

};

void Actor::setRaceType(EnumRaceType type)
{

};

EnumStateType Actor::getStateType()
{

};

void Actor::setStateType(EnumStateType type)
{

};

void Actor::setTarget(Actor* target)
{

};

void Actor::setFacing(float degrees)
{

};

bool Actor::getAIEnabled()
{

};

void Actor::setAIEnabled(bool enable)
{

};

int Actor::hurt(BasicCollider* collider, bool dirKnockMode)
{

};

void Actor::hurtSoundEffects()
{

};

void Actor::normalAttackSoundEffects()
{

};

void Actor::specialAttackSoundEffects()
{

};

void Actor::playDyingEffects()
{

};


//attacking collision check
void Actor::normalAttack()
{

};

void Actor::specialAttack()
{

};


//State Machine switching functions
void Actor::idleMode()
{

};

void Actor::walkMode()
{

};

void Actor::attackMode()
{

};

void Actor::knockMode(Actor* collider, bool dirKnockMode)
{

};

void Actor::dyingMode(Actor* knockSource, int knockAmount)
{

};


//Base Update Functions
void Actor::stateMachineUpdate(float dt)
{

};

Actor* Actor::_findEnemy(EnumRaceType HeroOrMonster, bool &allDead)
{

};

bool Actor::_inRange() 
{

};


//AI function does not run every tick
void Actor::AI()
{

};

void Actor::baseUpdate(float dt)
{

};

void Actor::knockingUpdate(float dt)
{

};

void Actor::attackUpdate(float dt)
{

};

void Actor::walkUpdate(float dt) 
{

};

void Actor::movementUpdate(float dt)
{

};
