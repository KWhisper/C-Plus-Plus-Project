#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_tileMap = TMXTiledMap::create("map/MiddleMap.tmx");
	addChild(_tileMap, 0, 100);

	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("soldier");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	//_player = Sprite::create("ninja.png");
	_player = Soldier::create();
	_player->setPosition(Vec2(x+200, y+200));
	addChild(_player, 2, 200);

	setTouchEnabled(true);
	//����Ϊ���㴥
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	scheduleUpdate();

	return true;
}
void GameScene::update(float dt) {
	Vec2 playerPos = _player->getPosition();
	if ((playerPos.x - touchLocation.x > 0) && _player->isrunRight && (abs(playerPos.y - touchLocation.y ) < 5 )) {
		_player->isrunRight = false;
		_player->isrunUp = false;
		_player->isrunDown = false;
		_player->idle();
	}
	if ((playerPos.x - touchLocation.x < 0) && _player->isrunLeft && (abs(playerPos.y - touchLocation.y) < 5)) {
		_player->isrunLeft = false;
		_player->isrunUp = false;
		_player->isrunDown = false;
		_player->idle();
	}
		
	_player->update(dt);
}


bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	log("onTouchBegan");
	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event)
{
	log("onTouchMoved");
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
	log("onTouchEnded");
	//���OpenGL����
	touchLocation = touch->getLocation();
	log("touchLocation (%f ,%f) ", touchLocation.x, touchLocation.y);

	Vec2 playerPos = _player->getPosition();
	diff = touchLocation - playerPos;
	_player->diff[0] = diff.x;
	_player->diff[1] = diff.y;
		if (diff.x > 0) {
			_player->isrunRight = true;
			_player->isLeft = false;
			
			_player->runAnimation();
			
		}
		else {
			_player->isrunLeft = true;
			_player->isLeft = true;
			_player->runAnimation();

		}
	
		if (diff.y > 0) {
			_player->isrunUp = true;
		}
		else {
			_player->isrunDown = true;

		}
	
	log("playerPos (%f ,%f) ", playerPos.x, playerPos.y);
}
