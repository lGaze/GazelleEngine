/**************************************************************************/
/* @filename gzBaseApp.cpp
/* @author Victor Flores 
/* @date 2019/03/02
/* @brief 
/**************************************************************************/

#include "gzBaseApp.h"
#include "gzMesh.h"


namespace gzEngineSDK {

  BaseApp::BaseApp(uint32 windowWidth, 
                   uint32 windowHeight, 
                   String windowName,
                   uint32 posX,
                   uint32 posY) : 
    m_windowWidth(windowWidth),
    m_windowHeight(windowHeight),
    m_windowName(windowName),
    m_windowPosX(posX),
    m_windowPosY(posY) { }

  int32
  BaseApp::runMainLoop()
  {
    m_mainLoop = true;

    if ( !initApp() )
    {
      std::cout << "Init App Failed" << std::endl;
    }

    while(m_mainLoop)
    {

      m_pwindow->messageHandler();

      //Update
      update();

      //Render
      render();
    }

    return 0;
  }

  bool 
  BaseApp::initApp()
  {
    m_pwindow = new Window();
    if (!m_pwindow->initWindow( m_windowWidth, 
                                m_windowHeight, 
                                m_windowName,
                                m_windowPosX,
                                m_windowPosY ))
    {
      std::cout << "Init Window failed" << std::endl;
      return false;
    }

    if (!loadLibrary("gzGraphicsDX11d.dll", "CreateManagerObject"))
    {
      std::cout << "Failed to load the library " << std::endl;
      return false;
    }

    if (!postInit())
    {
      std::cout << "Failed to Initialize" << std::endl;
      return false;
    }

    return true;
  }

