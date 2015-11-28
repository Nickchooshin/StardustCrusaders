#include "StageScene.h"
#include "TitleScene.h"

#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* StageScene::createScene()
{
	Scene *scene = StageScene::create();

	return scene;
}

bool StageScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite *pBackground = Sprite::create("Images/Stage/Background.png");
	pBackground->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	this->addChild(pBackground);

	ui::Button *pNextButton = ui::Button::create("Images/Stage/Button_Next.png", "Images/Stage/Button_Next_Selected.png");
	pNextButton->setPosition(Vec2(504.0f, visibleSize.height - 76.0f));
	pNextButton->setTag(0);
	pNextButton->addClickEventListener(CC_CALLBACK_1(StageScene::MenuClick, this));
	this->addChild(pNextButton);

	ui::Button *pPrevButton = ui::Button::create("Images/Stage/Button_Prev.png", "Images/Stage/Button_Prev_Selected.png");
	pPrevButton->setPosition(Vec2(76.0f, visibleSize.height - 76.0f));
	pPrevButton->setTag(1);
	pPrevButton->addClickEventListener(CC_CALLBACK_1(StageScene::MenuClick, this));
	this->addChild(pPrevButton);

	return true;
}

void StageScene::MenuClick(Ref *pSender)
{
	ui::Button *pButton = (ui::Button*)pSender;
	int tag = pButton->getTag();

	switch (tag)
	{
	case 0:
		break;

	case 1:
		Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f, TitleScene::createScene()));
		break;
	}
}

void StageScene::StageClick(Ref *pSender)
{
	ui::Button *pButton = (ui::Button*)pSender;
	int tag = pButton->getTag();
}