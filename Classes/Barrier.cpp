#include "Barrier.h"

USING_NS_CC;

Barrier::Barrier()
	: m_barrierType(0)
{
}
Barrier::~Barrier()
{
}

bool Barrier::init()
{
	init(0);

	return true;
}

bool Barrier::init(int type)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_barrierType = type;

	char filename[128];
	sprintf(filename, "Images/Game/Barrier_%02d_01.png", m_barrierType); // Barrier_01_01

	ui::Button *button = ui::Button::create(filename);
	button->addClickEventListener(CC_CALLBACK_1(Barrier::ClickBarrier, this));
	button->setOpacity(0);
	addChild(button);

	Size buttonSize = button->getContentSize();

	Sprite *sprite = Sprite::create(filename);
	sprite->setPosition(buttonSize.width / 2.0f, buttonSize.height / 2.0f);
	Animation *animation = Animation::create();

	for (int i = 0; i < 6; i++)
	{
		sprintf(filename, "Images/Game/Barrier_%02d_%02d.png", m_barrierType, i + 1);
		animation->addSpriteFrameWithFile(filename);
	}

	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);

	Animate *animate = Animate::create(animation);
	RepeatForever *repeatForever = RepeatForever::create(animate);
	sprite->runAction(repeatForever);
	button->addChild(sprite);

	m_buttonDemolish = ui::Button::create("Images/Game/temp_x.png");
	m_buttonDemolish->setPosition(Vec2(buttonSize.width, buttonSize.height));
	m_buttonDemolish->setVisible(false);
	m_buttonDemolish->addClickEventListener(CC_CALLBACK_1(Barrier::ClickDemolish, this));
	button->addChild(m_buttonDemolish, 1);

	return true;
}

Barrier* Barrier::create(int type)
{
	Barrier *pRet = new(std::nothrow) Barrier();
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

void Barrier::ClickBarrier(cocos2d::Ref *pSender)
{
	bool isVisible = m_buttonDemolish->isVisible();

	m_buttonDemolish->setVisible(!isVisible);
}

void Barrier::ClickDemolish(cocos2d::Ref *pSender)
{
	getParent()->removeChild(this);
}