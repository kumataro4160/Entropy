export module entropy.xorshift64;

export import entropy.basic;
import entropy.time_seed;

export namespace entropy
{
	class Xorshift64
	{
		uint64_t x;

	public:
		constexpr Xorshift64()noexcept
		{
			x = getSeed64();
		}
		constexpr Xorshift64(uint64_t seed)noexcept
		{
			x = seed;
		}
		constexpr uint64_t next()noexcept
		{
			x ^= x << 7;
			x ^= x >> 9;
			return x;
		}
	};
}