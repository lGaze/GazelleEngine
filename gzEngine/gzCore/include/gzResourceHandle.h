/**************************************************************************/
/* @filename gzResourceHandle.h
/* @author Victor Flores 
/* @date 2019/07/20
/* @brief 
/**************************************************************************/

#pragma once
#include "gzPrerequisitesCore.h"

namespace gzEngineSDK {

template<class T>
class GZ_CORE_EXPORT ResourceHandle
{
 public:
   
  /**
   * @brief default constructor
   */
  ResourceHandle() = default;

  /**
   * @brief default destructor
   */
  ~ResourceHandle() = default;

  /************************************************************************/
  /* ResourceHandle functions                                             */
  /************************************************************************/

 public:

  /**
   * @brief This function returns the handle
   */
  FORCEINLINE int64
  getHandle() {
    return m_handle;
  }

  /**
   * @brief This function sets the data into the resource handle
   */
  FORCEINLINE void
  setHandle(T * resource){
    m_handle = reinterpret_cast<resource>(int64);
  }

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:

  int64 m_handle;
};

}
