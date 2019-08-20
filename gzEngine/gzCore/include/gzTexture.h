/**************************************************************************/
/* @filename gzTexture.h
/* @author Victor Flores 
/* @date 2019/03/16
/* @brief  This file works as an interface for create Textures
/**************************************************************************/

#pragma once

#include "gzPrerequisitesCore.h"
#include "gzResource.h"

namespace gzEngineSDK {
class GZ_CORE_EXPORT Texture : public Resource
{
 public:
   
  /**
   * @brief Default constructor
   */
  Texture();

  /**
   * @brief Default destructor
   */
  virtual
  ~Texture();
 
  /************************************************************************/
  /* Texture functions                                                    */
  /************************************************************************/

  /**
   * @brief Loads a Texture from a given path 
   * @param Path of the file 
   */
  void
  loadTextureFromFile(const String filepath);

  /**
   * @brief Gets the informatio of the texture
   * @return The information of the texture
   */
  FORCEINLINE unsigned char*
  getTextureInfo() {
    return &m_textureInfo[0];
  }

  /**
   * @brief Gets the width of the texture
   * @return Integer that indicates the width of the texture
   */
  FORCEINLINE int32
  getWidth() {
    return m_Width;
  }

  /**
   * @brief Gets the height of the texture
   * @return Integer that indicates the height of the texture
   */
  FORCEINLINE int32
  getHeight() {
    return m_Height;
  }

  /**
   * @brief Gets the chanels of the texture
   * @param integer that indicates the chanels of the texture
   */
  FORCEINLINE int32
  getChanels() { 
    return m_Channels;
  }

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
 protected:

 Vector<unsigned char> m_textureInfo;
 int32 m_Width;
 int32 m_Height;
 int32 m_Channels;

 public:
   
 };
}