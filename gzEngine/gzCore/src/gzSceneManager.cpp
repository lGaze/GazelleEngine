/**************************************************************************/
/* @filename gzSceneManager.cpp
/* @author Victor Flores 
/* @date 2019/08/03
/**************************************************************************/
#include "gzSceneManager.h"
#include "gzPrerequisitesCore.h"
#include "gzScene.h"
#include "gzGameObject.h"

namespace gzEngineSDK {

  SceneManager::SceneManager() : m_activeScene(nullptr){}

  void 
  SceneManager::setActiveScene()
  {

  }

  Scene * 
  SceneManager::getActiveScene()
  {
    return m_activeScene;
  }

  void 
  SceneManager::createScene()
  {
    Scene * newScene = new Scene();
    m_scenes.push_back(newScene);
  }

  GameObject &
  SceneManager::createEmptyGameObject()
  {
    GameObject * newGameObject = new GameObject();
    return *newGameObject;
  }

  void
  SceneManager::addGameObjectToScene(GameObject & gameObject)
  {
    m_activeScene->addGameObject(gameObject);
  }
}