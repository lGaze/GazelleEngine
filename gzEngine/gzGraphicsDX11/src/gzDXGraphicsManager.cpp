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
    m_prenderTarget(new RenderTarget()),
    m_pviewPort(new ViewPort()),
    m_pshader(new Shader()) { }


  bool
  DXGraphicsManager::InitGraphicsManager( void* hWnd, 
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
    return m_pdevice->CreateSamplerState( &m_psamplerState->getSamplerDesc(),
                                            m_psamplerState->getSamplerInterface() );
  }

  void 
  DXGraphicsManager::SetRenderTargets( uint32 NumViews )
  {
    m_pdeviceContext->SetRenderTargets( NumViews,
                                        m_prenderTarget->getRenderTargetInterface(),
                                        *m_pdepth->getDepthStencilViewInterface());
  }

  void
  DXGraphicsManager::SetViewports( uint32 NumViewports )
  {
    m_pdeviceContext->SetViewports( NumViewports,
                                    &m_pviewPort->getVewPortInterface() );
  }

  void 
  DXGraphicsManager::SetInputLayout()
  {
    m_pdeviceContext->SetInputLayout( *m_pinputLayout->getInputLayputInterface() );
  }

  void 
  DXGraphicsManager::SetVertexBuffers( uint32 StartSlot, 
                                       uint32 NumBuffers,
                                       const uint32 *pStrides, 
                                       const uint32 *pOffsets )
  {
    m_pdeviceContext->SetVertexBuffers( StartSlot,
                                        NumBuffers,
                                        m_pvertexBuffer->getBufferInterface(),
                                        pStrides,
                                        pOffsets );
  }

  void 
  DXGraphicsManager::SetIndexBuffer( DXGI_FORMAT Format, uint32 Offset )
  {
    m_pdeviceContext->SetIndexBuffer( *m_pindexBuffer->getBufferInterface(),
                                      Format,
                                      Offset );
  }

  void 
  DXGraphicsManager::SetPrimitiveTopology( uint32 Topology )
  {
    m_pdeviceContext->SetPrimitiveTopology( Topology );
  }

  void 
  DXGraphicsManager::UpdateSubresource( uint32 BufferIndex,
                                             uint32 DstSubresource,
                                             const D3D11_BOX *pDstBox,
                                             const void *pSrcData,
                                             uint32 SrcRowPitch, 
                                             uint32 SrcDepthPitch )
  {
    m_pdeviceContext->UpdateSubresource(
      *m_constantBuffers[BufferIndex]->getBufferInterface(),
      DstSubresource,
      pDstBox,
      pSrcData,
      SrcRowPitch,
      SrcDepthPitch );
  }

  void 
  DXGraphicsManager::ClearRenderTargetView( const float ColorRGBA[4] )
  {
    m_pdeviceContext->ClearRenderTargetView( 
      *m_prenderTarget->getRenderTargetInterface(),
       ColorRGBA );
  }

  void 
  DXGraphicsManager::ClearDepthStencilView( uint32 ClearFlags, float Depth, uint8 Stencil )
  {
    m_pdeviceContext->ClearDepthStencilView( *m_pdepth->getDepthStencilViewInterface(),
                                             ClearFlags,
                                             Depth,
                                             Stencil );
  }

  void 
  DXGraphicsManager::SetVertexShader( ID3D11ClassInstance *const *ppClassInstances,
                                      uint32 NumClassInstances )
  {
    m_pdeviceContext->SetVertexShader( *m_pvertexShader->getVertexShaderInterface(),
                                       ppClassInstances,
                                       NumClassInstances );

  }

  void 
  DXGraphicsManager::SetVSConstantBuffers( uint32 BufferIndex,
                                           uint32 StartSlot,
                                           uint32 NumBuffers )
  {
    m_pdeviceContext->SetVSConstantBuffers(
      StartSlot,
      NumBuffers,
      m_constantBuffers[BufferIndex]->getBufferInterface() );
  }

  void 
  DXGraphicsManager::SetPixelShader( ID3D11ClassInstance *const *ppClassInstances, uint32 NumClassInstances )
  {
    m_pdeviceContext->SetPixelShader( *m_ppixelShader->getPixelShaderInterface(),
                                      ppClassInstances,
                                      NumClassInstances );
  }

  void 
  DXGraphicsManager::SetPSConstantBuffers( uint32 BufferIndex, uint32 StartSlot, uint32 NumBuffers )
  {
    m_pdeviceContext->SetPSConstantBuffers(
      StartSlot,
      NumBuffers,
      m_constantBuffers[BufferIndex]->getBufferInterface());
  }

 
  void
  DXGraphicsManager::SetShaderResources( uint32 StartSlot, uint32 NumViews )
  {
    m_pdeviceContext->SetShaderResources( StartSlot,
                                          NumViews,
                                          &m_pshader->m_pTextureRV );
  }

  void
  DXGraphicsManager::SetSamplers( uint32 StartSlot, uint32 NumSamplers )
  {
    m_pdeviceContext->SetSamplers( StartSlot,
                                   NumSamplers,
                                   m_psamplerState->getSamplerInterface() );
  }

  void 
  DXGraphicsManager::DrawIndexed( uint32 indexCount,
                                       uint32 StartIndexLocation,
                                       int32 BaseVertexLocation )
  {
    m_pdeviceContext->DrawIndexed( indexCount,
                                   StartIndexLocation,
                                   BaseVertexLocation );
  }

  bool DXGraphicsManager::GetBuffer( uint32 Buffer )
  {
    return m_pswapChain->getBuffer( Buffer,
                                   __uuidof( ID3D11Texture2D ),
                                   ( LPVOID* ) m_ptexture->GetTextureInterface());
  }

  bool DXGraphicsManager::Present( uint32 SyncInterval, uint32 Flags )
  {
    return m_pswapChain->Present( SyncInterval, Flags );
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
    return m_pdevice->CreateVertexshader( m_pvertexShader->m_pVSBlob->GetBufferPointer(),
                                            m_pvertexShader->m_pVSBlob->GetBufferSize(),
                                            nullptr,
                                            m_pvertexShader->getVertexShaderInterface() );
  }

  bool 
  DXGraphicsManager::CreateInputLayout()
  {
    m_pinputLayout = new InputLayout();
    return m_pdevice->CreateInputLayout( &m_pinputLayout->m_vLayout[0],
                                           m_pinputLayout->m_vLayout.size(),
                                           m_pvertexShader->m_pVSBlob->GetBufferPointer(),
                                           m_pvertexShader->m_pVSBlob->GetBufferSize(),
                                           m_pinputLayout->getInputLayputInterface() );
  }

  bool 
  DXGraphicsManager::CreatePixelShader()
  {
    return m_pdevice->CreatePixelShader( m_ppixelShader->m_pPSBlob->GetBufferPointer(),
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
      bool result = m_pdevice->CreateBuffer(
        &m_pvertexBuffer->getBufferDesc(),
        pInitialData,
        m_pvertexBuffer->getBufferInterface() );
      return result;
    }

    if ( bufferType == 2 )
    {
      m_pindexBuffer = tempBuffer;
      return m_pdevice->CreateBuffer(
        &m_pindexBuffer->getBufferDesc(),
        pInitialData,
        m_pindexBuffer->getBufferInterface() );
    }

    if ( bufferType == 4 )
    {
      m_pdevice->CreateBuffer(
        &tempBuffer->getBufferDesc(),
        pInitialData,
        tempBuffer->getBufferInterface() );
      m_constantBuffers.push_back( tempBuffer );
    }
  }

}