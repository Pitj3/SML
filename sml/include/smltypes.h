#ifndef smltypes_h__
#define smltypes_h__

/* smltypes.h -- predefined variable types of the 'Simple Math Library'
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

#include <cstdint>
#include <type_traits>

// Predefined types
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long u64;
typedef signed long s64;

typedef float f32;
typedef double f64;

#define SML_NO_DISCARD [[nodiscard]]

namespace sml
{
    template<typename T>
    struct simdalign : std::integral_constant<size_t, 1>
    {
    };

    template<>
    struct simdalign<f32> : std::integral_constant<size_t, 16>
    {
    };

    template<>
    struct simdalign<f64> : std::integral_constant<size_t, 32>
    {
    };
}

#endif // smltypes_h__

