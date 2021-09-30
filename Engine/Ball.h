#pragma once

#include "Graphics.h"
#include "Vec2.h"

class Ball
{
public:
	Ball() = default;
	Ball(const Vec2& pos_in, const Vec2& vel_in);
	void Draw(Graphics& gfx);
	void Update(float dt);

private:
	static constexpr float radius = 7.0f;
	Vec2 pos;
	Vec2 vel;

};