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
	
	void registerMessage( enum MessageType messageType /*callback*/);

	void removeMessage(enum MessageType messageType/*callback*/);

	void dispatchMessage(enum MessageType messageType, struct MESSAGE_ANGRY_CHANGE param);
	void dispatchMessage(enum MessageType messageType, struct MESSAGE_BLOOD_MINUS param);
	void dispatchMessage(enum MessageType messageType, struct MESSAGE_SPECIAL_PERSPECTIVE param);

private:
	//std::map< enum MessageType, std::vector<std::function<void(Ref*)> > > MessageQue;

};
