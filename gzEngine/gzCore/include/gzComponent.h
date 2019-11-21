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
    virtual COMPONENT_TYPE::E
    getComponentType();

    /**
     * @brief This function returns if a component is rendereable
     */
    bool
    isRendereable() {
      return m_isRendereable;
    }

    /************************************************************************/
    /* Member declarations                                                  */
    /************************************************************************/

   private:

    COMPONENT_TYPE::E m_type;

   protected:

    bool m_isRendereable;
 };
}
