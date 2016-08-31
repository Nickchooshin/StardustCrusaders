#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
private:

public:
	static cocos2d::Scene *createScene();

	virtual bool init() override;

	CREATE_FUNC(GameScene);
};

#endif