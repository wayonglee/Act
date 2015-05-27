#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_
#include"cocos2d.h"
#include"Hero.h"
#include"Enemy.h"

USING_NS_CC;

class GameLayer:public cocos2d::Layer
{
private:
	Hero* hero;
	CCArray* enemies;
	LabelTTF* enemyKilled;
	LabelTTF* enemyAlive;
public:
	int enemyKilledNumber;
	GameLayer(void);
	~GameLayer(void);
	CREATE_FUNC(GameLayer);
	virtual bool init();
	CCArray* getEnemies();
	void addEnemy(float);
	void addKilledCount();
	void addEnemyCount();
	void killed();
	void updateSelf(float);
};

#endif