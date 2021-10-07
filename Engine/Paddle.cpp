#include "Paddle.h"
#include <assert.h>

Paddle::Paddle(const Vec2 pos_in, float halfWidth_in, float halfHeight_in)
	:
	pos(pos_in),
	halfWidth(halfWidth_in),
	halfHeight(halfHeight_in),
	exitXFactor(maxExitRatio / halfWidth),
	fixedZoneHalfWidth(halfWidth* fixedZoneWidthRatio),
	fixedZoneExitX(fixedZoneHalfWidth * exitXFactor)
{
}

void Paddle::Draw(Graphics& gfx)
{
	RectF rect = GetRect();
	gfx.DrawRect(rect, wingColor);
	rect.left += wingWidth;
	rect.right -= wingWidth;
	gfx.DrawRect(rect, c);
}

void Paddle::Update(const Keyboard& kbd, float dt)
{
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		pos.x -= speed * dt;
	}
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		pos.x += speed * dt;
	}
}

RectF Paddle::GetRect() const
{
	return RectF::FromCenter(pos, halfWidth, halfHeight);
}

bool Paddle::CheckBallColision(Ball& ball)
{
	if (!isCooldown)
	{
		return GetRect().IsOverlapping(ball.GetRect());
	}
	else
	{
		return false;
	}
}

bool Paddle::DoBallCollision(Ball& ball)
{
	if (ball.GetVelocity().y > 0.0f && GetRect().IsOverlapping(ball.GetRect()))
	{
		ball.ReboundY();
		return true;
	}
	return false;
}

void Paddle::ExcuteBallCollision(Ball& ball)
{
	assert(CheckBallColision(ball));

	const RectF rect = GetRect();

	if (ball.IsCollisionY(rect))
	{
		const float xDifference = ball.GetPosition().x - pos.x;
		if (std::abs(xDifference) < fixedZoneHalfWidth)
		{
			if (xDifference < 0.0f)
			{
				dir = Vec2(-fixedZoneExitX, -1.0f);
			}
			else
			{
				dir = Vec2(fixedZoneExitX, -1.0f);
			}
		}
		else
		{
			dir = Vec2(xDifference * exitXFactor, -1.0f);
		}
		ball.SetDirection(dir);
	}
	else
	{
		ball.ReboundX();
	}
	isCooldown = true;
}

void Paddle::DoWallCollision(const RectF& walls)
{
	const RectF rect = GetRect();

	if (rect.right > walls.right)
	{
		pos.x -= rect.right - walls.right;
	}
	else if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
	}
}

void Paddle::ResetCooldown()
{
	isCooldown = false;
}
