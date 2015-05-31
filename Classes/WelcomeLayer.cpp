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
	auto menuLogo = Sprite::create("res/menuLogo.jpg");//����logo����
	menuLogo->setPosition( Vec2( visibleSize.width / 2, visibleSize.height / 5 * 4 ) );
	menuLogo->setAnchorPoint(Vec2(0.5,0));
	menuLogo->setScale(0.6f);
	addChild(menuLogo);//���logo
}

void WelcomeLayer::addMenuSprite()
{
	Scale9Sprite* btnNormal1 = Scale9Sprite::create("res/normal_menu.png"); 
	Scale9Sprite* btnPress1 = Scale9Sprite::create("res/press_menu.png");

	LabelTTF* singleGameTTF = LabelTTF::create("Single Game", "arial.ttf", 18);//�����˵������Label����
	ControlButton* singleGameBtn = ControlButton::create(singleGameTTF, btnNormal1);//����controlButton
	singleGameBtn->setBackgroundSpriteForState(btnPress1, Control::State::HIGH_LIGHTED);//���singleButton�˵���pressЧ��ͼƬ
	singleGameBtn->setPosition(Vec2( visibleSize.width / 2, visibleSize.height - 100));//����λ��
	singleGameBtn->setPreferredSize(Size(150, 40));//���ô�С
	singleGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(WelcomeLayer::menuTouchDown), Control::EventType::TOUCH_UP_INSIDE);//���õ���ص�����
	singleGameBtn->setTag(1);//����Tag
	addChild(singleGameBtn);//��ӵ�����Ϸ��ť


	Scale9Sprite* btnNormal2 = Scale9Sprite::create("res/normal_menu.png"); 
	Scale9Sprite* btnPress2 = Scale9Sprite::create("res/press_menu.png");
	LabelTTF* multiGameTTF = LabelTTF::create("Multi Game", "arial.ttf", 18);//�����˵������Label����
	ControlButton* multiGameBtn = ControlButton::create(multiGameTTF, btnNormal2);//����controlButton
	multiGameBtn->setBackgroundSpriteForState(btnPress2, Control::State::HIGH_LIGHTED);//���singleButton�˵���pressЧ��ͼƬ
	multiGameBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 150));//����λ��
	multiGameBtn->setPreferredSize(Size(150, 40));//���ô�С
	multiGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(WelcomeLayer::menuTouchDown), Control::EventType::TOUCH_UP_INSIDE);//���õ���ص�����
	multiGameBtn->setTag(2);//����Tag
	addChild(multiGameBtn);//��Ӷ�����Ϸ��ť


	Scale9Sprite* btnNormal3 = Scale9Sprite::create("res/normal_menu.png"); 
	Scale9Sprite* btnPress3 = Scale9Sprite::create("res/press_menu.png");

	if (UserDefault::getInstance()->getBoolForKey("isExit", false) == false)
		
	{
		UserDefault::getInstance()->setBoolForKey("isExit", true);
	}

	bool music_on = UserDefault::getInstance()->getBoolForKey("music_key",true);//��ȡ��Ч����
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

	ControlButton* musicBtn = ControlButton::create(musicTTF, btnNormal3);//����controlButton
	musicBtn->setBackgroundSpriteForState(btnPress3, Control::State::HIGH_LIGHTED);//���singleButton�˵���pressЧ��ͼƬ
	musicBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 200));//����λ��
	musicBtn->setPreferredSize(Size(150, 40));//���ô�С
	musicBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(WelcomeLayer::menuTouchDown), Control::EventType::TOUCH_UP_INSIDE);//���õ���ص�����
	musicBtn->setTag(3);//����Tag
	addChild(musicBtn);//���������ְ�ť


	Scale9Sprite* btnNormal4 = Scale9Sprite::create("res/normal_menu.png");
	Scale9Sprite* btnPress4 = Scale9Sprite::create("res/press_menu.png");
	LabelTTF* quitGameTTF = LabelTTF::create("Quit Game", "arial.ttf", 18);//�����˵������Label����
	ControlButton* quitGameBtn = ControlButton::create(quitGameTTF, btnNormal4);//����controlButton
	quitGameBtn->setBackgroundSpriteForState(btnPress4, Control::State::HIGH_LIGHTED);//���singleButton�˵���pressЧ��ͼƬ
	quitGameBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 250));//����λ��
	quitGameBtn->setPreferredSize(Size(150, 40));//���ô�С
	quitGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(WelcomeLayer::menuTouchDown), Control::EventType::TOUCH_UP_INSIDE);//���õ���ص�����
	quitGameBtn->setTag(4);//����Tag
	addChild(quitGameBtn);//����˳���ť

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
			UserDefault::getInstance()->setBoolForKey("music_key", false);//������Ч��
			button->setTitleForState("Music Off", Control::State::NORMAL);//��menu������ʾoff
			UserDefault::getInstance()->flush();
			SimpleAudioEngine::getInstance()->stopBackgroundMusic("res/MenuMusic.mp3");
		}
		else
		{
			UserDefault::getInstance()->setBoolForKey("music_key", true);//������Ч��
			button->setTitleForState("Music On", Control::State::NORMAL);// ��menu������ʾon
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