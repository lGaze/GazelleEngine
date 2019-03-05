/**************************************************************************/
/* @filename gzDXShader.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/
#pragma once

#include "gzDXPrerequisites.h"

//TODO: Arreglr las deprecated
namespace gzEngineSDK {
class Shader
{
 public:
   
  /**
   * @brief default constructor
   */
  Shader();
	
  /**
   * @brief default destructor
   */
  ~Shader() = default;
	
  /************************************************************************/
  /* Shader functions                                                     */
  /************************************************************************/
	
  /**
   * @brief 
   */
  bool
  CompileShaderFromFile( LPCSTR  szFileName,
                         LPCSTR szEntryPoint,
                         LPCSTR szShaderModel,
                         ID3DBlob** ppBlobOut );

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
