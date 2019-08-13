/**************************************************************************/
/* @filename gzPBRRendererPlugin.cpp
/* @author Victor Flores 
/* @date 2019/08/11
/* @brief 
/**************************************************************************/

#include "gzPBRRendererPrerequisites.h"
#include "gzPBRRenderer.h"

namespace gzEngineSDK {
  extern "C" __declspec(dllexport) void
  CreateManagerObject()
  {
    Renderer::startUp<PBRRenderer>();
  }
}