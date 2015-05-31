#include "cocos2d.h"
#include"cocos-ext.h"
#include"GameScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ChooseMapLayer : public Layer, public ScrollViewDelegate
{
private:
	Size visibleSize;
	Layer* scrollLayer;
	Vector<Sprite*> stage;
	void adjustScrollView(float offset);
	ScrollView* scrollView;
	Point touchPoint;
	int CurPage;
	EventListenerTouchOneByOne* touchListener;
public:
	ChooseMapLayer();
	~ChooseMapLayer();
	virtual bool init();
	CREATE_FUNC(ChooseMapLayer);
	void addBackgroundSprite();
	void addScrollView();
	void scrollViewDidScroll(ScrollView* view);//scrollview滚动的时候会调用
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
};