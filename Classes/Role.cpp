#include "Role.h"
#include "DamageShow.h"
#include<sstream>

using namespace std;

Role::Role(void):
	stayAction(NULL),
	walkAction(NULL),
	attackAction(NULL),
	hurtAction(NULL),
	deadAction(NULL),
	curState(STAY),
	stateChangeable(true),
	stateBreakable(true),
	direction(Vec2(0,0)),
	isFlipped(false),
	speed(1),
	curtLifeValue(100.0f),
	sumLifeValue(100.0f),
	attackDamage(5.0f)
{
	
}


Role::~Role(void)
{
	CC_SAFE_RELEASE_NULL(stayAction);
	CC_SAFE_RELEASE_NULL(walkAction);
	CC_SAFE_RELEASE_NULL(attackAction);
	CC_SAFE_RELEASE_NULL(hurtAction);
	CC_SAFE_RELEASE_NULL(deadAction);
}

void Role::runStayAction()
{
	this->runAction(stayAction);
}

void Role::runWalkAction()
{
	this->runAction(walkAction);
}

void Role::runAttackAction()
{
	this->runAction(attackAction);
}

void Role::runHurtAction()
{
	this->runAction(hurtAction);
}

void Role::runDeadAction()
{
	this->runAction(deadAction);
}

Animation* Role::createAnimation(const char* formatStr,int frameSize,int fps)
{
	Vector<SpriteFrame*> pFrames;
	for(int i=0;i<frameSize;i++)
	{
		const char* frameName = String::createWithFormat(formatStr,i)->getCString();
		SpriteFrame* pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
		pFrames.insert(i,pFrame);
	}
	return Animation::createWithSpriteFrames(pFrames, 1.0f / fps);
}

Animation* Role::createAttackAnimation(const char* formatStr,int beginFrame,int endFrame,int fps)
{
	Vector<SpriteFrame*> pFrames;
	for(int i=beginFrame;i<endFrame;i++)
	{
		const char* frameName = String::createWithFormat(formatStr,i)->getCString();
		SpriteFrame* pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
		pFrames.insert(i-beginFrame,pFrame);
	}
	return Animation::createWithSpriteFrames(pFrames, 1.0f / fps);
}

void Role::move(Vec2 dir , bool isFlipped)
{
	if(curState==WALK)
	{
		this->setFlippedX(isFlipped);
		Vec2 destdir = Vec2(dir.x*speed,dir.y*speed);
		this->runAction(MoveBy::create(1/60,destdir));
	}
}

bool Role::changeState(RoleState state,float delay,float roll,float damage)
{
	if(curState!=DEAD)
	{
		if( (stateChangeable&&curState!=state) || (state==HURT&&stateBreakable))
		{
			stopAllActions();
			//this->unscheduleAllSelectors();
			switch(state)
			{
				case STAY: stateChangeable = true; stateBreakable = true; this->runStayAction(); break;
				case WALK: stateChangeable = true; stateBreakable = true; this->runWalkAction(); direction = Vec2(0,0); break;
				case PREATTACK: stateChangeable = false; stateBreakable = true; this->attack(roll,delay); break;
				case HURT: stateChangeable = false; stateBreakable = false; this->hurt(delay); lostLife(damage);break;
				case DEAD: stateChangeable = false; stateBreakable = false; this->runDeadAction(); break;
			}
			curState = state;
			return true;
		}
	}
	return false;
}

void Role::attack(float roll,float delay)
{
	runAttackAction();
	this->scheduleOnce(schedule_selector(Role::attackBegin),roll);
	this->scheduleOnce(schedule_selector(Role::attackFinish),delay);
}

void Role::attackBegin(float)
{
	if(curState==PREATTACK)
	{
		stateBreakable = false;
		this->setCurState(ATTACK);
	}
}

void Role::attackFinish(float)
{
	stateChangeable = true;
	changeState(STAY);
}

void Role::hurt(float delay)
{
	runHurtAction();
	this->scheduleOnce(schedule_selector(Role::hurtFinish),delay);
}

void Role::hurtFinish(float)
{
	if(curState==HURT)
	{
		stateChangeable = true;
		stateBreakable = true;
		changeState(STAY);
	}
}

void Role::lostLife(float damage)
{
	curtLifeValue -= damage;
	string damageString;
	ostringstream oss;
	oss<<damage;
	damageString = oss.str();
	LabelTTF* damageShow = LabelTTF::create(damageString, "Arial", 18);
	damageShow->setColor(Color3B::RED);
	damageShow->setPosition(this->getPosition().x,this->getPosition().y+70);
	this->getParent()->addChild(damageShow,1000);
	damageShow->runAction(MoveBy::create(0.5f,Vec2(0,30)));
	damageShow->scheduleOnce(schedule_selector(DamageShow::removeSelf),0.7f);
}

