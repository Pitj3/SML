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

#include "smltypes.h"
#include "config.h"

namespace sml
{
    template<typename T>
    class vec4
    {
        public:
            vec4()
            {
                zero();
            }

            vec4(T x, T y, T z, T w)
            {
                set(x, y, z, w);
            }

            explicit vec4(T v)
            {
                set(v, v, v, v);
            }

            vec4(const vec4& other)
            {
                set(aOther.v);
            }

            vec4(vec4&& other) noexcept
            {
                v[0] = std::move(other.v[0]);
                v[1] = std::move(other.v[1]);
                v[1] = std::move(other.v[2]);
                v[3] = std::move(other.v[3]);
            }

            void zero()
            {
                set(T(0), T(0), T(0), T(0));
            }

            void set(T x, T y, T z, T w)
            {
                this->x = x;
                this->y = y;
                this->z = z;
                this->w = w;
            }

            void set(T v[4])
            {
                this->v[0] = v[0];
                this->v[1] = v[1];
                this->v[2] = v[2];
                this->v[3] = v[3];
            }

            // Operators 
            inline bool operator == (const vec4& other) const
            {
                return x == other.x && y == other.y && z == other.z && w == other.w;
            }

            inline bool operator != (const vec4& other) const
            {
                return x != other.x || y != other.y || z != other.z || w != other.w;
            }

            vec4& operator = (const vec4& other)
            {
                set(other.v);

                return *this;
            }

            vec4& operator = (vec4&& other) noexcept
            {
                v[0] = std::move(other.v[0]);
                v[1] = std::move(other.v[1]);
                v[2] = std::move(other.v[2]);
                v[3] = std::move(other.v[3]);

                return *this;
            }

            vec4& operator += (const vec4& other)
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_set_ps(v[0], v[1], v[2], v[3]);
                    __m128 him = _mm_set_ps(other.v[0], other.v[1], other.v[2], other.v[3]);
                    __m128 res = _mm_add_ps(me, him);

                    _mm_storer_ps(v, res);

                    return *this;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m256d me = _mm256_set_pd(v[0], v[1], v[2], v[3]);
                    __m256d him = _mm256_set_pd(other.v[0], other.v[1], other.v[2], other.v[3]);
                    __m256d res = _mm256_add_pd(me, him);

                    _mm_storer_pd(v, res);

                    return *this;
                }

                x += other.x;
                y += other.y;
                z += other.z;
                w += other.w;

