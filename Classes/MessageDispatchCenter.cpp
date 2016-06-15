﻿#include "MessageDispatchCenter.h"
#include <iostream>
#include "GlobalVariables.h"

MessageDispatchCenter * MessageDispatchCenter::instance = nullptr;

MessageDispatchCenter* MessageDispatchCenter::getInstance()
{
	if( instance == nullptr)
	{
		instance = new MessageDispatchCenter();
	}
	return instance;
}

void MessageDispatchCenter::registerMessage(enum MessageType messageType, std::function<void(Actor*)> callfunc)
{
	if(MessageQue.find(messageType) != MessageQue.end() )
	{
		std::vector<std::function<void(Actor*)> > &funcList = MessageQue.at(messageType);
		funcList.push_back(callfunc);
	}
	else
	{
		std::vector<std::function<void(Actor*)> > funcList;
		funcList.push_back(callfunc);
		MessageQue[messageType] = funcList;
	}
}

void MessageDispatchCenter::removeMessage(enum MessageType messageType, std::function<void(Actor*)> callfunc)
{
	/*std::vector<std::function<void(Actor*)>> funcList = MessageQue.at(messageType);
	funcList.erase(std::find(funcList.begin(), funcList.end(), callfunc));*/
}

void MessageDispatchCenter::dispatchMessage(enum MessageType messageType, Actor* param)
{
	if(MessageQue.find(messageType) != MessageQue.end())
	{
		std::vector<std::function<void(Actor*)>> funcList = MessageQue.at(messageType);

		for( auto func : funcList)
		{
			func(param);
		}
	}
}

