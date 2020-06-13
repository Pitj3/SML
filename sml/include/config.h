#ifndef sml_config_h__
#define sml_config_h__

/* config.h -- config of the 'Simple Math Library'
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

#include <cmath>
#include <float.h>

#include "smltypes.h"

// Undefine these for matrix functions
#ifdef near
#undef near
#endif

#ifdef near
#undef far
#endif

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

namespace sml
{
	// Struct holding version data
	struct smlVersion
	{
		s32 major;
		s32 minor;
		s32 revision;
	};

	/// Current version.
	smlVersion version = { 0, 1, 0 };
} // namespace sml

#endif // sml_config_h__