export module entropy.uniform_distribution_0to1;

export import entropy.basic;
import entropy.integer_distribution;

namespace entropy
{
	constexpr float64_t c = 0.5 / static_cast<float64_t>(0x8000000000000000ULL);
}

export namespace entropy
{
	template <class RandomEngine>
	constexpr float64_t sampleUniformDistribution_0to1(RandomEngine& randomEngine)noexcept
	{
		return c * static_cast<float64_t>(sampleIntegerDistribution_uint64(randomEngine));

	}

	inline float64_t sampleUniformDistribution_0to1()noexcept
	{
		return c * static_cast<float64_t>(sampleIntegerDistribution_uint64());
	}
}