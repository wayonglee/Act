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
	dataInit();

	this->runStayAction();
	
	this->schedule(schedule_selector(Hero::updateSelf));
	return true;
}

void Hero::addAnimate()
{
	Animation* stayAnimation = this->createAnimation("boy_idle_%02d.png",3,5);//创建停留动画
	this->setStayAction(RepeatForever::create(Animate::create(stayAnimation)));

    Animation* walkAnimation = this->createAnimation("boy_run_%02d.png",8,10);//创建移动动画
	this->setWalkAction(RepeatForever::create(Animate::create(walkAnimation)));

	Animation *attackAnimation1 = this->createAttackAnimation("boy_attack_00_%02d.png", 0, 3, 10);//创建攻击动画
	Animation *attackAnimation2 = this->createAttackAnimation("boy_attack_00_%02d.png", 3, 8, 10);
	this->setAttackAction(Sequence::create( Animate::create(attackAnimation1),Animate::create(attackAnimation2),NULL) );

	Animation *skillAnimation11 = this->createAttackAnimation("boy_attack_01_%02d.png", 0, 3, 10);//创建技能1动画
	Animation *skillAnimation12 = this->createAttackAnimation("boy_attack_01_%02d.png", 3, 8, 10);
	this->setSkillAction1(Sequence::create( Animate::create(skillAnimation11),Animate::create(skillAnimation12),NULL) );

	Animation *skillAnimation21 = this->createAttackAnimation("boy_attack_02_%02d.png", 0, 3, 10);//创建技能2动画
	Animation *skillAnimation22 = this->createAttackAnimation("boy_attack_02_%02d.png", 3, 6, 10);
	this->setSkillAction2(Sequence::create( Animate::create(skillAnimation21),Animate::create(skillAnimation22),NULL) );

	Animation *skillAnimation31 = this->createAttackAnimation("boy_change_attack_%02d.png", 0, 5, 10);//创建技能3动画
	Animation *skillAnimation32 = this->createAttackAnimation("boy_change_attack_%02d.png", 5, 12, 10);
	this->setSkillAction3(Sequence::create( Animate::create(skillAnimation31),Animate::create(skillAnimation32),NULL) );

	Animation *runningAttackAnimation1 = this->createAttackAnimation("boy_run_attack_%02d.png", 0, 4, 10);//创建跑动攻击动画
	Animation *runningAttackAnimation2 = this->createAttackAnimation("boy_run_attack_%02d.png", 4, 9, 10);
	this->setRunningAttackAction(Sequence::create( Animate::create(runningAttackAnimation1),Animate::create(runningAttackAnimation2),NULL) );

	Animation* hurtAnimation = this->createAnimation("boy_hurt_%02d.png",2,5);//创建受伤动画
	this->setHurtAction(RepeatForever::create(Animate::create(hurtAnimation)));

	Animation* deadAnimation = this->createAnimation("boy_dead_%02d.png",3,10);//创建死亡动画
	this->setDeadAction(Animate::create(deadAnimation));
}

void Hero::dataInit()
{
	setSpeed(3);//速度
	setAttackDamage(50.0f);//伤害
	setAttackRange(Vec2(100,25));//攻击前方范围
	setSkillRange1(Vec2(100,40));//技能前方范围
	setSkillRange2(Vec2(100,40));
	setSkillRange3(Vec2(120,50));
	setRunningAttackRange(Vec2(100,25));
	setAttackRangeBack(Vec2(5,25));//攻击后方范围
	setSkillRangeBack1(Vec2(40,40));//技能后方范围
	setSkillRangeBack2(Vec2(40,40));
	setSkillRangeBack3(Vec2(0,50));
	setRunningAttackRangeBack(Vec2(50,25));
	skillRatio1 = 1.1f;//技能伤害倍率
	skillRatio2 = 1.2f;
	skillRatio3 = 2.0f;
	setAttackCD(0);//设置CD
	setSkillCD1(0);
	setSkillCD2(0);
	setSkillCD3(0);
	setRunningAttackCD(0);
	setAttackDelay(0.8f);//设置硬直
	setSkillDelay1(0.8f);
	setSkillDelay2(0.6f);
	setSkillDelay3(1.2f);
	setRunningAttackDelay(0.9f);
	setAttackRoll(0.3f);//设置前摇
	setSkillRoll1(0.3f);
	setSkillRoll2(0.3f);
	setSkillRoll3(0.5f);
	setRunningAttackRoll(0.4f);
	setAttackHurtDelay(0.2f);//设置伤害硬直
	setSkillHurtDelay1(0.65f);
	setSkillHurtDelay2(0.65f);
	setSkillHurtDelay3(1.0f);
	setrunningAttackHurtDelay(0.2f);
}

