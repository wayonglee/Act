#include "WelcomeScene.h"


WelcomeScene::WelcomeScene()
{
}


WelcomeScene::~WelcomeScene()
{
}

bool WelcomeScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	WelcomeLayer* welcomeLayer = WelcomeLayer::create();
	this->addChild(welcomeLayer, 1, 1);
	return true;
}