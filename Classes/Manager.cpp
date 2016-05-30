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
