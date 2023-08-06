export module entropy.uniform_distribution;

export import entropy.basic;
import entropy.uniform_distribution_0to1;

export namespace entropy
{
	template <class RandomEngine>
	constexpr float64_t sampleUniformDistribution(float64_t lower, float64_t upper, RandomEngine& randomEngine)noexcept
	{
		const float64_t zeroToOne = sampleUniformDistribution_0to1(randomEngine);
		return (upper-lower) * zeroToOne + lower;
	}

	inline float64_t sampleUniformDistribution(float64_t lower, float64_t upper)noexcept
	{
		const float64_t zeroToOne = sampleUniformDistribution_0to1();
		return (upper - lower) * zeroToOne + lower;
	}
}