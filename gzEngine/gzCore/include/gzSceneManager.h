/**************************************************************************/
/* @filename gzSceneManager.h
/* @author Victor Flores 
/* @date 2019/08/03
/* @brief This file can create an manipulate Scenes
/**************************************************************************/
#pragma once
#include "gzPrerequisitesCore.h"
#include <gzModule.h>
#include "gzScene.h"
#include "gzResourceHandle.h"

namespace gzEngineSDK {
class GZ_CORE_EXPORT SceneManager : public Module<SceneManager>
{
 public:
   
  /**
   * @brief default constructor
   */
  SceneManager();

  /**
   * @brief default destructor
   */
  ~SceneManager() = default;

  /************************************************************************/
  /* SceneManager functions                                               */
  /************************************************************************/

  /**
   * @brief Sets the active scene
   */
  void
  setActiveScene();

  /**
   * @brief Gets the active Scene
   * @return pointer to the Active Scene
   */
  Scene *
  getActiveScene();

  /**
   * @brief Load the given scene
   */
  void
  loadScene();

  /**
   * @brief Creates a Scene
   */
  void
  createScene();

  /**
   * @brief Creates a empty game object
   * @paran Return a Game object 
   */
  GameObjectHandle 
  createEmptyGameObject();

  /**
   * @brief This function creates a empty Game Object with the given name
   */
  GameObjectHandle
  createEmptyGameObject(String gameObjectName);

  /**
   * @brief Adds a Scene to the active scene
   * @param Reference to the game object that is going to be added to the active Scene 
   */
  void
  addGameObjectToScene(GameObjectHandle gameObject);

  /**
   * @brief Function Update for the active Scene
   */
  void
  update();

  /**
   * @brief Funtion that returns true if is something in the scene to render
   */
  bool
  isActiveSceneEmpty();

  /**
   * @brief this function returns all the rendereable Game Objects
   */
  Vector<GameObjectHandle>
  getRendereableGameObjects();

  /**
   * @brief This function returns the children of the root node of the active Scene
   */
  Vector<GameObject*>
  getChildren();

  /**
   * @brief This function returns the name of the active scene
   */
  String
  getActiveSceneName();

  /**
   * @brief This function finds the Game Object by the name given
   */
  GameObjectHandle
  findGameObjectByName(String gamObjectName);

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:

  Vector<Scene *> m_scenes;
  Scene * m_activeScene;
  Map<String, GameObjectHandle> m_gameObjectMap;
  uint32 m_objectId;

 };
}
