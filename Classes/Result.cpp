#include "Result.h"
#include "Counting.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

#define SCISSOR	0
#define ROCK 1
#define PAPER 2

extern int g_userselect;

Scene* Result::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Result::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Result::init()
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

    // add a label shows "Hello World"
    // create and initialize a label


    //// add "HelloWorld" splash screen"
	statusLabel = LabelTTF::create("", "fonts/Marker Felt.ttf", 40);
	statusLabel->setColor(Color3B::WHITE);
	statusLabel->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	statusLabel->setVisible(true);
	addChild(statusLabel);

	auto texture = Director::getInstance()->getTextureCache()->addImage("Images/main04.png");
	spScissor = Sprite::createWithTexture(texture, Rect(0, 0, 200, 290));
	spRock = Sprite::createWithTexture(texture, Rect(200, 0, 220, 290));
	spPaper = Sprite::createWithTexture(texture, Rect(420, 0, 220, 290));
	spScissor->setAnchorPoint(Point(0.5, 0));
	spRock->setAnchorPoint(Point(0.5, 0));
	spPaper->setAnchorPoint(Point(0.5, 0));
	spScissor->setPosition(Point(origin.x + visibleSize.width / 2, 0));
	spRock->setPosition(Point(origin.x + visibleSize.width / 2, 0));
	spPaper->setPosition(Point(origin.x + visibleSize.width / 2, 0));
	this->addChild(spScissor);
	this->addChild(spRock);
	this->addChild(spPaper);
	spScissor->setVisible(false);
	spRock->setVisible(false);
	spPaper->setVisible(false);

	spScissorCom = Sprite::createWithTexture(texture, Rect(0, 0, 200, 290));
	spRockCom = Sprite::createWithTexture(texture, Rect(200, 0, 220, 290));
	spPaperCom = Sprite::createWithTexture(texture, Rect(420, 0, 220, 290));
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

    //// position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    //// add the sprite as a child to this layer
    //this->addChild(sprite, 0);
    
    return true;
}


void Result::onEnter()
{
	Layer::onEnter();

	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	_listener1 = EventListenerTouchOneByOne::create();
	_listener1->setSwallowTouches(true);
	_listener1->onTouchBegan = CC_CALLBACK_2(Result::onTouchBegan, this);
	dispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);

	computer = rand() % 3;
	user = g_userselect;// UserDefault::getInstance()->getIntegerForKey("userSelect");
	user = user == -1 ? (computer*rand()) % 3 : user;

	log("computer:%d, user:%d", computer, user);

	switch (computer )
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
		spScissor->setVisible(true);
		break;
	case ROCK:
		spRock->setVisible(true);
		break;
	case PAPER:
		spPaper->setVisible(true);
		break;
	}

	if (computer == user)
	{
		statusLabel->setString("Draw!!");
		this->schedule(schedule_selector(Result::doEvent1), 1.0f, 0, 1.0f);
	}
	else if ((computer == SCISSOR && user == ROCK) || (computer == ROCK && user == PAPER) || (computer == PAPER && user == SCISSOR))
	{
		statusLabel->setString("You win!!");
	}
	else
	{
		statusLabel->setString("You lose!!");
	}
/*
	_listener1 = EventListenerCustom::create("game_start_event", CC_CALLBACK_1(HelloWorld::doEvent1, this));
	_eventDispatcher->addEventListenerWithFixedPriority(_listener1, 1);
*/
}

void Result::onExit()
{
	_eventDispatcher->removeEventListener(_listener1);
	Layer::onExit();
}

bool Result::onTouchBegan(Touch * touch, Event * unused_event)
{
	Scene *pScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(pScene);
	return true;
}

void Result::doEvent1(float dt)
{
	Scene *pScene = Counting::createScene();
	Director::getInstance()->replaceScene(pScene);
}
