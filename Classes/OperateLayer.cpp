#include "OperateLayer.h"
#include "Hero.h"

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

	auto skillItem1 = MenuItemImage::create("res/attackbuttonNormal.png","res/attackbuttonSelected.png",CC_CALLBACK_1(OperateLayer::skillButton1,this));
	skillItem1->setScale(1.5);
	skillItem1->setPosition(visibleSize.width - attackItem->getContentSize().width/2-100, attackItem->getContentSize().height/2+20);

	auto menu = Menu::create(attackItem,skillItem1,NULL);
	menu->setPosition(Vec2(0,0));
	this->addChild(menu,100);
}



void OperateLayer::attackButton(Ref* pSender)
{
	if(myHero->getAttackCD()<=0)
	{
		myHero->changeState(PREATTACK,myHero->getAttackDelay(),myHero->getAttackRoll());
	}
}

void OperateLayer::skillButton1(Ref* pSender)
{
	if(myHero->getSkill1CD()<=0)
	{
		myHero->changeState(PRESKILL1,myHero->getskill1Delay(),myHero->getskill1Roll());
	}
}

void OperateLayer::connect()
{
	myHero = (Hero*)this->getParent()->getChildByTag(0)->getChildByTag(10);
}
