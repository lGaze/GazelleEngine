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

  SceneManager::SceneManager() 
  {
    m_activeScene = nullptr;
  }

  void 
  SceneManager::setActiveScene()
  {
    m_activeScene = m_scenes[0];
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

  GameObject *
  SceneManager::createEmptyGameObject()
  {
    GameObject * newGameObject = new GameObject();
    return newGameObject;
  }

  void
  SceneManager::addGameObjectToScene(GameObject * gameObject)
  {
    m_activeScene->addGameObject(gameObject);
  }

  void 
  SceneManager::update()
  {
    m_activeScene->update();
  }

  bool
  SceneManager::isActiveSceneEmpty()
  {
    return m_activeScene->isRootEmpty();
  }


  Vector<GameObject*>
  SceneManager::getRendereableGameObjects()
  {
    return m_activeScene->getRendereableGameObjects();
  }

  String
  SceneManager::getActiveSceneName()
  {
    return m_activeScene->m_name.c_str();
  }

}