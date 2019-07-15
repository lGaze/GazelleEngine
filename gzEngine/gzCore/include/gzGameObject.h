/**************************************************************************/
/* @filename gzGameObject.h
/* @author Victor Flores 
/* @date 2019/07/13
/* @brief Class for GameObjects
/**************************************************************************/

#pragma once

#include "gzPrerequisitesCore.h"
#include "gzTransform.h"
#include "gzMeshComponent.h"

namespace gzEngineSDK {
class GZ_CORE_EXPORT GameObject
{
 public:
   
  /**
   * @brief default constructor
   */
  GameObject();

  /**
   * @brief default destructor
   */
  ~GameObject() = default;

  /************************************************************************/
  /* GameObject functions                                                 */
  /************************************************************************/

  /**
   * @brief This function adds a component to the vector of components
   */
  void
  addComponent(Component * newComponent);

  /**
   * @brief This function remove a component of the components vector
   */
  void
  removeComponent();

  /**
   * @brief 
   */
  Component &
  getComponent(COMPONENT_TYPE::E componentType);

  /**
   * @brief 
   */
  void
  createComponent(COMPONENT_TYPE::E componentType);

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 public:

 private:

  Vector<Component* > m_components;
  Transform m_transform;
  String m_objectName;
  bool m_isEneabled;
   
 };
}


