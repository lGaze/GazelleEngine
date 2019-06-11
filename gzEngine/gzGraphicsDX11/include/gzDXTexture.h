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
  getShaderResourceViewInterface()
  {
    return &m_pShaderResourceView;
  }

  /**
   * @brief 
   */
  FORCEINLINE ID3D11DepthStencilView**
  getDepthStencilViewInterface()
  {
    return &m_pDepthStencilView;
  }

  /**
   * @brief 
   */
  FORCEINLINE ID3D11RenderTargetView**
  getRenderTargetViewInterface()
  {
    return &m_pRenderTargetView;
  }

  /**
   * @brief 
   */
  FORCEINLINE D3D11_SUBRESOURCE_DATA *
  getInitData()
  {
    return &m_initBuffer;
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
    * @brief Shader Resource View interface
    */
   ID3D11ShaderResourceView*  m_pShaderResourceView;

   /**
    * @brief Depth Stencil View
    */
   ID3D11DepthStencilView* m_pDepthStencilView;

   /**
    * @brief Render Target View
    */
   ID3D11RenderTargetView * m_pRenderTargetView;

   /**
    * @brief 
    */
   D3D11_SUBRESOURCE_DATA m_initBuffer;
};
}