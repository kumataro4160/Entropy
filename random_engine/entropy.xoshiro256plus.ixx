export module entropy.xoshiro256plus;

export import entropy.basic;
import entropy._xoshiro_base;

export namespace entropy
{
	class Xoshiro256plus
	{
		_XoshiroBase base;

	public:
		constexpr Xoshiro256plus()noexcept
		{

		}
		constexpr Xoshiro256plus(uint64_t seed0, uint64_t seed1, uint64_t seed2, uint64_t seed3)noexcept :
			base(seed0, seed1, seed2, seed3)
		{

		}
		constexpr uint64_t next()noexcept
		{
			base.update();
			return base.s[0] + base.s[3];
		}
	};
}