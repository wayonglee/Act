#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_
#include"cocos2d.h"

class GameScene:public cocos2d::Scene
{
public:
	GameScene(void);
	~GameScene(void);
	CREATE_FUNC(GameScene);
	virtual bool init();
};

#endif