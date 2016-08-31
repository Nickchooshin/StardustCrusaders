#include "PlanetMap.h"

#include "DataManager.h"
#include "Planet.h"
#include "Barrier.h"

#include "ui/CocosGUI.h"

USING_NS_CC;

float PlanetMap::m_mapSpace[3] = { 136.0f, 68.0f, 46.0f };
Vec2 PlanetMap::m_startPosition[3] = { Vec2(151.0f, 247.0f), Vec2(117.0f, 213.0f), Vec2(106.0f, 202.0f) };

PlanetMap::PlanetMap()
	: m_map(nullptr)
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

	sprintf(filepath, "Data/Map/%d.dat", mapNumber);
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
	int planetCount = 0;

	m_map = new int*[m_size];
	for (int i = 0; i < m_size; i++)
	{
		m_map[i] = new int[m_size];

		for (int j = 0; j < m_size; j++)
			m_map[i][j] = -1;
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
				position.x += m_mapSpace[index] * i;
				position.y -= m_mapSpace[index] * j;

				Planet *planet = Planet::create(type);
				planet->setPosition(position);
				planet->setTag(planetCount);
				planetNode->addChild(planet);

				m_map[i][j] = planetCount;
				++planetCount;
			}
		}
	}

	fclose(file);

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
			position.x += m_mapSpace[index] * i;
			position.y -= m_mapSpace[index] * j;

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
	EventListenerCustom *eventListenerCustom = EventListenerCustom::create("BarrierUI_Click", CC_CALLBACK_1(PlanetMap::BarrierBuildPositionSelect, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListenerCustom, this);

	return true;
}

void PlanetMap::BarrierBuildPosition_Click(cocos2d::Ref *pSender)
{
	ui::Button *buttonTileFrame = (ui::Button*)pSender;
	int tag = buttonTileFrame->getTag();

	if (m_selectedTileFrameTag != tag)
	{
		m_selectedTileFrameTag = tag;

		Node *planetNode = getChildByName("Planet_Node");

		Barrier *barrier = (Barrier*)planetNode->getChildByName("Barrier");

		if (barrier == nullptr)
		{
			barrier = Barrier::create(m_selectedBarrierType);
			barrier->setName("Barrier");
			planetNode->addChild(barrier);
		}

		barrier->setPosition(buttonTileFrame->getPosition());
	}
	else
	{
		m_selectedTileFrameTag = -1;

		Node *planetNode = getChildByName("Planet_Node");
		Barrier *barrier = (Barrier*)planetNode->getChildByName("Barrier");
		barrier->setName("");

		BarrierBuildPositionSelect_End();
	}
}

// Event - BarrierUI_Click
void PlanetMap::BarrierBuildPositionSelect(EventCustom *event)
{
	m_selectedBarrierType = *(int*)event->getUserData();

	Node *tileFrameNode = getChildByName("TileFrame_Node");

	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			if (m_map[i][j] == -1)
			{
				Node *tileFrame = tileFrameNode->getChildByTag(j + (i * m_size));
				tileFrame->setVisible(true);
			}
		}
	}
}

void PlanetMap::BarrierBuildPositionSelect_End()
{
	Node *tileFrameNode = getChildByName("TileFrame_Node");
	auto tileFrameList = tileFrameNode->getChildren();

	for (auto tileFrame : tileFrameList)
		tileFrame->setVisible(false);
}