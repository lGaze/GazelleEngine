/**************************************************************************/
/* @filename gzScene.cpp
/* @author Victor Flores 
/* @date 2019/08/03
/* @brief 
/**************************************************************************/

#include "gzScene.h"
#include "gzGameObject.h"

namespace gzEngineSDK {
  
  Scene::Scene() : m_root(nullptr) {}

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
}