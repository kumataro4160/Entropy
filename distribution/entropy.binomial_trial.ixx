export module entropy.binomial_trial;

export import entropy.basic;
import entropy.uniform_distribution_0to1;

export namespace entropy
{
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