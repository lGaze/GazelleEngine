/**************************************************************************/
/* @filename gzDXDevice.cpp
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#include "gzDXDevice.h"

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
    for ( UINT driverTypeIndex = 0; driverTypeIndex < m_numFeatureLevels; driverTypeIndex++ )
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

}