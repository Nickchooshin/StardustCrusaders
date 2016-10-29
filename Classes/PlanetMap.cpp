#include "PlanetMap.h"

#include "DataManager.h"
#include "Planet.h"
#include "Barrier.h"

#include "ui/CocosGUI.h"

USING_NS_CC;

float PlanetMap::m_mapSpace[3] = { 136.0f, 68.0f, 46.0f };
Vec2 PlanetMap::m_startPosition[3] = { Vec2(151.0f, 247.0f), Vec2(117.0f, 213.0f), Vec2(106.0f, 202.0f) };

PlanetMap::PlanetMap()
	: m_isObject(nullptr)
	, m_size(0)
	, m_selectedBarrierType(0)
	, m_selectedTileFrameTag(-1)
{
}
PlanetMap::~PlanetMap()
{
}

bool PlanetMap::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	int mapNumber = DataManager::GetInstance()->GetSelectedStage();

	FILE *file;
	char filepath[100];

	sprintf(filepath, "Data/Map/Map_%d.dat", mapNumber);
	file = fopen(filepath, "r");

	fscanf(file, "%d\n", &m_size);

	// Map Background
	Sprite *background = nullptr;

	switch (m_size)
	{
	case 3:
		background = Sprite::create("Images/Game/Background_S.png");
		break;

	case 6:
		background = Sprite::create("Images/Game/Background_M.png");
		break;

	case 9:
		background = Sprite::create("Images/Game/Background_L.png");
		break;
	}

	background->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	addChild(background);

	// Map Object
	const int index = (m_size / 3) - 1;
	const float space = m_mapSpace[index];
	const Vec2 startPositon = m_startPosition[index];

	m_isObject = new bool*[m_size];
	for (int i = 0; i < m_size; i++)
	{
		m_isObject[i] = new bool[m_size];

		for (int j = 0; j < m_size; j++)
			m_isObject[i][j] = false;
	}

	Node *planetNode = Node::create();
	planetNode->setName("Planet_Node");
	addChild(planetNode, 1);

	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			int type;
			fscanf(file, "%d ", &type);

			if (type != 0)
			{
				Vec2 position = m_startPosition[index];
				position.y = visibleSize.height - position.y;
				position.x += m_mapSpace[index] * j;
				position.y -= m_mapSpace[index] * i;

				Planet *planet = Planet::create(type);
				planet->setPosition(position);
				planet->setTag(j + (i * m_size));
				planetNode->addChild(planet);

				m_isObject[i][j] = true;
			}
		}
	}

	fclose(file);

	// Barrier Node
	Node *barrierNode = Node::create();
	barrierNode->setName("Barrier_Node");
	addChild(barrierNode, 1);

	// Map Tile Area
	Node *tileFrameNode = Node::create();
	tileFrameNode->setName("TileFrame_Node");
	addChild(tileFrameNode, 1);

	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			Vec2 position = m_startPosition[index];
			position.y = visibleSize.height - position.y;
			position.x += m_mapSpace[index] * j;
			position.y -= m_mapSpace[index] * i;

			ui::Button *buttonTileFrame = ui::Button::create("Images/Game/TileFrame.png");
			buttonTileFrame->setPosition(position);
			buttonTileFrame->setContentSize(Size(m_mapSpace[index], m_mapSpace[index]));
			buttonTileFrame->setOpacity(191);
			buttonTileFrame->setVisible(false);
			buttonTileFrame->addClickEventListener(CC_CALLBACK_1(PlanetMap::BarrierBuildPosition_Click, this));
			buttonTileFrame->setTag(j + (i * m_size));
			tileFrameNode->addChild(buttonTileFrame);
		}
	}

	// UI
	char buffer[100];
	sprintf(buffer, "STAGE %d", mapNumber);
	ui::Text *textStageName = ui::Text::create(buffer, "Fonts/NanumBarunGothicBold.ttf", 50.0f);
	textStageName->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height - 36.0f));
	textStageName->setColor(Color3B(255, 255, 255));
	textStageName->enableOutline(Color4B(0, 0, 0, 0), 3);
	addChild(textStageName, 2);

	// Event
	EventListenerCustom *eventListener_BarrierUI_Click = EventListenerCustom::create("BarrierUI_Click", CC_CALLBACK_1(PlanetMap::BarrierBuildPositionSelect, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener_BarrierUI_Click, this);

	EventListenerCustom *eventListener_Barrier_Demolish = EventListenerCustom::create("Barrier_Demolish", CC_CALLBACK_1(PlanetMap::BarrierDemolish, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener_Barrier_Demolish, this);

	return true;
}

void PlanetMap::BarrierBuildPosition_Click(cocos2d::Ref *pSender)
{
	ui::Button *buttonTileFrame = (ui::Button*)pSender;
	int tag = buttonTileFrame->getTag();

	if (m_selectedTileFrameTag != tag)
	{
		m_selectedTileFrameTag = tag;

		Node *barrierNode = getChildByName("Barrier_Node");

		Barrier *barrier = (Barrier*)barrierNode->getChildByName("Barrier");

		if (barrier == nullptr)
		{
			barrier = Barrier::create(m_selectedBarrierType);
			barrier->setName("Barrier");
			barrierNode->addChild(barrier);
		}

		barrier->setPosition(buttonTileFrame->getPosition());
	}
	else
	{
		m_selectedTileFrameTag = -1;

		Node *barrierNode = getChildByName("Barrier_Node");
		Barrier *barrier = (Barrier*)barrierNode->getChildByName("Barrier");
		barrier->setName("");
		barrier->setTag(tag);

		int y = tag / m_size;
		int x = tag % m_size;
		m_isObject[y][x] = true;

		BarrierBuildPositionSelect_End();

		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("Barrier_Build", barrier);
	}
}

// Event - BarrierUI_Click
void PlanetMap::BarrierBuildPositionSelect(EventCustom *event)
{
	int selectedBarrierType = *(int*)event->getUserData();

	if (selectedBarrierType != m_selectedBarrierType)
	{
		m_selectedBarrierType = selectedBarrierType;

		Node *tileFrameNode = getChildByName("TileFrame_Node");

		for (int i = 0; i < m_size; i++)
		{
			for (int j = 0; j < m_size; j++)
			{
				if (m_isObject[i][j] == false)
				{
					Node *tileFrame = tileFrameNode->getChildByTag(j + (i * m_size));
					tileFrame->setVisible(true);
				}
			}
		}
	}
	else
	{
		m_selectedBarrierType = 0;

		BarrierBuildPositionSelect_End();
	}

	Node *barrierNode = getChildByName("Barrier_Node");
	barrierNode->removeChildByName("Barrier");
}

void PlanetMap::BarrierBuildPositionSelect_End()
{
	Node *tileFrameNode = getChildByName("TileFrame_Node");
	auto tileFrameList = tileFrameNode->getChildren();

	for (auto tileFrame : tileFrameList)
		tileFrame->setVisible(false);
}

// Event - Barrier_Demolish
void PlanetMap::BarrierDemolish(cocos2d::EventCustom *event)
{
	Barrier *barrier = (Barrier*)event->getUserData();
	int tag = barrier->getTag();
	int y = tag / m_size;
	int x = tag % m_size;

	m_isObject[y][x] = false;

	Node *barrierNode = getChildByName("Barrier_Node");
	barrierNode->removeChild(barrier);
}