#ifndef _MAP_LAYER_H_
#define _MAP_LAYER_H_
#include"cocos2d.h"

class MapLayer:public cocos2d::Layer
{
public:
	MapLayer(void);
	~MapLayer(void);
	CREATE_FUNC(MapLayer);
	virtual bool init();
};

#endif