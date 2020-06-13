#ifndef sml_vec2_h__
#define sml_vec2_h__

/* vec2.h -- vec2 implementation of the 'Simple Math Library'
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

#include <string>
#include <immintrin.h>
#include <mmintrin.h>
#include <smmintrin.h>

#include "smltypes.h"

namespace sml
{
    template<typename T>
    class vec2view;

    template<typename T>
    class alignas(16) vec2
    {
        public:
            vec2()
            {
                zero();
                v[2] = 0;
                v[3] = 0;
            }

            vec2(T x, T y)
            {
                set(x, y);
                v[2] = 0;
                v[3] = 0;
            }

            explicit vec2(T v)
            {
                set(v, v);
                v[2] = 0;
                v[3] = 0;
            }

            vec2(const vec2& other)
            {
                set(other.v);
                v[2] = 0;
                v[3] = 0;
            }

            vec2(vec2&& other) noexcept
            {
                v[0] = std::move(other.v[0]);
                v[1] = std::move(other.v[1]);
                v[2] = 0;
                v[3] = 0;
            }

            vec2& operator = (const vec2view<T>& other);
            vec2& operator = (vec2view<T>&& other);

            void zero()
            {
                set(T(0), T(0));
            }

            void set(T x, T y)
            {
                this->x = x;
                this->y = y;
            }

            void set(T v[2])
            {
                this->v[0] = v[0];
                this->v[1] = v[1];
            }

            // Operators
            inline bool operator == (const vec2& other) const
            {
                if constexpr (std::is_same<T, f32>::value)
                {
                    union m128
                    {
                        __m128 f;
                        __m128i i;
                    };

                    __m128 me = _mm_load_ps(v);
                    __m128 ot = _mm_load_ps(other.v);

                    m128 cmp = { _mm_cmpeq_ps(me, ot) };
                    s32 result = _mm_testc_si128(cmp.i, cmp.i);

                    return result != 0;
                }

                if constexpr (std::is_same<T, f64>::value)
                {
                    union m128
                    {
                        __m128d d;
                        __m128i i;
                    };

                    __m128d me = _mm_load_pd(v);
                    __m128d ot = _mm_load_pd(other.v);

                    m128 cmp = { _mm_cmpeq_pd(me, ot) };
                    s32 result = _mm_testc_si128(cmp.i, cmp.i);

                    return result != 0;
                }

                return x == other.x && y == other.y;
            }

            inline bool operator != (const vec2& other) const
            {
                if constexpr (std::is_same<T, f32>::value)
                {
                    union m128
                    {
                        __m128 f;
                        __m128i i;
                    };

                    __m128 me = _mm_load_ps(v);
                    __m128 ot = _mm_load_ps(other.v);

                    m128 cmp = { _mm_cmpneq_ps(me, ot) };
                    s32 result = _mm_testc_si128(cmp.i, cmp.i);

                    return result != 0;
                }

                if constexpr (std::is_same<T, f64>::value)
                {
                    union m128
                    {
                        __m128d d;
                        __m128i i;
                    };

                    __m128d me = _mm_load_pd(v);
                    __m128d ot = _mm_load_pd(other.v);

                    m128 cmp = { _mm_cmpneq_pd(me, ot) };
                    s32 result = _mm_testc_si128(cmp.i, cmp.i);

                    return result != 0;
                }

                return x != other.x || y != other.y;
            }

            vec2& operator = (const vec2& other)
            {
                set(other.v);

                return *this;
            }

            vec2& operator = (vec2&& other) noexcept
            {
                v[0] = std::move(other.v[0]);
                v[1] = std::move(other.v[1]);

                return *this;
            }

            vec2& operator += (const vec2& other)
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_load_ps(v);
                    __m128 ot = _mm_load_ps(other.v);

                    __m128 res = _mm_add_ps(me, ot);

                    _mm_store_ps(v, res);

                    return *this;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m128d me = _mm_load_pd(v);
                    __m128d ot = _mm_load_pd(other.v);
                    __m128d res = _mm_add_pd(me, ot);

                    _mm_store_pd(v, res);

                    return *this;
                }

                x += other.x;
                y += other.y;

                return *this;
            }

            vec2& operator -= (const vec2& other)
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_load_ps(v);
                    __m128 ot = _mm_load_ps(other.v);
                    __m128 res = _mm_sub_ps(me, ot);

                    _mm_store_ps(v, res);

                    return *this;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m128d me = _mm_load_pd(v);
                    __m128d ot = _mm_load_pd(other.v);
                    __m128d res = _mm_sub_pd(me, ot);

                    _mm_store_pd(v, res);

                    return *this;
                }

                x -= other.x;
                y -= other.y;

                return *this;
            }

            vec2& operator *= (const vec2& other)
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_load_ps(v);
                    __m128 ot = _mm_load_ps(other.v);
                    __m128 res = _mm_mul_ps(me, ot);

                    _mm_store_ps(v, res);

                    return *this;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m128d me = _mm_load_pd(v);
                    __m128d ot = _mm_load_pd(other.v);
                    __m128d res = _mm_mul_pd(me, ot);

                    _mm_store_pd(v, res);

                    return *this;
                }

                x *= other.x;
                y *= other.y;

                return *this;
            }

            vec2& operator *= (const T other)
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_load_ps(v);
                    __m128 ot = _mm_broadcast_ss(&other);
                    __m128 res = _mm_mul_ps(me, ot);

                    _mm_store_ps(v, res);

                    return *this;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m128d me = _mm_load_pd(v);
                    __m128d ot = _mm_broadcast_pd(&other);
                    __m128d res = _mm_mul_pd(me, ot);

                    _mm_store_pd(v, res);

                    return *this;
                }

                x *= other;
                y *= other;

                return *this;
            }

            vec2& operator /= (const vec2& other)
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_load_ps(v);
                    __m128 ot = _mm_load_ps(other.v);
                    __m128 res = _mm_div_ps(me, ot);

                    _mm_store_ps(v, res);

                    return *this;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m128d me = _mm_load_pd(v);
                    __m128d ot = _mm_load_pd(other.v);
                    __m128d res = _mm_div_pd(me, ot);

                    _mm_store_pd(v, res);

                    return *this;
                }

                x /= other.x;
                y /= other.y;

                return *this;
            }

            vec2& operator /= (const T other)
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_load_ps(v);
                    __m128 ot = _mm_broadcast_ss(&other);
                    __m128 res = _mm_div_ps(me, ot);

                    _mm_store_ps(v, res);

                    return *this;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m128d me = _mm_load_pd(v);
                    __m128d ot = _mm_broadcast_ss(&other);
                    __m128d res = _mm_div_pd(me, ot);

                    _mm_store_pd(v, res);

                    return *this;
                }

                x /= other;
                y /= other;

                return *this;
            }

            // Operations
            inline T dot(vec2 other) const
            {
                if constexpr (std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_load_ps(v);
                    __m128 ot = _mm_load_ps(other.v);
                    __m128 product = _mm_mul_ps(me, ot);
                    __m128 dp = _mm_hadd_ps(product, product);

                    s32 res = _mm_extract_epi32(_mm_hadd_ps(dp, dp), 0);

                    return *reinterpret_cast<f32*>(&(res));
                }

                if constexpr (std::is_same<T, f64>::value)
                {
                    __m256d me = _mm256_load_pd(v);
                    __m256d ot = _mm256_load_pd(other.v);
                    __m256d product = _mm256_mul_pd(me, ot);
                    __m256d dp = _mm256_hadd_pd(product, product);

                    s32 res = _mm256_extract_epi32(_mm256_hadd_ps(dp, dp), 0);

                    return *reinterpret_cast<f64*>(&(res));
                }

                return (x * other.x) + (y * other.y);
            }

            inline T length() const
            {
                return sml::sqrt((x * x) + (y * y));
            }

            inline T lengthsquared() const
            {
                return (x * x) + (y * y);
            }

            inline vec2& normalize()
            {
                float mag = length();

                if(mag > constants::epsilon)
                    *this /= length();
                else
                    set(0, 0);

                return *this;
            }

            inline vec2 normalized()
            {
                vec2 copy(x, y);
                return copy.normalize();
            }

            inline bool any() const
            {
                return x || y;
            }

            inline bool all() const
            {
                return x && y;
            } 

            inline bool none() const
            {
                return !x && !y;
            }

            inline std::string toString()
            {
                return std::to_string(x) + ", " + std::to_string(y);
            }

            // Statics
            static inline vec2 distance(const vec2& a, const vec2& b)
            {
                vec2 delta = b - a;
                return delta.length();
            }

            static inline vec2 min(const vec2& a, const vec2& b)
            {
                vec4 result;

                if constexpr (std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_load_ps(a.v);
                    __m128 ot = _mm_load_ps(b.v);

                    __m128 maxres = _mm_min_ps(me, ot);

                    _mm_store_ps(result.v, maxres);

                    return result;
                }

                if constexpr (std::is_same<T, f64>::value)
                {
                    __m256d me = _mm256_load_pd(a.v);
                    __m256d ot = _mm256_load_pd(b.v);

                    __m256d maxres = _mm256_min_pd(me, ot);

                    _mm256_store_pd(result.v, maxres);

                    return result;
                }

                return 
                {
                    sml::min(a.x, b.x), 
                    sml::min(a.y, b.y)
                };
            }

            static inline vec2 max(const vec2& a, const vec2& b)
            {
                vec4 result;

                if constexpr (std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_load_ps(a.v);
                    __m128 ot = _mm_load_ps(b.v);

                    __m128 maxres = _mm_max_ps(me, ot);

                    _mm_store_ps(result.v, maxres);

                    return result;
                }

                if constexpr (std::is_same<T, f64>::value)
                {
                    __m256d me = _mm256_load_pd(a.v);
                    __m256d ot = _mm256_load_pd(b.v);

                    __m256d maxres = _mm256_max_pd(me, ot);

                    _mm256_store_pd(result.v, maxres);

                    return result;
                }

                return 
                {
                    sml::max(a.x, b.y), 
                    sml::max(a.y, b.y)
                };
            }

            static inline vec2 clamp(const vec2& v, const vec2& a, const vec2& b)
            {
                return max(a, min(x, b));
            }

            static inline vec2 lerp(const vec2& a, const vec2& b, T t)
            {
                T retX = sml::lerp(a.x, b.x, t);
                T retY = sml::lerp(a.y, b.y, t);

                return vec2(retX, retY);
            }

            static inline vec2 lerpclamped(const vec2& a, const vec2& b, T t)
            {
                T retX = sml::lerpclamped(a.x, b.x, t);
                T retY = sml::lerpclamped(a.y, b.y, t);

                return vec2(retX, retY);
            }

            // Data
            union
            {
                struct
                {
                    T x, y;
                };

                T v[4];
            };
    };

    // Operators
    template<typename T>
    vec2<T> operator + (vec2<T> left, vec2<T> right)
    {
        left += right;
        return left;
    }

    template<typename T>
    vec2<T> operator - (vec2<T> left, vec2<T> right)
    {
        left -= right;
        return left;
    }

    template<typename T>
    vec2<T> operator * (vec2<T> left, vec2<T> right)
    {
        left *= right;
        return left;
    }

    template<typename T>
    vec2<T> operator * (vec2<T> left, T right)
    {
        left += right;
        return left;
    }

    template<typename T>
    vec2<T> operator / (vec2<T> left, vec2<T> right)
    {
        left /= right;
        return left;
    }

    template<typename T>
    vec2<T> operator / (vec2<T> left, T right)
    {
        left += right;
        return left;
    }

    // Predefined types
    typedef vec2<bool> bvec2;
    typedef vec2<u32> uvec2;
    typedef vec2<s32> ivec2;
    typedef vec2<f32> fvec2;
    typedef vec2<f64> dvec2;

    template<typename T>
    class vec2view
    {
        public:
            vec2view() = default;

            vec2view(const vec2<T>& other)
            {
                x = other.x;
                y = other.y;
            }

            vec2view(vec2<T>&& other) noexcept
            {
                x = std::move(other.x);
                y = std::move(other.y);
            }

            vec2view& operator = (const vec2<T>& other)
            {
                x = other.x;
                y = other.y;

                return *this;
            }

            vec2view& operator = (vec2<T>&& other) noexcept
            {
                x = std::move(other.x);
                y = std::move(other.y);

                return *this;
            }

            T x = static_cast<T>(0), y = static_cast<T>(0);
    };

    template<typename T>
    vec2<T>& vec2<T>::operator = (const vec2view<T>& other)
    {
        x = other.x;
        y = other.y;

        return *this;
    }

    template<typename T>
    vec2<T>& vec2<T>::operator = (vec2view<T>&& other)
    {
        x = std::move(other.x);
        y = std::move(other.y);

        return *this;
    }
} // namespace sml

#endif // sml_vec2_h__