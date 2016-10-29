#include "TitleScene.h"
#include "StageScene.h"

#include "ui/CocosGUI.h"

#include "LineEffect.h"

#include "AudioEngine.h"

/*
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
*/

USING_NS_CC;
using namespace experimental;

const int MAX_LINEEFFECT = 20;

Scene* TitleScene::createScene()
{
	Scene *scene = TitleScene::create();

	return scene;
}

bool TitleScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite *background = Sprite::create("Images/Title/Background.jpg");
	background->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	addChild(background);

	ui::Text *textTitle = ui::Text::create("Stardust Crusaders", "Fonts/NanumBarunGothicBold.ttf", 45.0f);
	textTitle->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height - 134.0f));
	textTitle->setColor(Color3B(255, 255, 255));
	textTitle->enableOutline(Color4B(0, 0, 0, 0));
	addChild(textTitle, 2);

	ui::Button *buttonStart = ui::Button::create("Images/Title/Button_Start.png", "Images/Title/Button_Start_Selected.png");
	buttonStart->setPosition(Vec2(288.0f, visibleSize.height - 570.0f));
	buttonStart->setTag(0);
	buttonStart->addClickEventListener(CC_CALLBACK_1(TitleScene::ButtonClick, this));
	addChild(buttonStart, 2);

	ui::Button *buttonExit = ui::Button::create("Images/Title/Button_Exit.png", "Images/Title/Button_Exit_Selected.png");
	buttonExit->setPosition(Vec2(288.0f, visibleSize.height - 670.0f));
	buttonExit->setTag(1);
	buttonExit->addClickEventListener(CC_CALLBACK_1(TitleScene::ButtonClick, this));
	addChild(buttonExit, 2);

	for (int i = 0; i < MAX_LINEEFFECT; i++)
	{
		LineEffect *lineEffect = LineEffect::create();
		lineEffect->setPosition(-9999.0f, -9999.0f);
		addChild(lineEffect, 1);
		m_lineEffectList.emplace_back(lineEffect);
	}

	schedule(schedule_selector(TitleScene::LineEffectUpdate));

	AudioEngine::preload("Sounds/BGM-01.ogg");
	AudioEngine::preload("Sounds/SE_button.ogg");

	AudioEngine::play2d("Sounds/BGM-01.ogg", true);

	return true;
}

void TitleScene::LineEffectUpdate(float dt)
{
	for (auto lineEffect : m_lineEffectList)
		lineEffect->Update(dt);
}

void TitleScene::ButtonClick(Ref *pSender)
{
	ui::Button *button = (ui::Button*)pSender;

	network::HttpRequest *request;

	switch (button->getTag())
	{
	case 0:
		/*
		AudioEngine::stopAll();
		AudioEngine::play2d("Sounds/SE_button.ogg");
		Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f, StageScene::createScene()));
		*/
		
		request = new network::HttpRequest();
		//request->setUrl("http://192.168.0.13:8000/");
		request->setUrl("http://127.0.0.1:9080/");
		request->setRequestType(network::HttpRequest::Type::POST);
		request->setResponseCallback(CC_CALLBACK_2(TitleScene::onHttpRequestCompleted, this));
		request->setRequestData("id=1&pwd=2", 10);
		network::HttpClient::getInstance()->send(request);
		request->release();
		
		break;

	case 1:
		AudioEngine::play2d("Sounds/SE_button.ogg");
		Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
		break;
	}
}


void TitleScene::onHttpRequestCompleted(network::HttpClient *sender, network::HttpResponse *response)
{
	if (response->isSucceed())
	{
		std::vector<char> *buffer = response->getResponseData();

		for (unsigned int i = 0; i < buffer->size(); i++)
		{
		}
	}
}
