#ifndef KUMATARO_INCLUDE_ENTROPY_DISTRIBUTION_H
#define KUMATARO_INCLUDE_ENTROPY_DISTRIBUTION_H

#include <cstdint>
#include <numbers>
#include <cmath>
#include "entropy.base.h"
#include "entropy.random_engine.h"
#include "entropy.distribution.math.h"


namespace kuma::impl_entropy
{
	static Xoshiro256plusplus globalRandomEngine;

	constexpr float64_t c = 0.5 / static_cast<float64_t>(0x8000000000000000ULL);
}

namespace kuma
{
	using namespace std;
	using namespace impl_entropy;

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

	template <class RandomEngine>
	constexpr float64_t sampleUniformDistribution_0to1(RandomEngine& randomEngine)noexcept
	{
		return c * static_cast<float64_t>(sampleIntegerDistribution_uint64(randomEngine));

	}

	inline float64_t sampleUniformDistribution_0to1()noexcept
	{
		return c * static_cast<float64_t>(sampleIntegerDistribution_uint64());
	}

	template <class RandomEngine>
	constexpr float64_t sampleUniformDistribution(float64_t lower, float64_t upper, RandomEngine& randomEngine)noexcept
	{
		const float64_t zeroToOne = sampleUniformDistribution_0to1(randomEngine);
		return (upper - lower) * zeroToOne + lower;
	}

	inline float64_t sampleUniformDistribution(float64_t lower, float64_t upper)noexcept
	{
		const float64_t zeroToOne = sampleUniformDistribution_0to1();
		return (upper - lower) * zeroToOne + lower;
	}

	template <class RandomEngine>
	constexpr float64_t sampleNormalDistribution(RandomEngine& randomEngine)noexcept
	{
		const float64_t r1 = sampleUniformDistribution_0to1(randomEngine);
		const float64_t r2 = sampleUniformDistribution_0to1(randomEngine);
		return kuma::sqrt(-2.0 * kuma::log(r1)) * kuma::cos(2.0 * std::numbers::pi * r2);
	}

	inline float64_t sampleNormalDistribution()noexcept
	{
		const float64_t r1 = sampleUniformDistribution_0to1();
		const float64_t r2 = sampleUniformDistribution_0to1();
		return std::sqrt(-2.0 * std::log(r1)) * std::cos(2.0 * std::numbers::pi * r2);
	}

	template <class RandomEngine>
	constexpr bool sampleBinomialTrial(float64_t probabilityOfTrue, RandomEngine& randomEngine)noexcept
	{
		const float64_t randomValue0to1 = sampleUniformDistribution_0to1(randomEngine);
		return randomValue0to1 < probabilityOfTrue;
	}

	inline bool sampleBinomialTrial(float64_t probabilityOfTrue)noexcept
	{
		const float64_t randomValue0to1 = sampleUniformDistribution_0to1();
		return randomValue0to1 < probabilityOfTrue;
	}
}


#endif