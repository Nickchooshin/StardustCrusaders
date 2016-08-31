#include "StageScene.h"
#include "TitleScene.h"
#include "TutorialScene.h"
#include "GameScene.h"

#include "ui/CocosGUI.h"
#include "AudioEngine.h"

#include "DataManager.h"

USING_NS_CC;
using namespace experimental;

int StageScene::m_selectedStageNumber = 0;

Scene* StageScene::createScene()
{
	Scene *scene = StageScene::create();

	return scene;
}

bool StageScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// Save Load
	DataManager::GetInstance()->LoadData();
	m_unlockStageNumber = DataManager::GetInstance()->GetUnlockStage();

	// Images
	Sprite *background = Sprite::create("Images/Stage/Background.png");
	background->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	this->addChild(background);

	ui::Button *buttonNext = ui::Button::create("Images/Stage/Button_Next.png", "Images/Stage/Button_Next_Selected.png");
	buttonNext->setPosition(Vec2(504.0f, visibleSize.height - 76.0f));
	buttonNext->setTag(-1);
	buttonNext->addClickEventListener(CC_CALLBACK_1(StageScene::MenuClick, this));
	addChild(buttonNext);

	ui::Button *buttonPrev = ui::Button::create("Images/Stage/Button_Prev.png", "Images/Stage/Button_Prev_Selected.png");
	buttonPrev->setPosition(Vec2(76.0f, visibleSize.height - 76.0f));
	buttonPrev->setTag(-2);
	buttonPrev->addClickEventListener(CC_CALLBACK_1(StageScene::MenuClick, this));
	addChild(buttonPrev);

	for (int i = 0; i < 20; i++)
	{
		float x = 108.0f + ((i % 4) * (90.0f + 30.0f));
		float y = visibleSize.height - (200.0f + ((i / 4) * (90.0f + 34.0f)));

		ui::Button *button = ui::Button::create("Images/Stage/Button_Stage.png", "", "Images/Stage/Button_Stage_Disable.png");
		button->setPosition(Vec2(x, y));
		button->setTag(i);
		button->addClickEventListener(CC_CALLBACK_1(StageScene::StageClick, this));
		addChild(button);

		if (i <= m_unlockStageNumber)
		{
			char filename[100];
			sprintf(filename, "Images/Stage/Stage_n_%02d.png", i);
			Sprite *spriteNumber = Sprite::create(filename);
			spriteNumber->setPosition(button->getContentSize().width / 2.0f, button->getContentSize().height / 2.0f);
			button->addChild(spriteNumber);
		}
		else
			button->setEnabled(false);
	}

	ui::Button *buttonStageSelected = (ui::Button*)getChildByTag(m_selectedStageNumber);

	buttonStageSelected->loadTextureNormal("Images/Stage/Button_Stage_Selected.png");

	// Sound
	AudioEngine::preload("Sounds/BGM-02.ogg");
	AudioEngine::preload("Sounds/SE_button.ogg");
	AudioEngine::preload("Sounds/SE_unlock.ogg");

	AudioEngine::play2d("Sounds/BGM-02.ogg");

	return true;
}

void StageScene::MenuClick(Ref *pSender)
{
	ui::Button *button = (ui::Button*)pSender;
	int tag = button->getTag();

	switch (tag)
	{
	case -1:
		AudioEngine::stopAll();
		AudioEngine::play2d("Sounds/SE_button.ogg");
		if (m_selectedStageNumber == 0)
		{
			Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f, TutorialScene::createScene()));
		}
		else
		{
			DataManager::GetInstance()->SetSelectedStage(m_selectedStageNumber);
			Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f, GameScene::createScene()));
		}
		break;

	case -2:
		AudioEngine::stopAll();
		AudioEngine::play2d("Sounds/SE_button.ogg");
		Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f, TitleScene::createScene()));
		break;
	}
}

void StageScene::StageClick(Ref *pSender)
{
	ui::Button *button = (ui::Button*)pSender;
	int tag = button->getTag();

	ui::Button *buttonPrevStage = (ui::Button*)getChildByTag(m_selectedStageNumber);

	buttonPrevStage->loadTextureNormal("Images/Stage/Button_Stage.png");
	button->loadTextureNormal("Images/Stage/Button_Stage_Selected.png");

	m_selectedStageNumber = button->getTag();

	AudioEngine::play2d("Sounds/SE_unlock.ogg");
}