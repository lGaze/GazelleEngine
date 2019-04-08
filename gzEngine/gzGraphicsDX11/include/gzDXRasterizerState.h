/**************************************************************************/
/* @filename gzDXRasterizerState.h
/* @author Victor Flores 
/* @date 2019/04/08
/* @brief 
/**************************************************************************/

#pragma once

#include "gzDXPrerequisites.h"
#include <gzRasterizerState.h>

namespace gzEngineSDK {
class DXRasterizerState : public RasterizerState
{
 public:
   
  /**
   * @brief default constructor
   */
   DXRasterizerState();
	
  /**
   * @brief default destructor
   */
  ~ DXRasterizerState() = default;
	
  /************************************************************************/
  /*  DXRasterizerState functions                                         */
  /************************************************************************/
	
  /**
   * @brief 
   */
  void
  createRasterizerStateDesc(RASTERIZER_DESCRIPTOR rasterizerDesc );

  /**
   * @brief 
   */
  FORCEINLINE ID3D11RasterizerState **
  getRasterizerStateInterface() {
    return &pRasterizerState;
  }

  /**
   * @brief 
   */
  FORCEINLINE D3D11_RASTERIZER_DESC
  getRasterizerStateDesc(){
    return m_rasterizerDesc;
  }

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
	
private:

  /**
   * @brief 
   */
  D3D11_RASTERIZER_DESC m_rasterizerDesc;

  /**
   * @brief 
   */
  ID3D11RasterizerState *pRasterizerState;
   
 };
}
