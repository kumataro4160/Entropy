export module entropy.rotateleft;

export import entropy.basic;

export namespace entropy
{
	constexpr uint64_t rotateLeft(uint64_t x, int n)noexcept//0 <= n <= 64
	{
		return (x << n) | (x >> (64 - n));
	}
}