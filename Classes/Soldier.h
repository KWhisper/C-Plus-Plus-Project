#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Soldier :public Sprite {
public:
	CREATE_FUNC(Soldier);
	bool init();
	bool isLeft;
	void idle();
	void down();
	void jump();
	void runLeft(float dt);
	void runRight(float dt);

	bool isDown;
	bool isJumping;
	bool isrunLeft;
	bool isrunRight;

	float vy;//Y轴上速度
	float g;//重力加速度
	float oy;//初位置

	void runAnimation();
	Sprite* sp;

	Action* run;

	void update(float dt);

	// listen Kboard Event
	void lisenKboardEvent();
	void onKeyPressed2(EventKeyboard::KeyCode code, Event * evt);
	void onKeyReleased2(EventKeyboard::KeyCode code, Event * evt);

};
