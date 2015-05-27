#include "GameLayer.h"
#include"MapLayer.h"
#include<sstream>

using namespace std;

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

	hero = Hero::create();//创建英雄
	hero->setPosition(100.0f,50.0f);
	this->addChild(hero,400,10);


	addKilledCount();//增加计数器
	addEnemyCount();

	this->schedule(schedule_selector(GameLayer::addEnemy),2.0f);
	this->schedule(schedule_selector(GameLayer::updateSelf));

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

void GameLayer::addKilledCount()
{
	enemyKilledNumber=0;//创建杀敌计数
	ostringstream oss;
	oss<<enemyKilledNumber;
	string number = oss.str();
	auto enemyKilledShow = LabelTTF::create("Killed","Arial",20);
	enemyKilledShow->setPosition(240,Director::getInstance()->getVisibleSize().height-20);
	enemyKilledShow->setColor(Color3B::RED);
	enemyKilled = LabelTTF::create(number,"Arial",20);
	enemyKilled->setPosition(240,Director::getInstance()->getVisibleSize().height-40);
	enemyKilled->setColor(Color3B::RED);
	this->addChild(enemyKilledShow,1,2);
	this->addChild(enemyKilled,1,3);
}

void GameLayer::addEnemyCount()
{
	ostringstream oss;
	oss<<enemies->count();
	string number = oss.str();
	auto enemyAliveShow = LabelTTF::create("Alive","Arial",20);
	enemyAliveShow->setPosition(240+100,Director::getInstance()->getVisibleSize().height-20);
	enemyAliveShow->setColor(Color3B::RED);
	enemyAlive = LabelTTF::create(number,"Arial",20);
	enemyAlive->setPosition(240+100,Director::getInstance()->getVisibleSize().height-40);
	enemyAlive->setColor(Color3B::RED);
	this->addChild(enemyAliveShow,1,4);
	this->addChild(enemyAlive,1,5);
}

void GameLayer::killed()
{
	enemyKilledNumber++;
	ostringstream oss;
	oss<<enemyKilledNumber;
	string number = oss.str();
	enemyKilled->setString(number);
}

void GameLayer::updateSelf(float)
{
	ostringstream oss;
	oss<<enemies->count();
	string number = oss.str();
	enemyAlive->setString(number);
}