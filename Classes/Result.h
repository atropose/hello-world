#ifndef _RESULT_SCENE_H__
#define _RESULT_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class Result : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Result);

	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);

	void doEvent1(float dt);

	LabelTTF*	statusLabel;

	Sprite* spRock;
	Sprite* spScissor;
	Sprite* spPaper;

	Sprite* spRockCom;
	Sprite* spScissorCom;
	Sprite* spPaperCom;

	EventListenerTouchOneByOne* _listener1;

	int computer;
	int user;
};

#endif // __HELLOWORLD_SCENE_H__
