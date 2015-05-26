#include "JoyStick.h"
#include "Hero.h"

JoyStick::JoyStick(void)
{
}

JoyStick::~JoyStick(void)
{
}

bool JoyStick::init()
{
	if(!Sprite::init())
	{
		return false;
	}
	stickPosition.setPoint(70,70);
	isW = false;
	first = true;
	setStick();
	addEventListener();
	hideJoyStick();
	return true;
}

void JoyStick::setStick()
{
	joyStick = Sprite::create("res/jsb.png");
	joyStickBackground = Sprite::create("res/jsbg.png");

	joyStickBackground->setScale(0.6f);
	
	joyStick->setAnchorPoint(Vec2(0.5f,0.5f));
	joyStickBackground->setAnchorPoint(Vec2(0.5f,0.5f));

	joyStick->setPosition(stickPosition);
	joyStickBackground->setPosition(stickPosition);

	this->addChild(joyStickBackground,0);
	this->addChild(joyStick,1);
}

void JoyStick::addEventListener()
{
	EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(JoyStick::onTouchesBegan,this);
	listener->onTouchesMoved = CC_CALLBACK_2(JoyStick::onTouchesMoved,this);
	listener->onTouchesEnded = CC_CALLBACK_2(JoyStick::onTouchesEnded,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}

void JoyStick::onTouchesBegan(const std::vector<Touch*>& touches,Event* pEvent)
{
	auto touchPoint = touches[0]->getLocation();
	if(touchPoint.distance(stickPosition)<=40)//在按
	{	
		isW = true;
		this->schedule(schedule_selector(JoyStick::updateMove));//开始移动
		showJoyStick();
		joyStick->setPosition(calculateJoyStickLocation(touchPoint));
	}
}
void JoyStick::onTouchesMoved(const std::vector<Touch*>& touches,Event* pEvent)
{
	if(isW)
	{
		auto touchPoint = touches[0]->getLocation();
		if(touchPoint.distance(stickPosition)<=120)
		{
			joyStick->setPosition(calculateJoyStickLocation(touchPoint));//防止按钮出范围
		}
		else 
		{
			hideJoyStick();
			joyStick->setPosition(stickPosition);
			this->unschedule(schedule_selector(JoyStick::updateMove));//停止移动
			myHero->changeState(STAY);//改变角色状态
			isW = false;
		}
	}
}
void JoyStick::onTouchesEnded(const std::vector<Touch*>& touches,Event* pEvent)
{
	//if(touches.size()==1)
	{
		if(isW)
			if(joyStick->getPosition()!=stickPosition)
			{
				hideJoyStick();
				joyStick->setPosition(stickPosition);
				this->unschedule(schedule_selector(JoyStick::updateMove));//停止移动
				myHero->changeState(STAY);//改变角色状态
				isW = false;
			}
	}
}

Vec2 JoyStick::calculateJoyStickLocation(Vec2 touchPoint)
{
	if(touchPoint.distance(stickPosition)<=40)
	{
		return touchPoint;
	}
	else 
	{
		float k,x,y;
		k = (touchPoint.y-stickPosition.y)/(touchPoint.x-stickPosition.x);
		x = sqrt(1600/(1+k*k));
		if(touchPoint.x<stickPosition.x)x=-x;
		y = k*x;
		return Vec2(x+stickPosition.x,y+stickPosition.y);
	}
}

void JoyStick::connect()
{
	myHero = (Hero*)this->getParent()->getParent()->getChildByTag(0)->getChildByTag(10);
	myMap = (TMXTiledMap*)this->getParent()->getParent()->getChildByTag(0)->getChildByTag(1)->getChildByTag(1);
	floor = myMap->getLayer("Floor");
	//myHero->connect();
}

void JoyStick::showJoyStick()
{
	joyStick->setOpacity(255);
	joyStickBackground->setOpacity(255);
}

void JoyStick::hideJoyStick()
{
	joyStick->setOpacity(50);
	joyStickBackground->setOpacity(50);
}

void JoyStick::updateMove(float)
{
	if( isW )
	{
		if(myHero->getCurState()!=WALK)myHero->changeState(WALK);
		bool isFlipped = false;
		float k,x,y;
		k = (joyStick->getPosition().y-stickPosition.y)/(joyStick->getPosition().x-stickPosition.x);
		x = sqrt(1/(1+k*k));
		if(joyStick->getPosition().x<stickPosition.x)x=-x;
		y = k*x;
		direction = Vec2(x,y);
		if(x<0)isFlipped = true;
		myHero->setDirection(direction);
		myHero->setIsFlipped(isFlipped);
	}
}
