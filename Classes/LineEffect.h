#ifndef _LINE_EFFECT_H_
#define _LINE_EFFECT_H_

#include "cocos2d.h"

class LineEffect : public cocos2d::Sprite
{
private:
	enum class Direction : int
	{
		NONE = 0,
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};
	Direction m_direction;
	float m_speed;
	float m_sizeHalf;

public:
	//static LineEffect *create();
	CREATE_FUNC(LineEffect);

	bool init() override;

	void InitLineEffect();

	void Update(float dt);

	const bool isLife() const;
};

#endif