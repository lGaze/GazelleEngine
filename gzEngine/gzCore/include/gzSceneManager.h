/**************************************************************************/
/* @filename gzSceneManager.h
/* @author Victor Flores 
/* @date 2019/08/03
/* @brief Scene Manager header file
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
  SceneManager() = default;

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
   */
  Scene
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
   */
  GameObject
  createEmptyGameObject();

  /**
   * @brief Adds a Scene to the active scene
   */
  void
  addGameObjectToScene();

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:

   Vector<Scene *> m_scenes;
   Scene * m_activeScene;
   
 };
}
