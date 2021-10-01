#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "Colors.h"
#include "Vec2.h"
#include "Ball.h"

class Paddle
{
public:
	Paddle(const Vec2 pos_in, float halfWidth_in, float halfHeight_in);
	void Draw(Graphics& gfx);
	void Update(Keyboard& kbd, float dt);
	RectF GetRect() const;
	bool DoBallCollision(Ball& ball);
	void DoWallCollision(const RectF& walls);

private:
	Color c = Colors::Gray;
	Vec2 pos;
	float speed = 300.0f;
	float halfWidth;
	float halfHeight;
};
