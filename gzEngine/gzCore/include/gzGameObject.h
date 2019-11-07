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
 
 protected:
  /**
   * @brief Default Constructor
   */
  GameObject();

  friend class SceneManager;

 public:

  /**
   * @brief Default Destructor
   */
  ~GameObject() = default;

  /************************************************************************/
  /* GameObject functions                                                 */
  /************************************************************************/

  /**
   * @brief This function adds a component to the vector of components
   * @param Pointer to the new component
   */
  void
  addComponent(Component * newComponent);

  /**
   * @brief This function remove a component of the components vector
   */
  void
  removeComponent();

  /**
   * @brief This function gets a specific component in his vector of components
   * @param The type of the wanted component
   * @return Reference to the wanted component
   */
  Component *
  getComponent(COMPONENT_TYPE::E componentType);

  /**
   * @brief This function creates a component 
   * @param Type of the component to be created
   */
  void
  createComponent(COMPONENT_TYPE::E componentType);

  /**
   * @brief Adds a children to the game object
   * @param Reference of the game object that will be added to the vector of game objects
   */
  void
  addChildren(GameObject & gameObject);

  /**
   * @brief Search the given name in the children of this game object
   * @param Name of the wanted game object
   * @return if founded returns the wanted game object
   */
  GameObject *
  findChildrenbyName(String gameObjectName);

/*
  / **
   * @brief This function searchs in the children vector for rendereable objects
   * /
  Vector<GameObject*>
  getRendereableChildrens();*/

  /**
   * @brief This function updates the game object
   */
  void
  update();

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 public:

  bool m_isEneabled; 
  Transform m_transform;
  String m_objectName;
 
private:

  Vector<Component*> m_components;
  Vector<GameObject*> m_children;
  GameObject * m_parent;
   
 };
}


