export module entropy.xoshiro256starstar;

export import entropy.basic;
import entropy._xoshiro_base;

export namespace entropy
{
	class Xoshiro256starstar
	{
		_XoshiroBase base;

	public:
		constexpr Xoshiro256starstar()noexcept
		{

		}
		constexpr Xoshiro256starstar(uint64_t seed0, uint64_t seed1, uint64_t seed2, uint64_t seed3)noexcept :
			base(seed0, seed1, seed2, seed3)
		{

		}
		constexpr uint64_t next()noexcept
		{
			base.update();
			return rotateLeft(base.s[1] * 5, 7) * 8;
		}
	};
}