void Hero::updateSelf(float)
{
	if(attackCD>0)attackCD--;
	if(skillCD1>0)skillCD1--;
	if(skillCD2>0)skillCD2--;
	if(skillCD3>0)skillCD3--;
	if(runningAttackCD>0)runningAttackCD--;
	if(curtLifeValue<=0)changeState(DEAD);
	if(curState == WALK ||curState == PRERUNNINGATTACK)//当在行走时
	{
		heroMove();
	}
	if(curState==ATTACK)//攻击时
	{
		attackJudge();
	}
	if(curState==SKILL1)//技能1时
	{
		skillJudge1();
	}
	if(curState==SKILL2)//技能1时
	{
		skillJudge2();
	}
	if(curState==SKILL3)
	{
		skillJudge3();
	}
	if(curState==RUNNINGATTACK)
	{
		runningAttackJudge();
	}
}

void Hero::heroMove()
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


void Hero::attackJudge()
{
	if(attackCD<=0)
		{
			Ref* it;
			Enemy* myEnemy;
			CCARRAY_FOREACH(myEnemies, it)//遍历敌人
			{
				myEnemy = (Enemy*)it;
				Vec2 distance = myEnemy->getPosition()-this->getPosition();
				if(!isFlipped)//面向右
				{
					if(distance.x<this->getAttackRange().x&&distance.x>-this->getAttackRangeBack().x&&abs(distance.y)<this->getAttackRange().y)
					{	//判断敌人是否在攻击范围内
						myEnemy->changeState(HURT,attackHurtDelay);
						myEnemy->lostLife(attackDamage);
					}
				}
				else
				{
					if(distance.x>-this->getAttackRange().x&&distance.x<this->getAttackRangeBack().x&&abs(distance.y)<this->getAttackRange().y)
					{	//判断敌人是否在攻击范围内
						myEnemy->changeState(HURT,attackHurtDelay);
						myEnemy->lostLife(attackDamage);
					}
				}
			}
		}
		attackCD=15;
}

void Hero::skillJudge1()
{
	if(skillCD1<=0)
		{
			Ref* it;
			Enemy* myEnemy;
			CCARRAY_FOREACH(myEnemies, it)//遍历敌人
			{
				myEnemy = (Enemy*)it;
				Vec2 distance = myEnemy->getPosition()-this->getPosition();
				if(!isFlipped)
				{
					if(distance.x<this->getSkillRange1().x&&distance.x>-this->getSkillRangeBack1().x&&abs(distance.y)<this->getSkillRange1().y)
					{	//判断敌人是否在攻击范围内
						myEnemy->changeState(HURT,skillHurtDelay1);
						myEnemy->lostLife(attackDamage*skillRatio1);
					}
				}
				else
				{
					if(distance.x>-this->getSkillRange1().x&&distance.x<this->getSkillRangeBack1().x&&abs(distance.y)<this->getSkillRange1().y)
					{	//判断敌人是否在攻击范围内
						myEnemy->changeState(HURT,skillHurtDelay1);
						myEnemy->lostLife(attackDamage*skillRatio1);
					}
				}
			}
		}
		skillCD1=120;
}

