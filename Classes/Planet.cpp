#include "Planet.h"

#include "ui/CocosGUI.h"

USING_NS_CC;

Planet::Planet()
{
}
Planet::~Planet()
{
}

bool Planet::init()
{
	init(1);

	return true;
}

bool Planet::init(int type)
{
	char filename[128];
	sprintf(filename, "Images/Game/Planet_%02d_01.png", type);

	ui::Button *button = ui::Button::create(filename);
	button->addClickEventListener(CC_CALLBACK_1(Planet::ClickPlanet, this));
	button->setOpacity(0);
	addChild(button);

	Size buttonSize = button->getContentSize();

	Sprite *sprite = Sprite::create(filename);
	sprite->setPosition(buttonSize.width / 2.0f, buttonSize.height / 2.0f);
	Animation *animation = Animation::create();

	for (int i = 0; i < 4; i++)
	{
		sprintf(filename, "Images/Game/Planet_%02d_%02d.png", type, i + 1);
		animation->addSpriteFrameWithFile(filename);
	}

	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);

	Animate *animate = Animate::create(animation);
	RepeatForever *repeatForever = RepeatForever::create(animate);
	sprite->runAction(repeatForever);
	button->addChild(sprite);

	return true;
}

Planet* Planet::create(int type)
{
	Planet *pRet = new(std::nothrow) Planet();
	if (pRet && pRet->init(type))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

void Planet::ClickPlanet(Ref *pSender)
{
}