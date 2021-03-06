#include "Enemy.h"
#include "Hero.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;


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
	this->initWithSpriteFrameName("bear_idle_00.png");//�����ʼͼƬ
	this->setAnchorPoint(Vec2(0.5,0.5));

	setSightRange(Vec2(300,100));
	setAttackRange(Vec2(50,15));

	attackCD=0;
	attackDelay=0.8f;
	attackRoll=0.4f;
	attackHurtDelay=0.1f;

	setAttackDamage(1.0f);

	addAnimate();

	runStayAction();

	return true;
}

void Enemy::addAnimate()
{
	Animation* stayAnimation = this->createAnimation("bear_idle_%02d.png",3,5);//����ͣ������
	this->setStayAction(RepeatForever::create(Animate::create(stayAnimation)));

    Animation* walkAnimation = this->createAnimation("bear_run_%02d.png",4,10);//�����ƶ�����
	this->setWalkAction(RepeatForever::create(Animate::create(walkAnimation)));

	Animation* attackAnimation = this->createAttackAnimation("bear_attack_00_%02d.png",0,9,10);//������������
	this->setAttackAction(RepeatForever::create(Animate::create(attackAnimation)));

	Animation* hurtAnimation = this->createAnimation("bear_hurt_%02d.png",2,5);//�������˶���
	this->setHurtAction(RepeatForever::create(Animate::create(hurtAnimation)));

	Animation* deadAnimation = this->createAnimation("bear_dead_%02d.png",2,5);//������������
	this->setDeadAction(RepeatForever::create(Animate::create(deadAnimation)));
}

void Enemy::updateSelf(float)
{
	if(curtLifeValue<=0)
	{
		changeState(DEAD);
		if(curState==DEAD)
		{
			this->runAction(Sequence::create(DelayTime::create(1.5f),FadeOut::create(1.0f),NULL));
			this->scheduleOnce(schedule_selector(Enemy::deleteSelf),2.5f);
		}
	}
	if(attackCD>0)attackCD--;
	Vec2 distance = myHero->getPosition()-this->getPosition();
	float x = abs(distance.x);
	float y = abs(distance.y);
	if (x<attackRange.x&&y<attackRange.y&&attackCD<=0)
	{
		changeState(PREATTACK,attackDelay,attackRoll);
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
				if(distance.x<attackRange.x&&distance.x>0&&y<attackRange.y)//�ж�Ӣ���Ƿ��ڷ�Χ��
				{
					myHero->changeState(HURT,attackHurtDelay);
					myHero->lostLife(attackDamage);
					SimpleAudioEngine::getInstance()->playEffect("res/NormalAttack.wav");
				}
			}
			else
			{
				if(distance.x>-attackRange.x&&distance.x<0&&y<attackRange.y)//�ж�Ӣ���Ƿ��ڷ�Χ��
				{
					myHero->changeState(HURT,attackHurtDelay);
					myHero->lostLife(attackDamage);
					SimpleAudioEngine::getInstance()->playEffect("res/NormalAttack.wav");
				}
			}
		}
		attackCD=40;
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
	gamelayer->killed();
	gamelayer->removeChild(this);
	myEnemies->removeObject(this);
	this->release();
}
