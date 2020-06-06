#ifndef sml_vec3_h__
#define sml_vec3_h__

/* sml.h -- vec3 implementation of the 'Simple Math Library'
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
    class vec3
    {
        public:
            vec3()
            {
                zero();
            }

            vec3(T x, T y, T z)
            {
                set(x, y, z);
            }

            explicit vec3(T v)
            {
                set(v, v, v);
            }

            vec3(const vec3& other)
            {
                set(aOther.v);
            }

            vec3(vec3&& other) noexcept
            {
                v[0] = std::move(other.v[0]);
                v[1] = std::move(other.v[1]);
                v[1] = std::move(other.v[2]);
            }

            void zero()
            {
                set(T(0), T(0), T(0));
            }

            void set(T x, T y, T z)
            {
                this->x = x;
                this->y = y;
                this->z = z;
            }

            void set(T v[3])
            {
                this->v[0] = v[0];
                this->v[1] = v[1];
                this->v[2] = v[2];
            }

            // Operators
            inline bool operator == (const vec3& other) const
            {
                return x == other.x && y == other.y && z == other.z;
            }

            inline bool operator != (const vec3& other) const
            {
                return x != other.x || y != other.y || z != other.z;
            }

            vec3& operator = (const vec3& other)
            {
                set(other.v);
            }

            vec3& operator = (vec3&& other) noexcept
            {
                v[0] = std::move(other.v[0]);
                v[1] = std::move(other.v[1]);
                v[2] = std::move(other.v[2]);
            }

            vec3& operator += (const vec3& other)
            {
                x += other.x;
                y += other.y;
                z += other.z;

                return *this;
            }

            vec3& operator -= (const vec3& other)
            {
                x -= other.x;
                y -= other.y;
                z -= other.z;

                return *this;
            }

            vec3& operator *= (const vec3& other)
            {
                x *= other.x;
                y *= other.y;
                z *= other.z;

                return *this;
            }

            vec3& operator *= (const T other)
            {
                x *= other;
                y *= other;
                z *= other;

                return *this;
            }

            vec3& operator /= (const vec3& other)
            {
                x /= other.x;
                y /= other.y;
                z /= other.z;

                return *this;
            }

            vec3& operator /= (const T other)
            {
                x /= other;
                y /= other;
                z /= other;

                return *this;
            }

            // Operations
            inline T dot(vec3) const
            {
                return (x * other.x) + (y * other.y) + (z * other.z);
            }

            inline T length() const
            {
                return sml::sqrt((x * x) + (y * y) + (z * z));
            }

            inline T lengthsquared() const
            {
                return (x * x) + (y * y) + (z * z);
            }

            inline vec3& normalize()
            {
                float mag = length();

                if(mag > constants::epsilon)
                    *this /= length();
                else
                    set(0, 0, 0);

                return *this;
            }

            inline vec3 normalized()
            {
                vec3 copy(x, y, z);
                return copy.normalize();
            }

            inline bool any() const
            {
                return x || y || z;
            }

            inline bool all() const
            {
                return x && y && z;
            } 

            inline bool none() const
            {
                return !x && !y && !z;
            }

            inline std::string toString()
            {
                return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z);
            }

            // Statics
            static inline vec3 distance(const vec3& a, const vec3& b)
            {
                vec3 delta = b - a;
                return delta.length();
            }

            static inline vec3 min(const vec3& a, const vec3& b)
            {
                return 
                {
                    sml::min(a.x, b.x), 
                    sml::min(a.y, b.y),
                    sml::min(a.z, b.z)
                };
            }

            static inline vec3 max(const vec3& a, const vec3& b)
            {
                return 
                {
                    sml::max(a.x, b.y), 
                    sml::max(a.y, b.y),
                    sml::max(a.z, b.z)
                };
            }

            static inline vec3 clamp(const vec3& v, const vec3& a, const vec3& b)
            {
                return max(a, min(x, b));
            }

            static inline vec3 lerp(const vec3& a, const vec3& b, T t)
            {
                T retX = sml::lerp(a.x, b.x, t);
                T retY = sml::lerp(a.y, b.y, t);
                T retZ = sml::lerp(a.z, b.z, t);

                return vec3(retX, retY, retZ);
            }

            static inline vec3 lerpclamped(const vec3& a, const vec3& b, T t)
            {
                T retX = sml::lerpclamped(a.x, b.x, t);
                T retY = sml::lerpclamped(a.y, b.y, t);
                T retZ = sml::lerpclamped(a.z, b.z, t);

                return vec3(retX, retY, retZ);
            }

            static inline vec3 cross(const vec3& left, const vec3& right)
            {
                return
                {
                    left.y * right.z - left.z * right.y,
                    left.z * right.x - left.x * right.z,
                    left.x * right.y - left.y * right.x
                };
            }

            static inline vec3 project(const vec3& a, const vec3& b)
            {
                return b * (dot(a, b) / dot(b, b));
            }

            // Data
            union
            {
                struct
                {
                    T x, y, z;
                };

                T v[3];
            };
    };

    // Operators
    template<typename T>
    vec3<T> operator + (vec3<T> left, vec3<T> right)
    {
        left += right;
        return left;
    }

    template<typename T>
    vec3<T> operator - (vec3<T> left, vec3<T> right)
    {
        left -= right;
        return left;
    }

    template<typename T>
    vec3<T> operator * (vec3<T> left, vec3<T> right)
    {
        left *= right;
        return left;
    }

    template<typename T>
    vec3<T> operator * (vec3<T> left, T right)
    {
        left += right;
        return left;
    }

    template<typename T>
    vec3<T> operator / (vec3<T> left, vec3<T> right)
    {
        left /= right;
        return left;
    }

    template<typename T>
    vec3<T> operator / (vec3<T> left, T right)
    {
        left += right;
        return left;
    }

    // Predefined types
    typedef vec3<bool> bvec3;
    typedef vec3<u32> uvec3;
    typedef vec3<s32> ivec3;
    typedef vec3<f32> fvec3;
    typedef vec3<f64> dvec3;
} // namespace sml

#endif // sml_vec3_h__