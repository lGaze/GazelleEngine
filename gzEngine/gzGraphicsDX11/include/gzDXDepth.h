/**************************************************************************/
/* @filename gzDXDepth.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/
#pragma once

#include "gzDXPrerequisites.h"
#include <gzDepth.h>

namespace gzEngineSDK {
class DXDepth : public Depth
{
 public:
   
  /**
   * @brief default constructor
   */
  DXDepth();
	
  /**
   * @brief default destructor
   */
  ~DXDepth() = default;
	
  /************************************************************************/
  /* Depth functions                                                      */
  /************************************************************************/

  /**
   * @brief Creates the description for DepthStencilView
   */
  void
  CreateDepthStencilViewDesc( DEPTH_STENCIL_VIEW_DESCRIPTOR &descDepth );

  /**
   * @brief Gets the texture of the DepthStencil
   */
  FORCEINLINE ID3D11Texture2D**
  getDepthStencilTexture() {
    return &m_pDepthStencil;
  }

  /**
   * @brief Gets the DepthStencilView Interface
   */
  FORCEINLINE ID3D11DepthStencilView**
  getDepthStencilViewInterface() {
    return &m_pDepthStencilView;
  }

  /**
   * @brief Gets the description of the DepthStencilView
   */
  FORCEINLINE D3D11_DEPTH_STENCIL_VIEW_DESC
  getDepthStencilViewDesc() {
    return m_DescDSV;
  }


  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
	
 private:

  /**
   * @brief 
   */
  ID3D11Texture2D* m_pDepthStencil;

  /**
   * @brief 
   */
  ID3D11DepthStencilView* m_pDepthStencilView;

  /**
   * @brief
   */
  D3D11_DEPTH_STENCIL_VIEW_DESC m_DescDSV;
   
 };
}
