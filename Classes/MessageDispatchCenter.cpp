#include "MessageDispatchCenter.h"
#include <iostream>
#include "GlobalVariables.h"


void MessageDispatchCenter::registerMessage(enum MessageType messageType/*callback*/)
{
	/*if self.MessageQue[messageType] == nil then
		self.MessageQue[messageType] = {}
	end
	local index = table.getn(self.MessageQue[messageType])
	self.MessageQue[messageType][index + 1] = callback*/
}

void MessageDispatchCenter::removeMessage(enum MessageType  messageType/*callback*/)
{
	//if self.MessageType[messageType] == nil or type(callback) ~= "function" then
	//	print("param is invalid")
	//	return
	//end
	//for i, v in pairs(self.MessageQue[messageType]) do
	//	if callback == v then
	//		table.remove(self.MessageQue[messageType], i)
	//		return
	//	end
	//end
}

void MessageDispatchCenter::dispatchMessage(enum MessageType  messageType, struct MESSAGE_ANGRY_CHANGE param)
{

}

void MessageDispatchCenter::dispatchMessage(enum MessageType  messageType, struct MESSAGE_BLOOD_MINUS param)
{

}

void MessageDispatchCenter::dispatchMessage(enum MessageType  messageType, struct MESSAGE_SPECIAL_PERSPECTIVE param)
{

}

//if self.MessageType[messageType] == nil then
	//	print("param is invalid")
	//	return
	//end

	//	
	//if self.MessageQue[messageType] == nil then
	//	return
	//end
	//for i, v in pairs(self.MessageQue[messageType]) do
	//	v(param)
	//end
