#include "RectF.h"

RectF::RectF(float left_in, float right_in, float top_in, float bottom_in)
	:
	left(left_in),
	right(right_in),
	top(top_in),
	bottom(bottom_in)
{
}

RectF::RectF(const Vec2& topLeft, const Vec2& bottomRight)
	:
	RectF(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
{
}

RectF::RectF(const Vec2& topLeft, float width, float height)
	:
	RectF(topLeft, topLeft + Vec2(width, height))
{
}

bool RectF::IsOverlapping(const RectF& other) const
{
	return right > other.left && left < other.right && bottom > other.top && top < other.bottom;
}

int RectF::GetOverlappingDirection(const RectF& other, const bool isCollisioned) const
{
	enum Directions{LEFT = 1, RIGHT, TOP, BOTTOM};

	if (isCollisioned)
	{
		if(top <= other.bottom && other.bottom < )
	}
	else
	{
		return 0;
	}
	return -1;
}

RectF RectF::FromCenter(const Vec2& center, float halfWidth, float halfHeight)
{
	const Vec2 half(halfWidth, halfHeight);
	return RectF(center - half, center + half);
}

RectF RectF::GetExpanded(float offset) const
{
	return RectF(left - offset, right + offset, top - offset, bottom + offset);
}

Vec2 RectF::GetCenter() const
{
	return Vec2((left + right) / 2.0f, (top + bottom) / 2.0f);
}
