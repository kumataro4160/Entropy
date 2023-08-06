export module entropy.normal_distribution:log;

export import entropy.basic;

export namespace entropy
{
	constexpr float64_t log_constexpr(float64_t x)noexcept;
}

import :e;

namespace entropy
{
	constexpr float64_t log1p_limited(float64_t x)noexcept;
}

export namespace entropy
{
	constexpr float64_t log_constexpr(float64_t x)noexcept
	{
		constexpr float64_t sqrt_e = 1.6487212707001281468486507878142;
		constexpr float64_t qdrt_e = 1.2840254166877414840734205680624;
		constexpr float64_t sqrt_ie = 1.0 / sqrt_e;
		constexpr float64_t qdrt_ie = 1.0 / qdrt_e;
		constexpr float64_t e_i = 1.0 / e;
		constexpr float64_t e_4 = e * e * e * e;
		constexpr float64_t e_i4 = 1.0 / e_4;
		if(x <= e_i4)
		{
			return log_constexpr(x * e_4) - 4.0;
		}
		if(e_4 <= x)
		{
			return log_constexpr(x * e_i4) + 4.0;
		}
		if(x <= e_i)
		{
			return log_constexpr(x * e) - 1.0;
		}
		if(e <= x)
		{
			return log_constexpr(x * e_i) + 1.0;
		}
		if(x <= sqrt_ie)
		{
			return log_constexpr(x * sqrt_e) - 0.5;
		}
		if(sqrt_e <= x)
		{
			return log_constexpr(x * sqrt_ie) + 0.5;
		}
		if(x <= qdrt_ie)
		{
			return log_constexpr(x * qdrt_e) - 0.25;
		}
		if(qdrt_e <= x)
		{
			return log_constexpr(x * qdrt_ie) + 0.25;
		}
		return log1p_limited(x - 1.0);// sqrt(1.0/e) < x < sqrt(e)
	}
}

namespace entropy
{
	// (1.0/e)^(1.0/4.0) - 1.0 < x < e^(1.0/4.0) - 1.0
	constexpr float64_t log1p_limited(float64_t x)noexcept
	{
		float64_t x_n = x;
		float64_t ret = x_n;
		x_n *= x;
		ret -= x_n / 2.0;
		x_n *= x;
		ret += x_n / 3.0;
		x_n *= x;
		ret -= x_n / 4.0;
		x_n *= x;
		ret += x_n / 5.0;
		x_n *= x;
		ret -= x_n / 6.0;
		x_n *= x;
		ret += x_n / 7.0;
		x_n *= x;
		ret -= x_n / 8.0;
		x_n *= x;
		ret += x_n / 9.0;
		x_n *= x;
		ret -= x_n / 10.0;
		x_n *= x;
		ret += x_n / 11.0;
		x_n *= x;
		ret -= x_n / 12.0;
		x_n *= x;
		ret += x_n / 13.0;
		x_n *= x;
		ret -= x_n / 14.0;
		x_n *= x;
		ret += x_n / 15.0;
		x_n *= x;
		ret -= x_n / 16.0;
		x_n *= x;
		ret += x_n / 17.0;
		x_n *= x;
		ret -= x_n / 18.0;
		x_n *= x;
		ret += x_n / 19.0;
		x_n *= x;
		ret -= x_n / 20.0;
		x_n *= x;
		ret += x_n / 21.0;
		x_n *= x;
		ret -= x_n / 22.0;
		x_n *= x;
		ret += x_n / 23.0;
		x_n *= x;
		ret -= x_n / 24.0;
		x_n *= x;
		ret += x_n / 25.0;
		x_n *= x;
		ret -= x_n / 26.0;
		return ret;
	}
}