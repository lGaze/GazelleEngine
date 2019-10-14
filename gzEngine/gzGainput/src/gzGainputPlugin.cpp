/**************************************************************************/
/* @filename gzGainputPlugin.cpp
/* @author Victor Flores 
/* @date 2019/10/13
/* @brief Plugin of Gainput
/*************************************************************************/

#include "gzGainputManager.h"

namespace gzEngineSDK {
  extern "C" __declspec(dllexport) void
  CreateManagerObject() {
    InputManager::startUp<GainputManager>();
  }
}