/**************************************************************************/
/* @filename gzResourceHandle.h
/* @author Victor Flores 
/* @date 2019/07/20
/* @brief This function works for make handle of the resources
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
   * @return Handle of the resource 
   */
  FORCEINLINE int64
  getHandle() {
    return m_handle;
  }

 protected:

  friend class ResourceManager;

  /**
   * @brief This function sets the data into the resource handle
   * @param pointer of the resource to be handled 
   */
  FORCEINLINE void
  setHandle(Resource * resource){
    m_handle = reinterpret_cast<int64>(resource);
  }

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:

  int64 m_handle;
};

}
