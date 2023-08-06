export module entropy.normal_distribution:cos;

export import entropy.basic;

export namespace entropy
{
	constexpr float64_t cos_constexpr(float64_t x)noexcept;
}

import :pi;

namespace entropy
{
	constexpr float64_t cos_limited(float64_t x_32)noexcept;
}

export namespace entropy
{
	constexpr float64_t cos_constexpr(float64_t x)noexcept
	{
		x = x - static_cast<int32_t>(x / (2.0 * pi)) * (2.0 * pi);
		return cos_limited(x);
	}
}

namespace entropy
{
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
}