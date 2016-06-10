#pragma once
#include <string>
#include "cocos2d.h"
#include <set>
#include <iostream>

USING_NS_CC;

class MessageDispatchCenter
{
public:
	CREATE_FUNC(MessageDispatchCenter);
	virtual bool init();

	void registerMessage(std::string messageType /*callback*/);
	void removeMessage(std::string messageType/*callback*/);
	void dispatchMessage(std::string messageType /*param*/);
private:
	//std::map<std::string , > MessageQue;
	std::set<std::string> MessageType;
};
