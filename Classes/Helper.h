#pragma once
#include <map>
#include <math/Vec2.h>
#include "cocos2d.h"
#include <cmath>

USING_NS_CC;

//Camera camera;
//camera = null
typedef
struct 
{
	float begin;
	float ended;
	float speed;
}timerange;

typedef
struct 
{
	/*attacker =
	target = */
}msgStruct;



//void print(std::map<> tab);
float radNormalize(float rad);
Vec3 getPosTable(/*obj*/);
Vec3 getNextStepPos(Vec2 curPos, Vec2 targetPos , float speed, float dt);
timerange createAnimationStruct(float var1, float var2, float var3);
Animate3D * createAnimation(std::string file, float begin, float finish, float speed);
msgStruct createKnockedMsgStruct(/*object*/);

//void cclog(...);                                           you can switch to printf or count 
//function CreateEnumTable(tbl, index)
//function removeAll(table)
//void copytable()
void delayExecute(/*target, func,*/float delay);

float DEGREES_TO_RADIANS(float _ANGLE);
float RADIANS_TO_DEGREES(float _ANGLE);