#include "ParticleManager.h"

ParticleManager* ParticleManager::_instance = nullptr;

ParticleManager* ParticleManager::getInstance()
{
	if(_instance == nullptr)
	{
		_instance = new ParticleManager();
	}
	return _instance;
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
	return _plistMap[keyname];
}
