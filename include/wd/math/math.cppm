export module wd.math.Math;

import wd.math.Point;

export namespace wd::math
{
	[[nodiscard]]
	constexpr int GCD(int num1, int num2) noexcept;
	[[nodiscard]]
	constexpr int LCM(int num1, int num2) noexcept;
	[[nodiscard]]
	constexpr int QuadrantIndex(const Point2D& point) noexcept;
	double Distance(const Point2D& a, const Point2D& b);
}
