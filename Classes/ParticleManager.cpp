#include "ParticleManager.h"
#include <map>

ParticleManager* ParticleManager::getInstance()
{
	if (instance == NULL)
		instance = new ParticleManager();
	return instance;
}

void ParticleManager::AddPlistData(std::string fileName, std::string keyName)
{
	if (fileName == "" || keyName == "")
		return;
	
	if (_plistMap.find(keyName) != _plistMap.end())
		log("the keyName is exist already.");

	auto plistData = FileUtils::getInstance()->getValueMapFromFile(fileName);
	_plistMap[keyName] = plistData;
}

ValueMap ParticleManager::getPlistData(std::string keyname)
{
	if (keyname == "")
		return;
	if (_plistMap.find(keyname) == _plistMap.end())
		log("can't find plistData by the specified keyName.");
	else
		return _plistMap[keyname];
}
