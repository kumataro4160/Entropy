module;

#include <cstdint>
#include <bit>

export module entropy.random_engine;

namespace kuma
{
	using namespace std;

	constexpr uint32_t _getTime()noexcept
	{
		//__TIME__ format: "hh:mm:ss"
		const char* const timeString = __TIME__;
		const uint32_t h = (timeString[0] - '0') * 10U + (timeString[1] - '0');
		const uint32_t m = (timeString[3] - '0') * 10U + (timeString[4] - '0');
		const uint32_t s = (timeString[6] - '0') * 10U + (timeString[7] - '0');
		return h * 24 * 60 + m * 60 + s;
	}

	constexpr uint32_t getSeed32()noexcept
	{
		return 0x3CFD0ABAUL + (_getTime() << 17);
	}

	constexpr uint64_t getSeed64()noexcept
	{
		return 0x180EC6D33CFD0ABAULL + (static_cast<uint64_t>(_getTime()) << 47);
	}
}

namespace kuma
{
	using namespace std;

	class _XoshiroBase
	{
	public:
		uint64_t s[4];

	public:
		constexpr _XoshiroBase()noexcept
		{
			for(uint64_t i = 0; i < 4; ++i)
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
			s[3] = std::rotl(s[3], 45);
		}
		constexpr void jump_2_128()noexcept
		{
			constexpr uint64_t magic[] = {0x180EC6D33CFD0ABAULL, 0xD5A61266F0C9392CULL, 0xA9582618E03FC9AAULL, 0x39aBDC4529B1661CULL};
			uint64_t s0 = 0;
			uint64_t s1 = 0;
			uint64_t s2 = 0;
			uint64_t s3 = 0;
			for(uint64_t i = 0; i < 4; i++)
			{
				for(uint64_t b = 0; b < 64; b++)
				{
					if(magic[i] & (1ULL << b))
					{
						s0 ^= s[0];
						s1 ^= s[1];
						s2 ^= s[2];
						s3 ^= s[3];
					}
					update();
				}
			}
			s[0] = s0;
			s[1] = s1;
			s[2] = s2;
			s[3] = s3;
		}
		constexpr void jump_2_192()noexcept
		{
			constexpr uint64_t magic[] = {0x76E15D3EFEFDCBBFULL, 0xC5004E441C522FB3ULL, 0x77710069854EE241ULL, 0x39109BB02ACBE635ULL};
			uint64_t s0 = 0;
			uint64_t s1 = 0;
			uint64_t s2 = 0;
			uint64_t s3 = 0;
			for(uint64_t i = 0; i < 4; i++)
			{
				for(uint64_t b = 0; b < 64; b++)
				{
					if(magic[i] & (1ULL << b))
					{
						s0 ^= s[0];
						s1 ^= s[1];
						s2 ^= s[2];
						s3 ^= s[3];
					}
					update();
				}
			}
			s[0] = s0;
			s[1] = s1;
			s[2] = s2;
			s[3] = s3;
		}
	};
}

export namespace kuma
{
	using namespace std;

	class Xoshiro256plus
	{
		_XoshiroBase base;

	public:
		constexpr Xoshiro256plus()noexcept
		{

		}
		constexpr Xoshiro256plus(uint64_t seed0, uint64_t seed1, uint64_t seed2, uint64_t seed3)noexcept :
			base(seed0, seed1, seed2, seed3)
		{

		}
		constexpr uint64_t next()noexcept
		{
			base.update();
			return base.s[0] + base.s[3];
		}
	};

	class Xoshiro256plusplus
	{
		_XoshiroBase base;

	public:
		constexpr Xoshiro256plusplus()noexcept
		{

		}
		constexpr Xoshiro256plusplus(uint64_t seed0, uint64_t seed1, uint64_t seed2, uint64_t seed3)noexcept :
			base(seed0, seed1, seed2, seed3)
		{

		}
		constexpr uint64_t next()noexcept
		{
			base.update();
			return std::rotl(base.s[0] + base.s[3], 23) + base.s[0];
		}
	};

	class Xoshiro256starstar
	{
		_XoshiroBase base;

	public:
		constexpr Xoshiro256starstar()noexcept
		{

		}
		constexpr Xoshiro256starstar(uint64_t seed0, uint64_t seed1, uint64_t seed2, uint64_t seed3)noexcept :
			base(seed0, seed1, seed2, seed3)
		{

		}
		constexpr uint64_t next()noexcept
		{
			base.update();
			return std::rotl(base.s[1] * 5, 7) * 9;
		}
	};
}