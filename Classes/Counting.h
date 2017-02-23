#ifndef __COUNTING_SCENE_H__
#define __COUNTING_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class Counting : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
        
    // implement the "static create()" method manually
    CREATE_FUNC(Counting);

	virtual void onEnter();
	virtual void onExit();

	void menuScissor(Ref* pSender);
	void menuRock(Ref * pSender);
	void menuPaper(Ref * pSender);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);

	void doEvent1(float dt);
	void doResult();

	Menu*	menuStart;

	Sprite* spRock;
	Sprite* spScissor;
	Sprite* spPaper;

	LabelTTF*	statusLabel;
	LabelTTF*	statusLabel2;

	EventListenerTouchOneByOne* _listener1;
	EventDispatcher* dispatcher;

	Sprite* spRockUser;
	Sprite* spScissorUser;
	Sprite* spPaperUser;

	Sprite* spRockCom;
	Sprite* spScissorCom;
	Sprite* spPaperCom;

	int computer;
	int user;
	int nRepeat;
};

#endif // __HELLOWORLD_SCENE_H__
