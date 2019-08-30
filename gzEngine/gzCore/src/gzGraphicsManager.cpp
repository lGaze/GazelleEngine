/**************************************************************************/
/* @filename gzGraphicsManager.cpp
/* @author Victor Flores 
/* @date 2019/03/07
/* @brief 
/**************************************************************************/

#include "gzGraphicsManager.h"

namespace gzEngineSDK {

  GraphicsManager::GraphicsManager() { }
  GraphicsManager::~GraphicsManager() { }

  GZ_CORE_EXPORT GraphicsManager& 
  g_GraphicsManager() {
    return GraphicsManager::instance();
  }
}