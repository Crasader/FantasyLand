#include "MessageDispatchCenter.h"


std::set<std::string> MessageType;

bool MessageDispatchCenter::init()
{
	std::vector<std::string> buffer = { 
		"BLOOD_MINUS",	"REDUCE_SCORE","KNOCKED",
		"KNOCKEDAOE",	"SPECIAL_PERSPECTIVE","SPECIAL_KNIGHT",
		"SPECIAL_ARCHER","SPECIAL_MAGE","ANGRY_CHANGE" };
	MessageType.insert(buffer.begin(), buffer.end());

	return true;
}

void MessageDispatchCenter::registerMessage(std::string messageType /*callback*/)
{
	if(MessageType.find(messageType) == MessageType.end() )
	{
		std::cout << "param is invalid";
		return;
	}
	

		
	/*if self.MessageQue[messageType] == nil then
		self.MessageQue[messageType] = {}
	end
	local index = table.getn(self.MessageQue[messageType])
	self.MessageQue[messageType][index + 1] = callback*/
}

void MessageDispatchCenter::removeMessage(std::string messageType/*callback*/)
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

void MessageDispatchCenter::dispatchMessage(std::string messageType/*callback*/)
{
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
}
