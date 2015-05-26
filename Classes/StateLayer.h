#ifndef _STATE_LAYER_H_
#define _STATE_LAYER_H_
#include"cocos2d.h"
#include"LifeShow.h"

class StateLayer:public cocos2d::Layer
{
private:
	LifeShow* lifeShow;
public:
	StateLayer(void);
	~StateLayer(void);
	CREATE_FUNC(StateLayer);
	virtual bool init();
};

#endif