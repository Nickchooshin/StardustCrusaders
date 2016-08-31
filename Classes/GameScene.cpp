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

	AudioEngine::preload("Sounds/BGM-03.ogg");
	AudioEngine::preload("Sounds/SE_select.ogg");
	AudioEngine::preload("Sounds/SE_button.ogg");

	AudioEngine::play2d("Sounds/BGM-03.ogg", true);

	return true;
}