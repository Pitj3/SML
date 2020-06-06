#ifndef sml_vec2_h__
#define sml_vec2_h__

/* sml.h -- vec2 implementation of the 'Simple Math Library'
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

namespace sml
{
    template<typename T>
    class vec2
    {
        public:
            vec2()
            {
                zero();
            }

            vec2(T x, T y)
            {
                set(x, y);
            }

            explicit vec2(T v)
            {
                set(v, v);
            }

            vec2(const vec2& other)
            {
                set(aOther.v);
            }

            vec2(vec2&& other) noexcept
            {
                v[0] = std::move(other.v[0]);
                v[1] = std::move(other.v[1]);
            }

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
                return x == other.x && y == other.y;
            }

            inline bool operator != (const vec2& other) const
            {
                return x != other.x || y != other.y;
            }

            vec2& operator = (const vec2& other)
            {
                set(other.v);
            }

            vec2& operator = (vec2&& other) noexcept
            {
                v[0] = std::move(other.v[0]);
                v[1] = std::move(other.v[1]);
            }

            vec2& operator += (const vec2& other)
            {
                x += other.x;
                y += other.y;

                return *this;
            }

            vec2& operator -= (const vec2& other)
            {
                x -= other.x;
                y -= other.y;

                return *this;
            }

            vec2& operator *= (const vec2& other)
            {
                x *= other.x;
                y *= other.y;

                return *this;
            }

            vec2& operator *= (const T other)
            {
                x *= other;
                y *= other;

                return *this;
            }

            vec2& operator /= (const vec2& other)
            {
                x /= other.x;
                y /= other.y;

                return *this;
            }

            vec2& operator /= (const T other)
            {
                x /= other;
                y /= other;

                return *this;
            }

            // Operations
            inline T dot(vec2) const
            {
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
                return 
                {
                    sml::min(a.x, b.x), 
                    sml::min(a.y, b.y)
                };
            }

            static inline vec2 max(const vec2& a, const vec2& b)
            {
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

                T v[2];
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
} // namespace sml

#endif // sml_vec2_h__