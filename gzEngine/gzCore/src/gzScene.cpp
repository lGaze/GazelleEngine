/**************************************************************************/
/* @filename gzScene.cpp
/* @author Victor Flores 
/* @date 2019/08/03
/* @brief 
/**************************************************************************/

#include "gzScene.h"
#include "gzGameObject.h"
#include "gzSceneManager.h"

namespace gzEngineSDK {
  
  Scene::Scene() : m_name("New Scene")
  {
    m_root = SceneManager::instance().createEmptyGameObject(m_name);
  }

  void 
  Scene::addGameObject(GameObject * gameObject)
  {
    m_root->addChildren(gameObject);
  }

  void 
  Scene::removeGameObject()
  {
  }

  String 
  Scene::getSceneName()
  {
    return String();
  }

  void 
  Scene::update()
  {
    m_root->update();
  }

  bool 
  Scene::isRootEmpty()
  {
    return m_root->getChildren().size() < 1;
  }


  Vector<GameObject*>
  Scene::getRendereableGameObjects()
  {
    return m_root->getRendereableChildrens();
  }

}