/**************************************************************************/
/* @filename gzDXShader.cpp
/* @author Victor Flores 
/* @date 2019/03/05
/* @brief 
/**************************************************************************/

#include "gzDXShader.h"

namespace gzEngineSDK {

  DXShader::DXShader() { }

  bool
    DXShader::CompileShaderFromFile( const WString & szFileName,
                                     const String & szEntryPoint,
                                     const String & szShaderModel,
                                     ID3DBlob ** m_pBlob)
  {
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )

    dwShaderFlags |= D3DCOMPILE_DEBUG;

#endif

    ID3DBlob* pErrorBlob;
    hr = D3DCompileFromFile( szFileName.c_str(),
                             nullptr,
                             D3D_COMPILE_STANDARD_FILE_INCLUDE, 
                             szEntryPoint.c_str(), 
                             szShaderModel.c_str(),
                             dwShaderFlags, 
                             0, 
                             m_pBlob,
                             &pErrorBlob);
    if ( FAILED( hr ) )
    {
      if ( pErrorBlob != nullptr )
      {

        MessageBoxA( nullptr,
                     static_cast< char* > ( pErrorBlob->GetBufferPointer() ),
                     "Shader Compiler Error",
                     MB_OK );
      }
      if ( pErrorBlob ) pErrorBlob->Release();
      return false;
    }
    if ( pErrorBlob ) pErrorBlob->Release();

    return true;
  }

}