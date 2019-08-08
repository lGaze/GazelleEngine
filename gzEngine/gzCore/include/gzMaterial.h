/**************************************************************************/
/* @filename gzMaterial.h
/* @author Victor Flores 
/* @date 2019/08/06
/* @brief Material header file 
/**************************************************************************/
#pragma once

#include "gzPrerequisitesCore.h"
#include "gzResource.h"

namespace gzEngineSDK {
class GZ_CORE_EXPORT Material : public Resource
{
 public:
   
  /**
   * @brief default constructor
   */
  Material() = default;

  /**
   * @brief default destructor
   */
  ~Material() = default;

  /************************************************************************/
  /* Material functions                                                   */
  /************************************************************************/

  /**
   * @brief Sets the given texture into the albedo pointer of the material
   */
  FORCEINLINE void
  setAlbedoTexture(Texture & albedoTexture){
    m_albedoTexture = &albedoTexture;
  }

  /**
   * @brief Sets the given texture into the albedo pointer of the material
   */
  FORCEINLINE Texture &
  getAlbedoTexture() {
    return *m_albedoTexture;
  }

  /**
   * @brief Sets the given texture into the albedo pointer of the material
   */
  FORCEINLINE void
  setMetallicTexture(Texture & metallicTexture){
    m_metallicTexture = &metallicTexture;
  }

  /**
   * @brief Sets the given texture into the roughness pointer of the material
   */
  FORCEINLINE void
  setRoughnessTexture(Texture & roughnessTexture) {
    m_roughnessTexture = &roughnessTexture;
  }

  /**
   * @brief Sets the given texture into the normal pointer of the material
   */
  FORCEINLINE void
  setNormalTexture(Texture & normalTexture){
    m_normalTexture = &normalTexture;
  }

  /**
   * @brief Sets the given texture into the emissive pointer of the material
   */
  FORCEINLINE void
  setEmissiveTexture(Texture & emissiveTexture){
    m_emissiveTexture = &emissiveTexture;
  }

  /**
   * @brief Sets the given texture into the specular pointer of the material
   */
  FORCEINLINE void
  setSpecularTexture(Texture & specularTexture){
    m_specularTexture = &specularTexture;
  }

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:

   Texture * m_albedoTexture;
   Texture * m_metallicTexture;
   Texture * m_roughnessTexture;
   Texture * m_normalTexture;
   Texture * m_emissiveTexture;
   Texture * m_specularTexture;
   
 };
}
