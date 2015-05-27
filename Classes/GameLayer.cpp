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

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/Boy.plist");//英雄动画缓存
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/Enemy.plist");//敌人动画缓存

	enemies = CCArray::create();//创建敌人数组
	enemies->retain();

	hero = Hero::create();
	hero->setPosition(100.0f,50.0f);
	this->addChild(hero,400,10);

	this->schedule(schedule_selector(GameLayer::addEnemy),1.0f);

	return true;
}

CCArray* GameLayer::getEnemies()
{
	return enemies;
}

void GameLayer::addEnemy(float)
{
	if(enemies->count()<10)
	{
		srand(time(NULL));
		float x = random<float>(-240,240);
		float y = random<float>(0,96);
		auto enemy = Enemy::create();
		enemy->setPosition(hero->getPosition().x+x,y);
		this->addChild(enemy,400);
		enemy->connect();
		enemies->addObject(enemy);
	}
}

