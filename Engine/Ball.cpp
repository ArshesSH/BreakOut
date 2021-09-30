#include "Ball.h"
#include "SpriteCodex.h"

Ball::Ball(const Vec2& pos_in, const Vec2& vel_in)
	:
	pos(pos_in),
	vel(vel_in)
{
}

void Ball::Draw(Graphics& gfx)
{
	SpriteCodex::DrawBall(pos, gfx);
}

void Ball::Update(float dt)
{
	pos += vel * dt;
}

bool Ball::DoWallcollision(const RectF& walls)
{
	bool isCollided = false;

	const RectF ballRect = GetRect();
	if (ballRect.left < walls.left)
	{
		ReboundX();
		isCollided = true;
	}
	else if (ballRect.right > walls.right)
	{
		ReboundX();
		isCollided = true;
	}

	if (ballRect.top > walls.top)
	{
		ReboundY();
		isCollided = true;
	}
	else if (ballRect.bottom < walls.right)
	{
		ReboundY();
		isCollided = true;
	}
}

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	vel.y = -vel.y;
}

RectF Ball::GetRect() const
{
	return RectF::FromCenter(pos, radius, radius);
}
