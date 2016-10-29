#ifndef _BARRIER_UI_H_
#define _BARRIER_UI_H_

#include "cocos2d.h"

class BarrierUI : public cocos2d::Node
{
private:
	int m_barrierType;
	int m_barrierNumber;

public:
	BarrierUI();
	BarrierUI(const BarrierUI&);
	~BarrierUI();

	virtual bool init() override;
	bool init(int type, int number);

	CREATE_FUNC(BarrierUI);
	static BarrierUI* create(int type, int number);

	const int GetBarrierType() const;

	void Add();
	void Sub();
private:
	void BarrierNumberUpdate();
	void BarrierAreaUIVisible(cocos2d::EventCustom *event);

	void Click(cocos2d::Ref *pSender);
};

#endif