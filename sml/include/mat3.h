#ifndef sml_mat3_h__
#define sml_mat3_h__

/* mat3.h -- column major mat3 implementation of the 'Simple Math Library'
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

#include "vec3.h"
#include "smltypes.h"

namespace sml
{
    template<typename T>
    class alignas(simdalign<T>::value) mat3
    {
        public:
            constexpr mat3() noexcept
            {
                identity();
                v[3] = v[7] = v[11] = static_cast<T>(0);
            }

            constexpr mat3(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22) noexcept
            {
                this->m00 = m00;
                this->m10 = m10;
                this->m20 = m20;

                this->m01 = m01;
                this->m11 = m11;
                this->m21 = m21;

                this->m02 = m02;
                this->m12 = m12;
                this->m22 = m22;

                v[3] = v[7] = v[11] = static_cast<T>(0);
            }

            constexpr explicit mat3(T diagonal) noexcept
            {
                m00 = diagonal;
                m10 = static_cast<T>(0);
                m20 = static_cast<T>(0);
                m01 = static_cast<T>(0);
                m11 = diagonal;
                m21 = static_cast<T>(0);
                m02 = static_cast<T>(0);
                m12 = static_cast<T>(0);
                m22 = diagonal;

                v[3] = v[7] = v[11] = static_cast<T>(0);
            }

            constexpr explicit mat3(T* v) noexcept
            {
                set(v);
                v[3] = v[7] = v[11] = static_cast<T>(0);
            }

            constexpr mat3(T col1[3], T col2[3], T col3[3]) noexcept
            {
                m00 = col1[0];
                m01 = col1[1];
                m02 = col1[2];

                m10 = col2[0];
                m11 = col2[1];
                m12 = col2[2];
                
                m20 = col3[0];
                m21 = col3[1];
                m22 = col3[2];
                v[3] = v[7] = v[11] = static_cast<T>(0);
            }

            constexpr mat3(const mat3& other) noexcept
            {
                m00 = other.m00;
                m10 = other.m10;
                m20 = other.m20;

                m01 = other.m01;
                m11 = other.m11;
                m21 = other.m21;
                
                m02 = other.m02;
                m12 = other.m12;
                m22 = other.m22;
                v[3] = v[7] = v[11] = static_cast<T>(0);
            }

            constexpr mat3(mat3&& other) noexcept
            {
                m00 = std::move(other.m00);
                m10 = std::move(other.m10);
                m20 = std::move(other.m20);

                m01 = std::move(other.m01);
                m11 = std::move(other.m11);
                m21 = std::move(other.m21);

                m02 = std::move(other.m02);
                m12 = std::move(other.m12);
                m22 = std::move(other.m22);
                v[3] = v[7] = v[11] = static_cast<T>(0);
            }

            constexpr void set(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22) noexcept
            {
                this->m00 = m00;
                this->m10 = m10;
                this->m20 = m20;

                this->m01 = m01;
                this->m11 = m11;
                this->m21 = m21;
                
                this->m02 = m02;
                this->m12 = m12;
                this->m22 = m22;
                v[3] = v[7] = v[11] = static_cast<T>(0);
            }

            constexpr void set(T* v) noexcept
            {
                s32 index = 0;
                for(int i = 0; i < 9; i++)
                {
                    if (i % 3 == 0 && i != 0)
                        index++;

                    this->v[index++] = v[i];
                }

                v[3] = v[7] = v[11] = static_cast<T>(0);
            }

            constexpr mat3& operator = (const mat3& other) noexcept
            {
                m00 = other.m00;
                m10 = other.m10;
                m20 = other.m20;

                m01 = other.m01;
                m11 = other.m11;
                m21 = other.m21;
                
                m02 = other.m02;
                m12 = other.m12;
                m22 = other.m22;

                return *this;
            }

            constexpr mat3& operator = (mat3&& other) noexcept
            {
                m00 = std::move(other.m00);
                m10 = std::move(other.m10);
                m20 = std::move(other.m20);

                m01 = std::move(other.m01);
                m11 = std::move(other.m11);
                m21 = std::move(other.m21);

                m02 = std::move(other.m02);
                m12 = std::move(other.m12);
                m22 = std::move(other.m22);

                return *this;
            }

            // Operators
            inline constexpr bool operator == (const mat3& other) const noexcept
            {
                if constexpr (std::is_same<T, f32>::value)
                {
                    union m128
                    {
                        __m128 f;
                        __m128i i;
                    };

                    s32 result = 0x0000;
                    for (s32 i = 0; i < 3; i++)
                    {
                        __m128 me = _mm_load_ps(v + (4 * i));
                        __m128 ot = _mm_load_ps(other.v + (4 * i));
                        __m128 res = _mm_cmpneq_ps(me, ot);

                        m128 cmp = { res };

                        result |= (_mm_movemask_epi8(cmp.i));
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
                    for (s32 i = 0; i < 3; i++)
                    {
                        __m256d me = _mm256_load_pd(v + (4 * i));
                        __m256d ot = _mm256_load_pd(other.v + (4 * i));
                        __m256d res = _mm256_cmp_pd(me, ot, _CMP_NEQ_OQ);

                        __m128d high = _mm256_extractf128_pd(res, 0);
                        __m128d low = _mm256_extractf128_pd(res, 1);

                        m128 highCMP = { high };
                        m128 lowCMP = { low };

                        result |= _mm_movemask_epi8(highCMP.i);
                        result |= _mm_movemask_epi8(lowCMP.i);
                    }

                    return result == 0;
                }

                return m00 == other.m00 && m10 == other.m10 && m20 == other.m20 
                    && m01 == other.m01 && m11 == other.m11 && m21 == other.m21
                    && m02 == other.m02 && m12 == other.m12 && m22 == other.m22;
            }

            inline constexpr bool operator != (const mat3& other) const noexcept
            {
                if constexpr (std::is_same<T, f32>::value)
                {
                    union m128
                    {
                        __m128 f;
                        __m128i i;
                    };

                    s32 result = 0xFFFF;
                    for (s32 i = 0; i < 3; i++)
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
                    for (s32 i = 0; i < 3; i++)
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

                return m00 != other.m00 || m10 != other.m10 || m20 != other.m20 
                    || m01 != other.m01 || m11 != other.m11 || m21 != other.m21
                    || m02 != other.m02 || m12 != other.m12 || m22 != other.m22;
            }

            mat3& operator *= (const mat3& other) noexcept
            {
                if constexpr (std::is_same<T, f32>::value)
                {
                    __m128 col0 = _mm_load_ps(v + 0);
                    __m128 col1 = _mm_load_ps(v + 4);
                    __m128 col2 = _mm_load_ps(v + 8);

                    for (s32 i = 0; i < 3; i++)
                    {
                        __m128 elem0 = _mm_broadcast_ss(other.v + (4 * i + 0));
                        __m128 elem1 = _mm_broadcast_ss(other.v + (4 * i + 1));
                        __m128 elem2 = _mm_broadcast_ss(other.v + (4 * i + 2));

                        __m128 result = _mm_add_ps(_mm_add_ps(_mm_mul_ps(elem0, col0), _mm_mul_ps(elem1, col1)), _mm_mul_ps(elem2, col2));
                        _mm_store_ps(v + 4 * i, result);
                    }

                    return *this;
                }

                if constexpr (std::is_same<T, f64>::value)
                {
                    alignas(simdalign<T>::value) f64 res[12];
                    __m256d col0 = _mm256_load_pd(&m00);
                    __m256d col1 = _mm256_load_pd(&m10);
                    __m256d col2 = _mm256_load_pd(&m20);

                    for (s32 i = 0; i < 3; i++)
                    {
                        __m256d elem0 = _mm256_set1_pd(*(&other.m00 + (4 * i + 0)));
                        __m256d elem1 = _mm256_set1_pd(*(&other.m00 + (4 * i + 1)));
                        __m256d elem2 = _mm256_set1_pd(*(&other.m00 + (4 * i + 2)));

                        __m256d result = _mm256_add_pd(_mm256_mul_pd(elem0, col0), _mm256_add_pd(_mm256_mul_pd(elem1, col1), _mm256_mul_pd(elem2, col2)));

                        _mm256_store_pd(res + (4 * i), result);
                    }

                    _mm256_store_pd(&m00, _mm256_load_pd(res + 0));
                    _mm256_store_pd(&m10, _mm256_load_pd(res + 4));
                    _mm256_store_pd(&m20, _mm256_load_pd(res + 8));

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
                m21 = newM21;
                
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
                m01 = static_cast<T>(0);
                m11 = static_cast<T>(1);
                m21 = static_cast<T>(0);
                m02 = static_cast<T>(0);
                m12 = static_cast<T>(0);
                m22 = static_cast<T>(1);
            }

            inline constexpr void transpose() noexcept
            {
                std::swap(m01, m10);
                std::swap(m02, m20);
                std::swap(m21, m12);
            }

            SML_NO_DISCARD inline constexpr mat3 transposed() const noexcept
            {
                mat3 copy(*this);
                copy.transpose();

                return copy;
            }

            inline constexpr void invert() noexcept
            {
                T det = determinant();

                if (det != static_cast<T>(0))
                {
                    T det_inv = static_cast<T>(1) / det;

                    /*if constexpr (std::is_same<T, f32>::value)
                    {
                        __m128 me1 = _mm_set_ps(m11, m12, m10, m02);
                        __m128 me2 = _mm_set_ps(m00, m01, m01, m02);
                        __m128 me3 = _mm_set_ps(m00, m00, m00, m00);

                        __m128 me4 = _mm_set_ps(m22, m20, m21, m21);
                        __m128 me5 = _mm_set_ps(m22, m20, m12, m10);
                        __m128 me6 = _mm_set_ps(m11, m11, m11, m11);

                        __m128 mul1 = _mm_mul_ps(me1, me4);
                        __m128 mul2 = _mm_mul_ps(me2, me5);
                        __m128 mul3 = _mm_mul_ps(me3, me6);

                        me1 = _mm_set_ps(m12, m10, m11, m11);
                        me2 = _mm_set_ps(m02, m00, m02, m00);
                        me3 = _mm_set_ps(m01, m01, m01, m01);

                        me4 = _mm_set_ps(m21, m22, m20, m22);
                        me5 = _mm_set_ps(m20, m21, m11, m12);
                        me6 = _mm_set_ps(m10, m10, m10, m10);

                        __m128 mul4 = _mm_mul_ps(me1, me4);
                        __m128 mul5 = _mm_mul_ps(me2, me5);
                        __m128 mul6 = _mm_mul_ps(me3, me6);

                        __m128 res1 = _mm_sub_ps(mul1, mul4);
                        __m128 res2 = _mm_sub_ps(mul2, mul5);
                        __m128 res3 = _mm_sub_ps(mul3, mul6);

                        __m128 detinvregister = _mm_broadcast_ss(&det_inv);

                        res1 = _mm_mul_ps(res1, detinvregister);
                        res2 = _mm_mul_ps(res2, detinvregister);
                        res3 = _mm_mul_ps(res3, detinvregister);

                        _mm_store_ps(v, res1);
                        _mm_store_ps(v + 4, res2);
                        _mm_store_ps(v + 8, res3);

                        return *this;
                    }*/

                    T t00 = m11 * m22 - m12 * m21;
                    T t01 = -m10 * m22 + m12 * m20;
                    T t02 = m10 * m21 - m11 * m20;
                    T t10 = -m01 * m22 + m02 * m21;
                    T t11 = m00 * m22 - m02 * m20;
                    T t12 = -m00 * m21 + m01 * m20;
                    T t20 = m01 * m12 - m02 * m11;
                    T t21 = -m00 * m12 + m02 * m10;
                    T t22 = m00 * m11 - m01 * m10;

                    mat3 res;

                    res.m00 = t00 * det_inv;
                    res.m11 = t11 * det_inv;
                    res.m22 = t22 * det_inv;
                    res.m01 = t10 * det_inv;
                    res.m10 = t01 * det_inv;
                    res.m20 = t02 * det_inv;
                    res.m02 = t20 * det_inv;
                    res.m12 = t21 * det_inv;
                    res.m21 = t12 * det_inv;

                    *this = res;
                }
            }

            inline constexpr void negate() noexcept
            {
                m00 = -m00;
                m10 = -m10;
                m20 = -m20;
                m01 = -m01;
                m11 = -m11;
                m21 = -m21;
                m02 = -m02;
                m12 = -m12;
                m22 = -m22;
            }

            SML_NO_DISCARD inline constexpr mat3 negated() const noexcept
            {
                mat3 copy(*this);
                copy.negate();

                return copy;
            }

            SML_NO_DISCARD inline constexpr mat3 inverted() const noexcept
            {
                mat3 copy(*this);
                copy.invert();

                return copy;
            }
            

            SML_NO_DISCARD inline constexpr T determinant() const noexcept
            {
                return m00 * (m11 * m22 - m12 * m21)
                            + m01 * (m12 * m20 - m10 * m22)
                            + m02 * (m10 * m21 - m11 * m20);
            }

            SML_NO_DISCARD inline std::string toString() const noexcept
            {
                return std::to_string(m00) + ", " + std::to_string(m10) + ", " + std::to_string(m20) + "\n" 
                    + std::to_string(m01) + ", " + std::to_string(m11) + ", " + std::to_string(m21) + "\n"
                    + std::to_string(m02) + ", " + std::to_string(m12) + ", " + std::to_string(m22);
            }

            // Data
            union
            {
                struct
                {
                    union
                    {
                        vec3<T> col0;
                        struct
                        {
                            T m00, m01, m02;
                        };
                    };

                    union
                    {
                        vec3<T> col1;
                        struct
                        {
                            T m10, m11, m12;
                        };
                    };

                    union
                    {
                        vec3<T> col2;
                        struct
                        {
                            T m20, m21, m22;
                        };
                    };
                };

                vec3<T> col[3];

                T v[12];            
            };
    };

    // Operators
    template<typename T>
    constexpr  mat3<T> operator * (const mat3<T>& left, const mat3<T>& right) noexcept
    {
        mat3<T> temp = left;
        temp *= right;

        return temp;
    }

    template<typename T>
    constexpr vec3<T> operator * (const mat3<T>& lhs, const vec3<T>& rhs) noexcept
    {
        alignas(simdalign<T>::value) vec3<T> res;

        if constexpr (std::is_same<T, f32>::value)
        {
            __m128 x = _mm_broadcast_ss(&rhs.x);
            __m128 y = _mm_broadcast_ss(&rhs.y);
            __m128 z = _mm_broadcast_ss(&rhs.z);

            __m128 c0 = _mm_load_ps(&lhs.m00);
            __m128 c1 = _mm_load_ps(&lhs.m10);
            __m128 c2 = _mm_load_ps(&lhs.m20);

            _mm_store_ps(res.v, _mm_add_ps(_mm_mul_ps(x, c0), _mm_add_ps(_mm_mul_ps(y, c1), _mm_mul_ps(z, c2))));

            return res;
        }

        if constexpr (std::is_same<T, f64>::value)
        {
            __m256d x = _mm256_set1_pd(rhs.x);
            __m256d y = _mm256_set1_pd(rhs.y);
            __m256d z = _mm256_set1_pd(rhs.z);

            __m256d c0 = _mm256_load_pd(lhs.col0.v);
            __m256d c1 = _mm256_load_pd(lhs.col1.v);
            __m256d c2 = _mm256_load_pd(lhs.col2.v);

            __m256d resu = _mm256_add_pd(_mm256_mul_pd(x, c0), _mm256_add_pd(_mm256_mul_pd(y, c1), _mm256_mul_pd(z, c2)));

            _mm256_store_pd(res.v, resu);

            return res;
        }

        T x = lhs.m00 * rhs.x + lhs.m10 * rhs.y + lhs.m20 * rhs.z;
        T y = lhs.m01 * rhs.x + lhs.m11 * rhs.y + lhs.m21 * rhs.z;
        T z = lhs.m02 * rhs.x + lhs.m11 * rhs.y + lhs.m22 * rhs.z;

        return { x, y, z };
    }

    // Predefined types
    typedef mat3<f32> fmat3;
    typedef mat3<f64> dmat3;
} // namespace sml

#endif // sml_mat3_h__
