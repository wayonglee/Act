#include "GameScene.h"
#include"GameLayer.h"
#include"OperateLayer.h"
#include"StateLayer.h"

USING_NS_CC;

GameScene::GameScene(void)
{
}


GameScene::~GameScene(void)
{
}

bool GameScene::init()
{
	if(!Scene::init())
	{
		return false;
	}
	auto gamelayer=GameLayer::create();
    this->addChild(gamelayer, 0 ,0);

    auto operateLayer = OperateLayer::create();
    this->addChild(operateLayer, 1 ,1);

    auto statelayer =StateLayer::create();
    this->addChild(statelayer, 2 ,2);
	
	return true;
}
