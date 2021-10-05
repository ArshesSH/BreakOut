#pragma once

#include "Graphics.h"
#include "Vec2.h"

class Ball
{
public:
	Ball(const Vec2& pos_in, const Vec2& vel_in);
	void Draw(Graphics& gfx);
	void Update(float dt);
	bool DoWallcollision(const RectF& walls);
	void ReboundX();
	void ReboundY();
	Vec2 GetVelocity() const;
	RectF GetRect() const;
	bool IsCollisionY(const RectF& target) const;
	float GetCollisionLength(const float coordTargetL, const float coordTargetS, const float coordBallL, const float coordBallS) const;
private:
	static constexpr float radius = 7.0f;
	Vec2 pos;
	Vec2 vel;

};