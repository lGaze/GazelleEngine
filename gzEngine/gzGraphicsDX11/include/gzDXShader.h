/**************************************************************************/
/* @filename gzDXShader.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/
#pragma once

#include "gzDXPrerequisites.h"
#include <gzShader.h>

//TODO: Arreglr las deprecated
namespace gzEngineSDK {
class DXShader : public Shader
{
 public:
   
  /**
   * @brief default constructor
   */
  DXShader();
	
  /**
   * @brief default destructor
   */
  ~DXShader() = default;
	
  /************************************************************************/
  /* Shader functions                                                     */
  /************************************************************************/
	
  /**
   * @brief 
   */
  bool
  CompileShaderFromFile( const WString & szFileName,
                         const String & szEntryPoint,
                         const String & szShaderModel,
                         ID3DBlob ** m_pBlob);

  /**
   * @brief 
   */
  bool
  LoadTexture( ID3D11Device* pDevice,
               LPCWSTR pSrcFile,
               HRESULT* pHResult );

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
	
 public:
  

  /**
   * @brief 
   */
  ID3D11ShaderResourceView* m_pTextureRV;



 };
}
