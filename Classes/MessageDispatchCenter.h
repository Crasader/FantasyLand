#pragma once
#include <string>
#include "cocos2d.h"
#include <set>

class MessageDispatchCenter
{
public:


	void registerMessage(std::string messageType /*callback*/);
	void removeMessage(std::string messageType/*callback*/);
	void dispatchMessage(std::string messageType /*param*/);
private:
	std::set<std::string> MessageType;
	//std::map<std::string , > MessageQue;
};
