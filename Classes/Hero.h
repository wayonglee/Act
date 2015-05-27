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
	float skill1Ratio;
public:
	Hero(void);
	~Hero(void);
	CREATE_FUNC(Hero);
	CC_SYNTHESIZE(Vec2,attackRange,AttackRange);
	CC_SYNTHESIZE(Vec2,skill1Range,Skill1Range);
	CC_SYNTHESIZE(Vec2,skill1RangeBack,Skill1RangeBack);
	CC_SYNTHESIZE(int,attackCD,AttackCD);
	CC_SYNTHESIZE(int,skill1CD,Skill1CD);
	CC_SYNTHESIZE(float,attackDelay,AttackDelay);//¹¥»÷Ó²Ö±
	CC_SYNTHESIZE(float,attackRoll,AttackRoll);//¹¥»÷Ç°Ò¡
	CC_SYNTHESIZE(float,attackHurtDelay,AttackHurtDelay);//ÉËº¦Ó²Ö±
	CC_SYNTHESIZE(float,skill1Delay,skill1Delay);
	CC_SYNTHESIZE(float,skill1Roll,skill1Roll);
	CC_SYNTHESIZE(float,skill1HurtDelay,Skill1HurtDelay);
	virtual bool init();
	void addAnimate();
	void updateSelf(float);
	void connect();
};

#endif