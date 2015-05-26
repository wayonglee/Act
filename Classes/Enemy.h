#ifndef _ENEMY_H_
#define _ENEMY_H_
#include"cocos2d.h"
#include"Role.h"

class Hero;

enum EnemyState
{
	ENEMY_STAY,
	ENEMY_CHASE,
	ENEMY_ATTACK
};

class Enemy:public Role
{
private:
	Hero* myHero;
	int attackCD;
	CCArray* myEnemies;
public:
	CC_SYNTHESIZE(EnemyState,enemyCurState,EnemyCurState);
	CC_SYNTHESIZE(Vec2,sightRange,SightRange);
	CC_SYNTHESIZE(Vec2,attackRange,AttackRange);
	Enemy(void);
	~Enemy(void);
	CREATE_FUNC(Enemy);
	virtual bool init();
	void addAnimate();
	void updateSelf(float);
	void connect();
	//void changeEnemyState(EnemyState);
	void getChaseDirection();
	void deleteSelf(float);
};

#endif