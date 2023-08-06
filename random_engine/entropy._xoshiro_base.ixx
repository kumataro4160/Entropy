export module entropy._xoshiro_base;

export import entropy.basic;
import entropy.time_seed;
import entropy.rotateleft;

export namespace entropy
{
	class _XoshiroBase
	{
	public:
		uint64_t s[4];

	public:
		constexpr _XoshiroBase()noexcept
		{
			for(uint64_t i = 0ULL; i < 4ULL; ++i)
			{
				s[i] = getSeed64();
			}
		}
		constexpr _XoshiroBase(uint64_t seed0, uint64_t seed1, uint64_t seed2, uint64_t seed3)noexcept
		{
			s[0] = seed0;
			s[1] = seed1;
			s[2] = seed2;
			s[3] = seed3;
		}
		constexpr void update()noexcept
		{
			const uint64_t t = s[1] << 17;
			s[2] ^= s[0];
			s[3] ^= s[1];
			s[1] ^= s[2];
			s[0] ^= s[3];
			s[2] ^= t;
			s[3] = rotateLeft(s[3], 45);
		}
		constexpr void jump_2_128()noexcept
		{
			constexpr uint64_t magic[] = {0x180EC6D33CFD0ABAULL, 0xD5A61266F0C9392CULL, 0xA9582618E03FC9AAULL, 0x39aBDC4529B1661CULL};
			uint64_t s0 = 0ULL;
			uint64_t s1 = 0ULL;
			uint64_t s2 = 0ULL;
			uint64_t s3 = 0ULL;
			for(uint64_t i = 0ULL; i < 4ULL; i++)
			{
				for(uint64_t b = 0ULL; b < 64ULL; b++)
				{
					if(magic[i] & (1ULL << b))
					{
						s0 ^= s[0ULL];
						s1 ^= s[1ULL];
						s2 ^= s[2ULL];
						s3 ^= s[3ULL];
					}
					update();
				}
			}
			s[0ULL] = s0;
			s[1ULL] = s1;
			s[2ULL] = s2;
			s[3ULL] = s3;
		}
		constexpr void jump_2_192()noexcept
		{
			constexpr uint64_t magic[] = {0x76E15D3EFEFDCBBFULL, 0xC5004E441C522FB3ULL, 0x77710069854EE241ULL, 0x39109BB02ACBE635ULL};
			uint64_t s0 = 0;
			uint64_t s1 = 0;
			uint64_t s2 = 0;
			uint64_t s3 = 0;
			for(uint64_t i = 0ULL; i < 4ULL; i++)
			{
				for(uint64_t b = 0ULL; b < 64ULL; b++)
				{
					if(magic[i] & 1ULL << b)
					{
						s0 ^= s[0ULL];
						s1 ^= s[1ULL];
						s2 ^= s[2ULL];
						s3 ^= s[3ULL];
					}
					update();
				}
			}
			s[0ULL] = s0;
			s[1ULL] = s1;
			s[2ULL] = s2;
			s[3ULL] = s3;
		}
	};
}