/**************************************************************************/
/* @filename gzMeshComponent.h
/* @author Victor Flores 
/* @date 2019/07/14
/* @brief Class for the components of Mesh type
/**************************************************************************/
#pragma once
#include "gzPrerequisitesCore.h"
#include "gzComponent.h"

namespace gzEngineSDK {
class GZ_CORE_EXPORT MeshComponent : public Component
{
 public:
   
  /**
   * @brief default constructor
   */
  MeshComponent();

  /**
   * @brief default destructor
   */
  ~MeshComponent() = default;

  /************************************************************************/
  /* MeshComponent functions                                              */
  /************************************************************************/

  /**
   * @brief Functions that returns the type of this component
   */
  COMPONENT_TYPE::E
  getComponentType();

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 public:

  Model * m_model;
  COMPONENT_TYPE::E m_type;
   
 };
}
