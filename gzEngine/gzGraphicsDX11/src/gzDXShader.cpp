/**************************************************************************/
/* @filename gzDXShader.cpp
/* @author Victor Flores 
/* @date 2019/03/05
/* @brief 
/**************************************************************************/

#include "gzDXShader.h"

namespace gzEngineSDK {

  Shader::Shader() : m_pTextureRV(nullptr) { }

  bool
  Shader::CompileShaderFromFile( LPCSTR szFileName,
                                 LPCSTR szEntryPoint,
                                 LPCSTR szShaderModel,
                                 ID3DBlob ** ppBlobOut )
  {
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
  // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
  // Setting this flag improves the shader debugging experience, but still allows 
  // the shaders to be optimized and to run exactly the way they will run in 
  // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DX11CompileFromFile( szFileName, NULL, NULL, szEntryPoint, szShaderModel,
                                dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
    if ( FAILED( hr ) )
    {
      if ( pErrorBlob != NULL )
        OutputDebugStringA( ( char* ) pErrorBlob->GetBufferPointer() );
      if ( pErrorBlob ) pErrorBlob->Release();
      return false;
    }
    if ( pErrorBlob ) pErrorBlob->Release();

    return true;
  }


  bool 
  Shader::LoadTexture( ID3D11Device * pDevice, 
                       LPCWSTR pSrcFile, 
                       HRESULT * pHResult )
  {
    HRESULT result = S_OK;

    result = D3DX11CreateShaderResourceViewFromFileW( pDevice,
                                                      pSrcFile,
                                                      nullptr,
                                                      nullptr,
                                                      &m_pTextureRV, pHResult );
    
    if (FAILED(result))
    {
      return false;
    }
    return true;
  }
}