#pragma once

#include "Graphics.h"
#include "Vec2.h"
#include "CollisionInform.h"

class Ball
{
public:
	Ball(const Vec2& pos_in, const Vec2& dir_in);
	void Draw(Graphics& gfx);
	void Update(float dt);
	int DoWallcollision(const RectF& walls);
	void ReboundX();
	void ReboundY();
	Vec2 GetVelocity() const;
	Vec2 GetPosition() const;
	RectF GetRect() const;
	bool IsCollisionY(const RectF& target) const;
	float GetCollisionLength(const float coordTargetL, const float coordTargetS, const float coordBallL, const float coordBallS) const;
	RectF GetCollisionRect(const RectF& target) const;
	CollisionInform GetCollisionInform(const float coordTargetL, const float coordTargetS, const float coordBallL, const float coordBallS) const;
	void SetDirection(const Vec2& dir);
private:
	static constexpr float radius = 7.0f;
	Vec2 pos;
	Vec2 vel;
	float speed = 400.0f;
};