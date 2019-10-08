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
  
  Scene::Scene() : m_name("NewScene")
  {
    m_root = nullptr;
  }

  void 
  Scene::addGameObject(GameObject & gameObject)
  {
    if (m_root == nullptr)
    {
      m_root = &gameObject;
    }
    else
    {
      m_root->addChildren(gameObject);
    }
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
    return m_root == nullptr;
  }

}