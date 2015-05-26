#ifndef _OPERATE_LAYER_H_
#define _OPERATE_LAYER_H_
#include"cocos2d.h"
#include"JoyStick.h"

class Hero;

class OperateLayer:public cocos2d::Layer
{
private:
	Hero* myHero;
	bool first;
public:
	OperateLayer(void);
	~OperateLayer(void);
	CREATE_FUNC(OperateLayer);
	virtual bool init();
	void addAttckMenu();
	void attackButton(Ref* pSender);
	void connect();
};

#endif