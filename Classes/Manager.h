#pragma once
#include "Helper.h"
#include "Actor.h"
#include "GlobalVariables.h"
#include "Dragon.h"

extern std::vector<Actor *> HeroPool;
extern std::vector<Actor *> DragonPool;
extern std::vector<Actor *> SlimePool;
extern std::vector<Actor *> RatPool;
extern std::vector<Actor *> BossPool;
extern std::vector<Actor *> PigletPool;
extern std::vector<Actor *> HeroManager;
extern std::vector<Actor *> MonsterManager;


extern Size size ;
extern Scheduler* scheduler;

void solveCollision(Actor *object1,Actor * object2);
void collision(Actor* object);
void isOutOfBound(Actor *object);
void collisionDetect(float dt);
Vec2 getFocusPointOfHeros();
std::vector<Actor *> getPoolByName(std::string name);
