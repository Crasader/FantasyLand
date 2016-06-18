#include "MessageDispatchCenter.h"
#include <iostream>
#include "GlobalVariables.h"

MessageDispatchCenter * MessageDispatchCenter::_instance = nullptr;

MessageDispatchCenter* MessageDispatchCenter::getInstance()
{
	if( _instance == nullptr)
	{
		_instance = new MessageDispatchCenter();
	}
	return _instance;
}

void MessageDispatchCenter::registerMessage(enum MessageType messageType, std::function<void(Actor*)> callfunc)
{
	if(_MessageQue.find(messageType) != _MessageQue.end() )
	{
		std::vector<std::function<void(Actor*)> > &funcList = _MessageQue.at(messageType);
		funcList.push_back(callfunc);
	}
	else
	{
		std::vector<std::function<void(Actor*)> > funcList;
		funcList.push_back(callfunc);
		_MessageQue[messageType] = funcList;
	}
}

void MessageDispatchCenter::removeMessage(enum MessageType messageType, std::function<void(Actor*)> callfunc)
{
	//暂时用不到
}

void MessageDispatchCenter::dispatchMessage(enum MessageType messageType, Actor* param)
{
	if(_MessageQue.find(messageType) != _MessageQue.end())
	{
		std::vector<std::function<void(Actor*)>> funcList = _MessageQue.at(messageType);

		for( auto func : funcList)
		{
			func(param);
		}
	}
}

