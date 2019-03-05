/**************************************************************************/
/* @filename gzDXVertexShader.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/
#pragma once

#include "gzDXPrerequisites.h"

namespace gzEngineSDK {
class VertexShader
{
 public:
   
  /**
   * @brief default constructor
   */
  VertexShader();
	
  /**
   * @brief default destructor
   */
  ~VertexShader() = default;
	
  /************************************************************************/
  /* VertexShader functions                                               */
  /************************************************************************/
	
  /**
	 * @brief Gets the VertexShader interface
	 */
  FORCEINLINE ID3D11VertexShader**
  getVertexShaderInterface() {
    return &m_pVertexShader;
  }



  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
	
 private:

  /**
   * @brief VertexShader Interface
   */
  ID3D11VertexShader * m_pVertexShader;

 public:

   /**
    * @brief 
    */
   ID3DBlob * m_pVSBlob;
 };
}
