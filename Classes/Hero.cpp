#include "Hero.h"
#include "Enemy.h"
#include "GameLayer.h"

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

	this->initWithSpriteFrameName("boy_idle_00.png");//�����ʼͼƬ
	this->setAnchorPoint(Vec2(0.5,0.5));

	addAnimate();

	this->setSpeed(3);
	this->setAttackRange(Vec2(80,25));
	this->setAttackDamage(50.0f);

	this->runStayAction();
	//this->runHurtAction();
	this->schedule(schedule_selector(Hero::updateSelf));
	return true;

	attackCD=0;
}

void Hero::addAnimate()
{
	Animation* stayAnimation = this->createAnimation("boy_idle_%02d.png",3,5);//����ͣ������
	this->setStayAction(RepeatForever::create(Animate::create(stayAnimation)));

    Animation* walkAnimation = this->createAnimation("boy_run_%02d.png",8,10);//�����ƶ�����
	this->setWalkAction(RepeatForever::create(Animate::create(walkAnimation)));

	//Animation* attckAnimation = this->createAnimation("boy_attack_00_%02d.png",8,10);//������������
	//this->setAttackAction(RepeatForever::create(Animate::create(attckAnimation)));

	Animation *attackAnimation1 = this->createAttackAnimation("boy_attack_00_%02d.png", 0, 4, 10);//������������
	Animation *attackAnimation2 = this->createAttackAnimation("boy_attack_00_%02d.png", 4, 8, 10);
	this->setAttackAction(Sequence::create( Animate::create(attackAnimation1),Animate::create(attackAnimation2),NULL) );

	Animation* hurtAnimation = this->createAnimation("boy_hurt_%02d.png",2,5);//�������˶���
	this->setHurtAction(RepeatForever::create(Animate::create(hurtAnimation)));

	Animation* deadAnimation = this->createAnimation("boy_dead_%02d.png",3,10);//������������
	this->setDeadAction(Animate::create(deadAnimation));
}

void Hero::updateSelf(float)
{
	if(attackCD>0)attackCD--;
	if(curtLifeValue<=0)changeState(DEAD);
	if(curState == WALK)
	{
		float mapx = myMap->getPosition().x;
		float mapWidth = myMap->getBoundingBox().getMaxX();
		Vec2 dest = getPosition() + direction * getSpeed();
		if(dest.x < 0 ||dest.x >myMap->getMapSize().width * myMap->getTileSize().width)
		{
			direction.x = 0;
		}
		if(dest.y < 0 || dest.y > 96)
		{
			direction.y = 0;
		}
		move(direction,isFlipped);
		auto winSize = Director::getInstance()->getWinSize();
		int x = MAX(this->getPosition().x, winSize.width/2);
		int y = MAX(this->getPosition().y, winSize.height/2);
		x = MIN(x, (myMap->getMapSize().width * myMap->getTileSize().width) - winSize.width/2);
		y = MIN(y, (myMap->getMapSize().height * myMap->getTileSize().height) - winSize.height/2);
		Point actualPosition = Vec2(x, y);
		Point centerOfView = Vec2(winSize.width/2, winSize.height/2);
		Point viewPoint = centerOfView - actualPosition;
		this->getParent()->setPosition(viewPoint);
		this->getParent()->getChildByTag(2)->setPosition(x,Director::getInstance()->getVisibleSize().height-20);
		this->getParent()->getChildByTag(3)->setPosition(x,Director::getInstance()->getVisibleSize().height-40);
		this->getParent()->getChildByTag(4)->setPosition(x+100,Director::getInstance()->getVisibleSize().height-20);
		this->getParent()->getChildByTag(5)->setPosition(x+100,Director::getInstance()->getVisibleSize().height-40);
	}
	if(curState==ATTACK)
	{
		if(attackCD<=0)
		{
			Ref* it;
			Enemy* myEnemy;
			CCARRAY_FOREACH(myEnemies, it)//��������
			{
				myEnemy = (Enemy*)it;
				Vec2 distance = myEnemy->getPosition()-this->getPosition();
				if(!isFlipped)
				{
					if(distance.x<this->getAttackRange().x&&distance.x>-10&&abs(distance.y)<this->getAttackRange().y)
						//�жϵ����Ƿ��ڹ�����Χ��
						myEnemy->changeState(HURT,0.55f,0.0f,attackDamage);
				}
				else
				{
					if(distance.x>-this->getAttackRange().x&&distance.x<10&&abs(distance.y)<this->getAttackRange().y)
						//�жϵ����Ƿ��ڹ�����Χ��
						myEnemy->changeState(HURT,0.55f,0.0f,attackDamage);
				}
			}
		}
		attackCD=10;
	}
}

void Hero::connect()
{
	myMap = (TMXTiledMap*)this->getParent()->getParent()->getChildByTag(0)->getChildByTag(1)->getChildByTag(1);
	floor = myMap->getLayer("Floor");
	auto gamelayer = (GameLayer*)this->getParent()->getParent()->getChildByTag(0);
	myEnemies = gamelayer->getEnemies();
}