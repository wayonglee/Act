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
public:
	Hero(void);
	~Hero(void);
	CREATE_FUNC(Hero);
	CC_SYNTHESIZE(Vec2,attackRange,AttackRange);
	CC_SYNTHESIZE(int,attackCD,AttackCD);
	virtual bool init();
	void addAnimate();
	void updateSelf(float);
	void connect();
};

#endif