/**************************************************************************/
/* @filename gzGameObjectHandle.h
/* @author Victor Flores 
/* @date 2019/12/04
/* @brief This class works for make hande of the Game Objects
/**************************************************************************/


#pragma once
#include "gzPrerequisitesCore.h"

namespace gzEngineSDK {
class GZ_CORE_EXPORT GameObjectHandle
{
 public:
 
  /**
   * @brief default constructor
   */
  GameObjectHandle() = default;

  /**
   * @brief default destructor
   */
  ~GameObjectHandle() = default;

  /************************************************************************/
  /* GameObjectHandle functions                                           */
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

   /**
    * @brief Overload of the operator -> to acces to the Game object functions
    */
   GameObject *
   operator ->() {
     return reinterpret_cast<GameObject*>(m_handle);
   }

 protected:

   friend class SceneManager;

   /**
    * @brief This function sets the data into the resource handle
    * @param Pointer of the resource to be handled
    */
   FORCEINLINE void
   setHandle(GameObject * object) {
     m_handle = reinterpret_cast<int64>(object);
   }

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:

   int64 m_handle;
 };
}
