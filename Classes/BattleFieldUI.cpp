#include "BattleFieldUI.h"

bool BattleFieldUI::init()
{
	Layer::init();

	avatarInit();
	bloodbarInit();
	angrybarInit();
	touchButtonInit();
	timeInit();
	

	return true;
}