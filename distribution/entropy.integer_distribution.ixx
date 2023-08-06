export module entropy.integer_distribution;

export import entropy.basic;
import entropy.xoshiro256plusplus;
import entropy.time_seed;

namespace entropy
{
	Xoshiro256plusplus globalRandomEngine;
}

export namespace entropy
{
	template <class RandomEngine>
	constexpr int8_t sampleIntegerDistribution_int8(RandomEngine& randomEngine)noexcept
	{
		return static_cast<int8_t>(randomEngine.next());
	}

	inline int8_t sampleIntegerDistribution_int8()noexcept
	{
		return static_cast<int8_t>(globalRandomEngine.next());
	}

	template <class RandomEngine>
	constexpr uint8_t sampleIntegerDistribution_uint8(RandomEngine& randomEngine)noexcept
	{
		return static_cast<uint8_t>(randomEngine.next());
	}

	inline uint8_t sampleIntegerDistribution_uint8()noexcept
	{
		return static_cast<uint8_t>(globalRandomEngine.next());
	}

	template <class RandomEngine>
	constexpr int16_t sampleIntegerDistribution_int16(RandomEngine& randomEngine)noexcept
	{
		return static_cast<int16_t>(randomEngine.next());
	}

	inline int16_t sampleIntegerDistribution_int16()noexcept
	{
		return static_cast<int16_t>(globalRandomEngine.next());
	}

	template <class RandomEngine>
	constexpr uint16_t sampleIntegerDistribution_uint16(RandomEngine& randomEngine)noexcept
	{
		return static_cast<uint16_t>(randomEngine.next());
	}

	inline uint16_t sampleIntegerDistribution_uint16()noexcept
	{
		return static_cast<uint16_t>(globalRandomEngine.next());
	}

	template <class RandomEngine>
	constexpr int32_t sampleIntegerDistribution_int32(RandomEngine& randomEngine)noexcept
	{
		return static_cast<int32_t>(randomEngine.next());
	}

	inline int32_t sampleIntegerDistribution_int32()noexcept
	{
		return static_cast<int32_t>(globalRandomEngine.next());
	}

	template <class RandomEngine>
	constexpr uint32_t sampleIntegerDistribution_uint32(RandomEngine& randomEngine)noexcept
	{
		return static_cast<uint32_t>(randomEngine.next());
	}

	inline uint32_t sampleIntegerDistribution_uint32()noexcept
	{
		return static_cast<uint32_t>(globalRandomEngine.next());
	}

	template <class RandomEngine>
	constexpr int64_t sampleIntegerDistribution_int64(RandomEngine& randomEngine)noexcept
	{
		return static_cast<int64_t>(randomEngine.next());
	}

	inline int64_t sampleIntegerDistribution_int64()noexcept
	{
		return static_cast<int64_t>(globalRandomEngine.next());
	}

	template <class RandomEngine>
	constexpr uint64_t sampleIntegerDistribution_uint64(RandomEngine& randomEngine)noexcept
	{
		return randomEngine.next();
	}

	inline uint64_t sampleIntegerDistribution_uint64()noexcept
	{
		return globalRandomEngine.next();
	}
}