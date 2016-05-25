#include "Manager.h"


std::list<std::string> HeroPool ;
std::list<std::string> DragonPool ;
std::list<std::string> SlimePool;
std::list<std::string> RatPool;
std::list<std::string> BossPool;
std::list<std::string> HeroManager;
std::list<std::string> MonsterManager;

Size size = Director::getInstance()->getWinSize();
Scheduler* scheduler = Director::getInstance()->getScheduler();

void solveCollision(/*object1, object2*/);
void collision(/*object*/);
void isOutOfBound(/*object*/);
void collisionDetect(float dt);
Vec2 getFocusPointOfHeros();