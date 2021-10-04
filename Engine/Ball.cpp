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
		pos.x += walls.left - ballRect.left;
		ReboundX();
		isCollided = true;
	}
	else if (ballRect.right > walls.right)
	{
		pos.x -= ballRect.right - walls.right;
		ReboundX();
		isCollided = true;
	}

	if (ballRect.top < walls.top)
	{
		pos.y += walls.top - ballRect.top;
		ReboundY();
		isCollided = true;
	}
	else if (ballRect.bottom > walls.bottom)
	{
		pos.y -= ballRect.bottom - walls.bottom;
		ReboundY();
		isCollided = true;
	}
	return isCollided;
}

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	vel.y = -vel.y;
}

Vec2 Ball::GetVelocity()
{
	return vel;
}

RectF Ball::GetRect() const
{
	return RectF::FromCenter(pos, radius, radius);
}

int Ball::GetBallCollisionDir(const RectF& target) const
{
	enum Directions { LEFT, RIGHT, TOP, BOTTOM };
	const RectF rectBall = GetRect();

	if (rectBall.bottom >= target.top && rectBall.bottom < target.GetCenter().y)		// Direction from top
	{
		const float collisionHeight = rectBall.bottom - target.top;

		if (rectBall.right >= target.left && rectBall.right < target.right)		// LeftSide
		{
			const float collisionWidth = rectBall.right - target.left;

			if (collisionHeight > collisionWidth) { return LEFT; }
			else { return TOP; }
		}
		else if (rectBall.left <= target.right && rectBall.left > target.left)		// RightSide
		{
			const float collisionWidth = rectBall.left - target.right;

			if (collisionHeight > collisionWidth) { return RIGHT; }
			else { return TOP; }
		}
		else { return TOP; }
	}
	else
	{
		const float collisionHeight = rectBall.top - target.bottom;

		if (rectBall.right >= target.left && rectBall.right < target.right)		// LeftSide
		{
			const float collisionWidth = rectBall.right - target.left;

			if (collisionHeight > collisionWidth) { return LEFT; }
			else { return BOTTOM; }
		}
		else if (rectBall.left <= target.right && rectBall.left > target.left)		// RightSide
		{
			const float collisionWidth = rectBall.left - target.right;

			if (collisionHeight > collisionWidth) { return RIGHT; }
			else { return BOTTOM; }
		}
		else { return BOTTOM; }
	}
	return -1;
}
