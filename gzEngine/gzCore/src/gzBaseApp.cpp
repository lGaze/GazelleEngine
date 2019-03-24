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

    result = GraphicsManager::instance().initGraphicsManager(
      static_cast< void* >( m_pwindow->getHWND() ), 
      m_windowWidth, 
      m_windowHeight );

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

    DEPTH_STENCIL_VIEW_DESCRIPTOR desc;
    desc.Format = FORMAT_D24_UNORM_S8_UINT;
    desc.ViewDimension = DSV_DIMENSION_TEXTURE2D;


    m_pDepthStencilView =
      GraphicsManager::instance().createDepthStencilView( desc, 
                                                          depthTextureDesc );

    m_pBackBuffer = GraphicsManager::instance().creteRenderTargetFromBackBuffer();

    GraphicsManager::instance().setRenderTargets( 1,
                                                  m_pBackBuffer,
                                                  m_pDepthStencilView );

    VIEWPORT_DESCRIPTOR vp;
    vp.Width = static_cast< float >( m_windowWidth );
    vp.Height = static_cast< float >( m_windowHeight );
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;

    GraphicsManager::instance().setViewports( 1, vp );

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

