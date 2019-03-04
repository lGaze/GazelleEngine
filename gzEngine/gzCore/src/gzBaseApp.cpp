/**************************************************************************/
/* @filename gzBaseApp.cpp
/* @author Victor Flores 
/* @date 2019/03/02
/* @brief 
/**************************************************************************/

#include "gzBaseApp.h"

namespace gzEngineSDK {

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

      window->messageHandler();

      //Update
      update();

      //Render
      render();
    }

    return 0;
  }

  bool BaseApp::initApp()
  {
    window = new Window();
    if (!window->initWindow())
    {
      std::cout << "Init Window failed" << std::endl;
      return false;
    }
    return true;
  }

  void BaseApp::render()
  {
    //Render
  }

  void BaseApp::update()
  {
    //Update
  }

  BaseApp&
  g_baseApp()
  {
    return BaseApp::instance();
  }
}

