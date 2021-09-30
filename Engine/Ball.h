#pragma once

#include "Vec2.h"
#include "Rect.h"

class Ball
{
public:
	Ball() = default;
	Ball(const Vec2& pos_in, const Vec2& vel_in);


private:
	Vec2 pos;
	Vec2 vel;

};