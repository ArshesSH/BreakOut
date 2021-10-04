#pragma once

#include "Graphics.h"
#include "Colors.h"
#include "Ball.h"

class Brick
{
public:
	Brick() = default;
	Brick(const RectF& rect_in, Color color_in);
	void Draw(Graphics& gfx) const;
	bool CheckBallCollision(const Ball& ball) const;
	bool DoBallCollision(Ball& ball);
	void ExcuteBallCollision(Ball& ball);
	void CollisionEffect(Ball& ball);

private:
	static constexpr float padding = 1.0f;
	Color color;
	RectF rect;
	bool isDestroyed = false;
};