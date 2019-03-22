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
#include "gzDXViewPort.h"
#include "gzDXInputLayout.h"
#include "gzDXVertexShader.h"
#include "gzDXPixelShader.h"
#include "gzDXDepth.h"
#include "gzDXSamplerState.h"
#include "gzDXBuffer.h"
#include "gzDXShader.h"

namespace gzEngineSDK {

  DXGraphicsManager::DXGraphicsManager() : 
    m_pdevice(new Device()),
    m_pdeviceContext(new DeviceContext()),
    m_pswapChain(new SwapChain()),
    m_prenderTarget(new DXRenderTarget()),
    m_pviewPort(new ViewPort()),
    m_pshader(new Shader()) { }


  bool
  DXGraphicsManager::initGraphicsManager( void* hWnd, 
                                          int32 width,
                                          int32 height )
  {
    bool restult = true;

    //Create SwapChain description
    m_pswapChain->CreateSwapChainDesc( width, height, hWnd );

    //Create the Device, Swapchain and Device Context
    restult = m_pdevice->CreateDeviceAndSwapChain(
      m_pswapChain->getCurrentSCD(),
      m_pswapChain->getSwapChainInterface(),
      m_pdeviceContext->getDeviceContextInterface() );
   

    return restult;
  }

  Texture* 
  DXGraphicsManager::createTexture2D( TEXTURE2D_DESCRIPTOR textureInfo )
  {
    m_ptexture = new DXTexture();
    //Create the DX texture descriptor and the texture
    m_ptexture->create2DTextueDescriptor( textureInfo );
    m_pdevice->CreateTexture2D( &m_ptexture->gzGetTextureDesc(),
                                nullptr,
                                m_ptexture->gzGetTextureInterface() );

    return reinterpret_cast< Texture* >( m_ptexture );
  }


  RenderTarget* 
  DXGraphicsManager::creteRenderTargetFromBackBuffer()
  {
    m_prenderTarget = new DXRenderTarget();
    m_ptexture = new DXTexture();
    m_pswapChain->getBuffer( 
      0,
      __uuidof( ID3D11Texture2D ),                          
      ( LPVOID* ) m_ptexture->gzGetTextureInterface() );

    m_pdevice->CreateRenderTargetView(
      *m_ptexture->gzGetTextureInterface(),
      nullptr,
      m_prenderTarget->getRenderTargetInterface() );

    return reinterpret_cast< RenderTarget* >( m_prenderTarget );
  }


  void 
  DXGraphicsManager::setRenderTargets( uint32 NumViews, 
                                       RenderTarget * renderTarget,
                                       Depth * depth)
  {

    m_pdepth = reinterpret_cast< DXDepth* >( depth );
    m_prenderTarget = reinterpret_cast< DXRenderTarget* > ( renderTarget );

    m_pdeviceContext->SetRenderTargets(
      NumViews,
      m_prenderTarget->getRenderTargetInterface(),
      nullptr );

  }

  void 
  DXGraphicsManager::clearRenderTargetView( const float ColorRGBA[4], 
                                            RenderTarget * renderTarget )
  {
    m_prenderTarget = reinterpret_cast< DXRenderTarget* > ( renderTarget );

    m_pdeviceContext->ClearRenderTargetView(
      *m_prenderTarget->getRenderTargetInterface(),
      ColorRGBA );
  }

  RenderTarget*
  DXGraphicsManager::createRenderTarget( Texture * texture )
  {
    reinterpret_cast < DXTexture * > ( texture );

    //m_pdevice->CreateRenderTargetView()
    
    return reinterpret_cast< RenderTarget* > ( m_prenderTarget );
    
  }

  bool 
  DXGraphicsManager::present( uint32 SyncInterval, uint32 Flags )
  {
    return m_pswapChain->Present( SyncInterval, Flags );
  }

}