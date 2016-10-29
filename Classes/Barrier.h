#ifndef _BARRIER_H_
#define _BARRIER_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Barrier : public cocos2d::Node
{
private:
	int m_barrierType;

	std::vector<cocos2d::Vec2> m_barrierArea;

public:
	Barrier();
	Barrier(const Barrier&);
	~Barrier();

	virtual bool init() override;
	bool init(int type);

	CREATE_FUNC(Barrier);
	static Barrier* create(int type);

	const int GetBarrierType() const;
private:
	void ClickBarrier(cocos2d::Ref *pSender);
	void ClickDemolish(cocos2d::Ref *pSender);

	void ObjectMenuClose(cocos2d::EventCustom *event);
};

#endif