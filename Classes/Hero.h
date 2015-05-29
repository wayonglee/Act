#ifndef _HERO_H_
#define _HERO_H_
#include"cocos2d.h"
#include"Role.h"

class Hero:public Role
{
private:
	TMXTiledMap* myMap;
	TMXLayer* floor;
	CCArray* myEnemies;
	float skillRatio1;
	float skillRatio2;
	float skillRatio3;
public:
	Hero(void);
	~Hero(void);
	CREATE_FUNC(Hero);
	CC_SYNTHESIZE(Vec2,attackRange,AttackRange);
	CC_SYNTHESIZE(Vec2,skillRange1,SkillRange1);
	CC_SYNTHESIZE(Vec2,skillRange2,SkillRange2);
	CC_SYNTHESIZE(Vec2,skillRange3,SkillRange3);
	CC_SYNTHESIZE(Vec2,runningAttackRange,RunningAttackRange);
	CC_SYNTHESIZE(Vec2,attackRangeBack,AttackRangeBack);
	CC_SYNTHESIZE(Vec2,skillRangeBack1,SkillRangeBack1);
	CC_SYNTHESIZE(Vec2,skillRangeBack2,SkillRangeBack2);
	CC_SYNTHESIZE(Vec2,skillRangeBack3,SkillRangeBack3);
	CC_SYNTHESIZE(Vec2,runningAttackRangeBack,RunningAttackRangeBack);
	CC_SYNTHESIZE(int,attackCD,AttackCD);//CD
	CC_SYNTHESIZE(int,skillCD1,SkillCD1);
	CC_SYNTHESIZE(int,skillCD2,SkillCD2);
	CC_SYNTHESIZE(int,skillCD3,SkillCD3);
	CC_SYNTHESIZE(int,runningAttackCD,RunningAttackCD);
	CC_SYNTHESIZE(float,attackDelay,AttackDelay);//攻击硬直
	CC_SYNTHESIZE(float,skillDelay1,SkillDelay1);//技能1硬直
	CC_SYNTHESIZE(float,skillDelay2,SkillDelay2);//技能2硬直
	CC_SYNTHESIZE(float,skillDelay3,SkillDelay3);//技能3硬直
	CC_SYNTHESIZE(float,runningAttackDelay,RunningAttackDelay);
	CC_SYNTHESIZE(float,attackRoll,AttackRoll);//攻击前摇
	CC_SYNTHESIZE(float,skillRoll1,SkillRoll1);//技能1前摇
	CC_SYNTHESIZE(float,skillRoll2,SkillRoll2);//技能2前摇
	CC_SYNTHESIZE(float,skillRoll3,SkillRoll3);//技能2前摇
	CC_SYNTHESIZE(float,runningAttackRoll,RunningAttackRoll);//技能2前摇
	CC_SYNTHESIZE(float,attackHurtDelay,AttackHurtDelay);//伤害硬直
	CC_SYNTHESIZE(float,skillHurtDelay1,SkillHurtDelay1);//技能1伤害硬直
	CC_SYNTHESIZE(float,skillHurtDelay2,SkillHurtDelay2);//技能2伤害硬直
	CC_SYNTHESIZE(float,skillHurtDelay3,SkillHurtDelay3);//技能2伤害硬直
	CC_SYNTHESIZE(float,runningAttackHurtDelay,runningAttackHurtDelay);//技能2伤害硬直
	virtual bool init();
	void addAnimate();
	void dataInit();
	void updateSelf(float);
	void heroMove();
	void heroRunningAttack();
	void attackJudge();
	void skillJudge1();
	void skillJudge2();
	void skillJudge3();
	void runningAttackJudge();
	void connect();
};

#endif