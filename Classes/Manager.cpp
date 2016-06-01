#include "Manager.h"

std::vector<Actor *> HeroPool ;
std::vector<Actor *> DragonPool ;
std::vector<Actor *> SlimePool;
std::vector<Actor *> RatPool;
std::vector<Actor *> BossPool;
std::vector<Actor *> PigletPool;

std::vector<Actor *> HeroManager;
std::vector<Actor *> MonsterManager;


Size size = Director::getInstance()->getWinSize();
Scheduler* scheduler = Director::getInstance()->getScheduler();

void collision(Actor* object)
{
	for (int var = 0; var < HeroManager.size(); var++)
	{
		auto sprite = HeroManager[var];
		if (sprite->isAlive() && sprite != object)
			solveCollision(sprite,object);
	}

	for (int var = 0; var < MonsterManager; var++)
	{
		auto sprite = MonsterManager[var];
		if (sprite->isAlive() && sprite != object)
			solveCollision(sprite,object);
	}
}

void isOutOfBound(Actor* object)
{
	auto currentPos = ccp(object->getPositionX(),object->getPositionY());

	if(currentPos.x < G.activera.left)
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
	for (int val = HeroManager.size(); val >= 0; val--)
	{
		auto sprite = HeroManager[val];
		if(sprite->isAlive())
		{
			collision(sprite);
			isOutOfBound(sprite);
			(sprite->getMyPos());
		}
	}
	//for val = HeroManager.last, HeroManager.first, -1 do
	//	local sprite = HeroManager[val]
	//	if sprite._isalive == true then
	//		collision(sprite)
	//		isOutOfBound(sprite)
	//		sprite._effectNode:setPosition(sprite._myPos)
	//	else
	//		List.remove(HeroManager, val)
	//	end
	//end

	//for val = MonsterManager.last, MonsterManager.first, -1 do
	//	local sprite = MonsterManager[val]
	//	if sprite._isalive == true then
	//		collision(sprite)
	//		isOutOfBound(sprite)
	//	else
	//		List.remove(MonsterManager, val)
	//	end
	//end
}

Vec2 getFocusPointOfHeros()
{
	Vec2 ptFocus;
	ptFocus.x = 0;
	ptFocus.y = 0;

	for (int var = HeroManager.size(); var > -1; var-- )
	{
		ptFocus.x = ptFocus.x + HeroManager[var]->getPositionX();
		ptFocus.y = ptFocus.y + HeroManager[var]->getPositionY();
	}
	ptFocus.x = ptFocus.x / HeroManager.size();
	ptFocus.y = ptFocus.y / HeroManager.size();
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
