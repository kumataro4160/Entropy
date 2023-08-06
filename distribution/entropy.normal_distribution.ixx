module;

#include <cmath>

export module entropy.normal_distribution;

export import entropy.basic;
import entropy.uniform_distribution_0to1;
import :pi;
import :sqrt;
import :log;
import :cos;

export namespace entropy
{
	template <class RandomEngine>
	constexpr float64_t sampleNormalDistribution(RandomEngine& randomEngine)noexcept
	{
		const float64_t r1 = sampleUniformDistribution_0to1(randomEngine);
		const float64_t r2 = sampleUniformDistribution_0to1(randomEngine);
		return sqrt(-2.0 * log(r1)) * cos(2.0 * pi * r2);
	}

	inline float64_t sampleNormalDistribution()noexcept
	{
		const float64_t r1 = sampleUniformDistribution_0to1();
		const float64_t r2 = sampleUniformDistribution_0to1();
		return std::sqrt(-2.0 * std::log(r1)) * std::cos(2.0 * pi * r2);
	}
}