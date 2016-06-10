#pragma once
#include "cocos2d.h"

USING_NS_CC;

class MessageDispatchCenter
{
public:
	virtual bool init();

	void registerMessage(std::string messageType /*callback*/);
	void removeMessage(std::string messageType/*callback*/);
	void dispatchMessage(std::string messageType /*param*/);
private:
	//std::map<std::string , > MessageQue;
	std::set<std::string> MessageType;
};
