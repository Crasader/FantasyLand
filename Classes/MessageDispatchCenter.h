#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Actor;

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

	void registerMessage( enum MessageType messageType , std::function<void(Actor*)> callfunc);
	void removeMessage(enum MessageType messageType , std::function<void(Actor*)> callfunc);
	void dispatchMessage(enum MessageType messageType, Actor * param);

private:
	std::map< enum MessageType, std::vector<std::function<void(Actor*) > > > MessageQue;
	static MessageDispatchCenter* instance;
};
