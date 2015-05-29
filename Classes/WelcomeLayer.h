#include "cocos2d.h"
#include "cocos-ext.h"
#include"GameScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

class WelcomeLayer :public LayerColor
{
private:
	Size visibleSize;
public:
	WelcomeLayer();
	~WelcomeLayer();
	CREATE_FUNC(WelcomeLayer);
	virtual bool init();
	void addBackgroundSprite();
	void addMenuSprite();
	void menuTouchDown(Ref* pSender, Control::EventType event);
	void playBackgroundMusic(float);

};