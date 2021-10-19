#include "Brick.h"
#include <assert.h>

Brick::Brick(const RectF& rect_in, Color color_in)
	:
	rect(rect_in),
	isDestroyed(false),
	bev(color_in)
{
}

void Brick::Draw(Graphics& gfx) const
{
	if (!isDestroyed)
	{
		bev.DrawBeveledBrick(rect.GetExpanded(-padding), bevelSize, gfx);
	}
}

bool Brick::CheckBallCollision(const Ball& ball) const
{
	return !isDestroyed && rect.IsOverlapping(ball.GetRect());
}

bool Brick::DoBallCollision(Ball& ball)
{
	if (!isDestroyed && rect.IsOverlapping(ball.GetRect()))
	{
		ball.ReboundY();
		isDestroyed = true;
		return true;
	}
	return false;
}

void Brick::ExcuteBallCollision(Ball& ball)
{
	assert(CheckBallCollision(ball));

	if (ball.IsCollisionY(rect))
	{
		ball.ReboundY();
		isDestroyed = true;
	}
	else
	{
		ball.ReboundX();
		isDestroyed = true;
	}
}

Vec2 Brick::GetCenter() const
{
	return Vec2(rect.GetCenter());
}