void Hero::skillJudge2()
{
	if(skillCD2<=0)
		{
			Ref* it;
			Enemy* myEnemy;
			CCARRAY_FOREACH(myEnemies, it)//遍历敌人
			{
				myEnemy = (Enemy*)it;
				Vec2 distance = myEnemy->getPosition()-this->getPosition();
				if(!isFlipped)
				{
					if(distance.x<this->getSkillRange2().x&&distance.x>-this->getSkillRangeBack2().x&&abs(distance.y)<this->getSkillRange2().y)
					{	//判断敌人是否在攻击范围内
						myEnemy->changeState(HURT,skillHurtDelay2);
						myEnemy->lostLife(attackDamage*skillRatio2);
					}
				}
				else
				{
					if(distance.x>-this->getSkillRange2().x&&distance.x<this->getSkillRangeBack2().x&&abs(distance.y)<this->getSkillRange2().y)
					{	//判断敌人是否在攻击范围内
						myEnemy->changeState(HURT,skillHurtDelay2);
						myEnemy->lostLife(attackDamage*skillRatio2);
					}
				}
			}
		}
		skillCD2=120;
}

void Hero::skillJudge3()
{
	if(skillCD3<=0)
		{
			Ref* it;
			Enemy* myEnemy;
			CCARRAY_FOREACH(myEnemies, it)//遍历敌人
			{
				myEnemy = (Enemy*)it;
				Vec2 distance = myEnemy->getPosition()-this->getPosition();
				if(!isFlipped)
				{
					if(distance.x<this->getSkillRange3().x&&distance.x>-this->getSkillRangeBack3().x&&abs(distance.y)<this->getSkillRange3().y)
					{	//判断敌人是否在攻击范围内
						myEnemy->changeState(HURT,skillHurtDelay3);
						myEnemy->lostLife(attackDamage*skillRatio3);
					}
				}
				else
				{
					if(distance.x>-this->getSkillRange3().x&&distance.x<this->getSkillRangeBack3().x&&abs(distance.y)<this->getSkillRange3().y)
					{	//判断敌人是否在攻击范围内
						myEnemy->changeState(HURT,skillHurtDelay3);
						myEnemy->lostLife(attackDamage*skillRatio3);
					}
				}
			}
		}
		skillCD3=240;
}

void Hero::runningAttackJudge()
{
	if(runningAttackCD<=0)
		{
			Ref* it;
			Enemy* myEnemy;
			CCARRAY_FOREACH(myEnemies, it)//遍历敌人
			{
				myEnemy = (Enemy*)it;
				Vec2 distance = myEnemy->getPosition()-this->getPosition();
				if(!isFlipped)
				{
					if(distance.x<this->getRunningAttackRange().x&&distance.x>-this->getRunningAttackRangeBack().x&&abs(distance.y)<this->getRunningAttackRange().y)
					{	//判断敌人是否在攻击范围内
						myEnemy->changeState(HURT,runningAttackHurtDelay);
						myEnemy->lostLife(attackDamage);
					}
				}
				else
				{
					if(distance.x>-this->getRunningAttackRange().x&&distance.x<this->getRunningAttackRangeBack().x&&abs(distance.y)<this->getRunningAttackRange().y)
					{	//判断敌人是否在攻击范围内
						myEnemy->changeState(HURT,runningAttackHurtDelay);
						myEnemy->lostLife(attackDamage);
					}
				}
			}
		}
		runningAttackCD=120;
}

void Hero::connect()
{
	myMap = (TMXTiledMap*)this->getParent()->getParent()->getChildByTag(0)->getChildByTag(1)->getChildByTag(1);
	floor = myMap->getLayer("Floor");
	auto gamelayer = (GameLayer*)this->getParent()->getParent()->getChildByTag(0);
	myEnemies = gamelayer->getEnemies();
}
