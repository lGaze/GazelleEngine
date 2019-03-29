/**************************************************************************/
/* @filename gzDXPixelShader.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/
#pragma once

#include "gzDXPrerequisites.h"
#include <gzPixelShader.h>

namespace gzEngineSDK {
class DXPixelShader : public PixelShader
{
 public:
   
  /**
   * @brief default constructor
   */
  DXPixelShader();
	
  /**
   * @brief default destructor
   */
  ~DXPixelShader() = default;
	
  /************************************************************************/
  /* PixelShader functions                                                */
  /************************************************************************/
	
  /**
   * @brief Gets the PixelShaderInterface
   */
  FORCEINLINE ID3D11PixelShader**
  getPixelShaderInterface() {
    return &m_pPixelShader;
  }

  /**
   * @brief 
   */
  FORCEINLINE ID3DBlob ** 
  gzGetPSBlob()  {
    return &m_pPSBlob;
  };

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
	
 private:

  /**
   * @brief Pixel Shader interface
   */
  ID3D11PixelShader * m_pPixelShader;

 public:

  /**
   * @brief
   */
  ID3DBlob* m_pPSBlob;

 };
}
