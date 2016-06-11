#pragma once
#include "cocos2d.h"

USING_NS_CC;

enum MessageType
{
	BLOOD_MINUS,
	REDUCE_SCORE,
	KNOCKED,
	KNOCKEDAOE,
	SPECIAL_PERSPECTIVE,
	SPECIAL_KNIGHT,
	SPECIAL_ARCHER,
	SPECIAL_MAGE,
	ANGRY_CHANGE
};


class MessageDispatchCenter
{
public:
	static MessageDispatchCenter* getInstance();

	void registerMessage(std::string messageType /*callback*/);
	void removeMessage(std::string messageType/*callback*/);
	void dispatchMessage(std::string messageType /*param*/);

private:
	static MessageDispatchCenter * instance;

	//std::map<std::string , > MessageQue;
};
