#ifndef _PLANET_MAP_H_
#define _PLANET_MAP_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class PlanetMap : public cocos2d::Node
{
private:
	bool **m_isObject;
	int m_size;
	int m_selectedBarrierType;
	int m_selectedTileFrameTag;

	static float m_mapSpace[3];
	static cocos2d::Vec2 m_startPosition[3];

public:
	PlanetMap();
	PlanetMap(const PlanetMap&);
	~PlanetMap();

	virtual bool init() override;

	CREATE_FUNC(PlanetMap);
private:
	void BarrierBuildPosition_Click(cocos2d::Ref *pSender);

	void BarrierBuildPositionSelect(cocos2d::EventCustom *event);
	void BarrierBuildPositionSelect_End();
	void BarrierDemolish(cocos2d::EventCustom *event);
};

#endif