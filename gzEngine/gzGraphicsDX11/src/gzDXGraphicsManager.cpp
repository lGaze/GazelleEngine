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

namespace gzEngineSDK {

  DXGraphicsManager::DXGraphicsManager() : 
    m_pdevice(new Device()),
    m_pdeviceContext(new DeviceContext()),
    m_pswapChain(new SwapChain()),
    m_prenderTarget(new RenderTarget()),
    m_pviewPort(new ViewPort()) {}
    //m_pshader(new Shader()), 


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
  DXGraphicsManager::CreateVertexAndIndexBufferFromFile( std::string file )
  {
    return false;
  }

  bool 
  DXGraphicsManager::CreateSamplerState()
  {
    m_psamplerState = new SamplerState();
    m_psamplerState->CreateSamplerDesc();
    return m_pdevice->gzCreateSamplerState( &m_psamplerState->getSamplerDesc(),
                                            m_psamplerState->getSamplerInterface() );
  }

  bool
  DXGraphicsManager::CreateDepthStencilView()
  {
    m_pdepth = new Depth();

    m_pdepth->CreateDepthStencilViewDesc( m_ptexture->GetTextureDesc() );
    return m_pdevice->CreateDepthStencilView( *m_ptexture->GetTextureInterface(),
                                              &m_pdepth->getDepthStencilViewDesc(),
                                              m_pdepth->getDepthStencilViewInterface() );
  }

  bool 
  DXGraphicsManager::CreateVertexShader()
  {
    return m_pdevice->gzCreateVertexshader( m_pvertexShader->m_pVSBlob->GetBufferPointer(),
                                            m_pvertexShader->m_pVSBlob->GetBufferSize(),
                                            nullptr,
                                            m_pvertexShader->getVertexShaderInterface() );
  }

  bool 
  DXGraphicsManager::CreateInputLayout()
  {
    m_pinputLayout = new InputLayout();
    return m_pdevice->gzCreateInputLayout( &m_pinputLayout->m_vLayout[0],
                                           m_pinputLayout->m_vLayout.size(),
                                           m_pvertexShader->m_pVSBlob->GetBufferPointer(),
                                           m_pvertexShader->m_pVSBlob->GetBufferSize(),
                                           m_pinputLayout->getInputLayputInterface() );
  }

  bool 
  DXGraphicsManager::CreatePixelShader()
  {
    return m_pdevice->gzCreatePixelShader( m_ppixelShader->m_pPSBlob->GetBufferPointer(),
                                           m_ppixelShader->m_pPSBlob->GetBufferSize(),
                                           nullptr,
                                           m_ppixelShader->getPixelShaderInterface() );
  }

  bool 
    DXGraphicsManager::CreateBuffer( uint32 usage,
                                     uint32 bytewidth,
                                     uint32 bufferType,
                                     uint32 cpuflags,
                                     const D3D11_SUBRESOURCE_DATA * pInitialData )
  {
    Buffer * tempBuffer = new Buffer();
    tempBuffer->CreateBufferDesc( usage,
                                  bytewidth,
                                  bufferType,
                                  cpuflags );

    if ( bufferType == 1 )
    {
      m_pvertexBuffer = tempBuffer;
      bool result = m_pdevice->gzCreateBuffer(
        &m_pvertexBuffer->getBufferDesc(),
        pInitialData,
        m_pvertexBuffer->getBufferInterface() );
      return result;
    }

    if ( bufferType == 2 )
    {
      m_pindexBuffer = tempBuffer;
      return m_pdevice->gzCreateBuffer(
        &m_pindexBuffer->getBufferDesc(),
        pInitialData,
        m_pindexBuffer->getBufferInterface() );
    }

    if ( bufferType == 4 )
    {
      m_pdevice->gzCreateBuffer(
        &tempBuffer->getBufferDesc(),
        pInitialData,
        tempBuffer->getBufferInterface() );
      m_constantBuffers.push_back( tempBuffer );
    }
  }

}