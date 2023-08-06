export module entropy.xoshiro256plusplus;

export import entropy.basic;
import entropy._xoshiro_base;
import entropy.rotateleft;

export namespace entropy
{
	class Xoshiro256plusplus
	{
		_XoshiroBase base;

	public:
		constexpr Xoshiro256plusplus()noexcept
		{

		}
		constexpr Xoshiro256plusplus(uint64_t seed0, uint64_t seed1, uint64_t seed2, uint64_t seed3)noexcept :
			base(seed0, seed1, seed2, seed3)
		{

		}
		constexpr uint64_t next()noexcept
		{
			base.update();
			return rotateLeft(base.s[0] + base.s[3], 23) + base.s[0];
		}
	};
}