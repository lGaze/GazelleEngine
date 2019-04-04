/**************************************************************************/
/* @filename gzDXTexture.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#pragma once

#include "gzDXPrerequisites.h"
#include  <gzTexture.h>
#define STB_IMAGE_IMPLEMENTATION

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
   * @brief Creates a Shader Descriptor with a given descriptor
   */
  void
  createShaderResurceDescriptor( SHADER_RESOURCE_VIEW_DESC &desc );

  /**
   * @brief
   */
  void
  LoadTexture( const String filename );

  /**
   * @brief Gets the Texture Interface
   */
  FORCEINLINE ID3D11Texture2D**
  getTextureInterface()
  {
    return &m_ptex;
  };

  /**
   * @brief 
   */
  FORCEINLINE ID3D11ShaderResourceView**
  getShaderResourceInterface()
  {
    return &m_pTextureRV;
  }

  /**
   * @brief Gets the texture Descriptor
   */
  FORCEINLINE D3D11_TEXTURE2D_DESC  
  getTextureDesc()
  {
    return m_texDesc;
  };

  /**
   * @brief 
   */
  FORCEINLINE D3D11_SHADER_RESOURCE_VIEW_DESC
  getShaderResourceDesc()
  {
    return m_srvDesc;
  }

  /**
   * @brief 
   */
  FORCEINLINE D3D11_SUBRESOURCE_DATA *
  getInitData()
  {
    return &initBuffer;
  }

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:

   /**
    * @brief Texture Interface
    */
   ID3D11Texture2D* m_ptex;

   /**
    * @brief 
    */
   ID3D11ShaderResourceView*  m_pTextureRV;

   /**
    * @brief Texture Description
    */
   D3D11_TEXTURE2D_DESC m_texDesc;

   /**
    * @brief Sader Resource Description
    */
   D3D11_SHADER_RESOURCE_VIEW_DESC m_srvDesc;

   /**
    * @brief Init data of the texture
    */
   D3D11_SUBRESOURCE_DATA initBuffer;
   
};
}