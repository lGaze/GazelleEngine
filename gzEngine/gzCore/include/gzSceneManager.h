/**************************************************************************/
/* @filename gzSceneManager.h
/* @author Victor Flores 
/* @date 2019/08/03
/* @brief This file can create an manipulate Scenes
/**************************************************************************/
#pragma once
#include "gzPrerequisitesCore.h"
#include <gzModule.h>

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
  GameObject *
  createEmptyGameObject();

  /**
   * @brief Adds a Scene to the active scene
   * @param Reference to the game object that is going to be added to the active Scene 
   */
  void
  addGameObjectToScene(GameObject * gameObject);

  /**
   * @brief Function Update for the active Scene
   */
  void
  update();

  /**
   * @brief Funtion that returns true if is something in the scene to render
   */
  bool
  activeSceneEmpty();

  /**
   * @brief this function returns all the rendereable Game Objects
   */
  Vector<GameObject*>
  getRendereableGameObjects();

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:

  Vector<Scene *> m_scenes;
  Scene * m_activeScene;
 };
}
