/**************************************************************************/
/* @filename gzGameObject.cpp
/* @author Victor Flores 
/* @date 2019/07/14
/* @brief Implementation file of the class GameObject
/**************************************************************************/

#include "gzGameObject.h"


namespace gzEngineSDK {

  GameObject::GameObject()
  {
  }

  void
  GameObject::addComponent(Component * newComponent)
  {
    m_components.push_back(newComponent);
  }

  void 
  GameObject::removeComponent()
  {
  }

  Component &
  GameObject::getComponent(COMPONENT_TYPE::E componentType)
  {
    for (auto it : m_components)
    {
      if(it->getComponentType() == componentType)
      {
        return *it;
      }
    }
  }

  void 
  GameObject::createComponent(COMPONENT_TYPE::E componentType)
  {
    if (componentType == COMPONENT_TYPE::kMeshComponent)
    {
      MeshComponent * model = new MeshComponent();
      m_components.push_back(model);
    }
  }
}
