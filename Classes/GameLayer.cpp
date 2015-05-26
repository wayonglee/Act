#include "GameLayer.h"
#include"MapLayer.h"

GameLayer::GameLayer(void)
{
}


GameLayer::~GameLayer(void)
{
}

bool GameLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	auto maplayer = MapLayer::create();
	this->addChild(maplayer,-1,1);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/Boy.plist");//Ó¢ĞÛ¶¯»­»º´æ
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/Enemy.plist");//µĞÈË¶¯»­»º´æ

	enemies = CCArray::create();
	enemies->retain();

	hero = Hero::create();
	hero->setPosition(100.0f,50.0f);
	this->addChild(hero,400,10);

	this->schedule(schedule_selector(GameLayer::addEnemy),2);

	return true;
}

CCArray* GameLayer::getEnemies()
{
	return enemies;
}

void GameLayer::addEnemy(float)
{
	if(enemies->count()<3)
	{
		srand(time(NULL));
		float x = random<float>(0,480);
		float y = random<float>(0,96);
		auto enemy = Enemy::create();
		enemy->setPosition(x,y);
		this->addChild(enemy,400);
		enemy->connect();
		enemies->addObject(enemy);
	}
}

