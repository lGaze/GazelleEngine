/**************************************************************************/
/* @filename gzDXTexture.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#pragma once

#include "gzDXPrerequisites.h"
#include  <gzTexture.h>

namespace gzEngineSDK {
class DXTexture : public Texture
{
 public:
   
  /**
   * @brief default constructor
   */
  DXTexture();
	
  /**
   * @brief default destructor
   */
  ~DXTexture() = default;
	
  /************************************************************************/
  /* Texture functions                                                    */
  /************************************************************************/
  
  /**
   * @brief Creates a Directx Descriptor of a Core 2D Texture Descriptor
   */
  void 
  create2DTextueDescriptor( TEXTURE2D_DESCRIPTOR &desc );

  /**
   * @brief Gets the Texture Interface
   */
  FORCEINLINE ID3D11Texture2D**
  gzGetTextureInterface()
  {
    return &m_ptex;
  };

  /**
   * @brief Gets the texture Descriptor
   */
  FORCEINLINE D3D11_TEXTURE2D_DESC  
  gzGetTextureDesc()
  {
    return m_desc;
  };

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:

   /**
    * @brief Texture Interface
    */
   ID3D11Texture2D* m_ptex;

   /**
    * @brief Texture Description
    */
   D3D11_TEXTURE2D_DESC m_desc;
 
};
}