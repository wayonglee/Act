#include "Hero.h"

Hero::Hero(void)
{
}

Hero::~Hero(void)
{
}

bool Hero::init()
{
	if(!Sprite::init())
	{
		return false;
	}

	this->initWithSpriteFrameName("boy_idle_00.png");//载入初始图片
	this->setAnchorPoint(Vec2(0.5,0.5));

	addAnimate();

	this->setSpeed(3);
	this->setAttackRange(Vec2(50,20));

	this->runStayAction();
	//this->runHurtAction();
	this->schedule(schedule_selector(Hero::updateSelf));
	return true;
}

void Hero::addAnimate()
{
	Animation* stayAnimation = this->createAnimation("boy_idle_%02d.png",3,5);//创建停留动画
	this->setStayAction(RepeatForever::create(Animate::create(stayAnimation)));

    Animation* walkAnimation = this->createAnimation("boy_run_%02d.png",8,10);//创建移动动画
	this->setWalkAction(RepeatForever::create(Animate::create(walkAnimation)));

	//Animation* attckAnimation = this->createAnimation("boy_attack_00_%02d.png",8,10);//创建攻击动画
	//this->setAttackAction(RepeatForever::create(Animate::create(attckAnimation)));

	Animation *attackAnimation1 = this->createAttackAnimation("boy_attack_00_%02d.png", 0, 4, 10);//创建攻击动画
	Animation *attackAnimation2 = this->createAttackAnimation("boy_attack_00_%02d.png", 4, 8, 10);
	this->setAttackAction(Sequence::create( Animate::create(attackAnimation1),Animate::create(attackAnimation2),NULL) );

	Animation* hurtAnimation = this->createAnimation("boy_hurt_%02d.png",2,5);//创建受伤动画
	this->setHurtAction(RepeatForever::create(Animate::create(hurtAnimation)));
}

void Hero::updateSelf(float)
{

	if(curState == WALK)
	{
		float mapx = myMap->getPosition().x;
		float mapWidth = myMap->getBoundingBox().getMaxX();
		Vec2 dest = getPosition() + direction * getSpeed();
		if(dest.x < 0 || dest.x > 480)
		{
			direction.x = 0;
		}
		if(dest.y < 0 || dest.y > 96)
		{
			direction.y = 0;
		}
		if(dest.x - mapx >=255 && mapWidth-dest.x >=255)
		{
			moveMap(direction.x); 
			direction.x = 0;
		}
		move(direction,isFlipped);
	}
	if(curState == ATTACK)
	{
		if(abs(myEnemy->getPosition().x-this->getPosition().x)<attackRange.x)
			if(abs(myEnemy->getPosition().y-this->getPosition().y)<attackRange.y)
				myEnemy->changeState(HURT,0.4f);
	}
}

void Hero::moveMap(float dx)
{
	if(curState == WALK)
	{
		float realx = -dx*speed;
		if(myMap->getPosition().x + realx <= -5 && myMap->getBoundingBox().getMaxX() + realx >= 485)
		{
			Vec2 destdir = Vec2(realx,0);
			auto moveby = MoveBy::create(1/60,destdir);
			myMap->runAction(moveby);
			myEnemy->runAction(moveby->clone());
		}
	}
}

void Hero::connect()
{
	myMap = (TMXTiledMap*)Director::getInstance()->getRunningScene()->getChildByTag(0)->getChildByTag(1)->getChildByTag(1);
	floor = myMap->getLayer("Floor");
	myEnemy = (Enemy*)Director::getInstance()->getRunningScene()->getChildByTag(0)->getChildByTag(20);
	myEnemy->connect();
}