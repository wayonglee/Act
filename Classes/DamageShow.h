#ifndef _DAMAGE_SHOW_H_
#define _DAMAGE_SHOW_H_

#include"cocos2d.h"

class DamageShow:public cocos2d::LabelTTF
{
public:
	DamageShow(void);
	~DamageShow(void);
	CREATE_FUNC(DamageShow);
	virtual bool init();
	void removeSelf(float);
};

#endif