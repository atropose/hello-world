#include "HelloWorldScene.h"
#include "Counting.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

#define SCISSOR	0
#define ROCK 1
#define PAPER 2

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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

    // add a "close" icon to exit the progress. it's an autorelease object
	auto startItem = MenuItemImage::create("Images/Play-0.png", "Images/Play-1.png", CC_CALLBACK_1(HelloWorld::menuStartCallback, this));
	auto closeItem = MenuItemImage::create("Images/Quit-0.png", "Images/Quit-1.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	//auto startItem = MenuItemFont::create("Start Game", CC_CALLBACK_1(HelloWorld::menuStartCallback, this));
	//auto closeItem = MenuItemFont::create("End Game", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
/*
	startItem->setColor(Color3B::BLUE);
	startItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2+50));
	closeItem->setColor(Color3B::BLUE);
	closeItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2-50));
*/
    // create menu, it's an autorelease object
	menuStart = Menu::create(startItem, closeItem, NULL);
	menuStart->alignItemsVertically();
	menuStart->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(menuStart, 1);

    /////////////////////////////
    // 3. add your codes below...


    //// position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    //// add the sprite as a child to this layer
    //this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void HelloWorld::menuStartCallback(Ref* pSender)
{
	Scene *pScene = Counting::createScene();
	Director::getInstance()->replaceScene(pScene);
	//nRepeat = 0;
	//this->schedule(schedule_selector(HelloWorld::doEvent1), 1.0f, 4, 1.0f);

	//EventCustom customEndEvent("game_start_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}

void HelloWorld::onEnter()
{
	Layer::onEnter();
/*
	_listener1 = EventListenerCustom::create("game_start_event", CC_CALLBACK_1(HelloWorld::doEvent1, this));
	_eventDispatcher->addEventListenerWithFixedPriority(_listener1, 1);
*/
}

void HelloWorld::onExit()
{
//	_eventDispatcher->removeAllEventListeners();
	Layer::onExit();
}
