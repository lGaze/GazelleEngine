/**************************************************************************/
/* @filename gzDXRenderTarget.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#pragma once

#include "gzDXPrerequisites.h"
#include "gzDXGraphicsManager.h"
#include  <gzRenderTarget.h>

namespace gzEngineSDK {
class DXRenderTarget : public RenderTarget
{
 public:
   
  /**
   * @brief default constructor
   */
   DXRenderTarget();
	
  /**
   * @brief default destructor
   */
  ~DXRenderTarget() = default;
	
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
