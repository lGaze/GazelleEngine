/**************************************************************************/
/* @filename gzBaseApp.cpp
/* @author Victor Flores 
/* @date 2019/03/02
/* @brief 
/**************************************************************************/

#include "gzBaseApp.h"
#include "gzModel.h"
#include "gzTexture.h"


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

    //Creates the DepthStencil View
    m_pDepthStencilView =
      GraphicsManager::instance().createTexture2D( depthTextureDesc );


    //Creates the Viewport Descriptor
    vp.Width = static_cast< float >( m_windowWidth );
    vp.Height = static_cast< float >( m_windowHeight );
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0; 


    //Compile and create the vertex shader for light
    m_pLightVertexShader = GraphicsManager::instance().CreateVertexShader( 
      L"Shaders\\Phong.fx",
      "VS",
      "vs_4_0" );


    //Create the InputLayout with the blob
    inputLayout = GraphicsManager::instance().createInputLayout(
      m_pLightVertexShader);


    //Compile and Create the pixel shader for light
    m_pLightPixelShader = GraphicsManager::instance().createPixelShader(
      L"Shaders\\Phong.fx",
      "PS",
      "ps_4_0" );

        //Create the constant buffers desc
    BUFFER_DESCRIPTOR bufferDesc;
    memset( &bufferDesc, 0, sizeof( bufferDesc ) );
    bufferDesc.Usage = USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof( cbMatrix );
    bufferDesc.BindFlags = BIND_CONSTANT_BUFFER;
    bufferDesc.CPUAccessFlags = 0;

    //Create Constant buffer
    constantMatrix =
      GraphicsManager::instance().createBuffer( bufferDesc, nullptr );


    //Quad Aligned
    //quad->Load( "Meshes\\QuadPerron.obj" );
/*
    GraphicsManager::instance().createVertexAndIndexBufferFromMesh( 
      quad->getMeshData(), quad->getNumMeshes());*/

    //Cube
    // Model->loadModel( "Meshes\\claireredfieldout.obj" );
    m_model = new Model();
    m_model->Load( "Meshes\\sponza.obj" );
/*
    GraphicsManager::instance().createVertexAndIndexBufferFromMesh( 
      Model->getMeshData(), Model->getNumMeshes());*/

    //Create RasterizerState desc
    RASTERIZER_DESCRIPTOR rasterizerDesc;
    memset( &rasterizerDesc, 0, sizeof( rasterizerDesc ) );
    rasterizerDesc.CullMode = CULL_NONE;
    rasterizerDesc.FillMode = FILL_SOLID;

    //Create RasterizerState
    m_RasterizerState = 
      GraphicsManager::instance().createRasterizerState(rasterizerDesc);

    //Sets primitive topology
    GraphicsManager::instance().setPrimitiveTopology( 4 );
   



    SAMPLER_DESCRIPTOR sampDesc;
    memset( &sampDesc, 0 ,sizeof( sampDesc ) );
    sampDesc.Filter = FILTER_MIN_MAG_MIP_POINT;
    sampDesc.AddressU = TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressY = TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = 3.402823466e+38f;
    
    m_pSampler = GraphicsManager::instance().createSamplerState( sampDesc );

   //Initialize the matrices
    g_World.identity();

    //initialize the view matrix
    Eye = Vector3f( 0.0f, 0.0f, -175.0f);
    Vector3f At = Vector3f( 0.0f, 1.0f, 0.0f);
    Vector3f Up = Vector3f( 0.0f, 1.0f, 0.0f );
    g_View = g_View.matrixLookAtLH( Eye, At, Up );
    g_View.transpose();

    cbMatrixbuffer.view = g_View;

    //initialize the prijection matrix
    g_Projection = g_Projection.matrixPerspectiveFovLH(  
      0.785398163f,
      static_cast< float >(m_windowWidth) / static_cast<float>(m_windowHeight),
      3.0f,
      1000.0f );
    g_Projection.transpose();
   
    cbMatrixbuffer.projection = g_Projection;
    GraphicsManager::instance().updateSubresource( constantMatrix,
                                                   &cbMatrixbuffer );

    return result;

  }

  void 
  BaseApp::render()
  {

  /*  MESH_DATA * dwarf = Model->getMeshData();*/

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
    g_World.matrixRotationY( t );


    //Clear back buffer
    float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //Gris
    GraphicsManager::instance().clearRenderTargetView( ClearColor, 
                                                       m_pBackBufferTex);


    //Clear depth Stencil
    GraphicsManager::instance().clearDepthStencilView( CLEAR_DEPTH, 
                                                       1.0f, 
                                                       0, 
                                                       m_pDepthStencilView );

    g_World.transpose();
    cbMatrixbuffer.world = g_World;
    cbMatrixbuffer.ViewPosition = Vector4f( Eye.x, Eye.y, Eye.z, 1.0f );
   
    GraphicsManager::instance().updateSubresource( constantMatrix,
                                                   &cbMatrixbuffer );


    /************************************************************************/
    /* Light                                                                */
    /************************************************************************/

  
    GraphicsManager::instance().setRenderTargets( 1, m_pBackBufferTex,
                                                  m_pDepthStencilView );
    //Sets the Viewport
    GraphicsManager::instance().setViewports( 1, vp );

    uint32 Stride = sizeof( VERTEX );
    uint32 offset = 0;

/*

    for (int32 i = 0; i< Model->getNumMeshes(); i++)
    {
      GraphicsManager::instance().setVertexBuffers(
        0,
        1,
        reinterpret_cast< Buffer* >( dwarf[i].VertexBuffer ),
        &Stride,
        &offset );

      GraphicsManager::instance().setIndexBuffer( 
        FORMAT_R16_UINT,
        reinterpret_cast<Buffer*>( dwarf[i].IndexBuffer ),
        0 );
      GraphicsManager::instance().setRasterizerState( m_RasterizerState );
      GraphicsManager::instance().setInputLayout( inputLayout );
      GraphicsManager::instance().setVertexShader( m_pLightVertexShader );
      GraphicsManager::instance().setVSConstantBuffers( constantMatrix, 0, 1 );
      GraphicsManager::instance().setPixelShader( m_pLightPixelShader );
      GraphicsManager::instance().setShaderResources( Model->MeshTextures[i], 0, 1 );
      GraphicsManager::instance().setSamplerState( 0, m_pSampler, 1 );

      GraphicsManager::instance().drawIndexed( dwarf[i].IndexData.size(),
                                               0,
                                               0 );
    }*/

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

