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
