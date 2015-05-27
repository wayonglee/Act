#ifndef _ROLE_H_
#define _ROLE_H_
#include"cocos2d.h"

USING_NS_CC;
enum RoleState
{
	STAY,
	WALK,
	PREATTACK,
	PRESKILL1,
	ATTACK,
	SKILL1,
	HURT,
	DEAD
};

class Role:public Sprite
{
public:
	Role(void);
	~Role(void);
	CREATE_FUNC(Role);
	CC_SYNTHESIZE(RoleState,curState,CurState);
	CC_SYNTHESIZE(bool,stateChangeable,StateChangeable);
	CC_SYNTHESIZE(bool,stateBreakable,StateBreakable);
	CC_SYNTHESIZE(std::string,name,Name);//角色名
	CC_SYNTHESIZE(float,curtLifeValue,CurtLifeValue);//角色血
	CC_SYNTHESIZE(float,sumLifeValue,SumLifeValue);//总血
	CC_SYNTHESIZE(float,attackDamage,AttackDamage);//攻击力
	CC_SYNTHESIZE(float,speed,Speed);//速度
	CC_SYNTHESIZE(Vec2,direction,Direction);//移动方向
	CC_SYNTHESIZE(bool,isFlipped,IsFlipped);//是否反转
	CC_SYNTHESIZE_RETAIN(Action*, stayAction, StayAction);//停留动画
    CC_SYNTHESIZE_RETAIN(Action*, walkAction, WalkAction);//移动动画
	CC_SYNTHESIZE_RETAIN(Action*, attackAction, AttackAction);//攻击动画
	CC_SYNTHESIZE_RETAIN(Action*, skill1Action, Skill1Action);//技能动画1
	CC_SYNTHESIZE_RETAIN(Action*, hurtAction, HurtAction);//受伤动画
	CC_SYNTHESIZE_RETAIN(Action*, deadAction, DeadAction);//死亡动画
	void runStayAction();
	void runWalkAction();
	void runAttackAction();
	void runSkill1Action();
	void runHurtAction();
	void runDeadAction();
	Animation* createAnimation(const char*,int frameSize,int fps);
	Animation* createAttackAnimation(const char*,int beginFrame,int endFrame,int fps);
	void move(Vec2 direction,bool isFlipped);
	bool changeState(RoleState,float delay = 0,float roll = 0);
	void attack(float roll,float delay);//攻击函数
	void attackBegin(float);
	void attackFinish(float);
	void skill1(float roll,float delay);//技能函数
	void skill1Begin(float);
	void skill1Finish(float);
	void hurt(float delay);//伤害函数
	void hurtFinish(float);
	void lostLife(float damage);
};

#endif