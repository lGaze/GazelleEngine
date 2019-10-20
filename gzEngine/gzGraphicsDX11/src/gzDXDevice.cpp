/**************************************************************************/
/* @filename gzDXDevice.cpp
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#include "gzDXDevice.h"
#include "DDSTextureLoader.h"

namespace gzEngineSDK {

  Device::Device()
  {
    m_pDevice = nullptr;
    m_deviceFlags = 0;

#ifdef _DEBUG
    m_deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif 

    m_sdk = D3D11_SDK_VERSION;
    m_driverType = D3D_DRIVER_TYPE_NULL;
    m_featureLevel = D3D_FEATURE_LEVEL_11_0;
    m_numDriverTypes = ARRAYSIZE( m_driverTypes );
    m_numFeatureLevels = ARRAYSIZE( m_featureLevels );

  }

  bool 
  Device::CreateDeviceAndSwapChain( 
    DXGI_SWAP_CHAIN_DESC SwapChainDesc,
    IDXGISwapChain ** SwapChainInterface,
    ID3D11DeviceContext ** DeviceContextInterface )
  {
    for ( uint32 driverTypeIndex = 0; driverTypeIndex < m_numFeatureLevels; driverTypeIndex++ )
    {
      m_driverType = m_driverTypes[driverTypeIndex];
      HRESULT res = D3D11CreateDeviceAndSwapChain(
        nullptr,
        m_driverType,
        nullptr,
        m_deviceFlags,
        m_featureLevels,
        m_numFeatureLevels,
        m_sdk,
        &SwapChainDesc,
        SwapChainInterface,
        &m_pDevice,
        &m_featureLevel,
        DeviceContextInterface );

      if ( SUCCEEDED( res ) )
      {
        return true;
      }
    }
    return false;
  }

  bool 
  Device::CreateRenderTargetView( ID3D11Resource * pResource,
                                  const D3D11_RENDER_TARGET_VIEW_DESC * pDesc, 
                                  ID3D11RenderTargetView ** ppRTView )
  {
    HRESULT result = S_OK;

    result = m_pDevice->CreateRenderTargetView( pResource,
                                                pDesc,
                                                ppRTView );
    if (FAILED(result))
    {
      return false;
    }
    return true;
  }

  bool 
  Device::CreateTexture2D( const D3D11_TEXTURE2D_DESC * pDesc,
                           const D3D11_SUBRESOURCE_DATA * pInitialData,
                           ID3D11Texture2D ** ppTexture2D )
  {
    HRESULT result = S_OK;

    result = m_pDevice->CreateTexture2D( pDesc,
                                         pInitialData,
                                         ppTexture2D );
    if (FAILED(result))
    {
      return false;
    }

    return true;
  }

  bool 
  Device::CreateDepthStencilView( ID3D11Resource * pResource,
                                  const D3D11_DEPTH_STENCIL_VIEW_DESC * pDesc, 
                                  ID3D11DepthStencilView ** ppDepthStencilView )
  {
    HRESULT result = S_OK;

    result = m_pDevice->CreateDepthStencilView( pResource,
                                                pDesc,
                                                ppDepthStencilView );
    if (FAILED(result))
    {
      return false;
    }

    return true;
  }

  bool 
  Device::CreateVertexshader( const void * pShaderBytecode,
                                SIZE_T BytecodeLength, 
                                ID3D11ClassLinkage * pClassLinkage,
                                ID3D11VertexShader ** ppVertexShader )
  {
    HRESULT result = S_OK;

    result = m_pDevice->CreateVertexShader( pShaderBytecode,
                                            BytecodeLength,
                                            pClassLinkage,
                                            ppVertexShader );

    if (FAILED(result))
    {
      return false;
    }

    return true;
  }

  bool 
  Device::CreateInputLayout( const D3D11_INPUT_ELEMENT_DESC * pInputElementDescs,
                               uint32 NumElements,
                               const void * pShaderBytecodeWithInputSignature,
                               SIZE_T BytecodeLength, 
                               ID3D11InputLayout ** ppInputLayout )
  {
    HRESULT result = S_OK;

    result = m_pDevice->CreateInputLayout( pInputElementDescs,
                                           NumElements,
                                           pShaderBytecodeWithInputSignature,
                                           BytecodeLength,
                                           ppInputLayout );
    if (FAILED(result))
    {
      return false;
    }

    return true;
  }

  bool 
  Device::CreatePixelShader( const void * pShaderBytecode,
                               SIZE_T BytecodeLength, 
                               ID3D11ClassLinkage * pClassLinkage,
                               ID3D11PixelShader ** ppPixelShader )
  {
    HRESULT result = S_OK;

    result = m_pDevice->CreatePixelShader( pShaderBytecode,
                                           BytecodeLength,
                                           pClassLinkage,
                                           ppPixelShader );
    if (FAILED(result))
    {
      return false;
    }

    return true;
  }

  bool 
  Device::CreateBuffer( const D3D11_BUFFER_DESC * pDesc,
                          const D3D11_SUBRESOURCE_DATA * pInitialData,
                          ID3D11Buffer ** ppBuffer )
  {
    HRESULT result = S_OK;

    result = m_pDevice->CreateBuffer( pDesc,
                                      pInitialData,
                                      ppBuffer );
    
    if (FAILED(result))
    {
      return false;
    }
    return true;
  }

  bool 
  Device::CreateSamplerState( const D3D11_SAMPLER_DESC * pSamplerDesc,
                                ID3D11SamplerState ** ppSamplerState )
  {
    HRESULT result = S_OK;
    
    result = m_pDevice->CreateSamplerState( pSamplerDesc,
                                            ppSamplerState );

    if (FAILED(result))
    {
      return false;
    }

    return true;
  }

  bool 
  Device::CreateShaderResourceView( ID3D11Resource * pResource,
                                    const D3D11_SHADER_RESOURCE_VIEW_DESC * pDesc,
                                    ID3D11ShaderResourceView **ppSRView )
  {
    HRESULT result = S_OK;

    result = m_pDevice->CreateShaderResourceView( pResource,
                                                  pDesc,
                                                  ppSRView );
    if ( FAILED( result ) )
    {
      return false;
    }

    return true;

  }

  bool
  Device::CreateRasterizerState( D3D11_RASTERIZER_DESC * desc,
                                 ID3D11RasterizerState ** rasterizerState )
  {
    HRESULT result = S_OK;

    result = m_pDevice->CreateRasterizerState( desc, rasterizerState );

    if (FAILED (result))
    {
      return false;
    }

    return true;
  }

  bool 
  Device::CreateTextureFromDDSFile(const WCHAR * filename, 
                                   ID3D11Texture2D** pTexture)
  {
    HRESULT result = S_OK;
    ID3D11Resource** pResource = reinterpret_cast<ID3D11Resource**>(pTexture);
    result = DirectX::CreateDDSTextureFromFile(m_pDevice, 
                                               filename, 
                                               pResource, 
                                               nullptr);
    if (FAILED(result))
    {
      return false;
    }

    return true;
  }

}