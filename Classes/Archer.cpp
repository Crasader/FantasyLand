#include "Archer.h"


Archer::Archer()
{

};

bool Archer::init()
{

};

void Archer::update(float dt)
{

};

Sprite3D* Archer::createArrow()
{

};

void Archer::ArcherlAttackCallback(int audioID, std::string filePath)
{

};

void Archer::playDyingEffects()
{

};

void Archer::hurtSoundEffects()
{

};

void Archer::normalAttack()
{

};

void Archer::specialAttack()
{

};

void Archer::init3D()
{

};

void Archer::initActions()
{

};

//set default equipments
void Archer::setDefaultEqt()
{

};

void Archer::updataWeapon()
{

};

void Archer::updateHelmet()
{

};

void Archer::updateArmour()
{

};

//switth weapon
void Archer::switchWeapon()
{

};

//switch helmet
void Archer::switchHelmet()
{

};

//switch armour
void Archer::switchArmour()
{

};

//show/hide arrow
//isShow: true : Show false : Hide
//type: 0 : show / hide all 1 : show / hide 1 2 : show / hide 2
void Archer::showOrHideArrow(bool isShow, int arrowType)
{

};

//get weapon id
int Archer::getWeaponID()
{

};

//get armour id
int Archer::getArmourID()
{

};

//get helmet id
int Archer::getHelmetID()
{

};

int Archer::hurt(Actor* collider, bool dirKnockMode)
{

};
