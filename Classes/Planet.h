#ifndef _PLANET_H_
#define _PLANET_H_

#include "cocos2d.h"

class Planet : public cocos2d::Node
{
public:
	Planet();
	Planet(const Planet&);
	~Planet();

	virtual bool init() override;
	bool init(int type);

	CREATE_FUNC(Planet);
	static Planet* create(int type);
private:
	void ClickPlanet(cocos2d::Ref *pSender);
};

#endif