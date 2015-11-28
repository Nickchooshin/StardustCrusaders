#include "TitleScene.h"
#include "StageScene.h"

#include "ui/CocosGUI.h"

#include "LineEffect.h"

USING_NS_CC;

const int MAX_LINEEFFECT = 20;

Scene* TitleScene::createScene()
{
	Scene *scene = TitleScene::create();

	return scene;
}

bool TitleScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite *pBackground = Sprite::create("Images/Title/Background.jpg");
	pBackground->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	this->addChild(pBackground);

	Sprite *pTitle = Sprite::create("Images/Title/Title.png");
	pTitle->setPosition(288.0f, visibleSize.height - 134.0f);
	this->addChild(pTitle, 2);

	ui::Button *pStartButton = ui::Button::create("Images/Title/Button_Start.png", "Images/Title/Button_Start_Selected.png");
	pStartButton->setPosition(Vec2(288.0f, visibleSize.height - 570.0f));
	pStartButton->addClickEventListener(CC_CALLBACK_1(TitleScene::ButtonClick, this));
	this->addChild(pStartButton, 2);

	ui::Button *pExitButton = ui::Button::create("Images/Title/Button_Exit.png", "Images/Title/Button_Exit_Selected.png");
	pExitButton->setPosition(Vec2(288.0f, visibleSize.height - 670.0f));
	this->addChild(pExitButton, 2);

	for (int i = 0; i < MAX_LINEEFFECT; i++)
	{
		LineEffect *pLineEffect = LineEffect::create();
		pLineEffect->setPosition(-9999.0f, -9999.0f);
		this->addChild(pLineEffect, 1);
		m_lineEffectList.emplace_back(pLineEffect);
	}

	this->schedule(schedule_selector(TitleScene::LineEffectSchedule));

	return true;
}

void TitleScene::LineEffectSchedule(float dt)
{
	for (auto lineEffect : m_lineEffectList)
		lineEffect->Update(dt);
}

void TitleScene::ButtonClick(Ref *pSender)
{
	ui::Button *pButton = (ui::Button*)pSender;

	Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f, StageScene::createScene()));
}