#include "GameScene.h"
#include "SimpleAudioEngine.h"
#define PI 3.1415926

USING_NS_CC;


Scene* GameScene::createScene()
{
	return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//bg
	//bg  = Sprite::create("map.png");
	//bg = TMXTiledMap::create("map.png");

	bg = TMXTiledMap::create("map/MidddleMap.tmx");   
	addChild(bg, 0, 100);
	//bg->setAnchorPoint(Vec2(0, 0));
	//bg->setPosition(bg->getContentSize().width / 2, bg->getContentSize().height / 2);
	//this->addChild(bg);

	soldier = Soldier::create();
	soldier->setPosition(400, 300);
	this->addChild(soldier);

	//lisenKboardEvent();

	
	

	//this->schedule(schedule_selector(GameScene::update), 0.01);
	scheduleUpdate();

	return true;
}

void GameScene::update(float dt) {

	soldier->update(dt);
	//hitTest();
}


// listen Kboard Event
//void GameScene::lisenKboardEvent() {
//	//this->_eventDispatcher->removeAllEventListeners();
//
//	auto listener = EventListenerKeyboard::create();
//	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed2, this);
//	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased2, this);
//	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
//}
//
//void GameScene::onKeyPressed2(EventKeyboard::KeyCode code, Event * evt) {
//	
//}
//
//void GameScene::onKeyReleased2(EventKeyboard::KeyCode code, Event * evt) {
//	
//}

void GameScene::hitTest() {

	
}

bool GameScene::onTouchBegan(Touch* touch, Event* event) {
	log("onTouchBegan");
	return true;
}

void GameScene::onTouchMove(Touch* touch, Event* event) {
	log("onTouchMove");
}

void GameScene::onTouchEnded(Touch* touch, Event* event) {
	log("onTouchEnded");

	Vec2 touchLocation = touch->getLocation();
	Vec2 soldierPos = soldier->getPosition();
	Vec2 diff = touchLocation - soldierPos;

	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			soldierPos.x += bg->getTileSize().width;
			soldier->runAction(FlipX::create(false));
		}
		else {
			soldierPos.x -= bg->getTileSize().width;
			soldier->runAction(FlipX::create(true));
		}
	}
	else {
		if (diff.y > 0) {
			soldierPos.y += bg->getTileSize().height;
		}
		else {
			soldierPos.y -= bg->getTileSize().height;
		}
	}
	soldier->setPosition(soldierPos);

}







