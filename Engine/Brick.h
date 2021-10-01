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
	bool DoBallCollision(Ball& ball);

private:
	Color color;
	RectF rect;
	bool isDestroyed;
};