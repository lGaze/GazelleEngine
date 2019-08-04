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

  void 
  GameObject::addChildren(GameObject & gameObject)
  {
    m_children.push_back(&gameObject);
  }

  GameObject *
  GameObject::findChildrenbyName(String gameObjectName)
  {
    for (int i = 0; i < m_children.size(); i++)
    {
      if (m_children[i]->m_objectName == gameObjectName)
      {
        return m_children[i];
      }
    }
    return nullptr;
  }
}
