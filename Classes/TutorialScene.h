#ifndef _TUTORIAL_SCENE_H_
#define _TUTORIAL_SCENE_H_

#include "cocos2d.h"

class TutorialScene : public cocos2d::Scene
{
private:
	int m_tutorialNumber;
	bool m_isTouch;

public:
	static cocos2d::Scene *createScene();

	virtual bool init() override;

	CREATE_FUNC(TutorialScene);
private:
	bool TouchBeganScreen(cocos2d::Touch *touch, cocos2d::Event * unused_event);
	void TouchEndedScreen(cocos2d::Touch *touch, cocos2d::Event * unused_event);
};

#endif