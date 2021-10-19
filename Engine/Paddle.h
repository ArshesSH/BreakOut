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
	void Update(const Keyboard& kbd, float dt);
	RectF GetRect() const;
	bool CheckBallColision(Ball& ball);
	bool DoBallCollision(Ball& ball);
	void ExcuteBallCollision(Ball& ball);
	void DoWallCollision(const RectF& walls);
	void ResetCooldown();
private:
	static constexpr Color wingColor = {210, 255, 210};
	static constexpr Color c = {200, 220, 200};

	static constexpr float wingWidth = 6.0f;
	static constexpr float speed = 360.f;
	static constexpr float maxExitRatio = 2.6f;
	static constexpr float fixedZoneWidthRatio = 0.2f;

	Vec2 pos;

	float exitXFactor = 0.045f;
	float fixedZoneHalfWidth = 15.0f;
	float fixedZoneExitX;
	float halfWidth;
	float halfHeight;
	bool isCooldown = false;
};
