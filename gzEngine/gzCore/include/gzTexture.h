/**************************************************************************/
/* @filename gzTexture.h
/* @author Victor Flores 
/* @date 2019/03/16
/* @brief 
/**************************************************************************/

#pragma once

#include "gzPrerequisitesCore.h"

namespace gzEngineSDK {
class GZ_CORE_EXPORT Texture
{
 public:
   
  /**
   * @brief default constructor
   */
  Texture();
	
  /**
   * @brief default destructor
   */
  virtual
  ~Texture();
	 
  /************************************************************************/
  /* Texture functions                                                    */
  /************************************************************************/

  /**
   * @brief 
   */
  void
  loadTextureFromFile(const String filepath);

  /**
   * @brief 
   */
  FORCEINLINE unsigned char *
  getTextureInfo() {
    return m_textureInfo[0];
  }

  /**
   * @brief 
   */
  FORCEINLINE int32
  getWidth() {
    return m_Width;
  }

  /**
   * @brief 
   */
  FORCEINLINE int32
  getHeight() {
    return m_Height;
  }

  /**
   * @brief 
   */
  FORCEINLINE int32
  getChanels() { 
    return m_Channels;
  }

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
 protected:

 Vector<unsigned char*> m_textureInfo;
 int32 m_Width;
 int32 m_Height;
 int32 m_Channels;

 public:
   
 };
}