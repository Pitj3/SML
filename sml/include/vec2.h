#ifndef sml_vec2_h__
#define sml_vec2_h__

/* sml.h -- vec2 implementation of the 'Simple Math Library'
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

#include <typeinfo>
#include <type_traits>

#include "vec_type.h"

template<typename T>
class vec2
{
    public:
        vec2()
        {
            zero();
        }

        void zero()
        {
            x = y = T(0);
        }

        // Data
        union
        {
            T x, y;
            T v[2];
        }
};

#endif // sml_vec2_h__