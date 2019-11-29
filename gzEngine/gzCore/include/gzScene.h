/**************************************************************************/
/* @filename gzScene.h
/* @author Victor Flores 
/* @date 2019/08/03
/* @brief  Scene Header file
/**************************************************************************/
#pragma once
#include "gzPrerequisitesCore.h"
#include "gzGameObject.h"

namespace gzEngineSDK {
class GZ_CORE_EXPORT Scene
{
 public:
   
  /**
   * @brief default constructor
   */
  Scene();

  /**
   * @brief default destructor
   */
  ~Scene() = default;

  /************************************************************************/
  /* Scene functions                                                      */
  /************************************************************************/
  
  /**
   * @brief Adds a GameObject into the Scene
   * @param Reference to the game object
   */
  void
  addGameObject(GameObject * gameObject);

  /**
   * @brief Removes a GameObject from the scene
   */
  void
  removeGameObject();

  /**
   * @brief Gets the Scene Name
   * @return String name of the scene 
   */
  String
  getSceneName();

/*
  / **
   * @brief Gets all the objects in the scene
   * /
  Vector<GameObject*>
  getSceneGraph();*/

  /**
   * @brief Updates the scene
   */
  void
  update();

  /**
   * @brief Function that returns true if the root of the scene is nullptr
   */
  bool
  isRootEmpty();

  /**
   * @brief This Function returns all the rendereable Game Objects
   */
  Vector<GameObject*>
  getRendereableGameObjects();

  /**
   * @brief This function returns the children of the root node
   */
  FORCEINLINE
  Vector<GameObject*>
  getChildren() {
    return m_root->getChildren();
  }

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 public:

  String m_name;

 private:

  GameObject * m_root;

 };
}

