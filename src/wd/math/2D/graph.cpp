module wd.math.m2D.Graph;

namespace wd::math::m2D
{
	constexpr int QuadrantIndex(const Point& point) noexcept
	{
		if(point.X == 0 || point.Y == 0) return 0;

		if(point.X > 0)
		{
			if(point.Y > 0)
			{
				return 1;
			}

			return 4;
		}
		if(point.X < 0)
		{
			if(point.Y < 0)
			{
				return 3;
			}

			return 2;
		}

		return 0;
	}

	double Distance(const Point& a, const Point& b)
	{
		return 0;
	}
}
