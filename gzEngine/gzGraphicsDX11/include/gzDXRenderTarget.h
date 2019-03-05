/**************************************************************************/
/* @filename gzDXRenderTarget.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#pragma once

#include "gzDXPrerequisites.h"

namespace gzEngineSDK {
class RenderTarget
{
 public:
   
  /**
   * @brief default constructor
   */
  RenderTarget();
	
  /**
   * @brief default destructor
   */
  ~RenderTarget() = default;
	
  /************************************************************************/
  /* RenderTarget functions                                               */
  /************************************************************************/
	
  /**
   * @brief Gets the RenderTarget interface
   */
  FORCEINLINE ID3D11RenderTargetView**
  getRenderTargetInterface() {
    return &m_prenderTargetView;
  }

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
	
 private:

  /**
   * @brief RenderTarget Interface
   */
  ID3D11RenderTargetView * m_prenderTargetView;
   
};
}
