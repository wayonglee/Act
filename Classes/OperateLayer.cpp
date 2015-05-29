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
	attackItem->setScale(1.2);
	attackItem->setPosition(visibleSize.width - attackItem->getContentSize().width/2-50, attackItem->getContentSize().height/2+20);
	//攻击按钮
	auto skillItem1 = MenuItemImage::create("res/attackbuttonNormal.png","res/attackbuttonSelected.png",CC_CALLBACK_1(OperateLayer::skillButton1,this));
	skillItem1->setScale(1.2);
	skillItem1->setPosition(visibleSize.width - attackItem->getContentSize().width/2-100, attackItem->getContentSize().height/2+20);
	//技能1按钮
	auto skillItem2 = MenuItemImage::create("res/attackbuttonNormal.png","res/attackbuttonSelected.png",CC_CALLBACK_1(OperateLayer::skillButton2,this));
	skillItem2->setScale(1.2);
	skillItem2->setPosition(visibleSize.width - attackItem->getContentSize().width/2-150, attackItem->getContentSize().height/2+20);
	//技能2按钮

	auto skillItem3 = MenuItemImage::create("res/attackbuttonNormal.png","res/attackbuttonSelected.png",CC_CALLBACK_1(OperateLayer::skillButton3,this));
	skillItem3->setScale(1.2);
	skillItem3->setPosition(visibleSize.width - attackItem->getContentSize().width/2-200, attackItem->getContentSize().height/2+20);
	//技能2按钮

	auto menu = Menu::create(attackItem,skillItem1,skillItem2,skillItem3,NULL);
	menu->setPosition(Vec2(0,0));
	this->addChild(menu,100);
}



void OperateLayer::attackButton(Ref* pSender)
{
	if(myHero->getCurState()==WALK&&myHero->getRunningAttackCD()<=0)
	{
		myHero->changeState(PRERUNNINGATTACK,myHero->getRunningAttackDelay(),myHero->getRunningAttackRoll());
	}
	else if(myHero->getAttackCD()<=0)
	{
		myHero->changeState(PREATTACK,myHero->getAttackDelay(),myHero->getAttackRoll());
	}
}

void OperateLayer::skillButton1(Ref* pSender)
{
	if(myHero->getSkillCD1()<=0)
	{
		myHero->changeState(PRESKILL,myHero->getSkillDelay1(),myHero->getSkillRoll1(),1);
	}
}

void OperateLayer::skillButton2(Ref* pSender)
{
	if(myHero->getSkillCD2()<=0)
	{
		myHero->changeState(PRESKILL,myHero->getSkillDelay2(),myHero->getSkillRoll2(),2);
	}
}

void OperateLayer::skillButton3(Ref* pSender)
{
	if(myHero->getSkillCD3()<=0)
	{
		myHero->changeState(PRESKILL,myHero->getSkillDelay3(),myHero->getSkillRoll3(),3);
	}
}

void OperateLayer::connect()
{
	myHero = (Hero*)this->getParent()->getChildByTag(0)->getChildByTag(10);
}
