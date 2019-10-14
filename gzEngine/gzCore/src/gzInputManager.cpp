/**************************************************************************/
/* @filename gzInputManager.cpp
/* @author Victor Flores 
/* @date 2019/10/13
/* @brief 
/**************************************************************************/

#include "gzInputManager.h"

namespace gzEngineSDK {
  GZ_CORE_EXPORT InputManager & 
  g_InputManager() {
    return InputManager::instance();
  }
}