                return *this;
            }

            vec4& operator -= (const vec4& other)
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_set_ps(v[0], v[1], v[2], v[3]);
                    __m128 him = _mm_set_ps(other.v[0], other.v[1], other.v[2], other.v[3]);
                    __m128 res = _mm_sub_ps(me, him);

                    _mm_storer_ps(v, res);

                    return *this;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m256d me = _mm256_set_pd(v[0], v[1], v[2], v[3]);
                    __m256d him = _mm256_set_pd(other.v[0], other.v[1], other.v[2], other.v[3]);
                    __m256d res = _mm256_sub_pd(me, him);

                    _mm_storer_pd(v, res);

                    return *this;
                }

                x -= other.x;
                y -= other.y;
                z -= other.z;
                w -= other.w;

                return *this;
            }

            vec4& operator *= (const vec4& other)
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_set_ps(v[0], v[1], v[2], v[3]);
                    __m128 him = _mm_set_ps(other.v[0], other.v[1], other.v[2], other.v[3]);
                    __m128 res = _mm_mul_ps(me, him);

                    _mm_storer_ps(v, res);

                    return *this;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m256d me = _mm256_set_pd(v[0], v[1], v[2], v[3]);
                    __m256d him = _mm256_set_pd(other.v[0], other.v[1], other.v[2], other.v[3]);
                    __m256d res = _mm256_mul_pd(me, him);

                    _mm_storer_pd(v, res);

                    return *this;
                }

                x *= other.x;
                y *= other.y;
                z *= other.z;
                w *= other.w;

                return *this;
            }

            vec4& operator *= (const T other)
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_set_ps(v[0], v[1], v[2], v[3]);
                    __m128 him = _mm_set_ps1(other);
                    __m128 res = _mm_mul_ps(me, him);

                    _mm_storer_ps(v, res);

                    return *this;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m256d me = _mm256_set_pd(v[0], v[1], v[2], v[3]);
                    __m256d him = _mm256_set_pd1(other);
                    __m256d res = _mm256_mul_pd(me, him);

                    _mm_storer_pd(v, res);

                    return *this;
                }

                x *= other;
                y *= other;
                z *= other;
                w *= other;

                return *this;
            }

            vec4& operator /= (const vec4& other)
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_set_ps(v[0], v[1], v[2], v[3]);
                    __m128 him = _mm_set_ps(other.v[0], other.v[1], other.v[2], other.v[3]);
                    __m128 res = _mm_div_ps(me, him);

                    _mm_storer_ps(v, res);

                    return *this;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m256d me = _mm256_set_pd(v[0], v[1], v[2], v[3]);
                    __m256d him = _mm256_set_pd(other.v[0], other.v[1], other.v[2], other.v[3]);
                    __m256d res = _mm256_div_pd(me, him);

                    _mm_storer_pd(v, res);

                    return *this;
                }

                x /= other.x;
                y /= other.y;
                z /= other.z;
                w /= other.w;

                return *this;
            }

            vec4& operator /= (const T other)
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_set_ps(v[0], v[1], v[2], v[3]);
                    __m128 him = _mm_set_ps1(other);
                    __m128 res = _mm_div_ps(me, him);

                    _mm_storer_ps(v, res);

                    return *this;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m256d me = _mm256_set_pd(v[0], v[1], v[2], v[3]);
                    __m256d him = _mm256_set_pd1(other);
                    __m256d res = _mm256_div_pd(me, him);

                    _mm_storer_pd(v, res);

                    return *this;
                }

                x /= other;
                y /= other;
                z /= other;
                w /= other;

                return *this;
            }

            // Operations
            inline T dot(vec4) const
            {
                return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
            }

            inline T length() const
            {
                return sml::sqrt((x * x) + (y * y) + (z * z) + (w * w));
            }

            inline T lengthsquared() const
            {
                return (x * x) + (y * y) + (z * z) + (w * w);
            }

            inline vec4& normalize()
            {
                float mag = length();

                if(mag > constants::epsilon)
                    *this /= length();
                else
                    set(0, 0, 0, 0);

                return *this;
            }

            inline vec4 normalized()
            {
                vec4 copy(x, y, z, w);
                return copy.normalize();
            }

            inline bool any() const
            {
                return x || y || z || w;
            }

            inline bool all() const
            {
                return x && y && z && w;
            } 

            inline bool none() const
            {
                return !x && !y && !z && !w;
            }

            inline std::string toString()
            {
                return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w);
            }

            // Statics
            static inline vec4 distance(const vec4& a, const vec4& b)
            {
                vec4 delta = b - a;
                return delta.length();
            }

            static inline vec4 min(const vec4& a, const vec4& b)
            {
                return 
                {
                    sml::min(a.x, b.x), 
                    sml::min(a.y, b.y),
                    sml::min(a.z, b.z),
                    sml::min(a.w, b.w)
                };
            }

            static inline vec4 max(const vec4& a, const vec4& b)
            {
                return 
                {
                    sml::max(a.x, b.y), 
                    sml::max(a.y, b.y),
                    sml::max(a.z, b.z),
                    sml::max(a.w, b.w)
                };
            }

            static inline vec4 clamp(const vec4& v, const vec4& a, const vec4& b)
            {
                return max(a, min(x, b));
            }

            static inline vec4 lerp(const vec4& a, const vec4& b, T t)
            {
                T retX = sml::lerp(a.x, b.x, t);
                T retY = sml::lerp(a.y, b.y, t);
                T retZ = sml::lerp(a.z, b.z, t);
                T retW = sml::lerp(a.w, b.w, t);

                return vec4(retX, retY, retZ, retW);
            }

            static inline vec4 lerpclamped(const vec4& a, const vec4& b, T t)
            {
                T retX = sml::lerpclamped(a.x, b.x, t);
                T retY = sml::lerpclamped(a.y, b.y, t);
                T retZ = sml::lerpclamped(a.z, b.z, t);
                T retW = sml::lerpclamped(a.w, b.w, t);

                return vec4(retX, retY, retZ, retW);
            }

            static inline vec4 project(const vec4& a, const vec4& b)
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
    vec4<T> operator + (vec4<T> left, vec4<T> right)
    {
        left += right;
        return left;
    }

    template<typename T>
    vec4<T> operator - (vec4<T> left, vec4<T> right)
    {
        left -= right;
        return left;
    }

    template<typename T>
    vec4<T> operator * (vec4<T> left, vec4<T> right)
    {
        left *= right;
        return left;
    }

    template<typename T>
    vec4<T> operator * (vec4<T> left, T right)
    {
        left += right;
        return left;
    }

    template<typename T>
    vec4<T> operator / (vec4<T> left, vec4<T> right)
    {
        left /= right;
        return left;
    }

    template<typename T>
    vec4<T> operator / (vec4<T> left, T right)
    {
        left += right;
        return left;
    }

    // Predefined types
    typedef vec4<bool> bvec4;
    typedef vec4<u32> uvec4;
    typedef vec4<s32> ivec4;
    typedef vec4<f32> fvec4;
    typedef vec4<f64> dvec4;
} // namespace sml

#endif // sml_vec4_h__