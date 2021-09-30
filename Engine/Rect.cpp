#include "Rect.h"

Rect::Rect(float left_in, float right_in, float top_in, float bottom_in)
	:
	left(left_in),
	right(right_in),
	top(top_in),
	bottom(bottom_in)
{
}

Rect::Rect(const Vec2& topLeft, const Vec2& bottomRight)
	:
	Rect(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
{
}

Rect::Rect(const Vec2& topLeft, float width, float height)
	:
	Rect(topLeft, Vec2(width, height))
{
}

bool Rect::IsOverlapping(const Rect& other) const
{
	return right > other.left && left < other.right && bottom > other.top && top < other.bottom;
}
