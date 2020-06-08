#ifndef sml_mat3_h__
#define sml_mat3_h__

/* mat3.h -- row major mat3 implementation of the 'Simple Math Library'
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
    class mat3
    {
        public:
            mat3()
            {
                identity();
            }

            mat3(T diagonal)
            {
                m00 = diagonal;
                m10 = T(0);
                m20 = T(0);
                m01 = T(0);
                m11 = diagonal;
                m21 = T(0);
                m02 = T(0);
                m12 = T(0);
                m22 = diagonal;
            }

            mat3(T r1[3], T r2[3], T r3[3])
            {
                m00 = r1[0];
                m10 = r1[1];
                m20 = r1[2];

                m01 = r2[0];
                m11 = r2[1];
                m21 = r2[2];
                
                m02 = r3[0];
                m12 = r3[1];
                m22 = r3[2];
            }

            mat3(T m00, T m10, T m20, T m01, T m11, T m21, T m02, T m12, T m22)
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
            }

            mat3(const mat3& other)
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
            }

            mat3(mat3&& other) noexcept
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
            }

            void set(T m00, T m10, T m01, T m11)
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
            }

            void set(T v[9])
            {
                for(int i = 0; i < 9; i++)
                {
                    this->v[i] = v[i];
                }
            }

            mat3& operator = (const mat3& other)
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

            mat3& operator = (mat3&& other) noexcept
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
            inline bool operator == (const mat3& other) const
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m512 me = _mm512_set_ps(m00, m10, m20, m01, m11, m21, m02, m12, m22, 0, 0, 0, 0, 0, 0, 0);
                    __m512 him = _mm512_set_ps(other.m00, other.m10, other.m20, other.m01, other.m11, other.m21, other.m02, other.m12, other.m22, 0, 0, 0, 0, 0, 0, 0);

                    u16 mask = _mm512_cmpeq_ps_mask(me, him);
                    return mask == 0xff
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m512d me1 = _mm512_set_pd(m00, m10, m20, m01, m11, m21, 0, 0);
                    __m512d me2 = _mm512_set_pd(m02, m12, m22, 0, 0, 0, 0, 0);

                    __m512d him1 = _mm512_set_pd(other.m00, other.m10, other.m20, other.m01, other.m11, other.m21, 0, 0);
                    __m512d him2 = _mm512_set_pd(other.m02, other.m12, other.m22, 0, 0, 0, 0, 0);

                    u16 mask1 = _mm512_cmpeq_ps_mask(me1, him1);
                    u16 mask2 = _mm512_cmpeq_ps_mask(me2, him2);

                    return mask1 == 0xff && mask2 == 0xff;
                }

                return m00 == other.m00 && m10 == other.m10 && m20 == other.m20 
                    && m01 == other.m01 && m11 == other.m11 && m21 == other.m21
                    && m02 == other.m02 && m12 == other.m12 && m22 == other.m22;
            }

            inline bool operator != (const mat3& other) const
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m512 me = _mm512_set_ps(m00, m10, m20, m01, m11, m21, m02, m12, m22, 0, 0, 0, 0, 0, 0, 0);
                    __m512 him = _mm512_set_ps(other.m00, other.m10, other.m20, other.m01, other.m11, other.m21, other.m02, other.m12, other.m22, 0, 0, 0, 0, 0, 0, 0);

                    u16 mask = _mm512_cmpneq_ps_mask(me, him);
                    return mask != 0;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m512d me1 = _mm512_set_pd(m00, m10, m20, m01, m11, m21, 0, 0);
                    __m512d me2 = _mm512_set_pd(m02, m12, m22, 0, 0, 0, 0, 0);

                    __m512d him1 = _mm512_set_pd(other.m00, other.m10, other.m20, other.m01, other.m11, other.m21, 0, 0);
                    __m512d him2 = _mm512_set_pd(other.m02, other.m12, other.m22, 0, 0, 0, 0, 0);

                    u16 mask1 = _mm512_cmpneq_ps_mask(me1, him1);
                    u16 mask2 = _mm512_cmpneq_ps_mask(me2, him2);

                    return mask1 != 0 && mask2 != 0;
                }

                return m00 == other.m00 || m10 == other.m10 || m20 == other.m20 
                    || m01 == other.m01 || m11 == other.m11 || m21 == other.m21
                    || m02 == other.m02 || m12 == other.m12 || m22 == other.m22;
            }

            mat3& operator *= (const mat3& other)
            {
                T newM00 = m00 * other.m00 + m10 * other.m01 + m20 * other.m02;
                T newM01 = m01 * other.m00 + m11 * other.m01 + m21 * other.m02;
                T newM02 = m02 * other.m00 + m12 * other.m11 + m22 * other.m02;

                T newM00 = m00 * other.m10 + m10 * other.m11 + m20 * other.m12;
                T newM01 = m01 * other.m10 + m11 * other.m11 + m21 * other.m12;
                T newM02 = m02 * other.m10 + m12 * other.m11 + m22 * other.m12;

                T newM10 = m00 * other.m20 + m10 * other.m21 + m20 * other.m22;
                T newM11 = m01 * other.m20 + m11 * other.m21 + m21 * other.m22;
                T newM12 = m02 * other.m20 + m12 * other.m21 + m22 * other.m22;

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

            vec3<T> operator *= (const vec3<T>& other)
            {
                T x = m00 * other.x + m10 * other.y + m20 * other.z;
                T y = m01 * other.x + m11 * other.y + m21 * other.z;
                T z = m02 * other.x + m12 * other.y + m22 * other.z;

                return {x, y, z};
            }

            // Operations
            inline void identity()
            {
                m00 = T(1);
                m10 = T(0);
                m20 = T(0);
                m01 = T(0);
                m11 = T(1);
                m21 = T(0);
                m02 = T(0);
                m12 = T(0);
                m22 = T(1);
            }

            inline mat3& transpose()
            {
                T newM00 = m00;
                T newM01 = m10;
                T newM02 = m20;
                T newM10 = m01;
                T newM11 = m11;
                T newM12 = m21;
                T newM20 = m02;
                T newM21 = m12;
                T newM22 = m22;

                this->m00 = newM00;
                this->m01 = newM01;
                this->m02 = newM02;
                this->m10 = newM10;
                this->m11 = newM11;
                this->m12 = newM12;
                this->m20 = newM20;
                this->m21 = newM21;
                this->m22 = newM22;

                return *this;
            }

            inline mat3 transposed() const
            {
                mat3 c = mat3(*this);
                return c.transpose();
            }

            inline mat3& invert()
            {
                T det = determinant();

                if(det != T(0))
                {
                    T det_inv = T(1) / det;

                    T t00 = m11 * m22 - m12 * m21;
                    T t01 = -m10 * m22 + m12 * m20;
                    T t02 = m10 * m21 - m11 * m20;
                    T t10 = -m01 * m22 + m02 * m21;
                    T t11 = m00 * m22 - m02 * m20;
                    T t12 = -m00 * m21 + m01 * m20;
                    T t20 = m01 * m12 - m02 * m11;
                    T t21 = -m00 * m12 + m02 * m10;
                    T t22 = m00 * m11 - m01 * m10l

                    m00 = t00 * det_inv;
                    m11 = t11 * det_inv;
                    m22 = t22 * det_inv;

                    m01 = t10 * det_inv;
                    m10 = t01 * det_inv;
                    m20 = t02 * det_inv;

                    m02 = t20 * det_inv;
                    m12 = t21 * det_inv;
                    m21 = t12 * det_inv;
                }

                return *this;
            }

            inline mat3& negate()
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

                return *this;
            }

            inline mat3 inverted() const
            {
                mat3 c = mat(*this);
                return c.invert();
            }

            inline T determinant()
            {
                return m00 * (m11 * m22 - m12 * m21)
                            + m01 * (m12 * m20 - m10 * m22)
                            + m02 * (m10 * m21 - m11 * m20);
            }

            inline std::string toString() const
            {
                return std::to_string(m00) + ", " + std::to_string(m10) + ", " + std::to_string(m20) + "\n" 
                    + std::to_string(m01) + ", " + std::to_string(m11) + ", " + std::to_string(m21) "\n"
                    + std::to_string(m02) + ", " + std::to_string(m12) + ", " + std::to_string(m22);
            }

            // Data
            union
            {
                struct 
                {
                    T m00, m10, m20, m01, m11, m21, m02, m12, m22;
                };

                vec3<T> row[3];

                T v[9];            
            };
    };

    // Operators
    template<typename T>
    mat3<T> operator * (mat3<T> left, mat3<T> right)
    {
        left *= right;
        return left;
    }

    template<typename T>
    vec3<T> operator * (mat3<T> left, vec3<T> right)
    {
        vec3 r = left *= right;
        return r;
    }

    // Predefined types
    typedef mat3<f32> fmat3;
    typedef mat3<f64> dmat3;
} // namespace sml

#endif // sml_mat3_h__
