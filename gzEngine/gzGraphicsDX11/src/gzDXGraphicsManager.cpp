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
#include "gzDXTexture.h"
#include "gzDXViewPort.h"
#include "gzDXInputLayout.h"
#include "gzDXVertexShader.h"
#include "gzDXPixelShader.h"
#include "gzDXSamplerState.h"
#include "gzDXBuffer.h"
#include "gzDXShader.h"
#include "gzDXRasterizerState.h"



namespace gzEngineSDK {

  DXGraphicsManager::DXGraphicsManager() :
    m_pdevice( new Device() ),
    m_pdeviceContext( new DeviceContext() ),
    m_pswapChain( new SwapChain() ),
    m_pviewPort( new DXViewPort() ),
    m_pShader( new DXShader() ),
    m_pbackBuffer( new Texture() ),
    m_pdepthStencilView( new Texture() ) {}


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

    //BackBuffer
    m_pbackBuffer = createTextureFromBackBuffer();

    //Depth Stencil
    //Creates the Depth descriptor
    TEXTURE2D_DESCRIPTOR depthTextureDesc;
    depthTextureDesc.Width = width;
    depthTextureDesc.Height = height;
    depthTextureDesc.MipLevels = 1;
    depthTextureDesc.ArraySize = 1;
    depthTextureDesc.Format = FORMATS::E::FORMAT_D24_UNORM_S8_UINT;
    depthTextureDesc.Usage = USAGES::E::USAGE_DEFAULT;
    depthTextureDesc.BindFlags = BIND_FLAGS::E::BIND_DEPTH_STENCIL;
    depthTextureDesc.CPUAccessFlags = 0;
    depthTextureDesc.MiscFlags = 0;

    //Creates the DepthStencil View
    m_pdepthStencilView = createTexture2D(depthTextureDesc);

    //Creates the Viewport Descriptor
    memset(&m_viewPort, 0, sizeof(m_viewPort));
    m_viewPort.Width = static_cast<float>(width);
    m_viewPort.Height = static_cast<float>(height);
    m_viewPort.MinDepth = 0.0f;
    m_viewPort.MaxDepth = 1.0f;
    m_viewPort.TopLeftX = 0;
    m_viewPort.TopLeftY = 0;

    m_viewportDimensions = Vector2i(width, height);

