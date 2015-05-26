#ifndef _LIFE_SHOW_H_
#define _LIFE_SHOW_H_

#include"cocos2d.h"
#include"Hero.h"

class LifeShow:public cocos2d::Sprite
{
private:
	cocos2d::Sprite* life;
	cocos2d::Sprite* lifeBackground;
	Hero* myHero;
public:
	LifeShow(void);
	~LifeShow(void);
	CREATE_FUNC(LifeShow);
	virtual bool init();
	void connect();
	void updateSelf(float);
};

#endif