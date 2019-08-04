/**************************************************************************/
/* @filename gzResourceManager.cpp
/* @author Victor Flores 
/* @date 2019/07/23
/* @brief 
/**************************************************************************/

#include "gzResourceManager.h"
#include "gzGraphicsManager.h"
#include "gzTexture.h"
#include "gzModel.h"

namespace gzEngineSDK {

  ResourceHandle<Texture>
  ResourceManager::createTexture2D(TEXTURE2D_DESCRIPTOR & textureInfo)
  {
    Texture * tempTex = new Texture();
    tempTex = GraphicsManager::instance().createTexture2D(textureInfo);

    ResourceHandle<Texture> handle;
    handle.setHandle(tempTex);
    return handle;
  }

  ResourceHandle<Texture> 
  ResourceManager::loadTextureFromFile(const String filename)
  {
    Texture * tempTex = new Texture();
    tempTex = GraphicsManager::instance().LoadTextureFromFile(filename);

    ResourceHandle<Texture> handle;
    handle.setHandle(tempTex);
    return handle;
  }

  ResourceHandle<Model> 
  ResourceManager::loadModelFromFile(const String filename)
  {
    Model * tempModel = new Model();
    tempModel->Load(filename);

    ResourceHandle<Model> handle;
    handle.setHandle(tempModel);
    return handle;
  }

  void 
  ResourceManager::drawModel(ResourceHandle<Model> model)
  {
    Model * tempModel = reinterpret_cast<Model*>(model.getHandle());
    tempModel->Draw();
  }
}