  bool 
  BaseApp::postInit()
  {
    bool result = true;

    //Creates the Device, Context and SwapChain
    result = GraphicsManager::instance().initGraphicsManager(
      static_cast< void* >( m_pwindow->getHWND() ), 
      m_windowWidth, 
      m_windowHeight );


    //Creates the Backbuffer texture
    m_pBackBufferTex =
      GraphicsManager::instance().createTextureFromBackBuffer();

    //Creates the render target 
    m_pBackBuffer = 
      GraphicsManager::instance().createRenderTarget(m_pBackBufferTex);


    //Albedo Texture
    TEXTURE2D_DESCRIPTOR renderTexDesc;
    memset( &renderTexDesc, 0, sizeof( renderTexDesc ) );
    renderTexDesc.Height = m_windowHeight;
    renderTexDesc.Width = m_windowWidth;
    renderTexDesc.MipLevels = 4;
    renderTexDesc.ArraySize = 1;
    renderTexDesc.Format = FORMAT_R16G16B16A16_FLOAT;
    renderTexDesc.Usage = USAGE_DEFAULT;
    renderTexDesc.BindFlags = BIND_RENDER_TARGET | BIND_SHADER_RESOURCE;
    renderTexDesc.CPUAccessFlags = 0;
    renderTexDesc.MiscFlags = 0;

    m_pAlbedoTexture =
      GraphicsManager::instance().createTexture2D( renderTexDesc );

    //AlbedoRT
    m_pAlbedoRT = GraphicsManager::instance().createRenderTarget( m_pAlbedoTexture );


    //Luminance Texture
    m_pLuminanceTexture = 
      GraphicsManager::instance().createTexture2D( renderTexDesc );

    //LuminanceRT
    m_pLuminanceRT = 
      GraphicsManager::instance().createRenderTarget( m_pLuminanceTexture );
   

    //Creates the Depth descriptor
    TEXTURE2D_DESCRIPTOR depthTextureDesc;
    depthTextureDesc.Width = m_windowWidth;
    depthTextureDesc.Height = m_windowHeight;
    depthTextureDesc.MipLevels = 1;
    depthTextureDesc.ArraySize = 1;
    depthTextureDesc.Format = FORMAT_D24_UNORM_S8_UINT;
    depthTextureDesc.Usage = USAGE_DEFAULT;
    depthTextureDesc.BindFlags = BIND_DEPTH_STENCIL;
    depthTextureDesc.CPUAccessFlags = 0;
    depthTextureDesc.MiscFlags = 0;

    //Creates the Depth Stencil descriptor
    DEPTH_STENCIL_VIEW_DESCRIPTOR desc;
    desc.Format = FORMAT_D24_UNORM_S8_UINT;
    desc.ViewDimension = DSV_DIMENSION_TEXTURE2D;

    //Creates the DepthStencil View
    m_pDepthStencilView =
      GraphicsManager::instance().createDepthStencilView( desc, 
                                                          depthTextureDesc );


    //Creates the Viewport Descriptor
    VIEWPORT_DESCRIPTOR vp;
    vp.Width = static_cast< float >( m_windowWidth );
    vp.Height = static_cast< float >( m_windowHeight );
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;

    //Sets the Viewport
    GraphicsManager::instance().setViewports( 1, vp );

    //Compile and create the vertex shader
    m_pLightVertexShader = GraphicsManager::instance().CreateVertexShader( 
      L"Shaders\\Phong.fx",
      "VS",
      "vs_4_0" );


    //Create the InputLayout with the blob
    InputLayout * inputLayout;
    inputLayout = GraphicsManager::instance().createInputLayout(
      m_pLightVertexShader);

    //Set the InputLayout
    GraphicsManager::instance().setInputLayout( inputLayout );

    //Compile and Create the pixel shader
    m_pLightPixelShader = GraphicsManager::instance().createPixelShader(
      L"Shaders\\Phong.fx",
      "PS",
      "ps_4_0" );




    //Quad Aligned
    quad = new Mesh();
    quad->loadModel( "Meshes\\QuadPerron.obj" );
    GraphicsManager::instance().createAndsetVertexAndIndexBufferFromMesh(
      quad->getNumVertices(),
      quad->getVertexData(),
      quad->getNumIndices(),
      quad->getIndexData() );

    //cube
    cube = new Mesh();
    cube->loadModel( "Meshes\\TestBox.obj" );
    GraphicsManager::instance().createAndsetVertexAndIndexBufferFromMesh(
      cube->getNumVertices(),
      cube->getVertexData(),
      cube->getNumIndices(),
      cube->getIndexData() );

    //Sets primitive topology
    GraphicsManager::instance().setPrimitiveTopology( 4 );
   
    //Create the constant buffers desc
    BUFFER_DESCRIPTOR bufferDesc;
    memset( &bufferDesc, 0, sizeof( bufferDesc ) );
    bufferDesc.Usage = USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof( CBNeverChanges );
    bufferDesc.BindFlags = BIND_CONSTANT_BUFFER;
    bufferDesc.CPUAccessFlags = 0;

    //Create Constant buffer
    constantNeverChanges = 
      GraphicsManager::instance().createBuffer( bufferDesc, nullptr );

    bufferDesc.ByteWidth = sizeof( CBChangeOnResize );
    constantChangesonResize =
     GraphicsManager::instance().createBuffer( bufferDesc, nullptr );

    bufferDesc.ByteWidth = sizeof( CBChangesEveryFrame );
    constantChangesEveryFrame =
      GraphicsManager::instance().createBuffer( bufferDesc, nullptr );

    SHADER_RESOURCE_VIEW_DESC bd;
    memset( &bd, 0, sizeof( bd ) );

    //Load and create shader resource view
    textGorda = GraphicsManager::instance().CreateShaderResourceViewFromFile(
      "Textures\\texturagorda.jpg",
       bd );


    SAMPLER_DESCRIPTOR sampDesc;
    memset( &sampDesc, 0 ,sizeof( sampDesc ) );
    sampDesc.Filter = FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressY = TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = 3.402823466e+38f;
    
    m_pSampler = GraphicsManager::instance().createSamplerState( sampDesc );

   //Initialize the matrices
    g_World = DirectX::XMMatrixIdentity();

    //initialize the view matrix
    Eye = DirectX::XMVectorSet( 0.0f, 3.0f, -10.0f, 0.0f );
    DirectX::XMVECTOR At = DirectX::XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    DirectX::XMVECTOR Up = DirectX::XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    g_View = DirectX::XMMatrixLookAtLH( Eye, At, Up );

    CBNeverChanges cbNeverChanges;
    cbNeverChanges.mView = DirectX::XMMatrixTranspose( g_View );
    GraphicsManager::instance().updateSubresource( constantNeverChanges, 
                                                   &cbNeverChanges );

    //initialize the prijection matrix
    g_Projection = DirectX::XMMatrixPerspectiveFovLH( 
      0.785398163f,
      m_windowWidth / ( FLOAT ) m_windowHeight,
      0.001f,
      500.0f );

    CBChangeOnResize cbChangesonResize;
   
    cbChangesonResize.mProjection = DirectX::XMMatrixTranspose( g_Projection );
    GraphicsManager::instance().updateSubresource( constantChangesonResize,
                                                   &cbChangesonResize );

    return result;

  }

