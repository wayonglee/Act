#ifndef _ROLE_H_
#define _ROLE_H_
#include"cocos2d.h"

USING_NS_CC;
enum RoleState
{
	STAY,
	WALK,
	PREATTACK,
	PRESKILL,
	PRERUNNINGATTACK,
	ATTACK,
	SKILL1,
	SKILL2,
	SKILL3,
	RUNNINGATTACK,
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
	CC_SYNTHESIZE_RETAIN(Action*, skillAction1, SkillAction1);//技能1动画
	CC_SYNTHESIZE_RETAIN(Action*, skillAction2, SkillAction2);//技能2动画
	CC_SYNTHESIZE_RETAIN(Action*, skillAction3, SkillAction3);//技能3动画
	CC_SYNTHESIZE_RETAIN(Action*, runningAttackAction, RunningAttackAction);//跑步攻击动画
	CC_SYNTHESIZE_RETAIN(Action*, hurtAction, HurtAction);//受伤动画
	CC_SYNTHESIZE_RETAIN(Action*, deadAction, DeadAction);//死亡动画
	void runStayAction();
	void runWalkAction();
	void runAttackAction();
	void runSkillAction(int skill);
	void runRunningAttackAction();
	void runHurtAction();
	void runDeadAction();
	Animation* createAnimation(const char*,int frameSize,int fps);
	Animation* createAttackAnimation(const char*,int beginFrame,int endFrame,int fps);
	void move(Vec2 direction,bool isFlipped);
	bool changeState(RoleState,float delay = 0,float roll = 0,int skill = 0);
	void attack(float delay,float roll);//攻击函数
	void attackBegin(float);
	void attackFinish(float);
	void skill(float delay,float roll,int skill);//技能1函数
	void skillBegin1(float);
	void skillBegin2(float);
	void skillBegin3(float);
	void skillFinish(float);
	void runningAttack(float delay,float roll);
	void runningAttackBegin(float);
	void runningAttackFinish(float);
	void hurt(float delay);//伤害函数
	void hurtFinish(float);
	void lostLife(float damage);
};

#endif