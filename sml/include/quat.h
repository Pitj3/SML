#ifndef sml_quat_h__
#define sml_quat_h__

/* quat.h -- quaternion implementation of the 'Simple Math Library'
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

#include "common.h"
#include "smltypes.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"

namespace sml
{
	template<typename T>
	class alignas(simdalign<T>::value) quat
	{
		public:
			constexpr quat() noexcept
			{
				v.zero();
			}

            constexpr quat(T x, T y, T z, T w) noexcept
            {
                this->x = x;
                this->y = y;
                this->z = z;
                this->w = w;
            }

            constexpr quat(T* v) noexcept
            {
                for (int i = 0; i < 4; i++)
                {
                    this->v.v[i] = v[i];
                }
            }

            constexpr quat(const vec3<T>& xyz, T w) noexcept
            {
                this->xyz = xyz;
                this->w = w;
            }

            constexpr quat(T w, const vec3<T>& xyz) noexcept
            {
                this->xyz = xyz;
                this->w = w;
            }

            constexpr quat(const vec4<T>& other) noexcept
            {
                v = other;
            }

            constexpr explicit quat(T v) noexcept
            {
                x = y = z = w = v;
            }

            constexpr quat(const quat& other) noexcept
            {
                set(const_cast<T*>(other.v.v));
            }

            constexpr quat(quat&& other) noexcept
            {
                set(std::move(other.v.v));
            }

            constexpr void zero() noexcept
            {
                x = y = z = w = static_cast<T>(0);
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
                this->x = v[0];
                this->y = v[1];
                this->z = v[2];
                this->w = v[3];
            }

            constexpr void set(const vec4<T>& other) noexcept
            {
                v = other;
            }

            constexpr void set(const vec3<T>& xyz, T scalar)
            {
                this->xyz = xyz;
                w = scalar;
            }

            constexpr void set(T scalar, const vec3<T>& xyz)
            {
                this->xyz = xyz;
                w = scalar;
            }

            // Operators
            inline constexpr bool operator == (const quat& other) const noexcept
            {
                return sml::abs(v.normalized().dot(other.v.normalized())) > static_cast<T>(0.999999);
            }

            inline constexpr bool operator != (const quat& other) const noexcept
            {
                return sml::abs(v.normalized().dot(other.v.normalized())) <= static_cast<T>(0.999999);
            }

            constexpr quat& operator = (const quat& other) noexcept
            {
                set(other.v);

                return *this;
            }

            constexpr quat& operator = (quat&& other) noexcept
            {
                set(std::move(other.v));

                return *this; 
            }

            quat& operator += (const quat& other) noexcept
            {
                v += other.v;
                return *this;
            }

            quat& operator -= (const quat& other) noexcept
            { 
                v -= other.v;
                return *this;
            }

            quat& operator *= (const quat& other) noexcept
            {
                alignas(simdalign<T>::value) vec3<T> res = (xyz * other.w) + (other.xyz * other.w) + vec3<T>::cross(xyz, other.xyz);
                T scalar = (w * other.w) - vec3<T>::dot(xyz, other.xyz);

                set(res, scalar);

                return *this;
            }

            quat& operator *= (const T other) noexcept
            {
                v *= other;
                return *this;
            }

            // Operations 
            inline constexpr void normalize() noexcept
            {
                T scale = length();

                v /= scale;
            }

            SML_NO_DISCARD inline constexpr quat normalized() const noexcept
            {
                quat q(v);
                q.normalize();

                return q;
            }

            SML_NO_DISCARD inline constexpr T length() const noexcept
            {
                return v.length();
            }

            SML_NO_DISCARD inline constexpr T lengthsquared() const noexcept
            {
                return v.lengthsquared();
            }

            SML_NO_DISCARD inline constexpr quat conjugate() const noexcept
            {
                quat q(v);
                q.xyz = -q.xyz;

                return q;
            }

            inline constexpr void invert() noexcept
            {
                T lengthSq = lengthsquared();
                if (lengthSq != static_cast<T>(0))
                {
                    T i = lengthSq;
                    xyz /= -i;
                    w /= i;
                }
            }

            SML_NO_DISCARD inline constexpr quat inverse() const noexcept
            {
                quat q(v);
                q.invert();

                return q;
            }

            SML_NO_DISCARD inline constexpr T dot(const quat& other) const noexcept
            {
                return v.dot(other.v);
            }

            SML_NO_DISCARD inline constexpr vec3<T> normalizeAngles(vec3<T> angles) const noexcept
            {
                alignas(simdalign<T>::value) vec3<T> v(angles);

                v.x = normalizeAngle(angles.x);
                v.y = normalizeAngle(angles.y);
                v.z = normalizeAngle(angles.z);

                return v;
            }

            SML_NO_DISCARD inline constexpr vec3<T> eulerAngles() const noexcept
            {
                T sqw = w * w;
                T sqx = x * x;
                T sqy = y * y;
                T sqz = z * z;
                T unit = sqx + sqy + sqz + sqw;
                T singularityTest = (x * w) - (y * z);

                vec3<T> res;

                if (singularityTest > static_cast<T>(0.4995 * unit))
                {
                    res.y = static_cast<T>(2) * sml::atan2(y, x);
                    res.z = constants::pi / static_cast<T>(2);
                    res.x = static_cast<T>(0);

                    res *= static_cast<T>(constants::rad2deg);

                    return normalizeAngles(res);
                }

                if (singularityTest < static_cast<T>(-0.4995 * unit))
                {
                    res.y = static_cast<T>(-2) * sml::atan2(y, x);
                    res.z = -constants::pi / static_cast<T>(2);
                    res.x = static_cast<T>(0);

                    res *= static_cast<T>(constants::rad2deg);

                    return normalizeAngles(res);
                }

                quat q(x, y, z, w);
                res.y = sml::atan2(static_cast<T>(2) * q.x * q.w + static_cast<T>(2) * q.y * q.z, static_cast<T>(1) - static_cast<T>(2) * (q.z * q.z + q.w * q.w));
                res.z = sml::asin(static_cast<T>(2) * (q.x * q.z - q.w * q.y));
                res.x = sml::atan2(static_cast<T>(2) * q.x * q.y + static_cast<T>(2) * q.z * q.w, static_cast<T>(1) - static_cast<T>(2) * (q.y * q.y + q.z * q.z));

                res *= static_cast<T>(constants::rad2deg);

                return normalizeAngles(res);
            }

            // Statics
            SML_NO_DISCARD inline static constexpr quat identity() noexcept
            {
                return quat(0, 0, 0, 1);
            }

            SML_NO_DISCARD inline static constexpr quat normalize(const quat& value) noexcept
            {
                return value.normalized();
            }

            SML_NO_DISCARD inline static constexpr quat invert(const quat& value) noexcept
            {
                return value.inverse();
            }

            SML_NO_DISCARD inline static constexpr quat euler(const vec3<T>& rotation) noexcept
            {
                vec3<T> copyRotation = rotation;

                copyRotation *= constants::deg2rad;

                T yaw = copyRotation.x;
                T pitch = copyRotation.y;
                T roll = copyRotation.z;

                T c1 = sml::cos(yaw / static_cast<T>(2));
                T c2 = sml::cos(pitch / static_cast<T>(2));
                T c3 = sml::cos(roll / static_cast<T>(2));
                
                T s1 = sml::sin(yaw / static_cast<T>(2));
                T s2 = sml::sin(pitch / static_cast<T>(2));
                T s3 = sml::sin(roll / static_cast<T>(2));

                quat result;

                result.x = s1 * c2 * c3 + c1 * s2 * s3;
                result.y = c1 * s2 * c3 - s1 * c2 * s3;
                result.z = c1 * c2 * s3 + s1 * s2 * c3;
                result.w = c1 * c2 * c3 - s1 * s2 * s3;

                return result;
            }

            SML_NO_DISCARD inline static constexpr quat euler(T x, T y, T z) noexcept
            {
                return euler({ x, y, z });
            }

            SML_NO_DISCARD inline static constexpr quat axisangle(const vec3<T>& axis, T angle) noexcept
            {
                if (axis.lengthsquared() == static_cast<T>(0))
                {
                    return identity();
                }

                quat q = identity();

                angle *= static_cast<T>(0.5);
                axis.normalize();

                q.xyz = axis * sml::sin(angle);
                q.w = sml::cos(angle);

                return q.normalized();
            }

            SML_NO_DISCARD inline static constexpr quat frommatrix3(const mat3<T>& matrix)
            {
                // TODO (Roderick): Implement this
                return quat();
            }

            SML_NO_DISCARD inline static constexpr quat slerp(const quat<T>& a, const quat<T>& b, T blend) noexcept
            {
                if (a.lengthsquared() == static_cast<T>(0))
                {
                    if (b.lengthsquared() == static_cast<T>(0))
                    {
                        return identity();
                    }

                    return b;
                }

                if (b.lengthsquared() == static_cast<T>(0))
                {
                    return a;
                }

                T coshalfangle = (a.w * b.w) + vec3<T>::dot(a.xyz, b.xyz);
                if (coshalfangle >= static_cast<T>(1) || coshalfangle <= static_cast<T>(-1))
                {
                    return a;
                }

                if (coshalfangle < static_cast<T>(0))
                {
                    b.xyz = -b.xyz;
                    a.w = -a.w;
                    coshalfangle = -coshalfangle;
                }

                T blendA, blendB;
                if (coshalfangle < static_cast<T>(0.99))
                {
                    T halfangle = sml::acos(coshalfangle);
                    T sinhalfangle = sml::sin(halfangle);
                    T oneoversinhalfangle = static_cast<T>(1) / sinhalfangle;
                    blendA = sml::sin(halfangle * (static_cast<T>(1) - blend)) * oneoversinhalfangle;
                    blendB = sml::sin(halfangle * blend) * oneoversinhalfangle;
                }
                else
                {
                    blendA = static_cast<T>(1) - blend;
                    blendB = blend;
                }

                quat res((blendA * a.xyz) + (blendB * b.xyz), (blendA * a.w) + (blendB * b.w));
                if (res.lengthsquared() > static_cast<T>(0))
                {
                    return res.normalized();
                }

                return identity();
            }

            // Data
			union
			{
				struct
				{
					T x, y, z, w;
				};

                struct
                {
                    vec3<T> xyz;
                    T s;
                };

				vec4<T> v;
			};
	};

    // Operators
    template<typename T>
    constexpr quat<T> operator + (quat<T> left, quat<T> right) noexcept
    {
        quat<T> temp = left;
        temp += right;

        return temp;
    }

    template<typename T>
    constexpr quat<T> operator - (quat<T> left, quat<T> right) noexcept
    {
        quat<T> temp = left;
        temp -= right;

        return temp;
    }

    template<typename T>
    constexpr quat<T> operator * (quat<T> left, quat<T> right) noexcept
    {
        quat<T> temp = left;
        temp *= right;

        return temp;
    }

    template<typename T>
    constexpr vec3<T> operator * (quat<T> left, vec3<T> right) noexcept
    {
        T num = left.x * static_cast<T>(2);
        T num2 = left.y * static_cast<T>(2);
        T num3 = left.z * static_cast<T>(2);
        T num4 = left.x * num;
        T num5 = left.y * num2;
        T num6 = left.z * num3;
        T num7 = left.x * num2;
        T num8 = left.x * num3;
        T num9 = left.y * num3;
        T num10 = left.w * num;
        T num11 = left.w * num2;
        T num12 = left.w * num3;

        vec3<T> res;
        res.x = (static_cast<T>(1) - (num5 + num6)) * right.x + (num7 - num12) * right.y + (num8 + num11) * right.z;
        res.y = (num7 + num12) * right.x + (static_cast<T>(1) - (num4 + num6)) * right.y + (num9 - num10) * right.z;
        res.z = (num8 - num11) * right.x + (num9 + num10) * right.y + (static_cast<T>(1) - (num4 + num5)) * right.z;

        return res;
    }

    typedef quat<f32> fquat;
    typedef quat<f64> dquat;
} // namespace sml

#endif // sml_quat_h__