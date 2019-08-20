/**************************************************************************/
/* @filename gzDXVertexShader.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/
#pragma once

#include "gzDXPrerequisites.h"
#include <gzVertexShader.h>

namespace gzEngineSDK {
class DXVertexShader : public VertexShader
{
 public:
   
  /**
   * @brief default constructor
   */
  DXVertexShader();

  /**
   * @brief default destructor
   */
  ~DXVertexShader() = default;

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

  /**
   * @brief 
   */
  FORCEINLINE ID3DBlob **
  gzGetVSBlob() {
    return &m_pVSBlob;
  };

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
