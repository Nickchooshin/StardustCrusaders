#include "GameScene.h"
#include "StageScene.h"

#include "ui/CocosGUI.h"
#include "AudioEngine.h"

#include "DataManager.h"
#include "PlanetMap.h"
#include "GameUI.h"

USING_NS_CC;
using namespace experimental;

Scene* GameScene::createScene()
{
	Scene *scene = GameScene::create();

	return scene;
}

bool GameScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	PlanetMap *map = PlanetMap::create();
	addChild(map);

	GameUI *gameUI = GameUI::create();
	addChild(gameUI, 1);

	// Touch
	EventListenerTouchOneByOne *eventListener = EventListenerTouchOneByOne::create();
	eventListener->setSwallowTouches(true);
	eventListener->onTouchBegan = CC_CALLBACK_2(GameScene::TouchBegan, this);
	eventListener->onTouchEnded = CC_CALLBACK_2(GameScene::TouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	AudioEngine::preload("Sounds/BGM-03.ogg");
	AudioEngine::preload("Sounds/SE_select.ogg");
	AudioEngine::preload("Sounds/SE_button.ogg");

	AudioEngine::play2d("Sounds/BGM-03.ogg", true);

	return true;
}

bool GameScene::TouchBegan(cocos2d::Touch *touch, cocos2d::Event * unused_event)
{
	return true;
}

void GameScene::TouchEnded(Touch *touch, Event * unused_event)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("Object_Menu_Close", this);
}