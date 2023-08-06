export module entropy.time_seed;

export import entropy.basic;

namespace entropy
{
	constexpr uint32_t getTime()noexcept
	{
		//__TIME__ format: "hh:mm:ss"
		const char* const timeString = __TIME__;
		const uint32_t h = (timeString[0] - '0') * 10U + (timeString[1] - '0');
		const uint32_t m = (timeString[3] - '0') * 10U + (timeString[4] - '0');
		const uint32_t s = (timeString[6] - '0') * 10U + (timeString[7] - '0');
		return h * 24 * 60 + m * 60 + s;
	}
}

export namespace entropy
{
	constexpr uint32_t getSeed32()noexcept
	{
		return 463325252UL + (getTime() << 17);
	}

	constexpr uint64_t getSeed64()noexcept
	{
		return 88172645463325252ULL + (static_cast<uint64_t>(getTime()) << 47);
	}
}