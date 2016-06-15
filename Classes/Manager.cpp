#include "Manager.h"
#include "Actor.h"

std::vector<Actor *> HeroPool ;
std::vector<Actor *> DragonPool ;
std::vector<Actor *> SlimePool;
std::vector<Actor *> RatPool;
std::vector<Actor *> BossPool;
std::vector<Actor *> PigletPool;

std::vector<Actor *> HeroManager;
std::vector<Actor *> MonsterManager;

Scheduler* scheduler = Director::getInstance()->getScheduler();

void solveCollision(Actor* object1, Actor* object2)
{
	auto miniDistance = object1->getRadius() + object2->getRadius();
	auto obj1Pos = object1->getPosition();
	auto obj2Pos = object2->getPosition();
	auto tempDistance = ccpDistance(obj1Pos, obj2Pos);

	if( tempDistance < miniDistance )
	{
		auto angle = ccpToAngle(ccpSub(obj1Pos, obj2Pos));
		auto distance = miniDistance - tempDistance + 1;
		auto distance1 = (1 - object1->getMass() / (object1->getMass() + object2->getMass())) * distance;
		auto distance2 = distance - distance1;

		object1->setPosition(ccpRotateByAngle(ccpAdd(ccp(distance1, 0), obj1Pos), obj1Pos, angle));
		object2->setPosition(ccpRotateByAngle(ccpAdd(ccp(-distance2, 0), obj2Pos), obj2Pos, angle));
	}
}

void collision(Actor* object)
{
	for (int var = 0; var < HeroManager.size(); var++)
	{
		auto sprite = HeroManager[var];
		if (sprite->isAlive() && sprite != object)
		{
			solveCollision(sprite, object);
		}
	}

	for (int var = 0; var < MonsterManager.size(); var++)
	{
		auto sprite = MonsterManager[var];
		if (sprite->isAlive() && sprite != object)
			solveCollision(sprite,object);
	}
}

void isOutOfBound(Actor* object)
{
	auto currentPos = ccp(object->getPositionX(),object->getPositionY());

	if(currentPos.x < G.activearea.left)
	{
		currentPos.x = G.activearea.left;
	}

	if (currentPos.x > G.activearea.right)
	{
		currentPos.x = G.activearea.right;
	}
		
	if( currentPos.y <  G.activearea.bottom)
	{
		currentPos.y = G.activearea.bottom;
	}

	if(currentPos.y > G.activearea.top )
	{
		currentPos.y = G.activearea.top;
	}

	object->setPosition(currentPos);
}

void collisionDetect(float dt)
{
	
	for (int val = HeroManager.size()-1; val >= 0; val--)
	{
		auto sprite = HeroManager[val];
		if(sprite->isAlive())
		{
			collision(sprite);
			isOutOfBound(sprite);
			sprite->getEffectNode()->setPosition(sprite->getMyPos());
		}
		else
		{
			delete HeroManager[val];
			HeroManager.erase(HeroManager.begin() + val);
		}
	}
	
	for (int val = MonsterManager.size()-1; val >= 0; val--)
	{
		auto sprite = MonsterManager[val];
		if (sprite->isAlive())
		{
			collision(sprite);
			isOutOfBound(sprite);
		}
		else
		{
			delete MonsterManager[val];
			MonsterManager.erase(MonsterManager.begin() + val);
		}
	}

}

Vec2 getFocusPointOfHeros()
{
	Vec2 ptFocus;
	ptFocus.x = 0;
	ptFocus.y = 0;

	for (int var = HeroManager.size()-1; var > -1; var-- )
	{
		ptFocus.x += HeroManager[var]->getPositionX();
		ptFocus.y += HeroManager[var]->getPositionY();
	}
	ptFocus.x = ptFocus.x / HeroManager.size();
	ptFocus.y = ptFocus.y / HeroManager.size();
	return ptFocus;
}

std::vector<Actor *> getPoolByName(std::string name)
{
	if (name == "Piglet")
		return PigletPool;
	else if (name == "Slime")
		return SlimePool;
	else if (name == "Rat")
		return RatPool;
	else if (name == "Dragon")
		return DragonPool;
	else if (name == "Boss")
		return BossPool;
	else
		return HeroPool;
}
