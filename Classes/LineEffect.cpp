#include "LineEffect.h"

USING_NS_CC;

/*
LineEffect* LineEffect::create()
{
	LineEffect *lineEffect = new (std::nothrow) LineEffect();
	if (lineEffect && lineEffect->initWithFile("Images/Title/Line.png"))
	{
		lineEffect->autorelease();
		return lineEffect;
	}
	CC_SAFE_DELETE(lineEffect);
	return nullptr;
}
*/

bool LineEffect::init()
{
	m_direction = Direction::NONE;
	m_speed = 0.0f;
	m_sizeHalf = 0.0f;

	this->initWithFile("Images/Title/Line.png");

	return true;
}

void LineEffect::InitLineEffect()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_direction = (Direction)(rand() % 4 + 1);
	m_speed = ((rand() % 5 + 1) * 4.0f + 8.0f) * 30.0f;
	setScaleX((rand() % 3) * 0.5f + 1.0f);
	m_sizeHalf = (getContentSize().width / 2.0f) * getScaleX();

	switch (m_direction)
	{
	case Direction::UP:
		setPosition(Vec2(rand() % (int)visibleSize.width, -m_sizeHalf));
		setRotation(90.0f);
		break;

	case Direction::DOWN:
		setPosition(Vec2(rand() % (int)visibleSize.width, visibleSize.height + m_sizeHalf));
		m_speed = -m_speed;
		setRotation(90.0f);
		break;

	case Direction::LEFT:
		setPosition(Vec2(visibleSize.width + m_sizeHalf, rand() % (int)visibleSize.height));
		m_speed = -m_speed;
		setRotation(0.0f);
		break;

	case Direction::RIGHT:
		setPosition(Vec2(-m_sizeHalf, rand() % (int)visibleSize.height));
		setRotation(0.0f);
		break;
	}
}

void LineEffect::Update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	float speed = m_speed * dt * 2.0f;
	float x = getPositionX();
	float y = getPositionY();

	switch (m_direction)
	{
	case Direction::UP:
	case Direction::DOWN:
		y += speed;
		break;

	case Direction::LEFT:
	case Direction::RIGHT:
		x += speed;
		break;
	}

	setPosition(x, y);

	if ((x < -m_sizeHalf) || (x > visibleSize.width + m_sizeHalf) || (y < -m_sizeHalf) || (y > visibleSize.height + m_sizeHalf))
		InitLineEffect();
}