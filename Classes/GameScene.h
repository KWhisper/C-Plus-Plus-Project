#pragma once
#ifndef Game_Scene
#define Game_Scene

#include "cocos2d.h"
#include "MainScene.h"
#include "Soldier.h"

using namespace cocos2d;

class GameScene : public Scene
{
	Soldier * soldier;
	TMXTiledMap* bg;
public:
	static Scene* createScene();

	virtual bool init();

	void update(float dt); //detle time

	CREATE_FUNC(GameScene);

	// listen Kboard Event 
	void lisenKboardEvent();
	void onKeyPressed2(EventKeyboard::KeyCode code, Event * evt);
	void onKeyReleased2(EventKeyboard::KeyCode code, Event * evt);
	
	//move
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMove(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);



	void hitTest();


	//Sprite* bg;
	bool outScreen(Node* n);

};

#endif // __HELLOWORLD_SCENE_H__
