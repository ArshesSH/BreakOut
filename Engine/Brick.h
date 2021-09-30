#pragma once

#include "Graphics.h"
#include "Colors.h"
#include "RectF.h"

class Brick
{
public:
	Brick() = default;
	Brick(const RectF& rect_in, Color color_in);
	void Draw(Graphics& gfx) const;

private:
	Color color;
	RectF rect;
	bool isDestroyed;
};