#include"WelcomeLayer.h"
#include"SimpleAudioEngine.h"
#include"ChooseMapLayer.h"
using namespace CocosDenshion;



WelcomeLayer::WelcomeLayer()
{

}

WelcomeLayer::~WelcomeLayer()
{

}

bool WelcomeLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(Color4B::BLACK)))
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	addBackgroundSprite();
	addMenuSprite();

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("res/MenuMusic.mp3");

	return true;
}

void WelcomeLayer::addBackgroundSprite()
{
	auto menuLogo = Sprite::create("res/menuLogo.jpg");//创建logo精灵
	menuLogo->setPosition( Vec2( visibleSize.width / 2, visibleSize.height / 5 * 4 ) );
	menuLogo->setAnchorPoint(Vec2(0.5,0));
	menuLogo->setScale(0.6f);
	addChild(menuLogo);//添加logo
}

void WelcomeLayer::addMenuSprite()
{
	Scale9Sprite* btnNormal1 = Scale9Sprite::create("res/normal_menu.png"); 
	Scale9Sprite* btnPress1 = Scale9Sprite::create("res/press_menu.png");

	LabelTTF* singleGameTTF = LabelTTF::create("Single Game", "arial.ttf", 18);//创建菜单所需的Label对象
	ControlButton* singleGameBtn = ControlButton::create(singleGameTTF, btnNormal1);//创建controlButton
	singleGameBtn->setBackgroundSpriteForState(btnPress1, Control::State::HIGH_LIGHTED);//添加singleButton菜单的press效果图片
	singleGameBtn->setPosition(Vec2( visibleSize.width / 2, visibleSize.height - 100));//设置位置
	singleGameBtn->setPreferredSize(Size(150, 40));//设置大小
	singleGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(WelcomeLayer::menuTouchDown), Control::EventType::TOUCH_UP_INSIDE);//设置点击回调方法
	singleGameBtn->setTag(1);//设置Tag
	addChild(singleGameBtn);//添加单人游戏按钮


	Scale9Sprite* btnNormal2 = Scale9Sprite::create("res/normal_menu.png"); 
	Scale9Sprite* btnPress2 = Scale9Sprite::create("res/press_menu.png");
	LabelTTF* multiGameTTF = LabelTTF::create("Multi Game", "arial.ttf", 18);//创建菜单所需的Label对象
	ControlButton* multiGameBtn = ControlButton::create(multiGameTTF, btnNormal2);//创建controlButton
	multiGameBtn->setBackgroundSpriteForState(btnPress2, Control::State::HIGH_LIGHTED);//添加singleButton菜单的press效果图片
	multiGameBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 150));//设置位置
	multiGameBtn->setPreferredSize(Size(150, 40));//设置大小
	multiGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(WelcomeLayer::menuTouchDown), Control::EventType::TOUCH_UP_INSIDE);//设置点击回调方法
	multiGameBtn->setTag(2);//设置Tag
	addChild(multiGameBtn);//添加多人游戏按钮


	Scale9Sprite* btnNormal3 = Scale9Sprite::create("res/normal_menu.png"); 
	Scale9Sprite* btnPress3 = Scale9Sprite::create("res/press_menu.png");

	if (UserDefault::getInstance()->getBoolForKey("isExit", false) == false)
		
	{
		UserDefault::getInstance()->setBoolForKey("isExit", true);
	}

	bool music_on = UserDefault::getInstance()->getBoolForKey("music_key",true);//获取音效设置
	LabelTTF* musicTTF;
	if (music_on)
	{
		musicTTF = LabelTTF::create("Music On", "arial.ttf", 18);
		SimpleAudioEngine::getInstance()->playBackgroundMusic("res/MenuMusic.mp3");
		//this->scheduleOnce(schedule_selector(WelcomeLayer::playBackgroundMusic),1.0f);
	}
	else
	{
		musicTTF = LabelTTF::create("Music Off", "arial.ttf", 18);
	}

	ControlButton* musicBtn = ControlButton::create(musicTTF, btnNormal3);//创建controlButton
	musicBtn->setBackgroundSpriteForState(btnPress3, Control::State::HIGH_LIGHTED);//添加singleButton菜单的press效果图片
	musicBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 200));//设置位置
	musicBtn->setPreferredSize(Size(150, 40));//设置大小
	musicBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(WelcomeLayer::menuTouchDown), Control::EventType::TOUCH_UP_INSIDE);//设置点击回调方法
	musicBtn->setTag(3);//设置Tag
	addChild(musicBtn);//添加添加音乐按钮


	Scale9Sprite* btnNormal4 = Scale9Sprite::create("res/normal_menu.png");
	Scale9Sprite* btnPress4 = Scale9Sprite::create("res/press_menu.png");
	LabelTTF* quitGameTTF = LabelTTF::create("Quit Game", "arial.ttf", 18);//创建菜单所需的Label对象
	ControlButton* quitGameBtn = ControlButton::create(quitGameTTF, btnNormal4);//创建controlButton
	quitGameBtn->setBackgroundSpriteForState(btnPress4, Control::State::HIGH_LIGHTED);//添加singleButton菜单的press效果图片
	quitGameBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 250));//设置位置
	quitGameBtn->setPreferredSize(Size(150, 40));//设置大小
	quitGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(WelcomeLayer::menuTouchDown), Control::EventType::TOUCH_UP_INSIDE);//设置点击回调方法
	quitGameBtn->setTag(4);//设置Tag
	addChild(quitGameBtn);//添加退出按钮

}

void WelcomeLayer::menuTouchDown(Ref* pSender, Control::EventType event)
{
	log("single touched");
	ControlButton* button = (ControlButton*)pSender;
	int tag = button->getTag();
	switch (tag)
	{
	case 1:
	{
		log("single game");
		SimpleAudioEngine::getInstance()->stopBackgroundMusic("res/MenuMusic.mp3");
		/*auto scene = GameScene::create();
		Director::getInstance()->pushScene(scene);
		scene->connect();*/
		this->addChild(ChooseMapLayer::create());
	}

	case 2:
	{
		log("multi game");
		break;
	}

	case 3:
	{
		bool music_on = UserDefault::getInstance()->getBoolForKey("music_key", true);

		if (music_on)
		{
			UserDefault::getInstance()->setBoolForKey("music_key", false);//设置音效关
			button->setTitleForState("Music Off", Control::State::NORMAL);//让menu文字显示off
			UserDefault::getInstance()->flush();
			SimpleAudioEngine::getInstance()->stopBackgroundMusic("res/MenuMusic.mp3");
		}
		else
		{
			UserDefault::getInstance()->setBoolForKey("music_key", true);//设置音效开
			button->setTitleForState("Music On", Control::State::NORMAL);// 让menu文字显示on
			UserDefault::getInstance()->flush();
			SimpleAudioEngine::getInstance()->playBackgroundMusic("res/MenuMusic.mp3");
		}

		break;
	}
	case 4:
	{
		log("quit game");
		Director::getInstance()->end();
		break;
	}
	default:
		break;
	}
}

void WelcomeLayer::playBackgroundMusic(float)
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("res/MenuMusic.mp3");
}