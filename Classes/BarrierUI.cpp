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
	textBarrierNumber->setName("Text");
	addChild(textBarrierNumber, 1);

	sprintf(filename, "Images/Game/UI/Barrier_Area_%d.png", m_barrierType);

	Sprite *barrierArea = Sprite::create(filename);
	barrierArea->setPosition(0.0f, 92.0f);
	barrierArea->setVisible(false);
	barrierArea->setName("Area");
	addChild(barrierArea, 2);

	BarrierNumberUpdate();

	// Event
	EventListenerCustom *eventListener_BarrierUI_Click = EventListenerCustom::create("BarrierUI_Click", CC_CALLBACK_1(BarrierUI::BarrierAreaUIVisible, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener_BarrierUI_Click, this);

	EventListenerCustom *eventListener_Barrier_Build = EventListenerCustom::create("Barrier_Build", CC_CALLBACK_1(BarrierUI::BarrierAreaUIVisible, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener_Barrier_Build, this);

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

const int BarrierUI::GetBarrierType() const
{
	return m_barrierType;
}


void BarrierUI::Add()
{
	++m_barrierNumber;

	BarrierNumberUpdate();
}

void BarrierUI::Sub()
{
	--m_barrierNumber;

	BarrierNumberUpdate();
}

void BarrierUI::BarrierNumberUpdate()
{
	char text[10];
	sprintf(text, "%d", m_barrierNumber);

	ui::Text *textBarrierNumber = (ui::Text*)getChildByName("Text");
	textBarrierNumber->setText(text);
}

// Event - BarrierUI_Click
// Event - Barrier_Build
void BarrierUI::BarrierAreaUIVisible(EventCustom *event)
{
	Sprite *barrierArea = (Sprite*)getChildByName("Area");

	barrierArea->setVisible(false);
}

void BarrierUI::Click(cocos2d::Ref *pSender)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("Object_Menu_Close", nullptr);

	if (m_barrierNumber > 0)
	{
		Sprite *barrierArea = (Sprite*)getChildByName("Area");
		bool isBarrierAreaVisible = barrierArea->isVisible();

		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("Barrier_UI_Menu_Close", nullptr);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("BarrierUI_Click", &m_barrierType);

		if (isBarrierAreaVisible)
			barrierArea->setVisible(false);
		else
			barrierArea->setVisible(true);
	}
}