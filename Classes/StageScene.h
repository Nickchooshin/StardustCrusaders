#ifndef _STAGE_SCENE_H_
#define _STAGE_SCENE_H_

#include "cocos2d.h"

class StageScene : public cocos2d::Scene
{
private:
	static int m_selectedStageNumber;

	int m_unlockStageNumber;

public:
	static cocos2d::Scene *createScene();

	virtual bool init() override;

	CREATE_FUNC(StageScene);

private:
	void MenuClick(Ref *pSender);
	void StageClick(Ref *pSender);
};

#endif