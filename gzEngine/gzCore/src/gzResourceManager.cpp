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
    tempTex = g_GraphicsManager().createTexture2D(textureInfo);

    ResourceHandle<Texture> handle;
    handle.setHandle(tempTex);
    return handle;
  }

  ResourceHandle<Texture> 
  ResourceManager::loadTextureFromFile(const String filename)
  {
    Texture * tempTex = new Texture();
    tempTex = g_GraphicsManager().LoadTextureFromFile(filename);

    ResourceHandle<Texture> handle;
    handle.setHandle(tempTex);
    return handle;
  }

  ResourceHandle<Model> 
  ResourceManager::loadModelFromFile(const String filename)
  {
    ResourceHandle<Model> handle;

    auto mapfilename = m_modelMap.find(filename);

    if (mapfilename != m_modelMap.end())
    {
      handle.setHandle(mapfilename->second);
      return handle;
    }

    Model * model = new Model();
    model->Load(filename);
    handle.setHandle(model);
    
    m_modelMap.insert(std::pair<String,Model*>(filename, model));

    return handle;
  }

  void 
  ResourceManager::drawModel(ResourceHandle<Model> model)
  {
    Model * tempModel = reinterpret_cast<Model*>(model.getHandle());
    tempModel->Draw();
  }

  void 
  ResourceManager::changeMaterial(ResourceHandle<Model> model, Material & newMat)
  {
    Model * tempModel = reinterpret_cast<Model*>(model.getHandle());
    tempModel->changeMaterial(newMat);
  }
}
