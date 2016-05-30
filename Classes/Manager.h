#pragma once
#include "Helper.h"
#include "Actor.h"

//extern std::list<std::string> HeroPool;
//extern std::list<std::string> DragonPool;
//extern std::list<std::string> SlimePool;
//extern std::list<std::string> RatPool;
//extern std::list<std::string> PigletPool;
//extern std::list<std::string> BossPool;
extern std::vector<Actor *> HeroManager;
extern std::vector<Actor *> MonsterManager;


extern Size size ;
extern Scheduler* scheduler;

void solveCollision(/*object1, object2*/);
void collision(/*object*/);
void isOutOfBound(/*object*/);
void collisionDetect(float dt);
Vec2 getFocusPointOfHeros();
std::vector<Actor *> getPoolByName(std::string name);
