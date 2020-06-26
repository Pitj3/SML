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

#include "smltypes.h"
#include "common.h"

namespace sml
{
    template<typename T>
    class vec2view;

    template<typename T>
    class alignas(sml::simdalign<T>::value) vec2
    {
        public:
            constexpr vec2() noexcept
            {
                zero();
                v[2] = 0;
                v[3] = 0;
            }

            constexpr vec2(T x, T y) noexcept
            {
                set(x, y);
                v[2] = 0;
                v[3] = 0;
            }

            constexpr explicit vec2(T v) noexcept
            {
                set(v, v);
                this->v[2] = 0;
                this->v[3] = 0;
            }

            constexpr explicit vec2(T* v) noexcept
            {
                set(v);
                this->v[2] = 0;
                this->v[3] = 0;
            }

            constexpr vec2(const vec2& other) noexcept
            {
                set(const_cast<T*>(other.v));
                v[2] = 0;
                v[3] = 0;
            }

            constexpr vec2(vec2&& other) noexcept
            {
                v[0] = std::move(other.v[0]);
                v[1] = std::move(other.v[1]);
                v[2] = 0;
                v[3] = 0;
            }

            constexpr vec2& operator = (const vec2view<T>& other) noexcept;
            constexpr vec2& operator = (vec2view<T>&& other) noexcept;

            constexpr void zero() noexcept
            {
                set(static_cast<T>(0), static_cast<T>(0));
            }

            constexpr void set(T x, T y) noexcept
            {
                this->x = x;
                this->y = y;
            }

            void set(T* v) noexcept
            {
                this->v[0] = v[0];
                this->v[1] = v[1];
            }

            // Operators
            inline constexpr bool operator == (const vec2& other) const noexcept
            {
                return x == other.x && y == other.y;
            }

            inline constexpr bool operator != (const vec2& other) const noexcept
            {
                return x != other.x || y != other.y;
            }

            constexpr vec2& operator = (const vec2& other) noexcept
            {
                set(const_cast<T*>(other.v));

                return *this;
            }

            constexpr vec2& operator = (vec2&& other) noexcept
            {
                v[0] = std::move(other.v[0]);
                v[1] = std::move(other.v[1]);

                return *this;
            }

            vec2& operator += (const vec2& other) noexcept
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

            vec2& operator -= (const vec2& other) noexcept
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

            vec2& operator *= (const vec2& other) noexcept
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

            vec2& operator *= (const T other) noexcept
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
                    __m128d ot = _mm_set1_pd(other);
                    __m128d res = _mm_mul_pd(me, ot);

                    _mm_store_pd(v, res);

                    return *this;
                }

                x *= other;
                y *= other;

