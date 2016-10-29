#include "GameUI.h"

#include "DataManager.h"
#include "BarrierUI.h"
#include "Barrier.h"

#include "ui/CocosGUI.h"

USING_NS_CC;

GameUI::GameUI()
{
}
GameUI::~GameUI()
{
}

bool GameUI::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	FILE *file;
	char filepath[100];
	int barrierType[4], barrierNum[4];

	LoadBarrierDat(barrierType, barrierNum);

	ui::Button *buttonOperate = ui::Button::create("Images/Game/UI/Button_Operate.png", "Images/Game/UI/Button_Operate_Selected.png");
	buttonOperate->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height - 650.0f));
	addChild(buttonOperate);

	for (int i = 0; i < 4; i++)
	{
		BarrierUI *barrierUI = BarrierUI::create(barrierType[i], barrierNum[i]);
		barrierUI->setPosition(72.0f + (i * 144.0f), visibleSize.height - 737.0f);
		barrierUI->setTag(i);
		addChild(barrierUI);
	}

	// Event
	EventListenerCustom *eventListener_Barrier_Demolish = EventListenerCustom::create("Barrier_Demolish", CC_CALLBACK_1(GameUI::BarrierNumberAdd, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener_Barrier_Demolish, this);

	EventListenerCustom *eventListener_Barrier_Build = EventListenerCustom::create("Barrier_Build", CC_CALLBACK_1(GameUI::BarrierNumberSub, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener_Barrier_Build, this);

	return true;
}

void GameUI::LoadBarrierDat(int *barrierType, int *barrierNum)
{
	FILE *file;
	char filepath[100];

	int mapNumber = DataManager::GetInstance()->GetSelectedStage();

	sprintf(filepath, "Data/Map/Barrier_%d.dat", mapNumber);
	file = fopen(filepath, "r");

	for (int i = 0; i<4; i++)
		fscanf(file, "%d %d\n", &barrierType[i], &barrierNum[i]);

	fclose(file);
}

// Event - Barrier_Demolish
void GameUI::BarrierNumberAdd(EventCustom *event)
{
	Barrier *barrier = (Barrier*)event->getUserData();
	int barrierType = barrier->GetBarrierType();

	for (int i = 0; i < 4; i++)
	{
		BarrierUI *barrierUI = (BarrierUI*)getChildByTag(i);

		if (barrierUI->GetBarrierType() == barrierType)
		{
			barrierUI->Add();
			break;
		}
	}
}

// Event - Barrier_Build
void GameUI::BarrierNumberSub(EventCustom *event)
{
	Barrier *barrier = (Barrier*)event->getUserData();
	int barrierType = barrier->GetBarrierType();

	for (int i = 0; i < 4; i++)
	{
		BarrierUI *barrierUI = (BarrierUI*)getChildByTag(i);

		if (barrierUI->GetBarrierType() == barrierType)
		{
			barrierUI->Sub();
			break;
		}
	}
}