    return restult;
  }

  Texture*
  DXGraphicsManager::createTexture2D( TEXTURE2D_DESCRIPTOR &textureInfo )
  {
    m_ptexture = new DXTexture();

    D3D11_TEXTURE2D_DESC tempTexDesc;
    memset( &tempTexDesc, 0, sizeof( tempTexDesc ) );
    tempTexDesc.Width = textureInfo.Width;
    tempTexDesc.Height = textureInfo.Height;
    tempTexDesc.MipLevels = textureInfo.MipLevels;
    tempTexDesc.ArraySize = textureInfo.ArraySize;
    tempTexDesc.Format = static_cast< DXGI_FORMAT >( textureInfo.Format );
    tempTexDesc.SampleDesc.Count = 1;
    tempTexDesc.SampleDesc.Quality = 0;
    tempTexDesc.Usage = static_cast< D3D11_USAGE >( textureInfo.Usage );
    tempTexDesc.BindFlags = static_cast < D3D11_BIND_FLAG > ( textureInfo.BindFlags );
    tempTexDesc.CPUAccessFlags = textureInfo.CPUAccessFlags;
    tempTexDesc.MiscFlags = textureInfo.MiscFlags;

    m_pdevice->CreateTexture2D( &tempTexDesc,
                                nullptr,
                                m_ptexture->getTextureInterface() );

    if ( tempTexDesc.BindFlags == D3D11_BIND_SHADER_RESOURCE ||
        tempTexDesc.BindFlags == 40 )
    {
/*
      D3D11_SHADER_RESOURCE_VIEW_DESC tempDesc;
      memset( &tempDesc, 0, sizeof( tempDesc ) );
      tempDesc.Format = tempTexDesc.Format;
      tempDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
*/

      m_pdevice->CreateShaderResourceView(
        *m_ptexture->getTextureInterface(),
        nullptr,
        m_ptexture->getShaderResourceViewInterface() );
    }

    if ( tempTexDesc.BindFlags == D3D11_BIND_DEPTH_STENCIL )
    {
      D3D11_DEPTH_STENCIL_VIEW_DESC tempDesc;
      memset( &tempDesc, 0, sizeof( tempDesc ) );
      tempDesc.Format = tempTexDesc.Format;
      tempDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

      m_pdevice->CreateDepthStencilView( 
        *m_ptexture->getTextureInterface(),
        &tempDesc,

        m_ptexture->getDepthStencilViewInterface() );
    }

    if ( tempTexDesc.BindFlags == D3D11_BIND_RENDER_TARGET || 
        tempTexDesc.BindFlags == 40)
    {
      D3D11_RENDER_TARGET_VIEW_DESC tempDesc;
      memset( &tempDesc, 0, sizeof( tempDesc ) );
      tempDesc.Format = tempTexDesc.Format;
      tempDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

      m_pdevice->CreateRenderTargetView(
        *m_ptexture->getTextureInterface(),
        &tempDesc,
        m_ptexture->getRenderTargetViewInterface() );
    }

    return reinterpret_cast< Texture* >( m_ptexture );
  }

  void
  DXGraphicsManager::setRenderTarget( Texture * renderTargets)
  {
    m_pdepth = reinterpret_cast<DXTexture *> (m_pdepthStencilView);
    m_prenderTarget = reinterpret_cast< DXTexture* > ( renderTargets );

    m_pdeviceContext->SetRenderTargets(
      1,
      m_prenderTarget->getRenderTargetViewInterface(),
      *m_pdepth->getDepthStencilViewInterface());

  }

  void 
  DXGraphicsManager::setRenderTargets(Vector<Texture *> renderTargets)
  {
    m_pdepth = reinterpret_cast<DXTexture *> (m_pdepthStencilView);
    Vector<ID3D11RenderTargetView *> renderTextures;
    for (auto it : renderTargets)
    {
      m_prenderTarget = reinterpret_cast<DXTexture*> (it);
      renderTextures.push_back(*m_prenderTarget->getRenderTargetViewInterface());
    }

    m_pdeviceContext->SetRenderTargets(
      renderTargets.size(),
      &renderTextures[0],
      *m_pdepth->getDepthStencilViewInterface());
    
  }

  void* 
  DXGraphicsManager::getDevice()
  {
    return m_pdevice->getDevice();
  }

  void* 
  DXGraphicsManager::getContext()
  {
    return m_pdeviceContext->getContext();
  }

  gzEngineSDK::Texture * 
  DXGraphicsManager::loadDDSTextureFromFile(const WCHAR * filename)
  {
    m_ptexture = new DXTexture();
    m_pdevice->CreateTextureFromDDSFile(filename, 
                                        m_ptexture->getTextureInterface());

    m_pdevice->CreateShaderResourceView(
      *m_ptexture->getTextureInterface(),
      nullptr,
      m_ptexture->getShaderResourceViewInterface());

    auto * ret = reinterpret_cast<Texture*>(m_ptexture);
    return ret;
  }

  void
  DXGraphicsManager::clearRenderTargetView( const float ColorRGBA[4],
                                            Texture * renderTarget )
  {
    m_prenderTarget = reinterpret_cast< DXTexture* > ( renderTarget );

    m_pdeviceContext->ClearRenderTargetView(
      *m_prenderTarget->getRenderTargetViewInterface(),
      ColorRGBA );
  }

  bool
  DXGraphicsManager::present( uint32 SyncInterval, uint32 Flags )
  {
    return m_pswapChain->Present( SyncInterval, Flags );
  }

  void
  DXGraphicsManager::clearDepthStencilView(uint32 ClearFlags,
                                           float Depthf,
                                           uint8 Stencil)
  {
    m_pdepth = reinterpret_cast< DXTexture* >( m_pdepthStencilView );
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

    if (pInitialData == nullptr)
    {
      m_pdevice->CreateBuffer(
        &tempBufferDesc,
        nullptr,
        m_pBuffer->getBufferInterface() );
    }
    else
    {
      m_pdevice->CreateBuffer(
        &tempBufferDesc,
        reinterpret_cast< const D3D11_SUBRESOURCE_DATA * >( pInitialData ),
        m_pBuffer->getBufferInterface() );
    }
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
                                         12,
                                         0 );
  }

  Texture *
  DXGraphicsManager::LoadTextureFromFile( const String filename )
  {
    auto mapfilename = m_textureMap.find(filename);

    if (mapfilename != m_textureMap.end())
    {
      return mapfilename->second;
    }
     
    m_ptexture = new DXTexture();
    m_ptexture->LoadTexture( filename );

    D3D11_TEXTURE2D_DESC tempTexDesc;
    memset( &tempTexDesc, 0, sizeof( tempTexDesc ) );
    tempTexDesc.Width = m_ptexture->getWidth();
    tempTexDesc.Height = m_ptexture->getHeight();
    tempTexDesc.MipLevels = 1;
    tempTexDesc.ArraySize = 1;
    tempTexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    tempTexDesc.SampleDesc.Count = 1;
    tempTexDesc.SampleDesc.Quality = 0;
    tempTexDesc.Usage = D3D11_USAGE_DEFAULT;
    tempTexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    tempTexDesc.CPUAccessFlags = 0;
    tempTexDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA m_initBuffer;
    memset( &m_initBuffer, 0, sizeof( m_initBuffer ) );
    m_initBuffer.pSysMem = m_ptexture->getTextureInfo();
    m_initBuffer.SysMemPitch = m_ptexture->getWidth() * 4;

    m_pdevice->CreateTexture2D( &tempTexDesc,
                                &m_initBuffer,
                                m_ptexture->getTextureInterface() );

    m_pdevice->CreateShaderResourceView(
      *m_ptexture->getTextureInterface(),
      nullptr,
      m_ptexture->getShaderResourceViewInterface() );

    auto * ret = reinterpret_cast<Texture*>(m_ptexture);
    m_textureMap.insert(std::pair < String, Texture*>(filename, ret));
    return ret;
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
      m_ptexture->getShaderResourceViewInterface() );
  }

  Texture *
  DXGraphicsManager::createTextureFromBackBuffer()
  {
    m_ptexture = new DXTexture();
    m_pswapChain->getBuffer(
      0,
      __uuidof( ID3D11Texture2D ),
      ( LPVOID* ) m_ptexture->getTextureInterface());

    m_pdevice->CreateRenderTargetView(
      (*m_ptexture->getTextureInterface()),
      nullptr,
      m_ptexture->getRenderTargetViewInterface() );

    return reinterpret_cast< Texture* >( m_ptexture );
  }


