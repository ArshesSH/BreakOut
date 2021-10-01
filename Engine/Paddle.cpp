#include "Paddle.h"

Paddle::Paddle(const Vec2 pos_in, float halfWidth_in, float halfHeight_in)
	:
	pos(pos_in),
	halfWidth(halfWidth_in),
	halfHeight(halfHeight_in)
{
}

void Paddle::Draw(Graphics& gfx)
{
	gfx.DrawRect(GetRect(), c);
}

void Paddle::Update(Keyboard& kbd, float dt)
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

bool Paddle::DoBallCollision(Ball& ball)
{
	if (ball.GetVelocity().y > 0.0f && GetRect().IsOverlapping(ball.GetRect()))
	{
		ball.ReboundY();
		return true;
	}
	return false;
}

void Paddle::DoWallCollision(const RectF& walls)
{
}
