/**************************************************************************/
/* @filename gzMath.h
/* @author Victor Flores 
/* @date 2019/02/15
/* @brief 
/**************************************************************************/

#pragma once

#include "gzPrerequisitesUtilities.h"
#include "gzPlatformMath.h"

namespace gzEngineSDK {
#if GZ_PLATFORM == GZ_PLATFORM_WIN32 || \
    GZ_PLATFORM == GZ_PLATFORM_LINUX || \
    GZ_PLATFORM == GZ_PLATFORM_OSX

  using Math = PlatformMath;
#else
  using Math = PlatformMath;
#endif
}