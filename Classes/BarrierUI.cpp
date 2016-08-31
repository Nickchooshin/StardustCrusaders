#include "BarrierUI.h"

#include "ui/CocosGUI.h"

USING_NS_CC;

BarrierUI::BarrierUI()
	: m_barrierType(0)
	, m_barrierNumber(0)
{
}
BarrierUI::~BarrierUI()
{
}

bool BarrierUI::init()
{
	init(0, 0);

	return true;
}

bool BarrierUI::init(int type, int number)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_barrierType = type;
	m_barrierNumber = number;

	char filename[128];
	sprintf(filename, "Images/Game/UI/Barrier_UI_%d.png", m_barrierType);

	ui::Button *buttonBarrierUI = ui::Button::create(filename);
	buttonBarrierUI->addClickEventListener(CC_CALLBACK_1(BarrierUI::Click, this));
	addChild(buttonBarrierUI);

	ui::Text *textBarrierNumber = ui::Text::create();
	textBarrierNumber->setFontName("Fonts/NanumBarunGothicBold.ttf");
	textBarrierNumber->setFontSize(30.0f);
	textBarrierNumber->setColor(Color3B(0, 0, 0));
	textBarrierNumber->setPosition(Vec2(30.0f, 0.0f));
	textBarrierNumber->setName("text");
	addChild(textBarrierNumber, 1);

	BarrierNumberUpdate();

	return true;
}

BarrierUI* BarrierUI::create(int type, int number)
{
	BarrierUI *pRet = new(std::nothrow) BarrierUI();
	if (pRet && pRet->init(type, number))
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

void BarrierUI::BarrierNumberUpdate()
{
	char text[10];
	sprintf(text, "%d", m_barrierNumber);

	ui::Text *textBarrierNumber = (ui::Text*)getChildByName("text");
	textBarrierNumber->setText(text);
}

void BarrierUI::Click(cocos2d::Ref *pSender)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("BarrierUI_Click", &m_barrierType);
}