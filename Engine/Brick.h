#pragma once

#include "Graphics.h"
#include "Colors.h"
#include "Rect.h"

class Brick
{
public:
	Brick() = default;
	Brick(const Rect& rect_in, Color color_in);
	void Draw(Graphics& gfx) const;

private:
	Color color;
	Rect rect;
	bool isDestroyed;
};