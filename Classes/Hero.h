#ifndef _HERO_H_
#define _HERO_H_
#include"cocos2d.h"
#include"Role.h"
#include"Enemy.h"

class Hero:public Role
{
private:
	TMXTiledMap* myMap;
	TMXLayer* floor;
	Enemy* myEnemy;
public:
	Hero(void);
	~Hero(void);
	CREATE_FUNC(Hero);
	CC_SYNTHESIZE(Vec2,attackRange,AttackRange);
	virtual bool init();
	void addAnimate();
	void updateSelf(float);
	void moveMap(float);
	void connect();
};

#endif