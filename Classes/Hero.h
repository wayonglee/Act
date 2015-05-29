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
	CC_SYNTHESIZE(float,attackDelay,AttackDelay);//����Ӳֱ
	CC_SYNTHESIZE(float,skillDelay1,SkillDelay1);//����1Ӳֱ
	CC_SYNTHESIZE(float,skillDelay2,SkillDelay2);//����2Ӳֱ
	CC_SYNTHESIZE(float,skillDelay3,SkillDelay3);//����3Ӳֱ
	CC_SYNTHESIZE(float,runningAttackDelay,RunningAttackDelay);
	CC_SYNTHESIZE(float,attackRoll,AttackRoll);//����ǰҡ
	CC_SYNTHESIZE(float,skillRoll1,SkillRoll1);//����1ǰҡ
	CC_SYNTHESIZE(float,skillRoll2,SkillRoll2);//����2ǰҡ
	CC_SYNTHESIZE(float,skillRoll3,SkillRoll3);//����2ǰҡ
	CC_SYNTHESIZE(float,runningAttackRoll,RunningAttackRoll);//����2ǰҡ
	CC_SYNTHESIZE(float,attackHurtDelay,AttackHurtDelay);//�˺�Ӳֱ
	CC_SYNTHESIZE(float,skillHurtDelay1,SkillHurtDelay1);//����1�˺�Ӳֱ
	CC_SYNTHESIZE(float,skillHurtDelay2,SkillHurtDelay2);//����2�˺�Ӳֱ
	CC_SYNTHESIZE(float,skillHurtDelay3,SkillHurtDelay3);//����2�˺�Ӳֱ
	CC_SYNTHESIZE(float,runningAttackHurtDelay,runningAttackHurtDelay);//����2�˺�Ӳֱ
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