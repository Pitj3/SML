#ifndef sml_mat4_h__
#define sml_mat4_h__

/* mat4.h -- column major mat4 implementation of the 'Simple Math Library'
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

#include <immintrin.h>
#include <mmintrin.h>
#include <smmintrin.h>

#include "vec4.h"
#include "smltypes.h"
#include "common.h"

namespace sml
{
    template<typename T>
    class alignas(simdalign<T>::value) mat4
    {
        public:
            constexpr mat4() noexcept
            {
                identity();
            }

            constexpr explicit mat4(T diagonal) noexcept
            {
                m00 = diagonal;
                m10 = static_cast<T>(0);
                m20 = static_cast<T>(0);
                m30 = static_cast<T>(0);
                m01 = static_cast<T>(0);
                m11 = diagonal;
                m21 = static_cast<T>(0);
                m31 = static_cast<T>(0);
                m02 = static_cast<T>(0);
                m12 = static_cast<T>(0);
                m22 = diagonal;
                m32 = static_cast<T>(0);
                m03 = static_cast<T>(0);
                m13 = static_cast<T>(0);
                m23 = static_cast<T>(0);
                m33 = diagonal;
            }

            constexpr mat4(T col1[4], T col2[4], T col3[4], T col4[4]) noexcept
            {
                m00 = col1[0];
                m01 = col1[1];
                m02 = col1[2];
                m03 = col1[3];

                m10 = col2[0];
                m11 = col2[1];
                m12 = col2[2];
                m13 = col2[3];
                
                m20 = col3[0];
                m21 = col3[1];
                m22 = col3[2];
                m23 = col3[3];

                m30 = col4[0];
                m31 = col4[1];
                m32 = col4[2];
                m33 = col4[3];
            }

            constexpr mat4(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22, T m23, T m30, T m31, T m32, T m33) noexcept
            {
                this->m00 = m00;
                this->m10 = m10;
                this->m20 = m20;
                this->m30 = m30;

                this->m01 = m01;
                this->m11 = m11;
                this->m21 = m21;
                this->m31 = m31;
                
                this->m02 = m02;
                this->m12 = m12;
                this->m22 = m22;
                this->m32 = m32;

                this->m03 = m03;
                this->m13 = m13;
                this->m23 = m23;
                this->m33 = m33;
            }

            constexpr mat4(const mat4& other) noexcept
            {
                m00 = other.m00;
                m10 = other.m10;
                m20 = other.m20;
                m30 = other.m30;

                m01 = other.m01;
                m11 = other.m11;
                m21 = other.m21;
                m31 = other.m31;
                
                m02 = other.m02;
                m12 = other.m12;
                m22 = other.m22;
                m32 = other.m32;
                
                m03 = other.m03;
                m13 = other.m13;
                m23 = other.m23;
                m33 = other.m33;
            }

            constexpr mat4(mat4&& other) noexcept
            {
                m00 = std::move(other.m00);
                m10 = std::move(other.m10);
                m20 = std::move(other.m20);
                m30 = std::move(other.m30);

                m01 = std::move(other.m01);
                m11 = std::move(other.m11);
                m21 = std::move(other.m21);
                m31 = std::move(other.m31);

                m02 = std::move(other.m02);
                m12 = std::move(other.m12);
                m22 = std::move(other.m22);
                m32 = std::move(other.m32);

                m03 = std::move(other.m03);
                m13 = std::move(other.m13);
                m23 = std::move(other.m23);
                m33 = std::move(other.m33);
            }

            constexpr void set(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22) noexcept
            {
                this->m00 = m00;
                this->m10 = m10;
                this->m20 = m20;
                this->m30 = m30;

                this->m01 = m01;
                this->m11 = m11;
                this->m21 = m21;
                this->m31 = m31;
                
                this->m02 = m02;
                this->m12 = m12;
                this->m22 = m22;
                this->m32 = m32;

                this->m03 = m03;
                this->m13 = m13;
                this->m23 = m23;
                this->m33 = m33;
            }

            constexpr void set(T v[16]) noexcept
            {
                for(int i = 0; i < 16; i++)
                {
                    this->v[i] = v[i];
                }
            }

            constexpr mat4& operator = (const mat4& other) noexcept
            {
                m00 = other.m00;
                m10 = other.m10;
                m20 = other.m20;
                m30 = other.m30;

                m01 = other.m01;
                m11 = other.m11;
                m21 = other.m21;
                m31 = other.m31;
                
                m02 = other.m02;
                m12 = other.m12;
                m22 = other.m22;
                m32 = other.m32;
                
                m03 = other.m03;
                m13 = other.m13;
                m23 = other.m23;
                m33 = other.m33;

                return *this;
            }

            constexpr mat4& operator = (mat4&& other) noexcept
            {
                m00 = std::move(other.m00);
                m10 = std::move(other.m10);
                m20 = std::move(other.m20);
                m30 = std::move(other.m30);

                m01 = std::move(other.m01);
                m11 = std::move(other.m11);
                m21 = std::move(other.m21);
                m31 = std::move(other.m31);

                m02 = std::move(other.m02);
                m12 = std::move(other.m12);
                m22 = std::move(other.m22);
                m32 = std::move(other.m32);

                m03 = std::move(other.m03);
                m13 = std::move(other.m13);
                m23 = std::move(other.m23);
                m33 = std::move(other.m33);

                return *this;
            }

            // Operators
            inline bool constexpr operator == (const mat4& other) const noexcept
            {
                if constexpr (std::is_same<T, f32>::value)
                {
                    union m128
                    {
                        __m128 f;
                        __m128i i;
                    };

                    s32 result = 1;
                    for (s32 i = 0; i < 4; i++)
                    {
                        __m128 me = _mm_load_ps(&m00 + (4 * i));
                        __m128 ot = _mm_load_ps(&other.m00 + (4 * i));

                        m128 cmp = { _mm_cmpeq_ps(me, ot) };
                        result &= _mm_testc_si128(cmp.i, cmp.i);
                    }

                    return result != 0;
                }

                if constexpr (std::is_same<T, f64>::value)
                {
                    union m256
                    {
                        __m256d d;
                        __m256i i;
                    };

                    s32 result = 1;
                    for (s32 i = 0; i < 4; i++)
                    {
                        __m256d me = _mm256_load_pd(&m00 + (4 * i));
                        __m256d ot = _mm256_load_pd(&other.m00 + (4 * i));
                        
                        m256 cmp = { _mm256_cmp_pd(me, ot, _CMP_EQ_OQ) };
                        
                        result &= _mm256_testc_si256(cmp.i, cmp.i);
                    }

                    return result != 0;
                }

                return m00 == other.m00 && m10 == other.m10 && m20 == other.m20  && m30 == other.m30
                    && m01 == other.m01 && m11 == other.m11 && m21 == other.m21 && m31 == other.m31
                    && m02 == other.m02 && m12 == other.m12 && m22 == other.m22 && m32 == other.m32
                    && m03 == other.m03 && m13 == other.m13 && m23 == other.m23 && m33 == other.m33;
            }

            inline bool constexpr operator != (const mat4& other) const noexcept
            {
                if constexpr (std::is_same<T, f32>::value)
                {
                    union m128
                    {
                        __m128 f;
                        __m128i i;
                    };

                    s32 result = 1;
                    for (s32 i = 0; i < 4; i++)
                    {
                        __m128 me = _mm_load_ps(&m00 + (4 * i + 0));
                        __m128 ot = _mm_load_ps(&other.m00 + (4 * i + 0));

                        m128 cmp = { _mm_cmpneq_ps(me, ot) };
                        result &= _mm_testc_si128(cmp.i, cmp.i);
                    }

                    return result != 0;
                }

                if constexpr (std::is_same<T, f64>::value)
                {
                    union m256
                    {
                        __m256d d;
                        __m256i i;
                    };

                    s32 result = 1;
                    for (s32 i = 0; i < 4; i++)
                    {
                        __m256d me = _mm256_load_pd(&m00 + (2 * i + 0));
                        __m256d me1 = _mm256_load_pd(&m00 + (2 * i + 2));
                        __m256d ot = _mm256_load_pd(&other.m00 + (2 * i + 0));
                        __m256d ot1 = _mm256_load_pd(&other.m00 + (2 * i + 2));
                        
                        m256 cmp = { _mm256_cmp_pd(me, ot, _CMP_NEQ_OQ) };
                        m256 cmp1 = { _mm256_cmp_pd(me1, ot1, _CMP_NEQ_OQ) };
                        
                        result &= _mm256_testc_si256(cmp.i, cmp.i);
                        result &= _mm256_testc_si256(cmp1.i, cmp1.i);
                    }

                    return result != 0;
                }

                return m00 == other.m00 || m10 == other.m10 || m20 == other.m20 || m30 == other.m30
                    || m01 == other.m01 || m11 == other.m11 || m21 == other.m21 || m31 == other.m31
                    || m02 == other.m02 || m12 == other.m12 || m22 == other.m22 || m32 == other.m32
                    || m03 == other.m03 || m13 == other.m13 || m23 == other.m23 || m33 == other.m33;
            }

            mat4& operator *= (const mat4& other) noexcept
            {
                if constexpr (std::is_same<T, f32>::value)
                {
                    __m128 col0 = _mm_load_ps(v + 0);
                    __m128 col1 = _mm_load_ps(v + 4);
                    __m128 col2 = _mm_load_ps(v + 8);
                    __m128 col3 = _mm_load_ps(v + 8);

                    for (s32 i = 0; i < 4; i++)
                    {
                        __m128 elem0 = _mm_broadcast_ss(other.v + (4 * i + 0));
                        __m128 elem1 = _mm_broadcast_ss(other.v + (4 * i + 1));
                        __m128 elem2 = _mm_broadcast_ss(other.v + (4 * i + 2));
                        __m128 elem3 = _mm_broadcast_ss(other.v + (4 * i + 3));

                        __m128 result = _mm_add_ps(_mm_add_ps(_mm_mul_ps(elem0, col0), _mm_mul_ps(elem1, col1)), _mm_add_ps(_mm_mul_ps(elem2, col2), _mm_mul_ps(elem3, col3)));
                        _mm_store_ps(v + 4 * i, result);
                    }

                    return *this;
                }

                if constexpr (std::is_same<T, f64>::value)
                {
                    alignas(simdalign<T>::value) f64 res[16];
                    __m256d col0 = _mm256_load_pd(&m00);
                    __m256d col1 = _mm256_load_pd(&m10);
                    __m256d col2 = _mm256_load_pd(&m20);
                    __m256d col3 = _mm256_load_pd(&m30);

                    for (s32 i = 0; i < 4; i++)
                    {
                        __m256d elem0 = _mm256_set1_pd(*(&other.m00 + (4 * i + 0)));
                        __m256d elem1 = _mm256_set1_pd(*(&other.m00 + (4 * i + 1)));
                        __m256d elem2 = _mm256_set1_pd(*(&other.m00 + (4 * i + 2)));
                        __m256d elem3 = _mm256_set1_pd(*(&other.m00 + (4 * i + 3)));

                        __m256d result = _mm256_add_pd(_mm256_mul_pd(elem0, col0), _mm256_add_pd(_mm256_mul_pd(elem1, col1), _mm256_add_pd(_mm256_mul_pd(elem2, col2), _mm256_mul_pd(elem3, col3))));

                        _mm256_store_pd(res + (4 * i), result);
                    }

                    _mm256_store_pd(&m00, _mm256_load_pd(res + 0));
                    _mm256_store_pd(&m10, _mm256_load_pd(res + 4));
                    _mm256_store_pd(&m20, _mm256_load_pd(res + 8));
                    _mm256_store_pd(&m30, _mm256_load_pd(res + 12));

                    return *this;
                }

                T newM00 = m00 * other.m00 + m10 * other.m01 + m20 * other.m02;
                T newM01 = m01 * other.m00 + m11 * other.m01 + m21 * other.m02;
                T newM02 = m02 * other.m00 + m12 * other.m01 + m22 * other.m02;

                T newM10 = m00 * other.m10 + m10 * other.m11 + m20 * other.m12;
                T newM11 = m01 * other.m10 + m11 * other.m11 + m21 * other.m12;
                T newM12 = m02 * other.m10 + m12 * other.m11 + m22 * other.m12;

                T newM20 = m00 * other.m20 + m10 * other.m21 + m20 * other.m22;
                T newM21 = m01 * other.m20 + m11 * other.m21 + m21 * other.m22;
                T newM22 = m02 * other.m20 + m12 * other.m21 + m22 * other.m22;

                m00 = newM00;
                m10 = newM10;
                m20 = newM20;
                
                m01 = newM01;
                m11 = newM11;
                m12 = newM12;
                
                m02 = newM02;
                m12 = newM12;
                m22 = newM22;

                return *this;
            }

            // Operations
            inline constexpr void identity() noexcept
            {
                m00 = static_cast<T>(1);
                m10 = static_cast<T>(0);
                m20 = static_cast<T>(0);
                m30 = static_cast<T>(0);
                m01 = static_cast<T>(0);
                m11 = static_cast<T>(1);
                m21 = static_cast<T>(0);
                m31 = static_cast<T>(0);
                m02 = static_cast<T>(0);
                m12 = static_cast<T>(0);
                m22 = static_cast<T>(1);
                m32 = static_cast<T>(0);
                m03 = static_cast<T>(0);
                m13 = static_cast<T>(0);
                m23 = static_cast<T>(0);
                m33 = static_cast<T>(1);
            }

            SML_NO_DISCARD inline constexpr mat4& transpose() noexcept
            {
                std::swap(m01, m10);
                std::swap(m02, m20);
                std::swap(m03, m30);
                std::swap(m21, m12);
                std::swap(m22, m13);
                std::swap(m32, m23);

                return *this;
            }

            SML_NO_DISCARD inline constexpr mat4 transposed() const noexcept
            {
                mat4 c = mat4(*this);
                return c.transpose();
            }

            SML_NO_DISCARD inline constexpr mat4& invert() noexcept
            {
                T det = determinant();

                if (det != static_cast<T>(0))
                {
                    T det_inv = static_cast<T>(1) / det;

                    T t00 = m11 * m22 - m12 * m21;
                    T t01 = -m10 * m22 + m12 * m20;
                    T t02 = m10 * m21 - m11 * m20;
                    T t10 = -m01 * m22 + m02 * m21;
                    T t11 = m00 * m22 - m02 * m20;
                    T t12 = -m00 * m21 + m01 * m20;
                    T t20 = m01 * m12 - m02 * m11;
                    T t21 = -m00 * m12 + m02 * m10;
                    T t22 = m00 * m11 - m01 * m10;

                    m00 = t00 * det_inv;
                    m11 = t11 * det_inv;
                    m22 = t22 * det_inv;

                    m01 = t10 * det_inv;
                    m10 = t11 * det_inv;
                    m20 = t12 * det_inv;

                    m02 = t20 * det_inv;
                    m12 = t21 * det_inv;
                    m21 = t12 * det_inv;
                }

                return *this;
            }

            SML_NO_DISCARD inline constexpr mat4& negate() noexcept
            {
                m00 = -m00;
                m10 = -m10;
                m20 = -m20;
                m30 = -m30;
                m01 = -m01;
                m11 = -m11;
                m21 = -m21;
                m31 = -m31;
                m02 = -m02;
                m12 = -m12;
                m22 = -m22;
                m32 = -m32;
                m03 = -m03;
                m13 = -m13;
                m23 = -m23;
                m33 = -m33;

                return *this;
            }

            SML_NO_DISCARD inline constexpr mat4 inverted() const noexcept
            {
                mat4 c = mat(*this);
                return c.invert();
            }

            SML_NO_DISCARD inline constexpr T determinant() const noexcept
            {
                return static_cast<T>(0);
            }

            SML_NO_DISCARD inline std::string toString() const noexcept
            {
                return std::to_string(m00) + ", " + std::to_string(m10) + ", " + std::to_string(m20) + std::to_string(m30) + "\n" 
                    + std::to_string(m01) + ", " + std::to_string(m11) + ", " + std::to_string(m21) + std::to_string(m31) + "\n"
                    + std::to_string(m02) + ", " + std::to_string(m12) + ", " + std::to_string(m22) + std::to_string(m32) + "\n"
                    + std::to_string(m03) + ", " + std::to_string(m13) + ", " + std::to_string(m23) + std::to_string(m33);
            }

            SML_NO_DISCARD static inline constexpr mat4 view(const vec3<T>& eye, const vec3<T>& to, const vec3<T>& up) noexcept
            {
                mat4 res(static_cast<T>(1));

                vec3<T> zAxis = vec3<T>::normalize(eye - to);
                vec3<T> xAxis = vec3<T>::normalize(vec3<T>::cross(up, zAxis));
                vec3<T> yAxis = vec3<T>::normalize(vec3<T>::cross(zAxis, xAxis));

                res.m00 = xAxis.x;      res.m10 = xAxis.y;      res.m20 = xAxis.z;      res.m30 = -vec3<T>::dot(xAxis, eye);
                res.m01 = yAxis.x;      res.m11 = yAxis.y;      res.m21 = yAxis.z;      res.m31 = -vec3<T>::dot(yAxis, eye);
                res.m02 = zAxis.x;      res.m12 = zAxis.y;      res.m22 = zAxis.z;      res.m32 = -vec3<T>::dot(zAxis, eye);

                return res;
            }

            SML_NO_DISCARD static inline constexpr mat4 perspective(T fov, T aspect, T zNear, T zFar) noexcept
            {
                mat4 res(static_cast<T>(1));
                
                T width = static_cast<T>(1) - sml::tan(fov / static_cast<T>(2)), height = aspect / sml::tan(fov / static_cast<T>(2));

                res.m00 = width;
                res.m11 = height;
                res.m22 - zFar / (zNear - zFar);
                res.m32 = zFar * zNear / (zNear - zFar);
                res.m23 = static_cast<T>(-1);

                return res;
            }

            SML_NO_DISCARD static inline constexpr mat4 ortho(T width, T height, T zNear, T zFar) noexcept
            {
                mat4 res(static_cast<T>(1));

                res.m00 = static_cast<T>(2) / width;
                res.m11 = static_cast<T>(2) / height;
                res.m22 = static_cast<T>(2) / (zNear - zFar);
                res.m32 = zNear / (zNear - zFar);

                return res;
            }


            SML_NO_DISCARD static inline constexpr mat4 translate(const vec3<T>& translation) noexcept
            {
                mat4 res(static_cast<T>(1));

                res.m30 = translation.x;
                res.m31 = translation.y;
                res.m32 = translation.z;

                return res;
            }

            SML_NO_DISCARD static inline constexpr mat4 scale(const vec3<T>& scale) noexcept
            {
                mat4 res(static_cast<T>(1));

                res.m00 = scale.x;
                res.m11 = scale.y;
                res.m22 = scale.z;

                return res;
            }

            SML_NO_DISCARD static inline constexpr mat4 rotateX(T theta) noexcept
            {
                mat4 res(static_cast<T>(1));

                float cosT = sml::cos(theta);
                float sinT = sml::sin(theta);

                res.m11 = cosT;
                res.m12 = sinT;
                res.m21 = -sinT;
                res.m22 = cosT;

                return res;
            }

            SML_NO_DISCARD static inline constexpr mat4 rotateY(T theta) noexcept
            {
                mat4 res(static_cast<T>(1));

                float cosT = sml::cos(theta);
                float sinT = sml::sin(theta);

                res.m00 = cosT;
                res.m02 = sinT;
                res.m20 = -sinT;
                res.m22 = cosT;

                return res;
            }

            SML_NO_DISCARD static inline constexpr mat4 rotateZ(T theta) noexcept
            {
                mat4 res(static_cast<T>(1));

                float cosT = sml::cos(theta);
                float sinT = sml::sin(theta);

                res.m00 = cosT;
                res.m01 = sinT;
                res.m10 = -sinT;
                res.m11 = cosT;

                return res;
            }

            SML_NO_DISCARD static inline constexpr mat4 rotate(const vec3<T>& axis, T angle) noexcept
            {
                mat4 res(static_cast<T>(1));

                T c = sml::cos(angle);
                T s = sml::sin(angle);
                T t = static_cast<T>(1) - c;

                vec3<T> normalizedAxis = axis.normalized();
                T x = normalizedAxis.x;
                T y = normalizedAxis.y;
                T z = normalizedAxis.z;

                res.m00 = static_cast<T>(1) + t * (x * x - 1);
                res.m01 = z * s + t * x * y;
                res.m02 = -y * s + t * x * z;
                
                res.m10 = -z * s + t * x * y;
                res.m11 = static_cast<T>(1) + t * (y * y - 1);
                res.m12 = x * s + t * y * z;

                res.m20 = y * s + t * x * z;
                res.m21 = -x * s + t * y * z;
                res.m22 = static_cast<T>(1) + t * (z * z - 1);

                return res;
            }

            SML_NO_DISCARD static inline constexpr mat4 rotate(T yaw, T pitch, T roll) noexcept
            {
                return rotateY(yaw) * rotateX(pitch) * rotateZ(roll);
            }

            SML_NO_DISCARD static inline constexpr mat4 rotate(const vec3<T>& axis, T angle, const vec3<T>& center) noexcept
            {
                return translate(-center) * rotate(axis, angle) * translate(center);
            }

            // Data
            union
            {
                struct
                {
                    union
                    {
                        vec4<T> col0;
                        struct
                        {
                            T m00, m01, m02, m03;
                        };
                    };

                    union
                    {
                        vec4<T> col1;
                        struct
                        {
                            T m10, m11, m12, m13;
                        };
                    };

                    union
                    {
                        vec4<T> col2;
                        struct
                        {
                            T m20, m21, m22, m23;
                        };
                    };

                    union
                    {
                        vec4<T> col3;
                        struct
                        {
                            T m30, m31, m32, m33;
                        };
                    };
                };

                vec4<T> col[4];

                T v[16];            
            };
    };

    // Operators
    template<typename T>
    constexpr mat4<T> operator * (mat4<T> left, mat4<T> right) noexcept
    {
        left *= right;
        return left;
    }

    template<typename T>
    constexpr vec4<T> operator * (const mat4<T>& lhs, const vec4<T>& rhs) noexcept
    {
        alignas(simdalign<T>::value) vec4<T> res;

        if constexpr (std::is_same<T, f32>::value)
        {
            __m128 x = _mm_broadcast_ss(&rhs.x);
            __m128 y = _mm_broadcast_ss(&rhs.y);
            __m128 z = _mm_broadcast_ss(&rhs.z);
            __m128 w = _mm_broadcast_ss(&rhs.w);

            __m128 c0 = _mm_load_ps(&lhs.m00);
            __m128 c1 = _mm_load_ps(&lhs.m10);
            __m128 c2 = _mm_load_ps(&lhs.m20);
            __m128 c3 = _mm_load_ps(&lhs.m30);

            _mm_store_ps(res.v, _mm_add_ps(_mm_add_ps(_mm_mul_ps(x, c0), _mm_mul_ps(y, c1)), _mm_add_ps(_mm_mul_ps(z, c2), _mm_mul_ps(w, c3))));

            return res;
        }

        if constexpr (std::is_same<T, f64>::value)
        {
            __m256d x = _mm256_set1_pd(rhs.x);
            __m256d y = _mm256_set1_pd(rhs.y);
            __m256d z = _mm256_set1_pd(rhs.z);
            __m256d w = _mm256_set1_pd(rhs.w);

            __m256d c0 = _mm256_load_pd(&lhs.m00);
            __m256d c1 = _mm256_load_pd(&lhs.m10);
            __m256d c2 = _mm256_load_pd(&lhs.m20);
            __m256d c3 = _mm256_load_pd(&lhs.m30);

            _mm256_store_pd(res.v, _mm256_add_pd(_mm256_add_pd(_mm256_mul_pd(x, c0), _mm256_mul_pd(y, c1)), _mm256_add_pd(_mm256_mul_pd(z, c2), _mm256_mul_pd(w, c3))));

            return res;
        }

        T x = lhs.m00 * rhs.x + lhs.m10 * rhs.y + lhs.m20 * rhs.z + lhs.m30 * rhs.w;
        T y = lhs.m01 * rhs.x + lhs.m11 * rhs.y + lhs.m21 * rhs.z + lhs.m31 * rhs.w;
        T z = lhs.m02 * rhs.x + lhs.m12 * rhs.y + lhs.m22 * rhs.z + lhs.m32 * rhs.w;
        T w = lhs.m03 * rhs.x + lhs.m13 * rhs.y + lhs.m23 * rhs.z + lhs.m33 * rhs.w;

        return { x, y, z, w };
    }

    // Predefined types
    typedef mat4<f32> fmat4;
    typedef mat4<f64> dmat4;
} // namespace sml

#endif // sml_mat4_h__
