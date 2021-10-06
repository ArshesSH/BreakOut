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

Vec2 Ball::GetVelocity() const
{
	return vel;
}

RectF Ball::GetRect() const
{
	return RectF::FromCenter(pos, radius, radius);
}

bool Ball::IsCollisionY(const RectF& target) const
{
	const RectF rectBall = GetRect();

	const float collisionHeight = GetCollisionLength(target.bottom, target.top, rectBall.bottom, rectBall.top);
	const float collisionWidth = GetCollisionLength(target.right, target.left, rectBall.right, rectBall.left);

	if (collisionWidth >= collisionHeight)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float Ball::GetCollisionLength(const float coordTargetL, const float coordTargetS, const float coordBallL, const float coordBallS) const
{
	if (coordBallS >= coordTargetS && coordBallL <= coordTargetL)
	{
		return coordBallL - coordBallS;
	}
	else if (coordBallS < coordTargetS && coordBallL < coordTargetL)
	{
		return coordBallL - coordTargetS;
	}
	else if (coordBallS > coordTargetS && coordBallL > coordTargetL)
	{
		return coordTargetL - coordBallS;
	}
	else
	{
		return coordTargetL - coordTargetS;
	}
}

RectF Ball::GetCollisionRect(const RectF& target) const
{
	const RectF rectBall = GetRect();
	const CollisionInform widthX = GetCollisionInform(target.right, target.left, rectBall.right, rectBall.left);
	const CollisionInform heigthY = GetCollisionInform(target.bottom, target.top, rectBall.bottom, rectBall.top);
	return RectF(Vec2(widthX.coord, heigthY.coord), widthX.length, heigthY.length);
}

CollisionInform Ball::GetCollisionInform(const float coordTargetL, const float coordTargetS, const float coordBallL, const float coordBallS) const
{
	if (coordBallS >= coordTargetS && coordBallL <= coordTargetL)
	{
		return CollisionInform(coordBallL - coordBallS, coordBallS);
	}
	else if (coordBallS < coordTargetS && coordBallL < coordTargetL)
	{
		return CollisionInform(coordBallL - coordTargetS, coordTargetS);
	}
	else if (coordBallS > coordTargetS && coordBallL > coordTargetL)
	{
		return CollisionInform(coordTargetL - coordBallS, coordBallS);
	}
	else
	{
		return CollisionInform(coordTargetL - coordTargetS, coordTargetS);
	}
}
