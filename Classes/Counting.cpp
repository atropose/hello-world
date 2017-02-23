#include "Counting.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

#define NOSELECT	-1
#define SCISSOR	0
#define ROCK 1
#define PAPER 2

int g_userselect;


Scene* Counting::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Counting::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Counting::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    /////////////////////////////
    // 3. add your codes below...
	statusLabel = LabelTTF::create("", "fonts/Marker Felt.ttf", 40);
	statusLabel->setColor(Color3B::WHITE);
	statusLabel->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	statusLabel->setVisible(true);
	addChild(statusLabel);

	statusLabel2 = LabelTTF::create("Pick one of below within 4 seconds.\nOtherwise I'll pick one.", "fonts/Marker Felt.ttf", 17);
	statusLabel2->setColor(Color3B::WHITE);
	statusLabel2->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3));
	statusLabel2->setVisible(true);
	addChild(statusLabel2);

    // add a label shows "Hello World"
    // create and initialize a label

	auto texture = Director::getInstance()->getTextureCache()->addImage("Images/main_small.png");
	spScissor = Sprite::createWithTexture(texture, Rect(0, 0, 40, 41));
	spRock = Sprite::createWithTexture(texture, Rect(40, 0, 44, 41));
	spPaper = Sprite::createWithTexture(texture, Rect(84, 0, 44, 41));

	auto scissor = MenuItemSprite::create(spScissor, spScissor, CC_CALLBACK_1(Counting::menuScissor, this));
	auto rock = MenuItemSprite::create(spRock, spRock, CC_CALLBACK_1(Counting::menuRock, this));
	auto paper = MenuItemSprite::create(spPaper, spPaper, CC_CALLBACK_1(Counting::menuPaper, this));

	menuStart = Menu::create(scissor, rock, paper, NULL);
	menuStart->alignItemsHorizontallyWithPadding(10);
	menuStart->setAnchorPoint(Point(0, 0));
	menuStart->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 5));
	this->addChild(menuStart);
    
	/////////////////////

	auto texture2 = Director::getInstance()->getTextureCache()->addImage("Images/main04.png");
	spScissorUser = Sprite::createWithTexture(texture2, Rect(0, 0, 200, 290));
	spRockUser = Sprite::createWithTexture(texture2, Rect(200, 0, 220, 290));
	spPaperUser = Sprite::createWithTexture(texture2, Rect(420, 0, 220, 290));
	spScissorUser->setAnchorPoint(Point(0.5, 0));
	spRockUser->setAnchorPoint(Point(0.5, 0));
	spPaperUser->setAnchorPoint(Point(0.5, 0));
	spScissorUser->setPosition(Point(origin.x + visibleSize.width / 2, 0));
	spRockUser->setPosition(Point(origin.x + visibleSize.width / 2, 0));
	spPaperUser->setPosition(Point(origin.x + visibleSize.width / 2, 0));
	this->addChild(spScissorUser);
	this->addChild(spRockUser);
	this->addChild(spPaperUser);
	spScissorUser->setVisible(false);
	spRockUser->setVisible(false);
	spPaperUser->setVisible(false);

	spScissorCom = Sprite::createWithTexture(texture2, Rect(0, 0, 200, 290));
	spRockCom = Sprite::createWithTexture(texture2, Rect(200, 0, 220, 290));
	spPaperCom = Sprite::createWithTexture(texture2, Rect(420, 0, 220, 290));
	spScissorCom->setFlippedY(true);// > setRotation(180.0);
	spRockCom->setFlippedY(true);//setRotation(180.0);
	spPaperCom->setFlippedY(true);//setRotation(180.0);
	spScissorCom->setAnchorPoint(Point(0.5, 1));
	spRockCom->setAnchorPoint(Point(0.5, 1));
	spPaperCom->setAnchorPoint(Point(0.5, 1));
	spScissorCom->setPosition(Point(origin.x + visibleSize.width / 2, winSize.height));
	spRockCom->setPosition(Point(origin.x + visibleSize.width / 2, winSize.height));
	spPaperCom->setPosition(Point(origin.x + visibleSize.width / 2, winSize.height));
	this->addChild(spScissorCom);
	this->addChild(spRockCom);
	this->addChild(spPaperCom);
	spScissorCom->setVisible(false);
	spRockCom->setVisible(false);
	spPaperCom->setVisible(false);

	this->setTouchEnabled(true);

    return true;
}

void Counting::onEnter()
{
	Layer::onEnter();

	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	_listener1 = EventListenerTouchOneByOne::create();
	_listener1->setSwallowTouches(true);
	_listener1->onTouchBegan = CC_CALLBACK_2(Counting::onTouchBegan, this);
	dispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);

	g_userselect = NOSELECT;
	nRepeat = 0;
	this->schedule(schedule_selector(Counting::doEvent1), 0.5f, 4, 0.0f);

}

void Counting::onExit()
{
	Layer::onExit();
}

void Counting::menuScissor(Ref * pSender)
{
	log("user Select Scissor");
	g_userselect = SCISSOR;
	spScissor->setScale(1.2);
	spRock->setScale(1.0);
	spPaper->setScale(1.0);

}

void Counting::menuRock(Ref * pSender)
{
	log("user Select Rock");
	g_userselect = ROCK;
	spScissor->setScale(1.0);
	spRock->setScale(1.2);
	spPaper->setScale(1.0);
}

void Counting::menuPaper(Ref * pSender)
{
	log("user Select Paper");
	g_userselect = PAPER;
	spScissor->setScale(1.0);
	spRock->setScale(1.0);
	spPaper->setScale(1.2);
}

void Counting::doEvent1(float dt)
{
	menuStart->setVisible(true);

	switch(nRepeat)
	{
	case 0:
		statusLabel->setString("Scissor");
		break;
	case 1:
		statusLabel->setString("Rock");
		break;
	case 2:
		statusLabel->setString("Paper");
		break;
	case 3:
		statusLabel->setString("Shoot!!");
		break;
	case 4:
		doResult();
		//Scene *pScene = Result::createScene();
		//Director::getInstance()->replaceScene(pScene);
		break;
	}
	++nRepeat;
}

void Counting::doResult()
{
	menuStart->setVisible(false);
	statusLabel2->setVisible(false);
	this->setTouchEnabled(true);
	computer = rand() % 3;
	user = g_userselect;// UserDefault::getInstance()->getIntegerForKey("userSelect");
	user = user == -1 ? (computer*rand()) % 3 : user;

	log("computer:%d, user:%d", computer, user);

	switch (computer)
	{
	case SCISSOR:
		spScissorCom->setVisible(true);
		break;
	case ROCK:
		spRockCom->setVisible(true);
		break;
	case PAPER:
		spPaperCom->setVisible(true);
		break;
	}

	switch (user)
	{
	case SCISSOR:
		spScissorUser->setVisible(true);
		break;
	case ROCK:
		spRockUser->setVisible(true);
		break;
	case PAPER:
		spPaperUser->setVisible(true);
		break;
	}

	if (computer == user)
	{
		statusLabel->setString("Draw!!");
//		this->unschedule(schedule_selector(Counting::doEvent1));
//		this->schedule(schedule_selector(Counting::doEvent1), 1.0f, 0, 1.0f);
	}
	else if ((computer == SCISSOR && user == ROCK) || (computer == ROCK && user == PAPER) || (computer == PAPER && user == SCISSOR))
	{
		statusLabel->setString("You win!!");
	}
	else
	{
		statusLabel->setString("You lose!!");
	}
}

bool Counting::onTouchBegan(Touch * touch, Event * unused_event)
{
	Scene *pScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(pScene);
	return true;
}
