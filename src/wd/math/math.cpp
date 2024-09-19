module;

#include <numeric>

module wd.math.Math;

namespace wd::math
{
	constexpr int GCD(int num1, int num2) noexcept
	{
		while (num2 != 0)
		{
			int r = num1 % num2;
			num1 = num2;
			num2 = r;
		}

		return num1;
	}

	constexpr int LCM(const int num1, const int num2) noexcept
	{
		return std::_Abs_u(num1 * num2) / GCD(num1, num2);
	}
}
