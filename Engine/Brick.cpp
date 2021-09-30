#include "Brick.h"

Brick::Brick(const Rect& rect_in, Color color_in)
	:
	rect(rect_in),
	color(color_in)
{
	isDestroyed = false;
}

void Brick::Draw(Graphics& gfx) const
{
	gfx.DrawRect(rect, color);
}