                return *this;
            }

            vec2& operator /= (const vec2& other) noexcept
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

            vec2& operator /= (const T other) noexcept
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_load_ps(v);
                    __m128 ot = _mm_broadcast_ss(&other);
                    __m128 res = _mm_div_ps(me, ot);

                    _mm_store_ps(v, res);

                    v[2] = v[3] = static_cast<T>(0);

                    return *this;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m128d me = _mm_load_pd(v);
                    __m128d ot = _mm_set1_pd(other);
                    __m128d res = _mm_div_pd(me, ot);

                    _mm_store_pd(v, res);

                    v[2] = v[3] = static_cast<T>(0);

                    return *this;
                }

                x /= other;
                y /= other;

                return *this;
            }

            // Operations 
            SML_NO_DISCARD inline constexpr T dot(vec2 other) const noexcept
            {
                if constexpr (std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_load_ps(v);
                    __m128 ot = _mm_load_ps(other.v);
                    __m128 product = _mm_mul_ps(me, ot);
                    __m128 dp = _mm_hadd_ps(product, product);

                    s32 res = _mm_extract_epi32(static_cast<__m128i>(_mm_hadd_ps(dp, dp)), 0);

                    return *reinterpret_cast<f32*>(&(res));
                }

                return (x * other.x) + (y * other.y);
            }

            SML_NO_DISCARD inline constexpr T length() const noexcept
            {
                return sml::sqrt((x * x) + (y * y));
            }

            SML_NO_DISCARD inline constexpr T lengthsquared() const noexcept
            {
                return (x * x) + (y * y);
            }

            inline constexpr void normalize() noexcept
            {
                float mag = length();

                if(mag > constants::epsilon)
                    *this /= length();
                else
                    set(0);
            }

            SML_NO_DISCARD inline constexpr vec2 normalized() const  noexcept
            {
                vec2 copy(v);
                copy.normalize();

                return copy;
            }

            SML_NO_DISCARD inline constexpr bool any() const noexcept
            {
                return x || y;
            }

            SML_NO_DISCARD inline constexpr bool all() const noexcept
            {
                return x && y;
            } 

            SML_NO_DISCARD inline constexpr bool none() const noexcept
            {
                return !x && !y;
            }

            SML_NO_DISCARD inline std::string toString() const noexcept
            {
                return std::to_string(x) + ", " + std::to_string(y);
            }

            // Statics
            SML_NO_DISCARD static inline constexpr vec2 normalize(const vec2& a) noexcept
            {
                vec2 copy(a.v);
                copy.normalize();

                return copy;
            }

            SML_NO_DISCARD static inline constexpr T dot(const vec2& lhs, const vec2& rhs) noexcept
            {
                return lhs.dot(rhs);
            }

            SML_NO_DISCARD static inline constexpr T distance(const vec2& a, const vec2& b) noexcept
            {
                vec2 delta = b - a;
                return delta.length();
            }

            SML_NO_DISCARD static inline constexpr vec2 min(const vec2& a, const vec2& b) noexcept
            {
                vec2 result;

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

            SML_NO_DISCARD static inline constexpr vec2 max(const vec2& a, const vec2& b) noexcept
            {
                vec2 result;

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

            SML_NO_DISCARD static inline constexpr vec2 clamp(const vec2& v, const vec2& a, const vec2& b) noexcept
            {
                return max(a, min(v, b));
            }

            SML_NO_DISCARD static inline constexpr vec2 lerp(const vec2& a, const vec2& b, T t) noexcept
            {
                T retX = sml::lerp(a.x, b.x, t);
                T retY = sml::lerp(a.y, b.y, t);

                return vec2(retX, retY);
            }

            SML_NO_DISCARD static inline constexpr vec2 lerpclamped(const vec2& a, const vec2& b, T t) noexcept
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
    constexpr vec2<T> operator + (const vec2<T>& left, const vec2<T>& right) noexcept
    {
        vec2<T> temp = left;

        temp += right;
        return temp;
    }

    template<typename T>
    constexpr vec2<T> operator - (const vec2<T>& left, const vec2<T>& right) noexcept
    {
        vec2<T> temp = left;

        temp -= right;
        return temp;
    }

    template<typename T> 
    constexpr vec2<T> operator * (const vec2<T>& left, const vec2<T>& right) noexcept
    {
        vec2<T> temp = left;

        temp *= right;
        return temp;
    }

    template<typename T>
    constexpr vec2<T> operator * (const vec2<T>& left, T right) noexcept
    {
        vec2<T> temp = left;

        temp *= right;
        return temp;
    }

    template<typename T>
    constexpr vec2<T> operator / (const vec2<T>& left, const vec2<T>& right) noexcept
    {
        vec2<T> temp = left;

        temp /= right;
        return temp;
    }

    template<typename T>
    constexpr vec2<T> operator / (const vec2<T>& left, T right) noexcept
    {
        vec2<T> temp = left;

        temp /= right;
        return temp;
    }

    template<typename T>
    constexpr vec2<T> operator - (const vec2<T>& left) noexcept
    {
        vec2<T> temp = left;
        temp *= -1;

        return temp;
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
            constexpr vec2view() = default;

            constexpr vec2view(const vec2<T>& other) noexcept
            {
                x = other.x;
                y = other.y;
            }

            constexpr vec2view(vec2<T>&& other) noexcept
            {
                x = std::move(other.x);
                y = std::move(other.y);
            }

            constexpr vec2view& operator = (const vec2<T>& other) noexcept
            {
                x = other.x;
                y = other.y;

                return *this;
            }

            constexpr vec2view& operator = (vec2<T>&& other) noexcept
            {
                x = std::move(other.x);
                y = std::move(other.y);

                return *this;
            }

            T x = static_cast<T>(0), y = static_cast<T>(0);
    };

    template<typename T>
    constexpr vec2<T>& vec2<T>::operator = (const vec2view<T>& other) noexcept
    {
        x = other.x;
        y = other.y;

        return *this;
    }

    template<typename T>
    constexpr vec2<T>& vec2<T>::operator = (vec2view<T>&& other) noexcept
    {
        x = std::move(other.x);
        y = std::move(other.y);

        return *this;
    }
} // namespace sml

#endif // sml_vec2_h__