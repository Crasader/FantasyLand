#pragma once
#include "cocos2d.h"

USING_NS_CC;

class ParticleManager
{
public:
	static ParticleManager* getInstance();

	void AddPlistData(std::string fileName, std::string keyName); 
	ValueMap getPlistData(std::string keyname);

private:
	std::map<std::string,ValueMap> _plistMap;
};

