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
   * @brief 
   */
  void
  drawModel(ResourceHandle<Model> model);


  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 public:

 };
}
