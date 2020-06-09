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

#include "vec3.h"
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
                    __m128 me1 = _mm_set_ps(m00, m10, m20, m01);
                    __m128 me2 = _mm_set_ps(m11, m21, m02, m12);
                    __m128 me3 = _mm_set_ps(m22, 0, 0, 0);

                    __m128 him1 = _mm_set_ps(other.m00, other.m10, other.m20, other.m01);
                    __m128 him2 = _mm_set_ps(other.m11, other.m21, other.m02, other.m12);
                    __m128 him3 = _mm_set_ps(other.m22, 0, 0, 0);

                    // m00 == other.m00 && m10 == other.m10 && m20 == other.m20 
                    // && m01 == other.m01 && m11 == other.m11 && m21 == other.m21
                    // && m02 == other.m02 && m12 == other.m12 && m22 == other.m22
                    s32 mask1 = _mm_movemask_pd(_mm_cmpeq_ps(me1, him1));
                    s32 mask2 = _mm_movemask_pd(_mm_cmpeq_ps(me2, him2));
                    s32 mask3 = _mm_movemask_pd(_mm_cmpeq_ps(me3, him3));

                    return mask1 == 0xffff && mask2 == 0xffff && mask3 == 0xffff;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m128d me1 = _mm_set_pd(m00, m10);
                    __m128d me2 = _mm_set_pd(m20, m01);
                    __m128d me3 = _mm_set_pd(m11, m21);
                    __m128d me4 = _mm_set_pd(m02, m12);
                    __m128d me5 = _mm_set_pd(m22, 0);

                    __m128d him1 = _mm_set_pd(other.m00, other.m10);
                    __m128d him2 = _mm_set_pd(other.m20, other.m01);
                    __m128d him3 = _mm_set_pd(other.m11, other.m21);
                    __m128d him4 = _mm_set_pd(other.m02, other.m12);
                    __m128d him5 = _mm_set_pd(other.m22, 0);

                    // m00 == other.m00 && m10 == other.m10 && m20 == other.m20 
                    // && m01 == other.m01 && m11 == other.m11 && m21 == other.m21
                    // && m02 == other.m02 && m12 == other.m12 && m22 == other.m22
                    s32 mask1 = _mm_movemask_pd(_mm_cmpeq_pd(me1, him1));
                    s32 mask2 = _mm_movemask_pd(_mm_cmpeq_pd(me2, him2));
                    s32 mask3 = _mm_movemask_pd(_mm_cmpeq_pd(me3, him3));
                    s32 mask4 = _mm_movemask_pd(_mm_cmpeq_pd(me4, him4));
                    s32 mask5 = _mm_movemask_pd(_mm_cmpeq_pd(me5, him5));

                    return mask1 == 0xffff && mask2 == 0xffff && mask3 == 0xffff && mask4 == 0xffff && mask5 == 0xffff;
                }

                return m00 == other.m00 && m10 == other.m10 && m20 == other.m20 
                    && m01 == other.m01 && m11 == other.m11 && m21 == other.m21
                    && m02 == other.m02 && m12 == other.m12 && m22 == other.m22;
            }

            inline bool operator != (const mat3& other) const
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 me1 = _mm_set_ps(m00, m10, m20, m01);
                    __m128 me2 = _mm_set_ps(m11, m21, m02, m12);
                    __m128 me3 = _mm_set_ps(m22, 0, 0, 0);

                    __m128 him1 = _mm_set_ps(other.m00, other.m10, other.m20, other.m01);
                    __m128 him2 = _mm_set_ps(other.m11, other.m21, other.m02, other.m12);
                    __m128 him3 = _mm_set_ps(other.m22, 0, 0, 0);

                    // m00 == other.m00 || m10 == other.m10 || m20 == other.m20 
                    // || m01 == other.m01 || m11 == other.m11 || m21 == other.m21
                    // || m02 == other.m02 || m12 == other.m12 || m22 == other.m22
                    s32 mask1 = _mm_movemask_pd(_mm_cmpneq_ps(me1, him1));
                    s32 mask2 = _mm_movemask_pd(_mm_cmpneq_ps(me2, him2));
                    s32 mask3 = _mm_movemask_pd(_mm_cmpneq_ps(me3, him3));

                    return mask1 != 0 || mask2 != 0 || mask3 != 0;
                }

                if constexpr(std::is_same<T, f64>::value)
                {
                    __m128d me1 = _mm_set_pd(m00, m10);
                    __m128d me2 = _mm_set_pd(m20, m01);
                    __m128d me3 = _mm_set_pd(m11, m21);
                    __m128d me4 = _mm_set_pd(m02, m12);
                    __m128d me5 = _mm_set_pd(m22, 0);

                    __m128d him1 = _mm_set_pd(other.m00, other.m10);
                    __m128d him2 = _mm_set_pd(other.m20, other.m01);
                    __m128d him3 = _mm_set_pd(other.m11, other.m21);
                    __m128d him4 = _mm_set_pd(other.m02, other.m12);
                    __m128d him5 = _mm_set_pd(other.m22, 0);

                    // m00 == other.m00 || m10 == other.m10 || m20 == other.m20 
                    // || m01 == other.m01 || m11 == other.m11 || m21 == other.m21
                    // || m02 == other.m02 || m12 == other.m12 || m22 == other.m22
                    s32 mask1 = _mm_movemask_pd(_mm_cmpeq_pd(me1, him1));
                    s32 mask2 = _mm_movemask_pd(_mm_cmpeq_pd(me2, him2));
                    s32 mask3 = _mm_movemask_pd(_mm_cmpeq_pd(me3, him3));
                    s32 mask4 = _mm_movemask_pd(_mm_cmpeq_pd(me4, him4));
                    s32 mask5 = _mm_movemask_pd(_mm_cmpeq_pd(me5, him5));

                    return mask1 != 0 || mask2 != 0 || mask3 != 0 || mask4 != 0 || mask5 != 0;
                }

                return m00 == other.m00 || m10 == other.m10 || m20 == other.m20 
                    || m01 == other.m01 || m11 == other.m11 || m21 == other.m21
                    || m02 == other.m02 || m12 == other.m12 || m22 == other.m22;
            }

            mat3& operator *= (const mat3& other)
            {
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 MV00 = _mm_set_ps(m00, m01, m02, m00);
                    __m128 MV01 = _mm_set_ps(m01, m02, m00, m01);
                    __m128 MV02 = _mm_set_ps(m02, 0, 0, 0);

                    __m128 MV10 = _mm_set_ps(other.m00, other.m00, other.m00, other.m10);
                    __m128 MV11 = _mm_set_ps(other.m10, other.m10, other.m20, other.m20);
                    __m128 MV12 = _mm_set_ps(other.m20, 0, 0, 0);

                    // m00 * other.m00
                    // m01 * other.m00
                    // m02 * other.m00
                    // m00 * other.m10
                    __m128 MV00010 = _mm_mul_ps(MV00, MV10);

                    // m01 * other.m10
                    // m02 * other.m10
                    // m00 * other.m20
                    // m01 * other.m20
                    __m128 MV00111 = _mm_mul_ps(MV01, MV11);

                    // m02 * other.m20
                    __m128 MV00212 = _mm_mul_ps(MV02, MV12);

                    MV00 = _mm_set_ps(m10, m11, m12, m10);
                    MV01 = _mm_set_ps(m11, m12, m10, m11);
                    MV02 = _mm_set_ps(m12, 0, 0, 0);

                    MV10 = _mm_set_ps(other.m01, other.m01, other.m01, other.m11);
                    MV11 = _mm_set_ps(other.m11, other.m11, other.m21, other.m21);
                    MV12 = _mm_set_ps(other.m21, 0, 0, 0);

                    // m10 * other.m01
                    // m11 * other.m01
                    // m12 * other.m01
                    // m10 * other.m11
                    __m128 MV10010 = _mm_mul_ps(MV00, MV10);

                    // m11 * other.m11
                    // m12 * other.m11
                    // m10 * other.m21
                    // m11 * other.m21
                    __m128 MV10111 = _mm_mul_ps(MV01, MV11);

                    // m12 * other.m21
                    __m128 MV10212 = _mm_mul_ps(MV02, MV12);

                    MV00 = _mm_set_ps(m20, m21, m22, m20);
                    MV01 = _mm_set_ps(m21, m22, m20, m21);
                    MV02 = _mm_set_ps(m22, 0, 0, 0);

                    MV10 = _mm_set_ps(other.m02, other.m02, other.m02, other.m12);
                    MV11 = _mm_set_ps(other.m12, other.m12, other.m22, other.m22);
                    MV12 = _mm_set_ps(other.m22, 0, 0, 0);

                    // m20 * other.m02
                    // m21 * other.m02
                    // m22 * other.m02
                    // m20 * other.m12
                    __m128 MV20010 = _mm_mul_ps(MV00, MV10);

                    // m21 * other.m12
                    // m22 * other.m12
                    // m20 * other.m22
                    // m21 * other.m22
                    __m128 MV20111 = _mm_mul_ps(MV01, MV11);

                    // m22 * other.m22
                    __m128 MV20212 = _mm_mul_ps(MV02, MV12);

                    // m00 * other.m00 + m10 * other.m01
                    // m01 * other.m00 + m11 * other.m01
                    // m02 * other.m00 + m12 * other.m01
                    // m00 * other.m10 + m10 * other.m11
                    __m128 MVRes01 = _mm_add_ps(MV00010, MV10010);

                    // m01 * other.m10 + m11 * other.m11
                    // m02 * other.m10 + m12 * other.m11
                    // m00 * other.m20 + m10 * other.m21
                    // m01 * other.m20 + m11 * other.m21
                    __m128 MVRes02 = _mm_add_ps(MV00111, MV10111);

                    // m02 * other.m20 + m12 * other.m21
                    __m128 MVRes03 = _mm_add_ps(MV00212, MV20212);

                    // m00 * other.m00 + m10 * other.m01 + m20 * other.m02
                    // m01 * other.m00 + m11 * other.m01 + m21 * other.m02
                    // m02 * other.m00 + m12 * other.m01 + m22 * other.m02
                    // m00 * other.m10 + m10 * other.m11 + m20 * other.m12
                    __m128 MVRes04 = _mm_add_ps(MVRes01, MV20010);

                    // m01 * other.m10 + m11 * other.m11 + m21 * other.m12
                    // m02 * other.m10 + m12 * other.m11 + m22 * other.m12
                    // m00 * other.m20 + m10 * other.m21 + m20 * other.m22
                    // m01 * other.m20 + m11 * other.m21 + m21 * other.m22
                    __m128 MVRes05 = _mm_add_ps(MVRes02, MV20111);

                    // m02 * other.m20 + m12 * other.m21 + m22 * other.m22
                    __m128 MVRes06 = _mm_add_ps(MVRes03, MV20212);

                    T upper[4];
                    T middle [4];
                    T lower [4];
                    _mm_store_ps(upper, MVRes04);
                    _mm_store_ps(middle, MVRes05);
                    _mm_store_ps(lower, MVRes06);

                    v[0] = upper[0];
                    v[1] = upper[1];
                    v[2] = upper[2];
                    v[3] = upper[3];

                    v[4] = middle[0];
                    v[5] = middle[1];
                    v[6] = middle[2];
                    v[7] = middle[3];

                    v[8] = lower[0];
                    
                    return *this;
                }

                T newM00 = m00 * other.m00 + m10 * other.m01 + m20 * other.m02;
                T newM01 = m01 * other.m00 + m11 * other.m01 + m21 * other.m02;
                T newM02 = m02 * other.m00 + m12 * other.m01 + m22 * other.m02;

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
                if constexpr(std::is_same<T, f32>::value)
                {
                    __m128 MV1 = _mm_set_ps(m00, m01, m02, 0);
                    __m128 MV2 = _mm_set_ps1(other.x);

                    // m00 * other.x
                    // m01 * other.x
                    // m02 * other.x
                    __m128 MV1Res = _mm_mul_ps(MV1, MV2);

                    MV1 = _mm_set_ps(m10, m11, m12, 0);
                    MV2 = _mm_set_ps1(other.y);

                    // m10 * other.y
                    // m11 * other.y
                    // m12 * other.y
                    __m128 MV2Res = _mm_mul_ps(MV1, MV2);

                    MV1 = _mm_set_ps(m20, m21, m22, 0);
                    MV2 = _mm_set_ps1(other.z);

                    // m20 * other.z
                    // m21 * other.z
                    // m22 * other.z
                    __m128 MV3Res = _mm_mul_ps(MV1, MV2);

                    // m00 * other.x + m10 * other.y
                    // m01 * other.x + m11 * other.y
                    // m02 * other.x + m12 * other.y
                    __m128 MV12Res = _mm_add_ps(MV1Res, MV2Res);

                    // m00 * other.x + m10 * other.y + m20 * other.z
                    // m01 * other.x + m11 * other.y + m21 * other.z
                    // m02 * other.x + m12 * other.y + m22 * other.z
                    __m128 MV123Res = _mm_add_ps(MV12Res, MV3Res);

                    T data[4];
                    _mm_store_ps(data, MV123Res);

                    return {data[0], data[1], data[2]};
                }

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

                    if constexpr(std::is_same<T, f32>::value)
                    {
                        __m128 TV00 = _mm_set_ps(m11, -m10, m10, -m01);
                        __m128 TV01 = _mm_set_ps(m00, -m00, m01, -m00);
                        __m128 TV02 = _mm_set_ps(m00, 0, 0, 0);

                        __m128 TV10 = _mm_set_ps(m22, m22, m21, m22);
                        __m128 TV11 = _mm_set_ps(m22, m21, m12, m12);
                        __m128 TV12 = _mm_set_ps(m11, 0, 0, 0);

                        // m11 * m22 
                        // -m10 * m22
                        // m10 * m21 
                        // -m01 * m22
                        __m128 TVRes00010 = _mm_mul_ps(TV00, TV10);

                        // m00 * m22 
                        // -m00 * m21
                        // m01 * m12 
                        // -m00 * m12
                        __m128 TVRes00111 = _mm_mul_ps(TV01, TV11);

                        // m00 * m11
                        __m128 TVRes00212 = _mm_mul_ps(TV02, TV12);

                        TV00 = _mm_set_ps(-m12, m12, -m11, m02);
                        TV01 = _mm_set_ps(-m02, m01, -m02, m02);
                        TV02 = _mm_set_ps(-m01, 0, 0, 0);

                        TV10 = _mm_set_ps(m21, m20, m20, m21);
                        TV11 = _mm_set_ps(m20, m20, m11, m10);
                        TV12 = _mm_set_ps(m10, 0, 0, 0);

                        // -m12 * m21 
                        // m12 * m20
                        // -m11 * m20 
                        // m02 * m21
                        __m128 TVRes10010 = _mm_mul_ps(TV00, TV10);

                        // -m02 * m20 
                        // m01 * m20
                        // -m02 * m11
                        // m02 * m10
                        __m128 TVRes10111 = _mm_mul_ps(TV01, TV11);

                        // -m01 * m10
                        __m128 TVRes10212 = _mm_mul_ps(TV02, TV12);

                        // m11 * m22 - m12 * m21
                        // -m10 * m22 + m12 * m20
                        // m10 * m21 - m11 * m20
                        // -m01 * m22 + m02 * m21
                        __m128 Res1 = _mm_mul_ps(TVRes00010, TVRes10010);

                        // m00 * m22 - m02 * m20
                        // -m00 * m21 + m01 * m20
                        // m01 * m12 - m02 * m11
                        // -m00 * m12 + m02 * m10
                        __m128 Res2 = _mm_mul_ps(TVRes00111, TVRes10111);

                        // m00 * m11 - m01 * m10
                        __m128 Res3 = _mm_mul_ps(TVRes00212, TVRes10202);

                        __m128 DetV = _mm_set_ps1(det_inv);

                        // m00 = t00 * det_inv;
                        // m11 = t11 * det_inv;
                        // m22 = t22 * det_inv;
                        // m01 = t10 * det_inv;
                        // m10 = t11 * det_inv;
                        // m20 = t12 * det_inv;
                        // m02 = t20 * det_inv;
                        // m12 = t21 * det_inv;
                        // m21 = t12 * det_inv;
                        Res1 = _mm_mul_ps(Res1, DetV);
                        Res2 = _mm_mul_ps(Res2, DetV);
                        Res3 = _mm_mul_ps(Res3, DetV);

                        T upper[4];
                        T middle[4];
                        T lower[4];

                        _mm_store_ps(upper, Res1);
                        _mm_store_ps(middle, Res2);
                        _mm_store_ps(lower, Res3);

                        v[0] = upper[0];
                        v[1] = upper[1];
                        v[2] = upper[2];
                        v[3] = upper[3];

                        v[4] = middle[0];
                        v[5] = middle[1];
                        v[6] = middle[2];
                        v[7] = middle[3];

                        v[8] = lower[0];

                        return *this;
                    }

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
