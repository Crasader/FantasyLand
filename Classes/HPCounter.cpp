#include "HPCounter.h"
#include "GlobalVariables.h"
#include "Actor.h"

bool HPCounter::init()
{
	Layer::init();
	_isBlooding = false;
	_num = 0;
	return true;
}

Label *HPCounter::showBloodLossNum(float dmage, Actor *racetype, bool atack)
{
	auto time = 1;
	auto getRandomXYZ = [time]()
	{
		auto rand_x = 20 * sin(rand_0_1()*(time*0.5 + 4356));
		auto rand_y = 20 * sin(rand_0_1()*(time*0.37 + 5436));
		auto rand_z = 20 * sin(rand_0_1()*(time*0.2 + 54325));
		return Vec3(rand_x, rand_y, rand_z);
	};

	auto getBlood = [this, getRandomXYZ, racetype, atack]()
	{
		num = _num;
		this->tm = 0.5f;
		pointZ = 50;


		TTFConfig ttfconfig;
		ttfconfig.outlineSize = 7;
		ttfconfig.fontSize = 50;
		ttfconfig.fontFilePath = "fonts/britanic bold.ttf";
		auto blood = Label::createWithTTF(ttfconfig, "-" + std::to_string(num), TextHAlignment::CENTER, 400);
		blood->enableOutline(Color4B(0, 0, 0, 255));
		blood->setRotation3D(Vec3(90, 0, 0));
		blood->setScale(0.1);
		//blood->setRotation3D(getRandomXYZ());

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

		if (racetype->getRaceType() != EnumRaceType::MONSTER)
			blood->setColor(Color3B(0, 180, 255));

		auto getAction = [this]()
		{
			auto sequence = Sequence::create(
				EaseElasticOut::create(ScaleTo::create(tm / 2, targetScale), 0.4),
				FadeOut::create(tm / 2),
				RemoveSelf::create(),
				CallFunc::create([this]()
			{
				_isBlooding = false;
				_num = 0;
			}), 
				NULL
				);

			auto spawn = Spawn::create(
				sequence,
				MoveBy::create(tm, Vec3(0, 0, pointZ)),
				RotateBy::create(tm, rand_0_1() * 80 - 40), 
				NULL);
			return spawn;
		};

		if (atack)
		{
			auto critleAttack = Sprite::createWithSpriteFrameName("hpcounter.png");
			this->tm = 1;
			critleAttack->runAction(getAction());
			critleAttack->setRotation3D(Vec3(90, 0, 0));
			if (racetype->getname() == "Rat")
				critleAttack->setPositionZ(G.winSize.height*0.25);
			racetype->addEffect(critleAttack);
			_cirtleAttack = critleAttack;
			pointZ = 80;
			targetScale = targetScale * 2;
		}

		_blood = blood;
		_blood->runAction(getAction());

		return _blood;
	};

	if (_isBlooding == false)
	{
		_isBlooding = true;
		_num = dmage;
	}
	else
	{
		_blood->stopAllActions();
		_blood->removeFromParent();
		_num = _num + dmage;
	}

	return getBlood();
}