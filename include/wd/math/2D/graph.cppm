export module wd.math.m2D.Graph;

import wd.math.m2D.Point;

export namespace wd::math::m2D
{
	[[nodiscard]]
	constexpr int QuadrantIndex(const Point& point) noexcept;
	double Distance(const Point& a, const Point& b);
}
