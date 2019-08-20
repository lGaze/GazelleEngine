/**************************************************************************/
/* @filename gzComponent.h
/* @author Victor Flores 
/* @date 2019/07/13
/* @brief Component class for the GameObjects
/**************************************************************************/

#pragma once

#include "gzPrerequisitesCore.h"
#include "gzResourceHandle.h"

namespace gzEngineSDK {

  namespace COMPONENT_TYPE
  {
    enum GZ_CORE_EXPORT E
    {
      kMeshComponent = 0,
    };
  }

  class GZ_CORE_EXPORT Component
  {
   public:

    /**
     * @brief Default Constructor
     */
    Component() = default;

    /**
     * @brief Default Destructor
     */
    virtual
    ~Component() = default;


    /************************************************************************/
    /* Component functions                                                  */
    /************************************************************************/

   public:

    /**
     * @brief Function that updates the components
     */
    virtual void
    update(){};

    /**
     * @brief Gets the type of the component
     * @return Componet type
     */
    COMPONENT_TYPE::E
    getComponentType();

    /************************************************************************/
    /* Member declarations                                                  */
    /************************************************************************/

   private:

    COMPONENT_TYPE::E m_type;

 };
}
