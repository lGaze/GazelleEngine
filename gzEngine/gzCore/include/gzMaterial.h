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
  Material();

  /**
   * @brief default destructor
   */
  ~Material();

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
   * @brief Gets the Albedo texture
   */
  FORCEINLINE Texture &
  getAlbedoTexture() {
    return *m_albedoTexture;
  }


  /**
   * @brief gets the Normal texture;
   */
  FORCEINLINE Texture &
  getNormalTexture() {
    return *m_normalTexture;
  }


  /**
   * @brief Gets the Metallic texture of the material
   */
  FORCEINLINE Texture &
  getMetallicTexture() {
    return *m_metallicTexture;
  }


  /**
   * @brief Gets the Roughness texture of the material
   */
  FORCEINLINE Texture &
    getRoughnessTexture() {
    return *m_roughnessTexture;
  }


  /**
   * @brief Gets the Emissive texture of the material
   */
  FORCEINLINE Texture &
  getEmissiveTexture() {
    return *m_emissiveTexture;
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

 private:

   /**
    * @brief 
    */
  void
  createAsDefault();

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
