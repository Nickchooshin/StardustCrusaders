#ifndef _TITLE_SCENE_H_
#define _TITLE_SCENE_H_

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "network/HttpResponse.h"

#include <vector>

class LineEffect;

class TitleScene : public cocos2d::Scene
{
private:
	std::vector<LineEffect*> m_lineEffectList;

public:
	static cocos2d::Scene *createScene();

	virtual bool init() override;

	CREATE_FUNC(TitleScene);
private:
	void LineEffectUpdate(float dt);

	void ButtonClick(Ref *pSender);

	void onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
};

#endif