#include "GameScene.h"
#include "Soldier.h"

bool Soldier::init() {
	Sprite::init();
	isLeft = false;
	isrunLeft = false;
	isrunRight = false;
	isJumping = false;
	isDown = false;

	lisenKboardEvent();
	idle();


	return true;
}


// listen Kboard Event
void Soldier::lisenKboardEvent() {
	this->_eventDispatcher->removeAllEventListeners();

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Soldier::onKeyPressed2, this);
	listener->onKeyReleased = CC_CALLBACK_2(Soldier::onKeyReleased2, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Soldier::onKeyPressed2(EventKeyboard::KeyCode code, Event * evt) {
	switch (int(code))
	{
	case 124://Left
		isrunLeft = true;
		isLeft = true;
		if (!isJumping && !isDown) {
			runAnimation();
			sp->setScaleX(isLeft ? 1 : -1);
		}
		break;
	case 127://Right
		isrunRight = true;
		isLeft = false;
		if (!isJumping && !isDown) {
			runAnimation();
			sp->setScaleX(isLeft ? 1 : -1);
		}
		break;
	case 142://down
		if (!isJumping)
		{
			if (isrunLeft || isrunRight)
				sp->stopAction(run);
			isDown = true;
			down();
		}
		break;
	case 146://jump
		if (!isJumping) {
			if (isrunLeft || isrunRight)
				sp->stopAction(run);
			jump();
			oy = getPositionY();
			vy = 6;
			g = -0.2;
			isJumping = true;
		}
		break;
	default:
		break;
	}

}

void Soldier::onKeyReleased2(EventKeyboard::KeyCode code, Event * evt) {
	switch (int(code))
	{
	case 124://Left
		isrunLeft = false;
		if (!isJumping) {
			sp->stopAction(run);
			idle();
		}
		break;
	case 127://Right
		isrunRight = false;
		if (!isJumping) {
			sp->stopAction(run);
			idle();
		}
		break;
	case 142://down
		isDown = false;
		if (!isJumping)
			idle();
		break;
	case 146://jump

		break;
	default:
		break;
	}
}

//update
void Soldier::update(float dt) {
	if (!isDown) {
		if (isrunLeft)
			runLeft(dt);
		if (isrunRight)
			runRight(dt);
	}
	if (isJumping) {
		setPositionY(getPositionY() + vy);
		vy = vy + g;
		if (getPositionY() < oy) {
			setPositionY(oy);
			isJumping = false;
			sp->stopAction(run);
			idle();
		}
	}
}


//idle
void Soldier::idle() {
	this->removeAllChildren();
	auto s = Sprite::create("tex/hero/idle.png");
	s->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(s);
	sp = s;
	sp->setScaleX(isLeft ? 1 : -1);

}

//down
void Soldier::down() {
	this->removeAllChildren();
	auto s = Sprite::create("tex/hero/down.png");
	s->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(s);
	s->setScaleX(isLeft ? 1 : -1);
}

//runAnimation
void Soldier::runAnimation() {
	Vector<SpriteFrame*>allFrames;
	char txt[100] = {};
	for (int i = 1; i < 4; i++) {
		sprintf_s(txt, "tex/hero/run_left000%d.png", i);
		SpriteFrame* sf = SpriteFrame::create(txt, Rect(0, 0, 55, 55));
		allFrames.pushBack(sf);
	}
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);
	run = sp->runAction(RepeatForever::create(Animate::create(ani)));
}


//jump
void Soldier::jump() {
	Vector<SpriteFrame*>allFrames;
	char txt[100] = {};
	for (int i = 1; i < 4; i++) {
		sprintf_s(txt, "tex/hero/jump000%d.png", i);
		SpriteFrame* sf = SpriteFrame::create(txt, Rect(0, 0, 55, 55));
		allFrames.pushBack(sf);
	}
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);
	run = sp->runAction(RepeatForever::create(Animate::create(ani)));
}

//Run Left
void Soldier::runLeft(float dt) {
	//isLeft = true;

	float d = dt * 200;
	setPositionX(getPositionX() - d);
}

//Run Right
void Soldier::runRight(float dt) {
	//isLeft = false;

	float d = dt * 200;
	setPositionX(getPositionX() + d);
}