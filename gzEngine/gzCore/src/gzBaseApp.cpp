/**************************************************************************/
/* @filename gzBaseApp.cpp
/* @author Victor Flores 
/* @date 2019/03/02
/* @brief 
/**************************************************************************/

#include "gzBaseApp.h"

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

    //Creates the Render Target
    m_pBackBuffer = GraphicsManager::instance().creteRenderTargetFromBackBuffer();

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

    //Sets the Render Target
    GraphicsManager::instance().setRenderTargets( 1,
                                                  m_pBackBuffer,
                                                  m_pDepthStencilView );

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
    m_pVertexShader = GraphicsManager::instance().CreateVertexShader( 
      L"Shaders\\Tutorial07.fx",
      "VS",
      "vs_4_0" );


    //Create the InputLayout with the blob
    InputLayout * inputLayout;
    inputLayout = GraphicsManager::instance().createInputLayout(
      m_pVertexShader);

    //Set the InputLayout
    GraphicsManager::instance().setInputLayout( inputLayout );

    //Compile and Create the pixel shader
    m_pPixelShader = GraphicsManager::instance().createPixelShader(
      L"Shaders\\Phong.fx",
      "PS",
      "ps_4_0" );


    // Create vertex buffer
    SimpleVertex vertices[] =
    {
        { XVECTOR3( -1.0f, 1.0f, -1.0f ), XVECTOR3( 0.0f, 1.0f, 0.0f ) },
        { XVECTOR3( 1.0f, 1.0f, -1.0f ),  XVECTOR3( 0.0f, 1.0f, 0.0f ) },
        { XVECTOR3( 1.0f, 1.0f, 1.0f ),   XVECTOR3( 0.0f, 1.0f, 0.0f ) },
        { XVECTOR3( -1.0f, 1.0f, 1.0f ),  XVECTOR3( 0.0f, 1.0f, 0.0f ) },

        { XVECTOR3( -1.0f, -1.0f, -1.0f ), XVECTOR3( 0.0f, -1.0f, 0.0f ) },
        { XVECTOR3( 1.0f, -1.0f, -1.0f ),  XVECTOR3( 0.0f, -1.0f, 0.0f ) },
        { XVECTOR3( 1.0f, -1.0f, 1.0f ),   XVECTOR3( 0.0f, -1.0f, 0.0f ) },
        { XVECTOR3( -1.0f, -1.0f, 1.0f ),  XVECTOR3( 0.0f, -1.0f, 0.0f ) },

        { XVECTOR3( -1.0f, -1.0f, 1.0f ),  XVECTOR3( -1.0f, 0.0f, 0.0f ) },
        { XVECTOR3( -1.0f, -1.0f, -1.0f ), XVECTOR3( -1.0f, 0.0f, 0.0f ) },
        { XVECTOR3( -1.0f, 1.0f, -1.0f ),  XVECTOR3( -1.0f, 0.0f, 0.0f ) },
        { XVECTOR3( -1.0f, 1.0f, 1.0f ),   XVECTOR3( -1.0f, 0.0f, 0.0f ) },

        { XVECTOR3( 1.0f, -1.0f, 1.0f ),  XVECTOR3( 1.0f, 0.0f, 0.0f ) },
        { XVECTOR3( 1.0f, -1.0f, -1.0f ), XVECTOR3( 1.0f, 0.0f, 0.0f ) },
        { XVECTOR3( 1.0f, 1.0f, -1.0f ),  XVECTOR3( 1.0f, 0.0f, 0.0f ) },
        { XVECTOR3( 1.0f, 1.0f, 1.0f ),   XVECTOR3( 1.0f, 0.0f, 0.0f ) },

        { XVECTOR3( -1.0f, -1.0f, -1.0f ), XVECTOR3( 0.0f, 0.0f, -1.0f ) },
        { XVECTOR3( 1.0f, -1.0f, -1.0f ),  XVECTOR3( 0.0f, 0.0f, -1.0f ) },
        { XVECTOR3( 1.0f, 1.0f, -1.0f ),   XVECTOR3( 0.0f, 0.0f, -1.0f ) },
        { XVECTOR3( -1.0f, 1.0f, -1.0f ),  XVECTOR3( 0.0f, 0.0f, -1.0f ) },

        { XVECTOR3( -1.0f, -1.0f, 1.0f ), XVECTOR3( 0.0f, 0.0f, 1.0f ) },
        { XVECTOR3( 1.0f, -1.0f, 1.0f ),  XVECTOR3( 0.0f, 0.0f, 1.0f ) },
        { XVECTOR3( 1.0f, 1.0f, 1.0f ),   XVECTOR3( 0.0f, 0.0f, 1.0f ) },
        { XVECTOR3( -1.0f, 1.0f, 1.0f ),  XVECTOR3( 0.0f, 0.0f, 1.0f ) },
    };  

    //Vertex buffer desc

    Buffer * vertexBuffer;
    SUBRESOUCE_DATA initData;
    memset( &initData, 0, sizeof( initData ) );
    BUFFER_DESCRIPTOR bufferDesc;
    memset( &bufferDesc, 0, sizeof( bufferDesc ) );
    bufferDesc.Usage = USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof( SimpleVertex ) * 24;
    bufferDesc.BindFlags = BIND_VERTEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;

    initData.pSysMem = vertices;

    vertexBuffer = GraphicsManager::instance().createBuffer( bufferDesc, 
                                                             &initData );

    //Sets the index buffer
    uint32 stride = sizeof( SimpleVertex );
    uint32 offset = 0;
    GraphicsManager::instance().setVertexBuffers( 0, 
                                                  1, 
                                                  vertexBuffer, 
                                                  &stride, 
                                                  &offset );

    //Create index buffer       
    WORD indices[] =
    {
        3,1,0,
        2,1,3,

        6,4,5,
        7,4,6,

        11,9,8,
        10,9,11,

        14,12,13,
        15,12,14,

        19,17,16,
        18,17,19,

        22,20,21,
        23,20,22
    };

    //Index buffer desc
    Buffer * indexBuffer;
    memset( &initData, 0, sizeof( initData ) );
    memset( &bufferDesc, 0, sizeof( bufferDesc ) );
    bufferDesc.Usage = USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof( WORD ) * 36;
    bufferDesc.BindFlags = BIND_INDEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;
    initData.pSysMem = indices;
    indexBuffer = 
      GraphicsManager::instance().createBuffer( bufferDesc, &initData );

    //Sets the index buffer
    GraphicsManager::instance().setIndexBuffer( FORMAT_R16_UINT, 
                                                indexBuffer, 
                                                0 );

    //Sets primitive topology
    GraphicsManager::instance().setPrimitiveTopology( 4 );
   
    //Create the constant buffers desc
    bufferDesc.Usage = USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof( CBNeverChanges );
    bufferDesc.BindFlags = BIND_CONSTANT_BUFFER;
    bufferDesc.CPUAccessFlags = 0;

    //Create Constant buffer
    GraphicsManager::instance().createBuffer( bufferDesc, nullptr );

    bufferDesc.ByteWidth = sizeof( CBChangeOnResize );
    GraphicsManager::instance().createBuffer( bufferDesc, nullptr );

    bufferDesc.ByteWidth = sizeof( CBChangesEveryFrame );
    GraphicsManager::instance().createBuffer( bufferDesc, nullptr );

    SHADER_RESOURCE_VIEW_DESC bd;
    memset( &bd, 0, sizeof( bd ) );

    //Load and create shader resource view
    GraphicsManager::instance().CreateShaderResourceViewFromFile(
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

   


    return result;

  }

  void 
  BaseApp::render()
  {
    float ClearColor[4] = { 1.0f, 0.7f, 0.0f, 1.0f };
    GraphicsManager::instance().clearRenderTargetView( ClearColor, m_pBackBuffer);
    GraphicsManager::instance().clearDepthStencilView( CLEAR_DEPTH, 
                                                       1.0f, 
                                                       0, 
                                                       m_pDepthStencilView );

    GraphicsManager::instance().setSamplerState( 0, m_pSampler, 1 );

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

