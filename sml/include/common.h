#ifndef sml_common_h__
#define sml_common_h__

/* sml.h -- common math implementation of the 'Simple Math Library'
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

#include <math.h>

#include "smltypes.h"

namespace constants 
{
    static inline constexpr f32 pi      = 3.14159265358979323846f;
    static inline constexpr f32 two_pi  = 6.28318530717958647692f;
    static inline constexpr f32 half_pi = 1.57079632679489661923f;
    static inline constexpr f32 maxflt = FLT_MAX;
    static inline constexpr f32 epsilon = FLT_EPSILON;
    static inline constexpr f32 infinity = INFINITY;
    static inline constexpr f32 negativeinfinity = -infinity;
    static inline constexpr f32 deg2rad = pi * 2.0f / 360.0f;
    static inline constexpr f32 rad2deg = 1.0f / deg2rad;
}

#endif // sml_common_h__