/**************************************************************************/
/* @filename gzLibraryLoader.cpp
/* @author Victor Flores 
/* @date 2019/08/07
/* @brief 
/**************************************************************************/
#include "gzLibraryLoader.h"
#include <windows.h>

namespace gzEngineSDK {

  bool 
  LibraryLoader::loadLibrary(String libraryName, String funcName)
  {
    HINSTANCE hCGDll = LoadLibraryEx(libraryName.c_str(),
                                     nullptr,
                                     LOAD_WITH_ALTERED_SEARCH_PATH);
/*

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

    hCGDll = LoadLibraryEx(libraryName.c_str(),
                           nullptr,
                           0);

    m_graphicsFunc = (createGraphicsManager)GetProcAddress(hCGDll,
                                                           funcName.c_str());
    m_graphicsFunc();*/
    return true; 
  }

}
