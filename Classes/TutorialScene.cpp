#include "TutorialScene.h"
#include "StageScene.h"

#include "ui/CocosGUI.h"
#include "AudioEngine.h"

#include "DataManager.h"

USING_NS_CC;
using namespace experimental;

Scene* TutorialScene::createScene()
{
	Scene *scene = TutorialScene::create();

	return scene;
}

bool TutorialScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	for (int i = 0; i < 7; i++)
	{
		char filepath[100];
		sprintf(filepath, "Images/Tutorial/tutorial_%02d.png", i + 1);

		Sprite *tutorial = Sprite::create(filepath);
		tutorial->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
		tutorial->setTag(i);
		addChild(tutorial);

		if (i != 0)
			tutorial->setVisible(false);
	}

	m_tutorialNumber = 0;
	m_isTouch = false;

	EventListenerTouchOneByOne *eventListener = EventListenerTouchOneByOne::create();
	eventListener->setSwallowTouches(true);
	eventListener->onTouchBegan = CC_CALLBACK_2(TutorialScene::TouchBeganScreen, this);
	eventListener->onTouchEnded = CC_CALLBACK_2(TutorialScene::TouchEndedScreen, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	AudioEngine::preload("Sounds/BGM-03.ogg");

	AudioEngine::play2d("Sounds/BGM-03.ogg", true);

	return true;
}

bool TutorialScene::TouchBeganScreen(cocos2d::Touch *touch, cocos2d::Event * unused_event)
{
	m_isTouch = true;

	return true;
}

void TutorialScene::TouchEndedScreen(cocos2d::Touch *touch, cocos2d::Event * unused_event)
{
	if (m_isTouch)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 position = touch->getLocation();

		if (position.x >= (visibleSize.width / 2.0f))
		{
			if (m_tutorialNumber < 6)
			{
				Sprite *toturoal = nullptr;

				++m_tutorialNumber;
				getChildByTag(m_tutorialNumber - 1)->setVisible(false);
				getChildByTag(m_tutorialNumber)->setVisible(true);
			}
			else
			{
				DataManager::GetInstance()->UnlockStage(1);

				AudioEngine::stopAll();
				Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f, StageScene::createScene()));
			}
		}
		else
		{
			if (m_tutorialNumber > 0)
			{
				Sprite *toturoal = nullptr;

				--m_tutorialNumber;
				getChildByTag(m_tutorialNumber + 1)->setVisible(false);
				getChildByTag(m_tutorialNumber)->setVisible(true);
			}
		}

		m_isTouch = false;
	}
}