/*
  void
  DXGraphicsManager::createVertexAndIndexBufferFromMesh( 
    MESH_DATA * Mesh,
    int32 numMeshes )
  {



    //Desc Vertex Buffer
    BUFFER_DESCRIPTOR BufferDesc;

    //Init Data Vertex
    SUBRESOUCE_DATA initData;

    for (int32 i = 0; i< numMeshes; i++)
    {
          DXBuffer * tempVBuffer = new DXBuffer();
    DXBuffer * tempIBuffer = new DXBuffer();
       memset( &BufferDesc, 0, sizeof( BufferDesc ) );
       BufferDesc.Usage = USAGE_DEFAULT;
       BufferDesc.ByteWidth = Mesh[i].VertexData.size() * sizeof( VERTICES );
       BufferDesc.BindFlags = BIND_VERTEX_BUFFER;

       tempVBuffer->CreateBufferDesc( BufferDesc );

       memset( &initData, 0, sizeof( initData ) );
       initData.pSysMem = &Mesh[i].VertexData[0];

       D3D11_BUFFER_DESC tempVBufferDesc = tempVBuffer->getBufferDesc();

       //Create Vertex Buffer
       m_pdevice->CreateBuffer(
         &tempVBufferDesc,
         reinterpret_cast< D3D11_SUBRESOURCE_DATA* >( &initData ),
         tempVBuffer->getBufferInterface() );


       //Desc Index Buffer
       BufferDesc.Usage = USAGE_DEFAULT;
       BufferDesc.ByteWidth = Mesh[i].IndexData.size() * sizeof( unsigned short );
       BufferDesc.BindFlags = BIND_INDEX_BUFFER;


       tempIBuffer->CreateBufferDesc( BufferDesc );

       //Init Data index
       initData.pSysMem = &Mesh[i].IndexData[0];

       D3D11_BUFFER_DESC tempIBufferDesc = tempIBuffer->getBufferDesc();
       //Creates index buffer
       m_pdevice->CreateBuffer(
         &tempIBufferDesc,
         reinterpret_cast< D3D11_SUBRESOURCE_DATA* >( &initData ),
         tempIBuffer->getBufferInterface() );

       Mesh[i].VertexBuffer = reinterpret_cast< Buffer* >( tempVBuffer );
       Mesh[i].IndexBuffer = reinterpret_cast< Buffer* >( tempIBuffer );
    }

  }*/

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

  Texture * 
  DXGraphicsManager::getBackBufferTex()
  {
    return m_pbackBuffer;
  }

  Texture * 
  DXGraphicsManager::getDepthStencilView()
  {
    return m_pdepthStencilView;
  }

  VIEWPORT_DESCRIPTOR 
  DXGraphicsManager::getViewport()
  {
    return m_viewPort;
  }

  Vector2i
  DXGraphicsManager::getViewportDimensions()
  {
    return m_viewportDimensions;
  }

}