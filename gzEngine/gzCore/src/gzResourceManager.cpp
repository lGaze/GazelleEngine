/**************************************************************************/
/* @filename gzResourceManager.cpp
/* @author Victor Flores 
/* @date 2019/07/23
/* @brief 
/**************************************************************************/

#include "gzResourceManager.h"
#include "gzResourceHandle.h"

namespace gzEngineSDK {

  ResourceHandle<class T>
  ResourceManager::createTexture2D(TEXTURE2D_DESCRIPTOR & textureInfo)
  {
    return ResourceHandle();
  }

  ResourceHandle<class T> 
  ResourceManager::loadTextureFromFile(const String filename)
  {
    return ResourceHandle();
  }

  ResourceHandle<class T> 
  ResourceManager::loadModelFromFile(const String filename)
  {
    return ResourceHandle();
  }
}
