export module entropy.normal_distribution:sqrt;

export import entropy.basic;

export namespace entropy
{
	constexpr float64_t sqrt_constexpr(float64_t x)noexcept;
}

namespace entropy
{
	constexpr float64_t sqrt_limited(float64_t x)noexcept;
}

export namespace entropy
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
}

namespace entropy
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
}