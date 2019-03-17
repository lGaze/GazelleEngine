/**************************************************************************/
/* @filename gzTexture.h
/* @author Victor Flores 
/* @date 2019/03/16
/* @brief 
/**************************************************************************/

#pragma once

#include "gzPrerequisitesCore.h"

namespace gzEngineSDK {
//TODO: hacer un structures y enums
struct TEXTURE2D_DESCRIPTOR
{
  uint32 Width;
  uint32 Height;
  uint32 MipLevels;
  uint32 ArraySize;
  uint32 Format;
  //DXGI_SAMPLE_DESC SampleDesc;
  uint32 Usage;
  uint32 BindFlags;
  uint32 CPUAccessFlags;
uint32 MiscFlags;
};

class GZ_CORE_EXPORT Texture
{
 public:
   
  /**
   * @brief default constructor
   */
  Texture() = default;
	
  /**
   * @brief default destructor
   */
  virtual
  ~Texture() = default;
	 
  /************************************************************************/
  /* Texture functions                                                    */
  /************************************************************************/
	
  /**
   * @brief This function creates a new Texture
   */
  virtual
  bool createTexture2D( TEXTURE2D_DESCRIPTOR texInfo ) = 0;

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
	
 public:
   
 };
}