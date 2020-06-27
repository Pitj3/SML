#ifndef sml_common_h__
#define sml_common_h__

/* common.h -- common math implementation of the 'Simple Math Library'
  Copyright (C) 2020 Roderick Griffioen
  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.
  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:
  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include <cmath>
#include <stdint.h>
#include <float.h>

#include "smltypes.h"

namespace constants
{
	// Commonly used constants
	static inline constexpr f32 pi = 3.14159265358979323846f;
	static inline constexpr f32 two_pi = 6.28318530717958647692f;
	static inline constexpr f32 half_pi = 1.57079632679489661923f;
	static inline constexpr f32 maxflt = FLT_MAX;
	static inline constexpr f32 epsilon = FLT_EPSILON;
	static inline constexpr f32 infinity = INFINITY;
	static inline constexpr f32 negativeinfinity = -infinity;
	static inline constexpr f32 deg2rad = pi / 180.0f;
	static inline constexpr f32 rad2deg = 1.0f / deg2rad;
} // namespace constants

namespace sml
{
	// Common math functions
	template <typename T>
	static inline T sin(T v)
	{
		return std::sin(v);
	}

	template <typename T>
	static inline T cos(T v)
	{
		return std::cos(v);
	}

	template <typename T>
	static inline T tan(T v)
	{
		return std::tan(v);
	}

	template <typename T>
	static inline T asin(T v)
	{
		return std::asin(v);
	}

	template <typename T>
	static inline T acos(T v)
	{
		return std::acos(v);
	}

	template <typename T>
	static inline T atan(T v)
	{
		return std::atan(v);
	}

	template <typename T>
	static inline T atan2(T a, T b)
	{
		return std::atan2(a, b);
	}

	template <typename T>
	static inline T sqrt(T v)
	{
		return std::sqrt(v);
	}

	template <typename T>
	static inline constexpr T abs(T v)
	{
		if constexpr(std::is_same<T, f32>::value)
		{
			union fi32
			{
				f32 f;
				u32 i;
			};

			fi32 u = {v};
			u.i &= ~(1UL << 31);

			return u.f;
		}
		else
		{
			return std::abs(v);
		}
	}

	template <typename T>
	static inline constexpr T min(T a, T b)
	{
		return a < b ? a : b;
	}

	template <typename T>
	static inline constexpr T max(T a, T b)
	{
		return a > b ? a : b;
	}

	template <typename T>
	static inline T pow(T v, T e)
	{
		return std::pow(v, e);
	}

	template <typename T>
	static inline T exp(T v)
	{
		return std::exp(v);
	}

	template <typename T>
	static inline T log(T b, T v)
	{
		return std::log(v) / std::log(b);
	}

	template <typename T>
	static inline T log10(T v)
	{
		return std::log10(v);
	}

	template <typename T>
	static inline T ceil(T v)
	{
		return std::ceil(v);
	}

	template <typename T>
	static inline T floor(T v)
	{
		return std::floor(v);
	}

	template <typename T>
	static inline T round(T v)
	{
		return std::round(v);
	}

	template <typename T>
	static inline T sign(T v)
	{
		return std::signbit(v);
	}

	template <typename T>
	static inline constexpr T clamp(T v, T min, T max)
	{
		if (v < min)
			v = min;
		else if (v > max)
			v = max;

		return v;
	}

	template <typename T>
	static inline constexpr T clamp01(T v)
	{
		if (v < T(0))
			v = T(0);
		else if (v > T(1))
			v = T(1);

		return v;
	}

	template <typename T>
	static inline constexpr T lerp(T a, T b, T t)
	{
		return a + (b - a) * t;
	}

	template <typename T>
	static inline constexpr T lerpclamped(T a, T b, T t)
	{
		return a + (b - a) * clamp01(t);
	}

	template <typename T>
	static inline constexpr T radtodeg(T r)
	{
		return r * constants::rad2deg;
	}

	template <typename T>
	static inline constexpr T degtorad(T r)
	{
		return r * constants::deg2rad;
	}

	template<typename T>
	static inline constexpr T normalizeAngle(T angle)
	{
		while (angle < static_cast<T>(0))
			angle += static_cast<T>(360);
		while (angle >= static_cast<T>(360))
			angle -= static_cast<T>(360);

		return angle;
	}
} // namespace sml

#endif // sml_common_h__