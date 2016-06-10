#include "Helper.h"
#include "Actor.h"

Camera * camera = Camera::create();

float radNormalize(float rad)
{
	float pi2 = 2 * M_PI;
	rad = fmod(rad, pi2);
	rad = fmod((rad + pi2), pi2);
	if( rad > M_PI)
	{
		rad = rad - M_PI;
	}
	return rad;
}

Vec2 getPosTable(Node* obj)
{
	Vec2 pos = obj->getPosition();
	return pos;
}

Vec2 getNextStepPos(Vec2 curPos, Vec2 targetPos, float speed, float dt)
{
	auto angel = atan2(targetPos.y - curPos.y, targetPos.x - curPos.x);
	Vec2 buffer;
	buffer.x = curPos.x + cos(angel)*speed*dt;
	buffer.y = curPos.y + sin(angel)*speed*dt;
	return buffer;
}

timerange createAnimationStruct(float var1, float var2, float var3)
{
	timerange buffer = { var1,var2,var3 };
	return buffer;
}

Animate3D* createAnimation(std::string file, float begin, float finish, float speed)
{
	auto animation3d = Animation3D::create(file);
	auto animate3d = Animate3D::create(animation3d, begin / 30, (finish - begin) / 30);
	animate3d->setSpeed(speed);
	animate3d->retain();
	return animate3d;
}

float DEGREES_TO_RADIANS(float _ANGLE)
{
	return _ANGLE * 0.01745329252;
}

float RADIANS_TO_DEGREES(float _ANGLE)
{
	return _ANGLE * 57.29577951;
}

msgStruct createKnockedMsgStruct(Actor * object)
{
	msgStruct buffer = { object , object->getTarget()};
	return buffer;
}

void delayExecute(Actor* target, void(* func)(), float delay)
{
	auto wait = DelayTime::create(delay);
	target->runAction(Sequence::create(wait, CallFunc::create(func)));
}
