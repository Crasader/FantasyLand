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

Vec2 getFocusPointOfHeros()
{
	Vec2 ptFoucs;
	ptFoucs.x = 0;
	ptFoucs.y = 0;

	/*local ptFocus = { x = 0, y = 0 }
	for var = HeroManager.last, HeroManager.first, -1 do
		ptFocus.x = ptFocus.x + HeroManager[var]:getPositionX()
		ptFocus.y = ptFocus.y + HeroManager[var] : getPositionY()
	end
	ptFocus.x = ptFocus.x / List.getSize(HeroManager)
	ptFocus.y = ptFocus.y / List.getSize(HeroManager)
	return ptFocus*/
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
