/**************************************************************************/
/* @filename gzDXPixelShader.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/
#pragma once

#include "gzDXPrerequisites.h"

namespace gzEngineSDK {
class PixelShader
{
 public:
   
  /**
   * @brief default constructor
   */
  PixelShader();
	
  /**
   * @brief default destructor
   */
  ~PixelShader() = default;
	
  /************************************************************************/
  /* PixelShader functions                                               */
  /************************************************************************/
	
  /**
   * @brief Gets the PixelShaderInterface
   */
  FORCEINLINE ID3D11PixelShader**
  getPixelShaderInterface() {
    return &m_pPixelShader;
  }

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
