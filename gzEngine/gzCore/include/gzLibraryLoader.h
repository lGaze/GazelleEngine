/**************************************************************************/
/* @filename gzLibraryLoader.h
/* @author Victor Flores 
/* @date 2019/08/07
/* @brief 
/**************************************************************************/
#pragma once
#include "gzPrerequisitesCore.h"

namespace gzEngineSDK {
class GZ_CORE_EXPORT LibraryLoader
{
 public:
   
  /**
   * @brief default constructor
   */
  LibraryLoader() = default;

  /**
   * @brief default destructor
   */
  ~LibraryLoader() = default;

  /************************************************************************/
  /* LibraryLoader functions                                              */
  /************************************************************************/

  /**
   * @brief Fuction that loads the given library 
   */
  bool
  loadLibrary(String libraryName, String funcName);

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:
   
 };
}
