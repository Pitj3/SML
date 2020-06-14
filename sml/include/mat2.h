#ifndef sml_mat2_h__
#define sml_mat2_h__

/* column.h -- col major mat2 implementation of the 'Simple Math Library'
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

#include "vec2.h"
#include "smltypes.h"

namespace sml
{
    template<typename T>
    class alignas(simdalign<T>::value) mat2
    {
        public:
            constexpr mat2() noexcept
            {
                identity();
            }

            constexpr explicit mat2(T diagonal) noexcept
            {
                m00 = diagonal;
                m10 = static_cast<T>(0);
                m01 = static_cast<T>(0);
                m11 = diagonal;
            }

            constexpr mat2(T col1[2], T col2[2]) noexcept
            {
                m00 = col1[0];
                m01 = col1[1];

                m10 = col2[0];
                m11 = col2[1];
            }

            constexpr mat2(T m00, T m01, T m10, T m11) noexcept
            {
                this->m00 = m00;
                this->m10 = m10;
                this->m01 = m01;
                this->m11 = m11;
            }

            constexpr mat2(const mat2& other) noexcept
            {
                m00 = other.m00;
                m10 = other.m10;
                m01 = other.m01;
                m11 = other.m11;
            }

            constexpr mat2(mat2&& other) noexcept
            {
                m00 = std::move(other.m00);
                m10 = std::move(other.m10);
                m01 = std::move(other.m01);
                m11 = std::move(other.m11);
            }

            constexpr void set(T m00, T m01, T m10, T m11) noexcept
            {
                this->m00 = m00;
                this->m10 = m10;
                this->m01 = m01;
                this->m11 = m11;
            }

            constexpr void set(T v[4]) noexcept
            {
                for(int i = 0; i < 4; i++)
                {
                    this->v[i] = v[i];
                }
            }

            constexpr mat2& operator = (const mat2& other) noexcept
            {
                m00 = other.m00;
                m10 = other.m10;
                m01 = other.m01;
                m11 = other.m11;

                return *this;
            }

            constexpr mat2& operator = (mat2&& other) noexcept
            {
                m00 = std::move(other.m00);
                m10 = std::move(other.m10);
                m01 = std::move(other.m01);
                m11 = std::move(other.m11);

                return *this;
            }

            // Operators
            inline constexpr bool operator == (const mat2& other) const noexcept
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    union m128
                    {
                        __m128 f;
                        __m128i i;
                    };

                    __m128 me = _mm_load_ps(&m00);
                    __m128 ot = _mm_load_ps(&other.m00);

                    m128 cmp = { _mm_cmpeq_ps(me, ot) };
                    s32 result = _mm_testc_si128(cmp.i, cmp.i);

                    return result != 0; 
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    union m256
                    {
                        __m256d d;
                        __m256i i;
                    };

                    __m256d me = _mm256_load_pd(&m00);
                    __m256d ot = _mm256_load_pd(&other.m00);

                    m256 cmp = { _mm256_cmp_pd(me, ot, _CMP_EQ_OQ) };
                    s32 result = _mm256_testc_si256(cmp.i, cmp.i);

                    return result != 0;
                }

                return m00 != other.m00 || m10 != other.m10 || m01 != other.m01 || m11 != other.m11;
            }

            inline constexpr bool operator != (const mat2& other) const noexcept
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    union m128
                    {
                        __m128 f;
                        __m128i i;
                    };

                    __m128 me = _mm_load_ps(&m00);
                    __m128 ot = _mm_load_ps(&other.m00);

                    m128 cmp = { _mm_cmpneq_ps(me, ot) };
                    s32 result = _mm_testc_si128(cmp.i, cmp.i);

                    return result != 0; 
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    union m256
                    {
                        __m256d d;
                        __m256i i;
                    };

                    __m256d me = _mm256_load_pd(&m00);
                    __m256d ot = _mm256_load_pd(&other.m00);

                    m256 cmp = { _mm256_cmp_pd(me, ot, _CMP_NEQ_OQ) };
                    s32 result = _mm256_testc_si128(cmp.i, cmp.i);

                    return result != 0;
                }

                return m00 != other.m00 || m10 != other.m10 || m01 != other.m01 || m11 != other.m11;
            }

            mat2& operator *= (const mat2& other) noexcept
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    alignas(simdalign<T>::value) f32 mat0[4] = {
                        m00,
                        m01,
                        m10,
                        m11
                    };

                    alignas(simdalign<T>::value) f32 mat1[4] = {
                        other.m00,
                        other.m01,
                        other.m10,
                        other.m11
                    };

                    __m128 lhs = _mm_load_ps(mat0);
                    __m128 rhs = _mm_load_ps(mat1);

                    __m128 m0 = _mm_shuffle_ps(lhs, lhs, _MM_SHUFFLE(3, 1, 3, 1));
                    __m128 m1 = _mm_shuffle_ps(rhs, rhs, _MM_SHUFFLE(3, 3, 2, 2));

                    __m128 res1 = _mm_mul_ps(m0, m1);

                    __m128 m2 = _mm_shuffle_ps(lhs, lhs, _MM_SHUFFLE(2, 0, 2, 0));
                    __m128 m3 = _mm_shuffle_ps(rhs, rhs, _MM_SHUFFLE(1, 1, 0, 0));
                    
                    __m128 res2 = _mm_mul_ps(m2, m3);

                    __m128 res = _mm_add_ps(res1, res2);

                    _mm_store_ps(v, res);

                    return *this;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    alignas(simdalign<T>::value) f64 res[4];

                    __m128d col0 = _mm_load_pd(&m00);
                    __m128d col1 = _mm_load_pd(&m10);

                    for(s32 i = 0; i < 2; i++)
                    {
                        __m128d elem0 = _mm_set1_pd(*(&other.m00 + (2 * i + 0)));
                        __m128d elem1 = _mm_set1_pd(*(&other.m00 + (2 * i + 1)));

                        __m128d result = _mm_add_pd(_mm_mul_pd(elem0, col0), _mm_mul_pd(elem1, col1));
                        
                        _mm_store_pd(res + (2 * i), result);
                    }

                    _mm_store_pd(&m00 + 0, _mm_load_pd(res + 0));
                    _mm_store_pd(&m00 + 2, _mm_load_pd(res + 2));

                    return *this;
                }

                T newM00 = m00 * other.m00 + m10 * other.m01;
                T newM01 = m01 * other.m00 + m11 * other.m01;
                T newM10 = m00 * other.m10 + m10 * other.m11;
                T newM11 = m01 * other.m10 + m11 * other.m11;

                m00 = newM00;
                m10 = newM10;
                m01 = newM01;
                m11 = newM11;

                return *this;
            }

            // Operations
            inline constexpr void identity() noexcept
            {
                m00 = static_cast<T>(1);
                m10 = static_cast<T>(0);
                m01 = static_cast<T>(0);
                m11 = static_cast<T>(1);
            }

            SML_NO_DISCARD inline constexpr mat2& transpose() noexcept
            {
                std::swap(m01, m10);

                return *this;
            }

            SML_NO_DISCARD inline constexpr mat2 transposed() const noexcept
            {
                mat2 c = mat2(*this);
                return c.transpose();
            }

            SML_NO_DISCARD inline constexpr mat2& invert() noexcept
            {
                T det = determinant();

                if(det != static_cast<T>(0))
                {
                    T det_inv = static_cast<T>(1) / det;

                    if constexpr(std::is_same<T, f32>::value)
                    {
                        __m128 me = _mm_set_ps(m11, -m01, -m10, m00);
                        __m128 det = _mm_set_ps1(det_inv);

                        __m128 res = _mm_mul_ps(me, det);

                        _mm_store_ps(v, res);

                        return *this;
                    }

                    if constexpr(std::is_same<T, f64>::value)
                    {
                        __m128d me1 = _mm_set_pd(m11, -m01);
                        __m128d me2 = _mm_set_pd(-m10, m00);

                        __m128d det = _mm_set1_pd(det_inv);

                        __m128d res1 = _mm_mul_pd(me1, det);
                        __m128d res2 = _mm_mul_pd(me2, det);

                        _mm_store_pd(&m00 + 0, res1);
                        _mm_store_pd(&m00 + 2, res2);

                        return *this;
                    }

                    m00 = m11 * det_inv;
                    m10 = -m01 * det_inv;
                    m01 = -m10 * det_inv;
                    m11 = m00 * det_inv;
                }

                return *this;
            }

            SML_NO_DISCARD inline constexpr mat2& negate() noexcept
            {
                m00 = -m00;
                m10 = -m10;
                m01 = -m01;
                m11 = -m11;

                return *this;
            }

            SML_NO_DISCARD inline constexpr mat2 inverted() const noexcept
            {
                mat2 c; c.set(m00, m10, m01, m11);
                return c.invert();
            }

            SML_NO_DISCARD inline constexpr T determinant() const noexcept
            {
                return m00 * m11 - m01 * m10;
            }

            SML_NO_DISCARD inline std::string toString() const noexcept
            {
                return std::to_string(m00) + ", " + std::to_string(m10) + "\n" + std::to_string(m01) + ", " + std::to_string(m11);
            }

            // Data
            union
            {
                struct 
                {
                    T m00, m01, m10, m11;
                };

                vec2view<T> col[2];

                T v[4];
            };
    };

    // Operators
    template<typename T>
    constexpr mat2<T> operator * (mat2<T> left, mat2<T> right) noexcept
    {
        left *= right;
        return left;
    }

    template<typename T>
    constexpr vec2<T> operator * (const mat2<T>& lhs, const vec2<T>& rhs) noexcept
    {
        alignas(simdalign<T>::value) vec2<T> res;

        if constexpr(std::is_same<T, f32>::value)
        {
            __m128 x = _mm_broadcast_ss(&rhs.x);
            __m128 y = _mm_broadcast_ss(&rhs.y);

            __m128 c0 = _mm_load_ps(&lhs.m00);
            __m128 c1 = _mm_shuffle_ps(c0, c0, _MM_SHUFFLE(2, 3, 0, 0));

            _mm_store_ps(res.v, _mm_add_ps(_mm_mul_ps(x, c0), _mm_mul_ps(y, c1)));

            return res;
        }

        if constexpr(std::is_same<T, f64>::value)
        {
            __m256d x = _mm256_set1_pd(rhs.x);
            __m256d y = _mm256_set1_pd(rhs.y);

            __m256d c0 = _mm256_load_pd(&lhs.m00);
            __m256d c1 = _mm256_shuffle_pd(c0, c0, 0);

            _mm256_store_pd(res.v, _mm256_add_pd(_mm256_mul_pd(x, c0), _mm256_mul_pd(y, c1)));

            return res;
        }

        T x = lhs.m00 * rhs.x + lhs.m10 * rhs.y;
        T y = lhs.m01 * rhs.x + lhs.m11 * rhs.y;

        return {x, y};
    }

    // Predefined types
    typedef mat2<f32> fmat2;
    typedef mat2<f64> dmat2;
} // namespace sml

#endif // sml_mat2_h__
