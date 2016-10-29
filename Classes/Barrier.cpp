#include "Barrier.h"

#include "json/document.h"
#include "json/filereadstream.h"

USING_NS_CC;

Barrier::Barrier()
	: m_barrierType(0)
	, m_barrierArea()
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

	// Barrier Area
	sprintf(filename, "Data/Barrier/Barrier_Type_%d.json", m_barrierType);

	char buffer[100];
	FILE *file = fopen(filename, "r");

	rapidjson::FileReadStream is(file, buffer, sizeof(buffer));
	rapidjson::Document document;

	document.ParseStream(is);
	fclose(file);

	rapidjson::Value &positionArray = document["position"];
	for (auto iter = positionArray.Begin(); iter != positionArray.End(); iter++)
	{
		Vec2 position;
		position.x = (float)(*iter)["x"].GetInt();
		position.y = (float)(*iter)["y"].GetInt();

		m_barrierArea.emplace_back(position);
	}

	rapidjson::Value &areaArray = document["area"];
	for (auto iter = areaArray.Begin(); iter != areaArray.End(); iter++)
	{
		Vec2 position;
		Vec2 scale;
		position.x = (float)(*iter)["x"].GetInt();
		position.y = (float)(*iter)["y"].GetInt();
		scale.x = (float)(*iter)["scale_x"].GetDouble();
		scale.y = (float)(*iter)["scale_y"].GetDouble();

		//m_barrierArea.emplace_back(position);
	}

	// Animation
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

	ui::Button *buttonDemolish = ui::Button::create("Images/Game/temp_x.png");
	buttonDemolish->setPosition(Vec2(buttonSize.width, buttonSize.height));
	buttonDemolish->setVisible(false);
	buttonDemolish->addClickEventListener(CC_CALLBACK_1(Barrier::ClickDemolish, this));
	buttonDemolish->setName("Button_Demolish");
	button->addChild(buttonDemolish, 1);

	// Event
	EventListenerCustom *eventListener = EventListenerCustom::create("Object_Menu_Close", CC_CALLBACK_1(Barrier::ObjectMenuClose, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

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

const int Barrier::GetBarrierType() const
{
	return m_barrierType;
}

void Barrier::ClickBarrier(cocos2d::Ref *pSender)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("Object_Menu_Close", this);

	ui::Button *buttonDemolish = (ui::Button*)getChildByName("Button_Demolish");
	bool isVisible = buttonDemolish->isVisible();

	buttonDemolish->setVisible(!isVisible);
}

void Barrier::ClickDemolish(cocos2d::Ref *pSender)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("Barrier_Demolish", this);
}

// Event - Object_Menu_Close
void Barrier::ObjectMenuClose(EventCustom *event)
{
	ui::Button *buttonDemolish = (ui::Button*)getChildByName("Button_Demolish");
	buttonDemolish->setVisible(false);
}