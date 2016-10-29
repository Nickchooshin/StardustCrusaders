#ifndef _GAME_UI_H_
#define _GAME_UI_H_

#include "cocos2d.h"

class GameUI : public cocos2d::Node
{
private:

public:
	GameUI();
	GameUI(const GameUI&);
	~GameUI();

	virtual bool init() override;

	CREATE_FUNC(GameUI);
private:
	void LoadBarrierDat(int *barrierType, int *barrierNum);

	void BarrierNumberAdd(cocos2d::EventCustom *event);
	void BarrierNumberSub(cocos2d::EventCustom *event);
};

#endif