#pragma once
#include "GlobalVariables.h"

extern std::vector<Actor *> HeroPool;
extern std::vector<Actor *> DragonPool;
extern std::vector<Actor *> SlimePool;
extern std::vector<Actor *> RatPool;
extern std::vector<Actor *> BossPool;
extern std::vector<Actor *> PigletPool;
extern std::vector<Actor *> HeroManager;
extern std::vector<Actor *> MonsterManager;

void solveCollision(Actor *object1,Actor * object2);
void collision(Actor* object);
void isOutOfBound(Actor *object);
void collisionDetect(float dt);
Vec2 getFocusPointOfHeros();
void PushBackPoolByName(std::string name, Actor * target);
