#include "ChooseMapLayer.h"

ChooseMapLayer::ChooseMapLayer()
{
}


ChooseMapLayer::~ChooseMapLayer()
{
}

bool ChooseMapLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}


	CurPage = 1;
	visibleSize = Director::getInstance()->getVisibleSize();

	addBackgroundSprite();
	addScrollView();
	//setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(ChooseMapLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(ChooseMapLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(ChooseMapLayer::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(ChooseMapLayer::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
}

void ChooseMapLayer::addBackgroundSprite()
{
	Sprite* backgroundSprite = Sprite::create("res/stage_background2.png");
	backgroundSprite->setScale(1.0);
	backgroundSprite->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	this->addChild(backgroundSprite, 0,1);
}

void ChooseMapLayer::addScrollView()
{
	scrollLayer = Layer::create();

	//Sprite* sprite;
	stage.pushBack( Sprite::create("res/stage1.png") );
	stage.at(0)->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	stage.at(0)->setScale(0.5);
	scrollLayer->addChild(stage.at(0), 2); 
	stage.pushBack( Sprite::create("res/stage2.png") );
	stage.at(1)->setPosition(Vec2(visibleSize.width / 2 * 3, visibleSize.height / 2));
	stage.at(1)->setScale(0.5);
	scrollLayer->addChild(stage.at(1), 2);
	stage.pushBack( Sprite::create("res/stage3.png") );
	stage.at(2)->setPosition(Vec2(visibleSize.width / 2 * 5, visibleSize.height / 2));
	stage.at(2)->setScale(0.5);
	scrollLayer->addChild(stage.at(2), 2);

	scrollView = ScrollView::create(visibleSize, scrollLayer);
	scrollView->setContentOffset(Vec2(0, 0));
	scrollView->setDelegate(this);
	scrollView->setBounceable(false);
	scrollView->setTouchEnabled(false);
	scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	scrollLayer->setContentSize(Size(visibleSize.width * 3, visibleSize.height));
	addChild(scrollView,1,2);
}


void ChooseMapLayer::scrollViewDidScroll(ScrollView* view)
{

}

bool ChooseMapLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	touchPoint = pTouch->getLocation();
	return true;
}

void ChooseMapLayer::onTouchMoved(Touch *pTouch, Event *pEvent)
{

}

void ChooseMapLayer::onTouchEnded(Touch *pTouch, Event *pEvent)
{

	Point endPoint = pTouch->getLocation();
	float offSet = endPoint.x - touchPoint.x;
	auto curStage = stage.at(CurPage-1);
	if (abs(offSet) > 5)
	{
		adjustScrollView(offSet);
	}
	else
	{
		scrollView->setContentOffset(Vec2(-visibleSize.width*(CurPage - 1), 0), true);
	}
	if (abs(touchPoint.x - curStage->getPosition().x) < curStage->getContentSize().width / 2 &&
		abs(touchPoint.y - curStage->getPosition().y) < curStage->getContentSize().height / 2 &&
		abs(offSet) <= 5)
	{
		auto scene = GameScene::create();
		Director::getInstance()->pushScene(scene);
		scene->connect();
	}
	
}

void ChooseMapLayer::adjustScrollView(float offSet)
{
	if (offSet < 0)
	{
		CurPage++; 
	}
	else
	{
		CurPage--;
	}
	if (CurPage < 1)
	{
		CurPage = 1;
	}
	if (CurPage > 3)
	{
		CurPage = 3;
	}
	scrollView->setContentOffset(Vec2(-visibleSize.width*(CurPage - 1), 0), true);
}