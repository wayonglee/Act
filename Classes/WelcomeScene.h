#include "cocos2d.h"
#include"WelcomeLayer.h"

USING_NS_CC;

class WelcomeScene:public Scene
{
public:
	WelcomeScene();
	~WelcomeScene();
	CREATE_FUNC(WelcomeScene);
	virtual bool init();
};