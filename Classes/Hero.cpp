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

	this->initWithSpriteFrameName("boy_idle_00.png");//载入初始图片
	this->setAnchorPoint(Vec2(0.5,0.5));

	addAnimate();

	this->setSpeed(3);
	this->setAttackRange(Vec2(100,25));
	this->setAttackDamage(50.0f);

	this->setSkill1Range(Vec2(100,40));
	this->setSkill1RangeBack(Vec2(40,40));

	this->runStayAction();
	//this->runHurtAction();

	attackCD=0;
	skill1CD=0;
	skill1Ratio = 1.2f;

	attackDelay = 0.8f;
	attackRoll = 0.3f;
	attackHurtDelay = 0.55f;
	skill1Delay = 0.8f;
	skill1Roll = 0.3f;
	skill1HurtDelay = 0.65f;

	this->schedule(schedule_selector(Hero::updateSelf));
	return true;
}

void Hero::addAnimate()
{
	Animation* stayAnimation = this->createAnimation("boy_idle_%02d.png",3,5);//创建停留动画
	this->setStayAction(RepeatForever::create(Animate::create(stayAnimation)));

    Animation* walkAnimation = this->createAnimation("boy_run_%02d.png",8,10);//创建移动动画
	this->setWalkAction(RepeatForever::create(Animate::create(walkAnimation)));

	Animation *attackAnimation1 = this->createAttackAnimation("boy_attack_00_%02d.png", 0, 4, 10);//创建攻击动画
	Animation *attackAnimation2 = this->createAttackAnimation("boy_attack_00_%02d.png", 4, 8, 10);
	this->setAttackAction(Sequence::create( Animate::create(attackAnimation1),Animate::create(attackAnimation2),NULL) );

	Animation *skill1Animation1 = this->createAttackAnimation("boy_attack_01_%02d.png", 0, 4, 10);//创建技能动画
	Animation *skill1Animation2 = this->createAttackAnimation("boy_attack_01_%02d.png", 4, 8, 10);
	this->setSkill1Action(Sequence::create( Animate::create(skill1Animation1),Animate::create(skill1Animation2),NULL) );

	Animation* hurtAnimation = this->createAnimation("boy_hurt_%02d.png",2,5);//创建受伤动画
	this->setHurtAction(RepeatForever::create(Animate::create(hurtAnimation)));

	Animation* deadAnimation = this->createAnimation("boy_dead_%02d.png",3,10);//创建死亡动画
	this->setDeadAction(Animate::create(deadAnimation));
}

void Hero::updateSelf(float)
{
	if(attackCD>0)attackCD--;
	if(skill1CD>0)skill1CD--;
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
			CCARRAY_FOREACH(myEnemies, it)//遍历敌人
			{
				myEnemy = (Enemy*)it;
				Vec2 distance = myEnemy->getPosition()-this->getPosition();
				if(!isFlipped)
				{
					if(distance.x<this->getAttackRange().x&&distance.x>0&&abs(distance.y)<this->getAttackRange().y)
					{	//判断敌人是否在攻击范围内
						myEnemy->changeState(HURT,attackHurtDelay);
						myEnemy->lostLife(attackDamage);
					}
				}
				else
				{
					if(distance.x>-this->getAttackRange().x&&distance.x<0&&abs(distance.y)<this->getAttackRange().y)
					{	//判断敌人是否在攻击范围内
						myEnemy->changeState(HURT,attackHurtDelay);
						myEnemy->lostLife(attackDamage);
					}
				}
			}
		}
		attackCD=10;
	}
	if(curState==SKILL1)
	{
		if(skill1CD<=0)
		{
			Ref* it;
			Enemy* myEnemy;
			CCARRAY_FOREACH(myEnemies, it)//遍历敌人
			{
				myEnemy = (Enemy*)it;
				Vec2 distance = myEnemy->getPosition()-this->getPosition();
				if(!isFlipped)
				{
					if(distance.x<this->getSkill1Range().x&&distance.x>-this->getSkill1RangeBack().x&&abs(distance.y)<this->getSkill1Range().y)
					{	//判断敌人是否在攻击范围内
						myEnemy->changeState(HURT,skill1HurtDelay);
						myEnemy->lostLife(attackDamage*skill1Ratio);
					}
				}
				else
				{
					if(distance.x>-this->getSkill1Range().x&&distance.x<this->getSkill1RangeBack().x&&abs(distance.y)<this->getSkill1Range().y)
					{	//判断敌人是否在攻击范围内
						myEnemy->changeState(HURT,skill1HurtDelay);
						myEnemy->lostLife(attackDamage*skill1Ratio);
					}
				}
			}
		}
		skill1CD=120;
	}
}

void Hero::connect()
{
	myMap = (TMXTiledMap*)this->getParent()->getParent()->getChildByTag(0)->getChildByTag(1)->getChildByTag(1);
	floor = myMap->getLayer("Floor");
	auto gamelayer = (GameLayer*)this->getParent()->getParent()->getChildByTag(0);
	myEnemies = gamelayer->getEnemies();
}