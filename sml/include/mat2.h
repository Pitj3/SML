#ifndef sml_mat2_h__
#define sml_mat2_h__

/* mat2.h -- row major mat2 implementation of the 'Simple Math Library'
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
    class mat2
    {
        public:
            mat2()
            {
                identity();
            }

            mat2(T diagonal)
            {
                m00 = diagonal;
                m10 = T(0);
                m01 = T(0);
                m11 = diagonal;
            }

            mat2(T r1[2], T r2[2])
            {
                m00 = r1[0];
                m10 = r1[1];

                m01 = r2[0];
                m11 = r2[1];
            }

            mat2(T m00, T m10, T m01, T m11)
            {
                this->m00 = m00;
                this->m10 = m10;
                this->m01 = m01;
                this->m11 = m11;
            }

            mat2(const mat2& other)
            {
                m00 = other.m00;
                m10 = other.m10;
                m01 = other.m01;
                m11 = other.m11;
            }

            mat2(mat2&& other) noexcept
            {
                m00 = std::move(other.m00);
                m10 = std::move(other.m10);
                m01 = std::move(other.m01);
                m11 = std::move(other.m11);
            }

            void set(T m00, T m10, T m01, T m11)
            {
                this->m00 = m00;
                this->m10 = m10;
                this->m01 = m01;
                this->m11 = m11;
            }

            void set(T v[4])
            {
                for(int i = 0; i < 4; i++)
                {
                    this->v[i] = v[i];
                }
            }

            mat2& operator = (const mat2& other)
            {
                m00 = other.m00;
                m10 = other.m10;
                m01 = other.m01;
                m11 = other.m11;

                return *this;
            }

            mat2& operator = (mat2&& other) noexcept
            {
                m00 = std::move(other.m00);
                m10 = std::move(other.m10);
                m01 = std::move(other.m01);
                m11 = std::move(other.m11);

                return *this;
            }

            // Operators
            inline constexpr bool operator == (const mat2& other) const
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_set_ps(m00, m10, m01, m11);
                    __m128 him = _mm_set_ps(other.m00, other.m10, other.m01, other.m11);

                    __m128 res = _mm_cmpeq_ps(me, him);
                    
                    int mask = _mm_movemask_ps(res);
                    return mask == 0xffff;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m256d me = _mm256_set_pd(m00, m10, m01, m11);
                    __m256d him = _mm256_set_pd(other.m00, other.m10, other.m01, other.m11);

                    __m256d res = _mm256_cmp_pd(me, him, _CMP_EQ_OQ);
                    
                    int mask = _mm256_movemask_pd(res);
                    return mask == 0xffff;
                }

                return m00 != other.m00 || m10 != other.m10 || m01 != other.m01 || m11 != other.m11;

            }

            inline constexpr bool operator != (const mat2& other) const
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me = _mm_set_ps(m00, m10, m01, m11);
                    __m128 him = _mm_set_ps(other.m00, other.m10, other.m01, other.m11);

                    __m128 res = _mm_cmpneq_ps(me, him);
                    
                    int mask = _mm_movemask_ps(res);
                    return mask != 0;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m256d me = _mm_set_pd(m00, m10, m01, m11);
                    __m256d him = _mm_set_pd(other.m00, other.m10, other.m01, other.m11);

                    __m256d res = _mm256_cmp_pd(me, him, _CMP_NEQ_OQ);
                    
                    int mask = _mm256_movemask_pd(res);
                    return mask != 0;
                }

                return m00 != other.m00 || m10 != other.m10 || m01 != other.m01 || m11 != other.m11;
            }

            mat2& operator *= (const mat2& other)
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 MV0 = _mm_set_ps(m00, m01, m00, m01);
                    __m128 MV1 = _mm_set_ps(other.m00, other.m00, other.m10, other.m10);
                    __m128 MV01Res = _mm_mul_ps(MV0, MV1);

                    __m128 MV2 = _mm_set_ps(m10, m11, m10, m11);
                    __m128 MV3 = _mm_set_ps(other.m01, other.m01, other.m11, other.m11);
                    __m128 MV23Res = _mm_mul_ps(MV2, MV3);

                    __m128 MV0123Res = _mm_add_ps(MV01Res, MV23Res);

                    _mm_store_ps(v, MV0123Res);

                    return *this;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m256d MV0 = _mm256_set_pd(m00, m01, m00, m01);
                    __m256d MV1 = _mm256_set_pd(other.m00, other.m00, other.m10, other.m10);
                    __m256d MV01Res = _mm256_mul_pd(MV0, MV1);

                    __m256d MV2 = _mm256_set_pd(m10, m11, m10, m11);
                    __m256d MV3 = _mm256_set_pd(other.m01, other.m01, other.m11, other.m11);
                    __m256d MV23Res = _mm256_mul_pd(MV2, MV3);

                    __m256d MV0123Res = _mm256_add_pd(MV01Res, MV23Res);

                    _mm256_store_pd(v, MV0123Res);

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

            vec2<T> operator *= (const vec2<T>& other)
            {
                if(std::is_same<T, f32>::value)
                {
                    __m128 me1 = _mm_set_ps(m00, m01, 0, 0);
                    __m128 me2 = _mm_set_ps(m10, m11, 0, 0);

                    __m128 other1 = _mm_set_ps(other.x, other.x, 0, 0);
                    __m128 other2 = _mm_set_ps(other.y, other.y, 0, 0);

                    __m128 res1 = _mm_mul_ps(me1, other1);
                    __m128 res2 = _mm_mul_ps(me2, other2);

                    __m128 res = _mm_add_ps(res1, res2);

                    T data[4];
                    _mm_store_ps(data, res);

                    return {data[0], data[1]};
                }

                if(std::is_same<T, f64>::value)
                {
                    __m256d me1 = _mm256_set_pd(m00, m01, 0, 0);
                    __m256d me2 = _mm256_set_pd(m10, m11, 0, 0);

                    __m256d other1 = _mm256_set_pd(other.x, other.x, 0, 0);
                    __m256d other2 = _mm256_set_pd(other.y, other.y, 0, 0);

                    __m256d res1 = _mm256_mul_pd(me1, other1);
                    __m256d res2 = _mm256_mul_pd(me2, other2);

                    __m256d res = _mm256_add_pd(res1, res2);

                    T data[4];
                    _mm256_store_pd(data, res);

                    return {data[0], data[1]};
                }

                T x = m00 * other.x + m10 * other.y;
                T y = m01 * other.x + m11 * other.y;

                return {x, y};

            }

            // Operations
            inline void identity()
            {
                m00 = T(1);
                m10 = T(0);
                m01 = T(0);
                m11 = T(1);
            }

            inline mat2& transpose()
            {
                T m2copy = m10;
                T m01copy = m01;

                m01 = m2copy;
                m10 = m01copy;

                return *this;
            }

            inline mat2 transposed() const
            {
                mat2 c = mat2(*this);
                return c.transpose();
            }

            inline mat2& invert()
            {
                T det = determinant();

                if(det != T(0))
                {
                    T det_inv = T(1) / det;

                    if constexpr(std::is_same<T, f32>::value)
                    {
                        __m128 me = _mm_set_ps(m11, -m01, m00, -m10);
                        __m128 det = _mm_set_ps1(det_inv);

                        __m128 res = _mm_mul_ps(me, det);

                        _mm_store_ps(v, res);

                        return *this;
                    }

                    if constexpr(std::is_same<T, f64>::value)
                    {
                        __m256d me = _mm256_set_pd(m11, -m01, m00, -m10);
                        __m256d det = _mm256_set_pd1(det_inv);

                        __m256d res = _mm256_mul_pd(me, det);

                        _mm256_store_pd(v, res);

                        return *this;
                    }

                    T t00 = m11 * det_inv;
                    T t01 = -m01 * det_inv;
                    T t11 = m00 * det_inv;
                    T t10 = -m10 * det_inv;

                    m00 = t00;
                    m10 = t10;
                    m01 = t01;
                    m11 = t11;
                }

                return *this;
            }

            inline mat2& negate()
            {
                m00 = -m00;
                m10 = -m10;
                m01 = -m01;
                m11 = -m11;

                return *this;
            }

            inline mat2 inverted() const
            {
                mat2 c = mat(*this);
                return c.invert();
            }

            inline T determinant()
            {
                return m00 * m11 - m01 * m10;
            }

            inline std::string toString() const
            {
                return std::to_string(m00) + ", " + std::to_string(m10) + "\n" + std::to_string(m01) + ", " + std::to_string(m11);
            }

            // Data
            union
            {
                struct 
                {
                    T m00, m10, m01, m11;
                };

                vec2<T> row[2];

                T v[4];            
            };
    };

    // Operators
    template<typename T>
    mat2<T> operator * (mat2<T> left, mat2<T> right)
    {
        left *= right;
        return left;
    }

    template<typename T>
    vec2<T> operator * (mat2<T> left, vec2<T> right)
    {
        vec2 r = left *= right;
        return r;
    }

    // Predefined types
    typedef mat2<f32> fmat2;
    typedef mat2<f64> dmat2;
} // namespace sml

#endif // sml_mat2_h__
