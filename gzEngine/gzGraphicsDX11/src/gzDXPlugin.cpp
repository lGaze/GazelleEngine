/**************************************************************************/
/* @filename gzDXPlugin.cpp
/* @author Victor Flores 
/* @date 2019/03/12
/* @brief 
/**************************************************************************/

#include "gzDXPrerequisites.h"

#include <gzDXGraphicsManager.h>

namespace gzEngineSDK {
  extern "C" __declspec( dllexport ) void
  CreateManagerObject() 
  {
   GraphicsManager::startUp<DXGraphicsManager>();
  }
}