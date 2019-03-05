/**************************************************************************/
/* @filename gzDXGraphicsManager.cpp
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#include "gzDXGraphicsManager.h"
#include "gzDXDevice.h"
#include "gzDXDeviceContext.h"
#include "gzDXSwapChain.h"
#include "gzDXRenderTarget.h"
#include "gzDXTexture.h"

namespace gzEngineSDK {

  DXGraphicsManager::DXGraphicsManager()
  {
    m_pdevice = new Device();
    m_pdeviceContext = new DeviceContext();
    m_pswapChain = new SwapChain();
    m_prenderTarget = new RenderTarget();
  }

  bool
  DXGraphicsManager::InitGraphicsManager( void* hWnd, 
                                          int32 width,
                                          int32 height )
  {
    bool restult = true;

    //Create SwapChain description
    m_pswapChain->CreateSwapChainDesc( width, height, hWnd );

    //Create the Device, Swapchain and DEvice Context
    restult = m_pdevice->CreateDeviceAndSwapChain(
      m_pswapChain->getCurrentSCD(),
      m_pswapChain->getSwapChainInterface(),
      m_pdeviceContext->getDeviceContextInterface() );
   

    return restult;
  }

  bool 
  DXGraphicsManager::CreateRenderTargetView()
  {
    bool result = true;
    Texture * renderTargetTex = new Texture();
    m_pswapChain->getBuffer( 0,
                             __uuidof( ID3D11Texture2D ),
                             ( LPVOID* ) renderTargetTex->GetTextureInterface());

    result = m_pdevice->CreateRenderTargetView(
      *renderTargetTex->GetTextureInterface(),
      nullptr,
      m_prenderTarget->getRenderTargetInterface());

    return result;
  }

  bool DXGraphicsManager::CreateTexture2D( uint32 width,
                                           uint32 height,
                                           uint32 format,
                                           uint32 usage )
  {
    bool result = true;

    m_ptexture = new Texture();
    m_ptexture->CreateTextureDesc( width,
                                   height,
                                   format,
                                   usage );

    result = m_pdevice->CreateTexture2D( &m_ptexture->GetTextureDesc(),
                                         nullptr,
                                         m_ptexture->GetTextureInterface() );

    return result;
  }

  bool
  DXGraphicsManager::CreateDepthStencilView()
  {
   
  }

}