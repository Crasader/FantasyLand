#include "HPCounter.h"

bool HPCounter::init()
{
	Layer::init();
	_isBlooding = false;
	_num = 0;
	return true;
}

void HPCounter::showBloodLossNum(float dmage, Actor *racetype, bool atack)
{
	if(atack)
	{
		auto critleAttack = Sprite::createWithSpriteFrameName("hpcounter.png");
		//tm=1;
		critleAttack->runAction(getAction(tm,targetScale,pointZ));
		critleAttack->setRotation3D(Vec3(90, 0, 0));
		if (racetype->getName() == "rat")
			critleAttack->setPosition3D(Vec3(90, 0, 0));
		racetype->addEffect(critleAttack);
		pointZ = 80;
		targetScale = targetScale * 2;
	}
	_blood=
}

Vec3 HPCounter::getRandomXYZ()
{
	int time = 1;
	auto rand_x = 20 * sin(rand_0_1()*(time*0.5 + 4356));
	auto rand_y = 20 * sin(rand_0_1()*(time*0.37 + 5436));
	auto rand_z = 20 * sin(rand_0_1()*(time*0.2 + 54325));
	return Vec3(rand_x, rand_y, rand_z);
}

LabelTTF *HPCounter::getBlood(Actor *racetype)
{
	num = _num;
	tm = 0.5f;
	pointZ = 50;

	//*$$$$$$$$$$$$$$$$$$$$*//
	auto blood = LabelTTF::create("fonts/britanic bold.ttf", "fonts/britanic bold.ttf", 50);
	blood->enableStroke(Color3B::BLACK, 7);
	blood->setRotation3D(Vec3(90, 0, 0));
	blood->setScale(0.1);
	blood->setRotation3D(getRandomXYZ());

	targetScale = 0.6;
	if (num > 1000)
		blood->setColor(Color3B(254, 58, 19));
	else if (num > 300)
	{
		targetScale = 0.45;
		blood->setColor(Color3B(255, 247, 153));
	}
	else
	{
		targetScale = 0.55;
		blood->setColor(Color3B(189, 0, 0));
	}

	//todo racetype
	if (racetype->getRaceType() == EnumRaceType::MONSTER)
		blood->setColor(Color3B(0, 180, 255));

	auto critleAttack = Sprite::createWithSpriteFrameName("hpcounter.png");
	//tm=1;
	critleAttack->runAction(getAction(tm, targetScale, pointZ));
	critleAttack->setRotation3D(Vec3(90, 0, 0));
	if (racetype->getName() == "rat")
		critleAttack->setPosition3D(Vec3(90, 0, 0));
	racetype->addEffect(critleAttack);
	pointZ = 80;
	targetScale = targetScale * 2;
}

Spawn *HPCounter::getAction(float tm, float targetScale, float pointZ)
{
	auto sequence = Sequence::create(
		EaseElasticOut::create(ScaleTo::create(tm / 2, targetScale), 0.4),
		FadeOut::create(tm / 2),
		RemoveSelf::create(),
		CallFunc::create(new std::function<double>)
		);

	auto spawn = Spawn::create(
		sequence,
		MoveBy::create(tm, Vec3(0, 0, pointZ)),
		RotateBy::create(tm, rand_0_1() * 80 - 40));
	return spawn;
}