#pragma once

#include "RectF.h"
#include "Graphics.h"
#include "Colors.h"
#include "Ball.h"
#include "Beveler.h"

class Brick
{
public:
	Brick() = default;
	Brick(const RectF& rect_in, Color color_in);
	void Draw(Graphics& gfx) const;
	bool CheckBallCollision(const Ball& ball) const;
	bool DoBallCollision(Ball& ball);
	void ExcuteBallCollision(Ball& ball);
	Vec2 GetCenter() const;
private:
	static constexpr float padding = 1.0f;
	static constexpr int bevelSize = 3;
	Beveler bev;
	RectF rect;
	bool isDestroyed = false;
};