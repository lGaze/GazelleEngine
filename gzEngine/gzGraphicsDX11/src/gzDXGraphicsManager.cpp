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
    m_pviewPort(new DXViewPort()),
    m_pShader(new DXShader()) { }


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
  DXGraphicsManager::createTexture2D( TEXTURE2D_DESCRIPTOR &textureInfo )
  {
    m_ptexture = new DXTexture();
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
      *m_pdepth->getDepthStencilViewInterface() );

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

  Depth* 
  DXGraphicsManager::createDepthStencilView( DEPTH_STENCIL_VIEW_DESCRIPTOR &desc,
                                             TEXTURE2D_DESCRIPTOR &texDesc)
  {
    m_ptexture = new DXTexture();
    m_pdepth = new DXDepth();
    m_ptexture->create2DTextueDescriptor( texDesc );
    m_pdevice->CreateTexture2D( &m_ptexture->gzGetTextureDesc(),
                                nullptr,
                                m_ptexture->gzGetTextureInterface() );
     
    m_pdepth->CreateDepthStencilViewDesc( desc );
    m_pdevice->CreateDepthStencilView( *m_ptexture->gzGetTextureInterface(),
                                       &m_pdepth->getDepthStencilViewDesc(),
                                       m_pdepth->getDepthStencilViewInterface() );

    return reinterpret_cast< Depth* >( m_pdepth );

  }

  void 
  DXGraphicsManager::clearDepthStencilView( uint32 ClearFlags, 
                                            float Depthf,
                                            uint8 Stencil,
                                            Depth * depth )
  {
    m_pdepth = reinterpret_cast< DXDepth* >( depth );
    m_pdeviceContext->ClearDepthStencilView(
      *m_pdepth->getDepthStencilViewInterface(),
      ClearFlags,
      Depthf,
      Stencil );
  }

  void 
  DXGraphicsManager::setViewports( uint32 NumViewports, 
                                   VIEWPORT_DESCRIPTOR &viewportDesc )
  {
    m_pviewPort->SetViewPort( viewportDesc );
    m_pdeviceContext->SetViewports( NumViewports, 
                                    &m_pviewPort->getVewPortDesc() );
  }

  Buffer* 
  DXGraphicsManager::createBuffer( BUFFER_DESCRIPTOR &bufferDesc,
                                   const SUBRESOUCE_DATA * pInitialData )
  {
    
    m_pBuffer = new DXBuffer();
    m_pBuffer->CreateBufferDesc( bufferDesc );

    m_pdevice->CreateBuffer(
      &m_pBuffer->getBufferDesc(),
      reinterpret_cast< const D3D11_SUBRESOURCE_DATA * >( pInitialData ),
      m_pBuffer->getBufferInterface() );

    return reinterpret_cast< Buffer* >( m_pBuffer );

  }

  void 
  DXGraphicsManager::setVertexBuffers( uint32 StartSlot, 
                                       uint32 NumBuffers, 
                                       Buffer * buffer, 
                                       const uint32 *pStrides, 
                                       const uint32 *pOffsets )
  {
    m_pBuffer = reinterpret_cast< DXBuffer* >( buffer );
    m_pdeviceContext->SetVertexBuffers( StartSlot,
                                        NumBuffers,
                                        m_pBuffer->getBufferInterface(),
                                        pStrides,
                                        pOffsets );
  }

  void 
  DXGraphicsManager::setIndexBuffer( int32 Format, Buffer * buffer, uint32 Offset )
  {
    m_pBuffer = reinterpret_cast< DXBuffer* >( buffer );
    m_pdeviceContext->SetIndexBuffer( *m_pBuffer->getBufferInterface(),
                                      static_cast< DXGI_FORMAT >( Format ),
                                      Offset );
  }

  SamplerState* 
  DXGraphicsManager::createSamplerState( SAMPLER_DESCRIPTOR &samplerDesc )
  {
    m_psamplerState = new DXSamplerState();
    m_psamplerState->CreateSamplerDesc( samplerDesc );
    m_pdevice->CreateSamplerState( &m_psamplerState->getSamplerDesc(),
                                   m_psamplerState->getSamplerInterface() );

    return reinterpret_cast< SamplerState* >( m_psamplerState );

  }

  void 
  DXGraphicsManager::setSamplerState( uint32 startSlot, 
                                      SamplerState* sampler, 
                                      uint32 numSamplers )
  {
    m_psamplerState = reinterpret_cast< DXSamplerState* >( sampler );
    m_pdeviceContext->SetSamplers( startSlot,
                                   numSamplers,
                                   m_psamplerState->getSamplerInterface() );
  }

  VertexShader* 
  DXGraphicsManager::CreateVertexShader( const WString & fileName, 
                                         const String & EntryPoint,
                                         const String & ShaderModel )
  {
    m_pvertexShader = new DXVertexShader();
    m_pShader->CompileShaderFromFile( fileName, 
                                      EntryPoint, 
                                      ShaderModel, 
                                      m_pvertexShader->gzGetVSBlob() );
    
    m_pdevice->CreateVertexshader( 
      m_pvertexShader->m_pVSBlob->GetBufferPointer(),
      m_pvertexShader->m_pVSBlob->GetBufferSize(),
      nullptr,
      m_pvertexShader->getVertexShaderInterface());

    return reinterpret_cast < VertexShader* > ( m_pvertexShader );
  }

  void 
  DXGraphicsManager::setVertexShader( VertexShader * vertexShader )
  {
    m_pvertexShader = reinterpret_cast< DXVertexShader* >( vertexShader );
    m_pdeviceContext->SetVertexShader( 
      *m_pvertexShader->getVertexShaderInterface(),
      nullptr,
      0 );
  }

  PixelShader* 
  DXGraphicsManager::createPixelShader( const WString & fileName, 
                                        const String & EntryPoint, 
                                        const String & ShaderModel )
  {
    m_ppixelShader = new DXPixelShader();
    m_pShader->CompileShaderFromFile( fileName,
                                      EntryPoint, 
                                      ShaderModel,
                                      m_ppixelShader->gzGetPSBlob() );

    m_pdevice->CreatePixelShader( m_ppixelShader->m_pPSBlob->GetBufferPointer(),
                                  m_ppixelShader->m_pPSBlob->GetBufferSize(),
                                  nullptr,
                                  m_ppixelShader->getPixelShaderInterface() );

    return reinterpret_cast < PixelShader* >( m_ppixelShader );
  }

  void 
  DXGraphicsManager::setPixelShader( PixelShader * pixelShader )
  {
    m_ppixelShader = reinterpret_cast < DXPixelShader* > ( pixelShader );
    m_pdeviceContext->SetPixelShader( *m_ppixelShader->getPixelShaderInterface(),
                                      nullptr,
                                      0 );
  }

}