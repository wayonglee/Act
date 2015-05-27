#include "Enemy.h"
#include "Hero.h"
#include "GameLayer.h"



Enemy::Enemy(void)
{
}


Enemy::~Enemy(void)
{
}

bool Enemy::init()
{
	if(!Sprite::init())
	{
		return false;
	}
	this->initWithSpriteFrameName("bear_idle_00.png");//载入初始图片
	this->setAnchorPoint(Vec2(0.5,0.5));

	setSightRange(Vec2(200,100));
	setAttackRange(Vec2(50,15));
	attackCD=0;

	setAttackDamage(1.0f);

	addAnimate();

	runStayAction();

	return true;
}

void Enemy::addAnimate()
{
	Animation* stayAnimation = this->createAnimation("bear_idle_%02d.png",3,5);//创建停留动画
	this->setStayAction(RepeatForever::create(Animate::create(stayAnimation)));

    Animation* walkAnimation = this->createAnimation("bear_run_%02d.png",4,10);//创建移动动画
	this->setWalkAction(RepeatForever::create(Animate::create(walkAnimation)));

	Animation* attackAnimation = this->createAttackAnimation("bear_attack_00_%02d.png",0,9,10);//创建攻击动画
	this->setAttackAction(RepeatForever::create(Animate::create(attackAnimation)));

	Animation* hurtAnimation = this->createAnimation("bear_hurt_%02d.png",2,5);//创建受伤动画
	this->setHurtAction(RepeatForever::create(Animate::create(hurtAnimation)));

	Animation* deadAnimation = this->createAnimation("bear_dead_%02d.png",2,5);//创建死亡动画
	this->setDeadAction(RepeatForever::create(Animate::create(deadAnimation)));
}

void Enemy::updateSelf(float)
{
	if(curtLifeValue<=0)
	{
		changeState(DEAD);
		this->scheduleOnce(schedule_selector(Enemy::deleteSelf),1);
	}
	attackCD--;
	Vec2 distance = myHero->getPosition()-this->getPosition();
	float x = abs(distance.x);
	float y = abs(distance.y);
	if (x<attackRange.x&&y<attackRange.y&&attackCD<=0)
	{
		changeState(PREATTACK,0.8f,0.5f);
	}
	else if(x<sightRange.x&&y<sightRange.y&&x>1)
	{
		changeState(WALK);
		getChaseDirection();
	}
	else changeState(STAY);
	if(curState==WALK)
	{
		move(direction,isFlipped);
	}
	if(curState==ATTACK)
	{
		if(attackCD<=0)
		{
			if(!isFlipped)
			{
				if(distance.x<attackRange.x&&distance.x>0&&y<attackRange.y)//判断英雄是否在范围内
				{
					myHero->changeState(HURT,0.05f,0.0f,attackDamage);
				}
			}
			else
			{
				if(distance.x>-attackRange.x&&distance.x<0&&y<attackRange.y)//判断英雄是否在范围内
				{
					myHero->changeState(HURT,0.05f,0.0f,attackDamage);
				}
			}
		}
		attackCD=20;
	}
	this->setLocalZOrder(400+myHero->getPosition().y-this->getPosition().y);
}

void Enemy::connect()
{
	myHero = (Hero*)this->getParent()->getParent()->getChildByTag(0)->getChildByTag(10);
	this->schedule(schedule_selector(Enemy::updateSelf));
	auto gamelayer = (GameLayer*)this->getParent()->getParent()->getChildByTag(0);
	myEnemies = gamelayer->getEnemies();
}

void Enemy::getChaseDirection()
{
	bool isFlipped = false;
	float k,x,y;
	k = (myHero->getPosition().y-this->getPosition().y)/(myHero->getPosition().x-this->getPosition().x);
	x = sqrt(1/(1+k*k));
	if(myHero->getPosition().x<this->getPosition().x)x=-x;
	y = k*x;
	direction = Vec2(x,y);
	if(x<0)isFlipped = true;
	this->setDirection(direction);
	this->setIsFlipped(isFlipped);
}

void Enemy::deleteSelf(float)
{

	auto gamelayer = (GameLayer*)this->getParent()->getParent()->getChildByTag(0);
	gamelayer->removeChild(this);
	myEnemies->removeObject(this);
	this->release();
}