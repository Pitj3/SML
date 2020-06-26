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

#include "vec3.h"
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

            constexpr explicit mat4(T* v) noexcept
            {
                set(v);
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

            constexpr void set(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22, T m23, T m30, T m31, T m32, T m33) noexcept
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

            constexpr void set(T* v) noexcept
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

                    s32 result = 0x0000;
                    for (s32 i = 0; i < 4; i++)
                    {
                        __m128 me = _mm_load_ps(v + (4 * i));
                        __m128 ot = _mm_load_ps(other.v + (4 * i));
                        __m128 res = _mm_cmp_ps(me, ot, _CMP_NEQ_OQ);

                        m128 cmp = { res };
                        result |= _mm_movemask_epi8(cmp.i);
                    }

                    return result == 0;
                }

                if constexpr (std::is_same<T, f64>::value)
                {
                    union m128
                    {
                        __m128d f;
                        __m128i i;
                    };

                    s32 result = 0x0000;
                    for (s32 i = 0; i < 4; i++)
                    {
                        __m256d me = _mm256_load_pd(v + (4 * i));
                        __m256d ot = _mm256_load_pd(other.v + (4 * i));
                        __m256d res = _mm256_cmp_pd(me, ot, _CMP_NEQ_OQ);

                        __m128d high = _mm256_extractf128_pd(res, 1);
                        __m128d low = _mm256_extractf128_pd(res, 0);

                        m128 highCMP = { high };
                        m128 lowCMP = { low };

                        result |= _mm_movemask_epi8(highCMP.i);
                        result |= _mm_movemask_epi8(lowCMP.i);
                    }

                    return result == 0;
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

                    s32 result = 0xFFFF;
                    for (s32 i = 0; i < 4; i++)
                    {
                        __m128 me = _mm_load_ps(v + (4 * i + 0));
                        __m128 ot = _mm_load_ps(other.v + (4 * i + 0));

                        m128 cmp = { _mm_cmpeq_ps(me, ot) };
                        result &= _mm_movemask_epi8(cmp.i);
                    }

                    return result != 0xFFFF;
                }

                if constexpr (std::is_same<T, f64>::value)
                {
                    union m128
                    {
                        __m128d f;
                        __m128i i;
                    };

                    s32 result = 0xFFFF;
                    for (s32 i = 0; i < 4; i++)
                    {
                        __m256d me = _mm256_load_pd(v + (4 * i));
                        __m256d ot = _mm256_load_pd(other.v + (4 * i));
                        __m256d res = _mm256_cmp_pd(me, ot, _CMP_EQ_OQ);

                        __m128d high = _mm256_extractf128_pd(res, 1);
                        __m128d low = _mm256_extractf128_pd(res, 0);

                        m128 highCMP = { high };
                        m128 lowCMP = { low };

                        result &= _mm_movemask_epi8(highCMP.i);
                        result &= _mm_movemask_epi8(lowCMP.i);
                    }

                    return result != 0xFFFF;
                }

                return m00 != other.m00 || m10 != other.m10 || m20 != other.m20 || m30 != other.m30
                    || m01 != other.m01 || m11 != other.m11 || m21 != other.m21 || m31 != other.m31
                    || m02 != other.m02 || m12 != other.m12 || m22 != other.m22 || m32 != other.m32
                    || m03 != other.m03 || m13 != other.m13 || m23 != other.m23 || m33 != other.m33;
            }

            mat4& operator *= (const mat4& other) noexcept
            {
                if constexpr (std::is_same<T, f32>::value)
                {
                    __m128 col0 = _mm_load_ps(v + 0);
                    __m128 col1 = _mm_load_ps(v + 4);
                    __m128 col2 = _mm_load_ps(v + 8);
                    __m128 col3 = _mm_load_ps(v + 12);
                    
                    for (s32 i = 0; i < 4; i++)
                    {
                        __m128 elem0 = _mm_broadcast_ss(other.v + (4 * i + 0));
                        __m128 elem1 = _mm_broadcast_ss(other.v + (4 * i + 1));
                        __m128 elem2 = _mm_broadcast_ss(other.v + (4 * i + 2));
                        __m128 elem3 = _mm_broadcast_ss(other.v + (4 * i + 3));

                        __m128 result = _mm_add_ps(_mm_add_ps(_mm_mul_ps(elem0, col0),
                            _mm_mul_ps(elem1, col1)),
                            _mm_add_ps(_mm_mul_ps(elem2, col2),
                                _mm_mul_ps(elem3, col3)));
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

                // TODO (Roderick): Implement non SIMD mat4 mul

                return *this;
            }

            mat4& operator *= (const T other) noexcept
            {
                if constexpr (std::is_same<T, f32>::value)
                {
                    __m128 col0 = _mm_load_ps(v + 0);
                    __m128 col1 = _mm_load_ps(v + 4);
                    __m128 col2 = _mm_load_ps(v + 8);
                    __m128 col3 = _mm_load_ps(v + 12);

                    __m128 multi = _mm_broadcast_ss(&other);

                    col0 = _mm_mul_ps(col0, multi);
                    col1 = _mm_mul_ps(col1, multi);
                    col2 = _mm_mul_ps(col2, multi);
                    col3 = _mm_mul_ps(col3, multi);

                    _mm_store_ps(v + 0, col0);
                    _mm_store_ps(v + 4, col1);
                    _mm_store_ps(v + 8, col2);
                    _mm_store_ps(v + 12, col3);

                    return *this;
                }

                if constexpr (std::is_same<T, f64>::value)
                {
                    __m256d col0 = _mm256_load_pd(v + 0);
                    __m256d col1 = _mm256_load_pd(v + 4);
                    __m256d col2 = _mm256_load_pd(v + 8);
                    __m256d col3 = _mm256_load_pd(v + 12);

                    __m256d multi = _mm256_set1_pd(other);

                    col0 = _mm256_mul_pd(col0, multi);
                    col1 = _mm256_mul_pd(col1, multi);
                    col2 = _mm256_mul_pd(col2, multi);
                    col3 = _mm256_mul_pd(col3, multi);

                    _mm256_store_pd(v + 0, col0);
                    _mm256_store_pd(v + 4, col1);
                    _mm256_store_pd(v + 8, col2);
                    _mm256_store_pd(v + 12, col3);

                    return *this;
                }

                for (int i = 0; i < 16; i++)
                {
                    v[i] *= other;
                }

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

            inline constexpr void transpose() noexcept
            {
                std::swap(m01, m10);
                std::swap(m02, m20);
                std::swap(m03, m30);
                std::swap(m12, m21);
                std::swap(m13, m31);
                std::swap(m23, m32);
            }

            SML_NO_DISCARD inline constexpr mat4 transposed() const noexcept
            {
                mat4 copy(*this);
                copy.transpose();

                return copy;
            }

            inline constexpr void invert() noexcept
            {
                T c00 = v[2 * 4 + 2] * v[3 * 4 + 3] -
                    v[3 * 4 + 2] * v[2 * 4 + 3];
                T c02 = v[1 * 4 + 2] * v[3 * 4 + 3] -
                    v[3 * 4 + 2] * v[1 * 4 + 3];
                T c03 = v[1 * 4 + 2] * v[2 * 4 + 3] -
                    v[2 * 4 + 2] * v[1 * 4 + 3];

                T c04 = v[2 * 4 + 1] * v[3 * 4 + 3] -
                    v[3 * 4 + 1] * v[2 * 4 + 3];
                T c06 = v[1 * 4 + 1] * v[3 * 4 + 3] -
                    v[3 * 4 + 1] * v[1 * 4 + 3];
                T c07 = v[1 * 4 + 1] * v[2 * 4 + 3] -
                    v[2 * 4 + 1] * v[1 * 4 + 3];

                T c08 = v[2 * 4 + 1] * v[3 * 4 + 2] -
                    v[3 * 4 + 1] * v[2 * 4 + 2];
                T c10 = v[1 * 4 + 1] * v[3 * 4 + 2] -
                    v[3 * 4 + 1] * v[1 * 4 + 2];
                T c11 = v[1 * 4 + 1] * v[2 * 4 + 2] -
                    v[2 * 4 + 1] * v[1 * 4 + 2];

                T c12 = v[2 * 4 + 0] * v[3 * 4 + 3] -
                    v[3 * 4 + 0] * v[2 * 4 + 3];
                T c14 = v[1 * 4 + 0] * v[3 * 4 + 3] -
                    v[3 * 4 + 0] * v[1 * 4 + 3];
                T c15 = v[1 * 4 + 0] * v[2 * 4 + 3] -
                    v[2 * 4 + 0] * v[1 * 4 + 3];

                T c16 = v[2 * 4 + 0] * v[3 * 4 + 2] -
                    v[3 * 4 + 0] * v[2 * 4 + 2];
                T c18 = v[1 * 4 + 0] * v[3 * 4 + 2] -
                    v[3 * 4 + 0] * v[1 * 4 + 2];
                T c19 = v[1 * 4 + 0] * v[2 * 4 + 2] -
                    v[2 * 4 + 0] * v[1 * 4 + 2];

                T c20 = v[2 * 4 + 0] * v[3 * 4 + 1] -
                    v[3 * 4 + 0] * v[2 * 4 + 1];
                T c22 = v[1 * 4 + 0] * v[3 * 4 + 1] -
                    v[3 * 4 + 0] * v[1 * 4 + 1];
                T c23 = v[1 * 4 + 0] * v[2 * 4 + 1] -
                    v[2 * 4 + 0] * v[1 * 4 + 1];

                vec4<T> fac0(c00, c00, c02, c03);
                vec4<T> fac1(c04, c04, c06, c07);
                vec4<T> fac2(c08, c08, c10, c11);
                vec4<T> fac3(c12, c12, c14, c15);
                vec4<T> fac4(c16, c16, c18, c19);
                vec4<T> fac5(c20, c20, c22, c23);

                vec4<T> vec0(v[1 * 4 + 0], v[0 * 4 + 0], v[0 * 4 + 0],
                    v[0 * 4 + 0]);
                vec4<T> vec1(v[1 * 4 + 1], v[0 * 4 + 1], v[0 * 4 + 1],
                    v[0 * 4 + 1]);
                vec4<T> vec2(v[1 * 4 + 2], v[0 * 4 + 2], v[0 * 4 + 2],
                    v[0 * 4 + 2]);
                vec4<T> vec3(v[1 * 4 + 3], v[0 * 4 + 3], v[0 * 4 + 3],
                    v[0 * 4 + 3]);

                vec4<T> inv0(vec1 * fac0 - vec2 * fac1 + vec3 * fac2);
                vec4<T> inv1(vec0 * fac0 - vec2 * fac3 + vec3 * fac4);
                vec4<T> inv2(vec0 * fac1 - vec1 * fac3 + vec3 * fac5);
                vec4<T> inv3(vec0 * fac2 - vec1 * fac4 + vec2 * fac5);

                vec4<T> sign1(1.0f, -1.0f, 1.0f, -1.0f);
                vec4<T> sign2(-1.0f, 1.0f, -1.0f, 1.0f);

                mat4<T> inver((inv0 * sign1).v, (inv1 * sign2).v, (inv2 * sign1).v,
                    (inv3 * sign2).v);
                vec4<T> row0 = { inver.v[0], inver.v[4], inver.v[8],
                                 inver.v[12] };
                vec4<T> dot0 = col0 * row0;
                T dot1 = dot0.x + dot0.y + dot0.z + dot0.w;
                T inv = 1.0f / dot1;
                inver *= inv;

                set(inver.v);
            }

            inline constexpr void negate() noexcept
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
            }

            SML_NO_DISCARD inline constexpr mat4 negated() const noexcept
            {
                mat4 copy(*this);
                copy.negate();

                return copy;
            }

            SML_NO_DISCARD inline constexpr mat4 inverted() const noexcept
            {
                mat4 copy(*this);
                copy.invert();

                return copy;
            }

            SML_NO_DISCARD inline constexpr T determinant() const noexcept
            {
                T f =
                    m00
                    * ((m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32)
                        - m13 * m22 * m31
                        - m11 * m23 * m32
                        - m12 * m21 * m33);
                f -= m01
                    * ((m10 * m22 * m33 + m12 * m23 * m30 + m13 * m20 * m32)
                        - m13 * m22 * m30
                        - m10 * m23 * m32
                        - m12 * m20 * m33);
                f += m02
                    * ((m10 * m21 * m33 + m11 * m23 * m30 + m13 * m20 * m31)
                        - m13 * m21 * m30
                        - m10 * m23 * m31
                        - m11 * m20 * m33);
                f -= m03
                    * ((m10 * m21 * m32 + m11 * m22 * m30 + m12 * m20 * m31)
                        - m12 * m21 * m30
                        - m10 * m22 * m31
                        - m11 * m20 * m32);

                return f;
            }

            SML_NO_DISCARD inline std::string toString() const noexcept
            {
                return std::to_string(m00) + ", " + std::to_string(m10) + ", " + std::to_string(m20) + std::to_string(m30) + "\n" 
                    + std::to_string(m01) + ", " + std::to_string(m11) + ", " + std::to_string(m21) + std::to_string(m31) + "\n"
                    + std::to_string(m02) + ", " + std::to_string(m12) + ", " + std::to_string(m22) + std::to_string(m32) + "\n"
                    + std::to_string(m03) + ", " + std::to_string(m13) + ", " + std::to_string(m23) + std::to_string(m33);
            }

            // Statics
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
        mat4<T> temp = left;
        temp *= right;

        return temp;
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
