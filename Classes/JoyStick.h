#ifndef _JOY_STICK_H_
#define _JOY_STICK_H_

#include"cocos2d.h"

USING_NS_CC;

class Hero;
class MapLayer;

class JoyStick:public Sprite
{
private:
	Sprite* joyStickBackground;
	Sprite* joyStick;
	Hero* myHero;
	TMXTiledMap* myMap;
	TMXLayer* floor;
	bool isW;
	bool first;
	Vec2 stickPosition;
	Vec2 direction;
public:
	JoyStick(void);
	~JoyStick(void);
	CREATE_FUNC(JoyStick);
	virtual bool init();
	void setStick();
	void addEventListener();
	void connect();
	virtual void onTouchesBegan(const std::vector<Touch*>& touches,Event* pEvent);
	virtual void onTouchesMoved(const std::vector<Touch*>& touches,Event* pEvent);
	virtual void onTouchesEnded(const std::vector<Touch*>& touches,Event* pEvent);
	Vec2 calculateJoyStickLocation(Vec2 touchPoint);
	void showJoyStick();
	void hideJoyStick();
	void updateMove(float);
};

#endif