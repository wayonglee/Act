#ifndef _STATE_LAYER_H_
#define _STATE_LAYER_H_
#include"cocos2d.h"

class StateLayer:public cocos2d::Layer
{
public:
	StateLayer(void);
	~StateLayer(void);
	CREATE_FUNC(StateLayer);
	virtual bool init();
};

#endif