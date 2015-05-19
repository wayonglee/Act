#include "GameLayer.h"
#include"MapLayer.h"
#include"Hero.h"
#include"Enemy.h"

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

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/Boy.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/Enemy.plist");


	hero = Hero::create();
	hero->setPosition(100.0f,50.0f);
	this->addChild(hero,400,10);

	enemy = Enemy::create();
	enemy->setPosition(400.0f,50.0f);
	this->addChild(enemy,400,20);

	return true;
}