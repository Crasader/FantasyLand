#include "GameMaster.h"

int gloableZOrder = 1;
enum monsterCount { dragon = 1, slime = 7, piglet = 2, rat = 0 };
int EXIST_MIN_MONSTER = 4;
unsigned int scheduleid;
int stage = 0;
int battleSiteX[3] = { -2800,-1800,-800 };
int frontDistanceWithHeroX = 600;
int backwardDistanceWithHeroX = 800;
int distanceWithHeroX = 150;
int distanceWithHeroY = 150;
