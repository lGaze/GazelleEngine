/**************************************************************************/
/* @filename gzGameObject.cpp
/* @author Victor Flores 
/* @date 2019/07/14
/* @brief Implementation file of the class GameObject
/**************************************************************************/

#include "gzGameObject.h"


namespace gzEngineSDK {

  GameObject::GameObject() : 
    m_isEneabled(true), m_objectName("GameObject"){}

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
    for (auto it : m_children )
    {
      if ( it->m_objectName == gameObjectName)
      {
        return it;
      }
    }
    return nullptr;
  }

/*
  Vector<GameObject*> 
  GameObject::getRendereableChildrens()
  {
/ *
    Vector<GameObject*> temp;
    for (uint32 i = 0; i < m_children.size(); i++)
    {
      if (m_children[i]->m_isRendereable)
      {
        temp.push_back(m_children[i]);
      }
    }
    return temp;* /
  }*/

  void 
  GameObject::update()
  {
    for (auto it : m_components)
    {
      it->update();
    }
  }
}
