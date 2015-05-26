#include "LifeShow.h"

USING_NS_CC;

LifeShow::LifeShow(void)
{
}


LifeShow::~LifeShow(void)
{
}

bool LifeShow::init()
{
	if(!Sprite::init())
	{
		return false;
	}

	auto visibleOrigin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	life = Sprite::create("res/blood.png");
	lifeBackground = Sprite::create("res/bloodBg.png");

	life->setAnchorPoint(Vec2(0,1));
	life->setPosition(visibleOrigin.x,visibleSize.height);

	lifeBackground->setAnchorPoint(Vec2(0,1));
	lifeBackground->setPosition(visibleOrigin.x,visibleSize.height);

	this->addChild(lifeBackground);
	this->addChild(life);

	return true;
}

void LifeShow::connect()
{
	myHero = (Hero*)this->getParent()->getParent()->getChildByTag(0)->getChildByTag(10);
	this->schedule(schedule_selector(LifeShow::updateSelf));
}

void LifeShow::updateSelf(float)
{
	life->setScaleX( myHero->getCurtLifeValue() / myHero->getSumLifeValue() );
}