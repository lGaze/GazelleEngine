
/**************************************************************************/
/* @filename gzBaseApp.cpp
/* @author Victor Flores 
/* @date 2019/03/02
/* @brief 
/**************************************************************************/

#include "gzBaseApp.h"
#include "gzSceneManager.h"
#include "gzResourceManager.h"
#include "gzRenderer.h"
#include "gzCameraManager.h"
#include <gzTime.h>

namespace gzEngineSDK {

  int32
  BaseApp::runMainLoop()
  {
    m_mainLoop = true;

    if (!initApp())
    {
      std::cout << "Init App Failed" << std::endl;
    }

    while (m_mainLoop)
    {

      m_pwindow->messageHandler();

      //Update
      update();

      //Render
      render();

      g_Time().update();
    }

    return 0;
  }

  bool
  BaseApp::initApp()
  {
    SceneManager::startUp();
    ResourceManager::startUp();
    CameraManager::startUp();
    Time::startUp();

    m_pwindow = new Window();
    if (!m_pwindow->initWindow(m_windowWidth,
                               m_windowHeight,
                               m_windowName,
                               m_windowPosX,
                               m_windowPosY))
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

    if (!loadLibrary("gzPBRRendererd.dll", "CreateManagerObject"))
    {
      std::cout << "Failed to load the library " << std::endl;
      return false;
    }

    return true;
  }

  void
  BaseApp::render()
  {
    Renderer::instance().render();
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

    m_library = (createLibrary)GetProcAddress(hCGDll,
                                              funcName.c_str());

    if (!m_library)
    {
      std::cout << "Could not locate the function" << std::endl;
      return false;
    }

    hCGDll = LoadLibraryEx( libraryName.c_str(),
                            nullptr,
                            0 );

    m_library = (createLibrary)GetProcAddress(hCGDll,
                                              funcName.c_str());
    m_library();
    return true;
  }

  BaseApp&
  g_baseApp()
  {
    return BaseApp::instance();
  }
}

