#pragma once

#include "Graphics.h"
#include "RectF.h"

class Beveler
{
public:
	Beveler(Color baseColor);
	void DrawOuterBevel(const RectF& rect, int size, Graphics& gfx) const;
	void DrawInnerBevel(const RectF& rect, int size, Graphics& gfx) const;
	void DrawBeveledBrick(const RectF& rect, int bevelsize, Graphics& gfx) const;
	void DrawBevelFrame(const RectF& rect, int bevelsize, Graphics& gfx) const;
	Color GetBaseColor() const;
	void SetBaseColor(Color base_in);
private:
	static constexpr float leftFactor = 1.10f;
	static constexpr float topFactor = 0.93f;
	static constexpr float bottomFactor = 0.80f;
	static constexpr float rightFactor = 0.65f;
	Color baseColor;
	Color topColor;
	Color bottomColor;
	Color leftColor;
	Color rightColor;
};