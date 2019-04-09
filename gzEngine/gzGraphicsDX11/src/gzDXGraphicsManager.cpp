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
#include "gzDXRasterizerState.h"



namespace gzEngineSDK {

  DXGraphicsManager::DXGraphicsManager() :
    m_pdevice( new Device() ),
    m_pdeviceContext( new DeviceContext() ),
    m_pswapChain( new SwapChain() ),
    m_prenderTarget( new DXRenderTarget() ),
    m_pviewPort( new DXViewPort() ),
    m_pShader( new DXShader() )
  {
  }


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
    D3D11_TEXTURE2D_DESC texDesc = m_ptexture->getTextureDesc();
    m_pdevice->CreateTexture2D( &texDesc,
                                nullptr,
                                m_ptexture->getTextureInterface() );

    return reinterpret_cast< Texture* >( m_ptexture );
  }

  void
    DXGraphicsManager::setRenderTargets( uint32 NumViews,
                                         RenderTarget * renderTargets,
                                         Depth * depth )
  {

    m_pdepth = reinterpret_cast< DXDepth* >( depth );
    m_prenderTarget = reinterpret_cast< DXRenderTarget* > ( renderTargets );

    if ( m_pdepth == nullptr )
    {
      m_pdeviceContext->SetRenderTargets(
        NumViews,
        m_prenderTarget->getRenderTargetInterface(),
        nullptr );
    }
    else
    {
      m_pdeviceContext->SetRenderTargets(
        NumViews,
        m_prenderTarget->getRenderTargetInterface(),
        *m_pdepth->getDepthStencilViewInterface() );
    }


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
    m_ptexture = reinterpret_cast < DXTexture * > ( texture );
    m_prenderTarget = new DXRenderTarget();

    m_pdevice->CreateRenderTargetView(
      *m_ptexture->getTextureInterface(),
      nullptr,
      m_prenderTarget->getRenderTargetInterface() );

    return reinterpret_cast< RenderTarget* > ( m_prenderTarget );

  }

  bool
    DXGraphicsManager::present( uint32 SyncInterval, uint32 Flags )
  {
    return m_pswapChain->Present( SyncInterval, Flags );
  }

  Depth*
    DXGraphicsManager::createDepthStencilView( DEPTH_STENCIL_VIEW_DESCRIPTOR &desc,
                                               TEXTURE2D_DESCRIPTOR &texDesc )
  {
    m_ptexture = new DXTexture();
    m_pdepth = new DXDepth();
    m_ptexture->create2DTextueDescriptor( texDesc );

    D3D11_TEXTURE2D_DESC temptexDesc = m_ptexture->getTextureDesc();
    m_pdevice->CreateTexture2D( &temptexDesc,
                                nullptr,
                                m_ptexture->getTextureInterface() );

    m_pdepth->CreateDepthStencilViewDesc( desc );

    D3D11_DEPTH_STENCIL_VIEW_DESC tempDepthDesc =
      m_pdepth->getDepthStencilViewDesc();
    m_pdevice->CreateDepthStencilView( *m_ptexture->getTextureInterface(),
                                       &tempDepthDesc,
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
    D3D11_VIEWPORT tempViewPortDesc = m_pviewPort->getVewPortDesc();
    m_pdeviceContext->SetViewports( NumViewports,
                                    &tempViewPortDesc );
  }

  Buffer*
    DXGraphicsManager::createBuffer( BUFFER_DESCRIPTOR &bufferDesc,
                                     const SUBRESOUCE_DATA * pInitialData )
  {

    m_pBuffer = new DXBuffer();
    m_pBuffer->CreateBufferDesc( bufferDesc );

    D3D11_BUFFER_DESC tempBufferDesc = m_pBuffer->getBufferDesc();

    m_pdevice->CreateBuffer(
      &tempBufferDesc,
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
    D3D11_SAMPLER_DESC tempSamplerDesc = m_psamplerState->getSamplerDesc();
    m_pdevice->CreateSamplerState( &tempSamplerDesc,
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
      m_pvertexShader->getVertexShaderInterface() );

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

  InputLayout*
    DXGraphicsManager::createInputLayout( VertexShader * vertexShader )
  {
    m_pinputLayout = new DXInputLayout();
    m_pvertexShader = reinterpret_cast< DXVertexShader* >( vertexShader );

    m_pinputLayout->CreateInputLayout( m_pvertexShader->m_pVSBlob );

    m_pdevice->CreateInputLayout(
      m_pinputLayout->getInputLayoutDesc(),
      m_pinputLayout->getnumElem(),
      m_pvertexShader->m_pVSBlob->GetBufferPointer(),
      m_pvertexShader->m_pVSBlob->GetBufferSize(),
      m_pinputLayout->getInputLayputInterface() );

    return reinterpret_cast < InputLayout* >( m_pinputLayout );
  }

  void
    DXGraphicsManager::setInputLayout( InputLayout * inputLayout )
  {
    m_pinputLayout = reinterpret_cast< DXInputLayout* >( inputLayout );
    m_pdeviceContext->SetInputLayout(
      *m_pinputLayout->getInputLayputInterface() );
  }

  void
    DXGraphicsManager::setPrimitiveTopology( uint32 Topology )
  {
    D3D_PRIMITIVE_TOPOLOGY topology =
      static_cast< D3D_PRIMITIVE_TOPOLOGY >( Topology );

    m_pdeviceContext->SetPrimitiveTopology( topology );
  }

  void
    DXGraphicsManager::setVSConstantBuffers( Buffer * buffer,
                                             uint32 StartSlot,
                                             uint32 NumBuffers )
  {
    m_pBuffer = reinterpret_cast< DXBuffer* >( buffer );

    m_pdeviceContext->SetVSConstantBuffers( StartSlot,
                                            NumBuffers,
                                            m_pBuffer->getBufferInterface() );
  }

  void
    DXGraphicsManager::setPSConstantBuffers( Buffer * buffer,
                                             uint32 StartSlot,
                                             uint32 NumBuffers )
  {
    m_pBuffer = reinterpret_cast< DXBuffer* >( buffer );

    m_pdeviceContext->SetPSConstantBuffers( StartSlot,
                                            NumBuffers,
                                            m_pBuffer->getBufferInterface() );
  }

  void
    DXGraphicsManager::drawIndexed( uint32 indexCount,
                                    uint32 StartIndexLocation,
                                    int32 BaseVertexLocation )
  {
    m_pdeviceContext->DrawIndexed( indexCount,
                                   StartIndexLocation,
                                   BaseVertexLocation );
  }

  void
    DXGraphicsManager::updateSubresource( Buffer * buffer, const void *pSrcData )
  {
    m_pBuffer = reinterpret_cast< DXBuffer* > ( buffer );

    m_pdeviceContext->UpdateSubresource( *m_pBuffer->getBufferInterface(),
                                         0,
                                         nullptr,
                                         pSrcData,
                                         0,
                                         0 );
  }

  Texture *
    DXGraphicsManager::LoadTextureFromFile( const String filename )
  {
    m_ptexture = new DXTexture();
    m_ptexture->LoadTexture( filename );

    D3D11_TEXTURE2D_DESC tempTexDesc = m_ptexture->getTextureDesc();
    m_pdevice->CreateTexture2D( &tempTexDesc,
                                m_ptexture->getInitData(),
                                m_ptexture->getTextureInterface() );

    return reinterpret_cast< Texture* >( m_ptexture );
  }

  void
    DXGraphicsManager::setShaderResources( Texture*texture,
                                           uint32 StartSlot,
                                           uint32 NumViews )
  {
    m_ptexture = reinterpret_cast< DXTexture* >( texture );

    m_pdeviceContext->SetShaderResources(
      StartSlot,
      NumViews,
      m_ptexture->getShaderResourceInterface() );
  }

  Texture *
    DXGraphicsManager::CreateShaderResourceViewFromFile(
      const String filenme )
  {
    m_ptexture = new DXTexture();
    m_ptexture->LoadTexture( filenme );

    D3D11_TEXTURE2D_DESC tempTextureDesc = m_ptexture->getTextureDesc();
    m_pdevice->CreateTexture2D( &tempTextureDesc,
                                m_ptexture->getInitData(),
                                m_ptexture->getTextureInterface() );

    m_pdevice->CreateShaderResourceView(
      *m_ptexture->getTextureInterface(),
      m_ptexture->getShaderResourceInterface() );

    return reinterpret_cast< Texture* >( m_ptexture );

  }

  Texture *
    DXGraphicsManager::CreateShaderResourceView( Texture * texture  )
  {
    m_ptexture = reinterpret_cast< DXTexture* >( texture );

    m_pdevice->CreateShaderResourceView(
      *m_ptexture->getTextureInterface(),
      m_ptexture->getShaderResourceInterface() );

    return reinterpret_cast< Texture* >( m_ptexture );
  }

  Texture *
    DXGraphicsManager::createTextureFromBackBuffer()
  {
    m_ptexture = new DXTexture();
    m_pswapChain->getBuffer(
      0,
      __uuidof( ID3D11Texture2D ),
      ( LPVOID* ) m_ptexture->getTextureInterface() );

    return reinterpret_cast< Texture* >( m_ptexture );
  }


  void
    DXGraphicsManager::createAndsetVertexAndIndexBufferFromMesh(
      uint32 Numvetices,
      VERTICES * vertexData,
      uint32 NumIndices,
      uint16 * indexData,
      Buffer ** Vbuffer,
      Buffer ** Ibuffer )
  {

    DXBuffer * tempVBuffer = new DXBuffer();
    DXBuffer * tempIBuffer = new DXBuffer();

    //Desc Vertex Buffer
    BUFFER_DESCRIPTOR BufferDesc;
    memset( &BufferDesc, 0, sizeof( BufferDesc ) );
    BufferDesc.Usage = USAGE_DEFAULT;
    BufferDesc.ByteWidth = Numvetices * sizeof( VERTICES );
    BufferDesc.BindFlags = BIND_VERTEX_BUFFER;

    tempVBuffer->CreateBufferDesc( BufferDesc );

    //Init Data Vertex
    SUBRESOUCE_DATA initData;
    memset( &initData, 0, sizeof( initData ) );
    initData.pSysMem = vertexData;

    D3D11_BUFFER_DESC tempVBufferDesc = tempVBuffer->getBufferDesc();
    //Create Vertex Buffer
    m_pdevice->CreateBuffer(
      &tempVBufferDesc,
      reinterpret_cast< D3D11_SUBRESOURCE_DATA* >( &initData ),
      tempVBuffer->getBufferInterface() );


    //Desc Index Buffer
    BufferDesc.Usage = USAGE_DEFAULT;
    BufferDesc.ByteWidth = NumIndices * sizeof( unsigned short );
    BufferDesc.BindFlags = BIND_INDEX_BUFFER;


    tempIBuffer->CreateBufferDesc( BufferDesc );

    //Init Data index
    initData.pSysMem = indexData;

    D3D11_BUFFER_DESC tempIBufferDesc = tempIBuffer->getBufferDesc();
    //Creates index buffer
    m_pdevice->CreateBuffer(
      &tempIBufferDesc,
      reinterpret_cast< D3D11_SUBRESOURCE_DATA* >( &initData ),
      tempIBuffer->getBufferInterface() );

    *Vbuffer = reinterpret_cast< Buffer* >( tempVBuffer );
    *Ibuffer = reinterpret_cast< Buffer* >( tempIBuffer );
  }

  RasterizerState *
    DXGraphicsManager::createRasterizerState( RASTERIZER_DESCRIPTOR desc )
  {
    m_pRasterizerState = new DXRasterizerState();

    m_pRasterizerState->createRasterizerStateDesc( desc );

    D3D11_RASTERIZER_DESC tempRasterizerDesc = 
      m_pRasterizerState->getRasterizerStateDesc();

    m_pdevice->CreateRasterizerState(
      &tempRasterizerDesc,
      m_pRasterizerState->getRasterizerStateInterface() );

    return reinterpret_cast< RasterizerState* >( m_pRasterizerState );

  }


  void
  DXGraphicsManager::setRasterizerState( RasterizerState * rasterizerState )
  {
    m_pRasterizerState = 
      reinterpret_cast< DXRasterizerState* >( rasterizerState );

    m_pdeviceContext->SetRasterizerState(
      *m_pRasterizerState->getRasterizerStateInterface() );

  }

}