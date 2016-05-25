#pragma once
#include "Helper.h"

extern std::list<std::string> HeroPool;
extern std::list<std::string> DragonPool;
extern std::list<std::string> SlimePool;
extern std::list<std::string> RatPool;
extern std::list<std::string> BossPool;
extern std::list<std::string> HeroManager;
extern std::list<std::string> MonsterManager;

extern Size size ;
extern Scheduler* scheduler;

void solveCollision(/*object1, object2*/);
void collision(/*object*/);
void isOutOfBound(/*object*/);
void collisionDetect(float dt);
Vec2 getFocusPointOfHeros();