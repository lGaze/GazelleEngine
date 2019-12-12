/**************************************************************************/
/* @filename gzResouceManager.h
/* @author Victor Flores 
/* @date 2019/07/19
/* @brief 
/*************************************************************************/
#pragma once

#include "gzPrerequisitesCore.h"
#include <gzModule.h>
#include "gzResourceHandle.h"


namespace gzEngineSDK {
class GZ_CORE_EXPORT ResourceManager : public Module<ResourceManager>
{
 public:

  /**
   * @brief default constructor
   */
  ResourceManager() = default;

  /**
   * @brief default destructor
   */
  ~ResourceManager() = default;

  /************************************************************************/
  /* ResourceManager functions                                            */
  /************************************************************************/

  /**
   * @brief Function that creates a texture 2D
   */
  ResourceHandle<Texture>
  createTexture2D(TEXTURE2D_DESCRIPTOR &textureInfo);

  /**
   * @brief Function that creates a texture from the given file
   */
  ResourceHandle<Texture>
  loadTextureFromFile(const String filename);

  /**
   * @brief Function that creates a texture from the given file
   */
  ResourceHandle<Model>
  loadModelFromFile(const String filename);

  /**
   * @brief This Function creates a material 
   */
  ResourceHandle<Material>
  createMaterial();

  /**
   * @brief 
   */
  void
  drawModel(ResourceHandle<Model> model);

  /**
   * @brief This function changes the Material of the given model
   */
  void
  changeMaterial(ResourceHandle<Model> model, Material & newMat);

  /**
   * @brief This function returns the material of the given model
   */
  Material
  getMaterial(ResourceHandle<Model> model);

  /**
   * @brief Returns the model name of the given resource handle
   */
  String
  getModelName(ResourceHandle<Model> model);


  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

  protected:

  Map<String, Model*> m_modelMap;
  Map<uint32, ResourceHandle<Material>> m_materialMap;
  uint32 m_materialUniqueID;

 };
}
