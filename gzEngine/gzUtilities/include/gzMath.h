#pragma once

#include "gzPrerequisitesUtilities.h"
#include "gzPlatformMath.h"

namespace gzEngineSDK {
#if GZ_PLATFORM == GZ_PLATFORM_WIN32 || \
    GZ_PLATFORM == GZ_PLATFORM_LINUX || \
    GZ_PLATFORM == GZ_PLATFORM_OSX

  using PlatformMath Math;
#else
  using PlatformMath Math;
#endif
}