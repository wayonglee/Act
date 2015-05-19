#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_
#include"cocos2d.h"

USING_NS_CC;

class Hero;
class Enemy;

class GameLayer:public cocos2d::Layer
{
private:
	Hero* hero;
	Enemy* enemy;
public:
	GameLayer(void);
	~GameLayer(void);
	CREATE_FUNC(GameLayer);
	virtual bool init();
};

#endif