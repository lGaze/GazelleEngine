/**************************************************************************/
/* @filename gzComponent.h
/* @author Victor Flores 
/* @date 2019/07/13
/* @brief Component class for the GameObjects
/**************************************************************************/

#pragma once

#include "gzPrerequisitesCore.h"

namespace gzEngineSDK {

  namespace COMPONENT_TYPE
  {
    enum E
    {
      kMeshComponent = 0,
    };
  }

  class GZ_CORE_EXPORT Component
  {
   public:

    /**
     * @brief default constructor
     */
    Component() = default;

    /**
     * @brief default destructor
     */
    ~Component() = default;


    /************************************************************************/
    /* Component functions                                                  */
    /************************************************************************/

   public:

/*
    / **
     * @brief Function that updates the components
     * /
    virtual void
    update() = 0;*/

    /**
     * @brief 
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
