module;

#include <numbers>
#include <cstdint>

export module entropy.distribution:math;

export import entropy.basic;

namespace kuma
{
	// 0.25 < x < 2.0
	constexpr float64_t sqrt_limited(float64_t x)noexcept
	{
		float64_t a_n = 1.0;
		for(uint64_t n = 6; n; --n)
		{
			a_n = ((x / a_n) + a_n) * 0.5;
		}
		return a_n;
	}

	//a0 = 2(1 - cos(x/32))
	constexpr float64_t calc_a0(float64_t x0)noexcept
	{
		constexpr float64_t inv_4P2 = 1.0 / (4 * 3);
		constexpr float64_t inv_6P4 = 1.0 / (6 * 5 * 4 * 3);
		constexpr float64_t inv_8P6 = 1.0 / (8 * 7 * 6 * 5 * 4 * 3);
		constexpr float64_t inv_10P8 = 1.0 / (10 * 9 * 8 * 7 * 6 * 5 * 4 * 3);
		constexpr float64_t inv_12P10 = 1.0 / (12.0 * 11 * 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3);
		constexpr float64_t inv_14P12 = 1.0 / (14.0 * 13 * 12 * 11 * 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3);
		const float64_t x0_2 = x0 * x0;
		return x0_2 * (1.0 - x0_2 * (inv_4P2 - x0_2 * (inv_6P4 - x0_2 * (inv_8P6 - x0_2 * (inv_10P8 - x0_2 * (inv_12P10 - x0_2 * inv_14P12))))));
	}

	//a5 = 2(1 - cos(x))
	template <size_t n>
	constexpr float64_t calc_an(float64_t a0)noexcept
	{
		for(size_t i = n; i; --i)
		{
			a0 = a0 * (4.0 - a0);
		}
		return a0;
	}

	constexpr float64_t cos_limited(float64_t x)noexcept
	{
		constexpr size_t n = 8;
		constexpr float64_t c = 1.0 / (1 << n);
		return 1.0 - calc_an<n>(calc_a0(x * c)) * 0.5;
	}

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

export namespace kuma
{
	constexpr float64_t sqrt_constexpr(float64_t x)noexcept
	{
		if(0.25 < x)
		{
			if(x < 2.0)
			{
				return sqrt_limited(x);// 0.25 < x < 2.0
			}
			return sqrt_constexpr(x * 0.25) * 2.0;
		}
		return sqrt_constexpr(x * 4.0) * 0.5;
	}

	constexpr float64_t cos_constexpr(float64_t x)noexcept
	{
		constexpr float64_t two_pi = 2.0 * std::numbers::pi;
		x = x - static_cast<int32_t>(x / two_pi) * two_pi;
		return cos_limited(x);
	}

	constexpr float64_t log_constexpr(float64_t x)noexcept
	{
		constexpr float64_t sqrt_e = 1.6487212707001281468486507878142;
		constexpr float64_t qdrt_e = 1.2840254166877414840734205680624;
		constexpr float64_t sqrt_ie = 1.0 / sqrt_e;
		constexpr float64_t qdrt_ie = 1.0 / qdrt_e;
		constexpr float64_t e_i = 1.0 / std::numbers::e;
		constexpr float64_t e_4 = std::numbers::e * std::numbers::e * std::numbers::e * std::numbers::e;
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
			return log_constexpr(x * std::numbers::e) - 1.0;
		}
		if(std::numbers::e <= x)
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