  void 
  BaseApp::render()
  {


    //Update our time
    float t = 0.0f;
    static DWORD dwTimeStart = 0;
    DWORD dwTimerCur = GetTickCount();
    if ( dwTimeStart == 0 )
    {
      dwTimeStart = dwTimerCur;
    }
    t = ( dwTimerCur - dwTimeStart ) / 1000.0f;


    //rotate mesh 
   // g_World = DirectX::XMMatrixRotationY( t );



   

    //Clear back buffer
    float ClearColor2[4] = { 0.0f, 0.0f, 1.0f, 0.0f }; //Azul
    float ClearColor[4] = { 1.0f, 0.0f, 1.0f, 1.0f }; //Rosa
    float ClearColor3[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; //Rojo
    GraphicsManager::instance().clearRenderTargetView( ClearColor, 
                                                       m_pBackBuffer);

    GraphicsManager::instance().clearRenderTargetView( ClearColor2, 
                                                       m_pAlbedoRT );    

    GraphicsManager::instance().clearRenderTargetView( ClearColor3, 
                                                       m_pLuminanceRT );

    

    //Clear depth Stencil
    GraphicsManager::instance().clearDepthStencilView( CLEAR_DEPTH, 
                                                       1.0f, 
                                                       0, 
                                                       m_pDepthStencilView );

    CBChangesEveryFrame cb;
    cb.mWorld = DirectX::XMMatrixTranspose( g_World );
    cb.vMeshColor = { 0.7f, 0.7f, 0.7f, 1.0f };
    cb.ViewPosition = DirectX::XMFLOAT4( Eye.m128_f32 );
    GraphicsManager::instance().updateSubresource( constantChangesEveryFrame,
                                                   &cb );

    


    //Main pass

    GraphicsManager::instance().setVertexShader( m_pLightVertexShader );
    GraphicsManager::instance().setVSConstantBuffers( constantNeverChanges, 0, 1 );
    GraphicsManager::instance().setVSConstantBuffers( constantChangesonResize, 1, 1 );
    GraphicsManager::instance().setVSConstantBuffers( constantChangesEveryFrame, 2, 1 );
    GraphicsManager::instance().setPixelShader( m_pLightPixelShader );
    GraphicsManager::instance().setPSConstantBuffers( constantChangesEveryFrame, 2, 1 );
    GraphicsManager::instance().setShaderResources( textGorda, 0, 1 );
    GraphicsManager::instance().setSamplerState( 0, m_pSampler, 1 );

    GraphicsManager::instance().setRenderTargets( 1, m_pAlbedoRT,
                                                  m_pDepthStencilView );

    GraphicsManager::instance().drawIndexed( quad->getNumIndices(), 0, 0 );
    

    GraphicsManager::instance().setRenderTargets( 0, m_pLuminanceRT, 
                                                  m_pDepthStencilView );

    GraphicsManager::instance().setShaderResources( m_pAlbedoTexture, 0, 1 );

    GraphicsManager::instance().drawIndexed( quad->getNumIndices(), 0, 0 );


   
    GraphicsManager::instance().present( 0, 0 );
  }

  void 
  BaseApp::update()
  {
    //Update
  }

  bool 
  BaseApp::loadLibrary( String libraryName, String funcName )
  {
    HINSTANCE hCGDll = LoadLibraryEx( libraryName.c_str(),
                                      nullptr,
                                      LOAD_WITH_ALTERED_SEARCH_PATH );

    if (!hCGDll)
    {
      std::cout << "Could not load the dynamic" << "" << std::endl;
      return false;
    }

    m_graphicsFunc = (createGraphicsManager)GetProcAddress(hCGDll,
                                                           funcName.c_str());

    if (!m_graphicsFunc)
    {
      std::cout << "Could not locate the function" << std::endl;
      return false;
    }

    hCGDll = LoadLibraryEx( libraryName.c_str(),
                            nullptr,
                            0 );

    m_graphicsFunc = (createGraphicsManager)GetProcAddress(hCGDll,
                                                           funcName.c_str());
    m_graphicsFunc();
    return true;                                                     
  }

  BaseApp&
  g_baseApp()
  {
    return BaseApp::instance();
  }
}

