#include "OperateLayer.h"
#include "Hero.h"
#include"JoyStick.h"

USING_NS_CC;

OperateLayer::OperateLayer(void)
{
}


OperateLayer::~OperateLayer(void)
{
}

bool OperateLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	first = true;

	JoyStick* joyStick = JoyStick::create();
	this->addChild(joyStick,1,1);

	addAttckMenu();

	return true;
}

void OperateLayer::addAttckMenu()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto attackItem = MenuItemImage::create("res/attackbuttonNormal.png","res/attackbuttonSelected.png",CC_CALLBACK_1(OperateLayer::attackButton,this));
	attackItem->setScale(1.5);
	attackItem->setPosition(visibleSize.width - attackItem->getContentSize().width/2-50, attackItem->getContentSize().height/2+20);
	auto menu = Menu::create(attackItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,100);
}

void OperateLayer::attackButton(Ref* pSender)
{
	if(first)myHero = (Hero*)Director::getInstance()->getRunningScene()->getChildByTag(0)->getChildByTag(10);
	myHero->changeState(PREATTACK,0.8f,0.4f);
}
