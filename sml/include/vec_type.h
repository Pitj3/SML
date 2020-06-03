#ifndef sml_vectype_h__
#define sml_vectype_h__

/* sml.h -- vector types of the 'Simple Math Library'
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

template<typename T, size_t Sz>
struct getDataType
{
    typedef void Type;
};

template<>
struct getDataType<float, 2>
{
    typedef __m64 Type;
};

template<typename T, size_t Sz>
using DataType = typename getDataType<T, Sz>::Type;

#endif // sml_vectype_h__