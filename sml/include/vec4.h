#ifndef sml_vec4_h__
#define sml_vec4_h__

/* vec4.h -- vec4 implementation of the 'Simple Math Library'
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
    class vec4view;

    template<typename T>
    class alignas(simdalign<T>::value) vec4
    {
        public:
            constexpr vec4() noexcept
            {
                zero();
            }

            constexpr vec4(T x, T y, T z, T w) noexcept
            {
                set(x, y, z, w);
            }

            constexpr explicit vec4(T v) noexcept
            {
                set(v, v, v, v);
            }

            constexpr explicit vec4(T* v) noexcept
            {
                set(v);
            }

            constexpr vec4(const vec4& other) noexcept
            {
                set(const_cast<T*>(other.v));
            }

            constexpr vec4(vec4&& other) noexcept
            {
                v[0] = std::move(other.v[0]);
                v[1] = std::move(other.v[1]);
                v[2] = std::move(other.v[2]);
                v[3] = std::move(other.v[3]);
            }

            constexpr vec4& operator = (const vec4view<T>& other) noexcept;
            constexpr vec4& operator = (vec4view<T>&& other) noexcept;

            constexpr void zero() noexcept
            {
                set(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
            }

            constexpr void set(T x, T y, T z, T w) noexcept
            {
                this->x = x;
                this->y = y;
                this->z = z;
                this->w = w;
            }

            constexpr void set(T* v) noexcept
            {
                this->v[0] = v[0];
                this->v[1] = v[1];
                this->v[2] = v[2];
                this->v[3] = v[3];
            }

            // Operators 
            inline constexpr bool operator == (const vec4& other) const noexcept
            {
                return x == other.x && y == other.y && z == other.z && w == other.w;
            }

            inline constexpr bool operator != (const vec4& other) const noexcept
            {
                return x != other.x || y != other.y || z != other.z || w != other.w;
            }

            constexpr vec4& operator = (const vec4& other) noexcept
            {
                set(const_cast<T*>(other.v));

                return *this;
            }

            constexpr vec4& operator = (vec4&& other) noexcept
            {
                v[0] = std::move(other.v[0]);
                v[1] = std::move(other.v[1]);
                v[2] = std::move(other.v[2]);
                v[3] = std::move(other.v[3]);

                return *this;
            }

            vec4& operator += (const vec4& other) noexcept
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_load_ps(v);
                    __m128 him = _mm_load_ps(other.v);
                    __m128 res = _mm_add_ps(me, him);

                    _mm_store_ps(v, res);

                    return *this;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m256d me = _mm256_load_pd(v);
                    __m256d him = _mm256_load_pd(other.v);
                    __m256d res = _mm256_add_pd(me, him);

                    _mm256_store_pd(v, res);

                    return *this;
                }

                x += other.x;
                y += other.y;
                z += other.z;
                w += other.w;

                return *this;
            }

            vec4& operator -= (const vec4& other) noexcept
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_load_ps(v);
                    __m128 him = _mm_load_ps(other.v);
                    __m128 res = _mm_sub_ps(me, him);

                    _mm_store_ps(v, res);

                    return *this;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m256d me = _mm256_load_pd(v);
                    __m256d him = _mm256_load_pd(other.v);
                    __m256d res = _mm256_sub_pd(me, him);

                    _mm256_store_pd(v, res);

                    return *this;
                }

                x -= other.x;
                y -= other.y;
                z -= other.z;
                w -= other.w;

                return *this;
            }

            vec4& operator *= (const vec4& other) noexcept
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_load_ps(v);
                    __m128 him = _mm_load_ps(other.v);
                    __m128 res = _mm_mul_ps(me, him);

                    _mm_store_ps(v, res);

                    return *this;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m256d me = _mm256_load_pd(v);
                    __m256d him = _mm256_load_pd(other.v);
                    __m256d res = _mm256_mul_pd(me, him);

                    _mm256_store_pd(v, res);

                    return *this;
                }

                x *= other.x;
                y *= other.y;
                z *= other.z;
                w *= other.w;

                return *this;
            }

            vec4& operator *= (const T other) noexcept
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_load_ps(v);
                    __m128 him = _mm_broadcast_ss(&other);
                    __m128 res = _mm_mul_ps(me, him);

                    _mm_store_ps(v, res);

                    return *this;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m256d me = _mm256_load_pd(v);
                    __m256d him = _mm256_set1_pd(other);
                    __m256d res = _mm256_mul_pd(me, him);

                    _mm256_store_pd(v, res);

                    return *this;
                }

                x *= other;
                y *= other;
                z *= other;
                w *= other;

                return *this;
            }

            vec4& operator /= (const vec4& other) noexcept
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_load_ps(v);
                    __m128 him = _mm_load_ps(other.v);
                    __m128 res = _mm_div_ps(me, him);

                    _mm_store_ps(v, res);

                    return *this;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m256d me = _mm256_load_pd(v);
                    __m256d him = _mm256_load_pd(other.v);
                    __m256d res = _mm256_div_pd(me, him);

                    _mm256_store_pd(v, res);

                    return *this;
                }

                x /= other.x;
                y /= other.y;
                z /= other.z;
                w /= other.w;

                return *this;
            }

            vec4& operator /= (const T other) noexcept
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_load_ps(v);
                    __m128 him = _mm_broadcast_ss(&other);
                    __m128 res = _mm_div_ps(me, him);

                    _mm_store_ps(v, res);

                    return *this;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m256d me = _mm256_load_pd(v);
                    __m256d him = _mm256_set1_pd(other);
                    __m256d res = _mm256_div_pd(me, him);

                    _mm256_store_pd(v, res);

                    return *this;
                }

                x /= other;
                y /= other;
                z /= other;
                w /= other;

                return *this;
            }

            // Operations
            SML_NO_DISCARD inline constexpr T dot(const vec4& other) const noexcept
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

                return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
            }

            SML_NO_DISCARD inline constexpr T length() const noexcept
            {
                return sml::sqrt((x * x) + (y * y) + (z * z) + (w * w));
            }

            SML_NO_DISCARD inline constexpr T lengthsquared() const noexcept
            {
                return (x * x) + (y * y) + (z * z) + (w * w);
            }

            inline constexpr void normalize() noexcept
            {
                float mag = length();

                if(mag > constants::epsilon)
                    *this /= length();
                else
                    set(0);
            }

            SML_NO_DISCARD inline constexpr vec4 normalized() const noexcept
            {
                vec4 copy(const_cast<T*>(v));
                copy.normalize();

                return copy;
            }

            SML_NO_DISCARD inline constexpr bool any() const noexcept
            {
                return x || y || z || w;
            }

            SML_NO_DISCARD inline constexpr bool all() const noexcept
            {
                return x && y && z && w;
            } 

            SML_NO_DISCARD inline constexpr bool none() const noexcept
            {
                return !x && !y && !z && !w;
            }

            SML_NO_DISCARD inline std::string toString() const noexcept
            {
                return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w);
            }

            // Statics
            SML_NO_DISCARD static inline constexpr vec4 normalize(const vec4& a) noexcept
            {
                vec4 copy(a.v);
                copy.normalize();

                return copy;
            }

            SML_NO_DISCARD static inline constexpr T dot(const vec4& lhs, const vec4& rhs) noexcept
            {
                return lhs.dot(rhs);
            }

            SML_NO_DISCARD static inline constexpr T distance(const vec4& a, const vec4& b) noexcept
            {
                vec4 delta = b - a;
                return delta.length();
            }

            SML_NO_DISCARD static inline constexpr vec4 min(const vec4& a, const vec4& b) noexcept
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
                    sml::min(a.y, b.y),
                    sml::min(a.z, b.z),
                    sml::min(a.w, b.w)
                };
            }

            SML_NO_DISCARD static inline constexpr vec4 max(const vec4& a, const vec4& b) noexcept
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
                    sml::max(a.y, b.y),
                    sml::max(a.z, b.z),
                    sml::max(a.w, b.w)
                };
            }

            SML_NO_DISCARD static inline constexpr vec4 clamp(const vec4& v, const vec4& a, const vec4& b) noexcept
            {
                return max(a, min(v, b));
            }

            SML_NO_DISCARD static inline constexpr vec4 lerp(const vec4& a, const vec4& b, T t) noexcept
            {
                T retX = sml::lerp(a.x, b.x, t);
                T retY = sml::lerp(a.y, b.y, t);
                T retZ = sml::lerp(a.z, b.z, t);
                T retW = sml::lerp(a.w, b.w, t);

                return vec4(retX, retY, retZ, retW);
            }

            SML_NO_DISCARD static inline constexpr vec4 lerpclamped(const vec4& a, const vec4& b, T t) noexcept
            {
                T retX = sml::lerpclamped(a.x, b.x, t);
                T retY = sml::lerpclamped(a.y, b.y, t);
                T retZ = sml::lerpclamped(a.z, b.z, t);
                T retW = sml::lerpclamped(a.w, b.w, t);

                return vec4(retX, retY, retZ, retW);
            }

            SML_NO_DISCARD static inline constexpr vec4 project(const vec4& a, const vec4& b) noexcept
            {
                return b * (dot(a, b) / dot(b, b));
            }

            // Data
            union
            {
                struct
                {
                    T x, y, z, w;
                };

                T v[4];
            };
    };

    // Operators
    template<typename T>
    constexpr vec4<T> operator + (const vec4<T>& left, const vec4<T>& right) noexcept
    {
        vec4<T> temp = left;
        temp += right;

        return temp;
    }

    template<typename T>
    constexpr vec4<T> operator - (const vec4<T>& left, const vec4<T>& right) noexcept
    {
        vec4<T> temp = left;
        temp -= right;

        return temp;
    }

    template<typename T>
    vec4<T> operator * (const vec4<T>& left, const vec4<T>& right) noexcept
    {
        vec4<T> temp = left;
        temp *= right;

        return temp;
    }

    template<typename T>
    constexpr vec4<T> operator * (const vec4<T>& left, T right) noexcept
    {
        vec4<T> temp = left;
        temp *= right;

        return temp;
    }

    template<typename T>
    constexpr vec4<T> operator / (const vec4<T>& left, const vec4<T>& right) noexcept
    {
        vec4<T> temp = left;
        temp /= right;

        return temp;
    }

    template<typename T>
    constexpr vec4<T> operator / (const vec4<T>& left, T right) noexcept
    {
        vec4<T> temp = left;
        temp /= right;
        
        return temp;
    }

    template<typename T>
    constexpr vec4<T> operator - (vec4<T> left) noexcept
    {
        vec4<T> temp = left;
        temp *= -1;

        return temp;
    }

    // Predefined types
    typedef vec4<bool> bvec4;
    typedef vec4<u32> uvec4;
    typedef vec4<s32> ivec4;
    typedef vec4<f32> fvec4;
    typedef vec4<f64> dvec4;

    template<typename T>
    class vec4view
    {
    public:
        constexpr vec4view() = default;

        constexpr vec4view(const vec4<T>& other) noexcept
        {
            x = other.x;
            y = other.y;
            z = other.z;
            w = other.w;
        }

        constexpr vec4view(vec4<T>&& other) noexcept
        {
            x = std::move(other.x);
            y = std::move(other.y);
            z = std::move(other.z);
            w = std::move(other.w);
        }

        constexpr vec4view& operator = (const vec4<T>& other) noexcept
        {
            x = other.x;
            y = other.y;
            z = other.z;
            w = other.w;

            return *this;
        }

        constexpr vec4view& operator = (vec4<T>&& other) noexcept
        {
            x = std::move(other.x);
            y = std::move(other.y);
            z = std::move(other.z);
            w = std::move(other.w);

            return *this;
        }

        T x = static_cast<T>(0), y = static_cast<T>(0), z = static_cast<T>(0), w = static_cast<T>(0);
    };

    template<typename T>
    constexpr vec4<T>& vec4<T>::operator = (const vec4view<T>& other) noexcept
    {
        x = other.x;
        y = other.y;
        z = other.z;

        return *this;
    }

    template<typename T>
    constexpr vec4<T>& vec4<T>::operator = (vec4view<T>&& other) noexcept
    {
        x = std::move(other.x);
        y = std::move(other.y);
        z = std::move(other.z);

        return *this;
    }
} // namespace sml

#endif // sml_vec4_h__