/**************************************************************************/
/* @filename gzMeshComponent.cpp
/* @author Victor Flores 
/* @date 2019/07/14
/* @brief MeshComponent implementation file
/**************************************************************************/

#include "gzMeshComponent.h"
#include "gzModel.h"
#include "gzResourceManager.h"


namespace gzEngineSDK {

  using namespace COMPONENT_TYPE;

  MeshComponent::MeshComponent()
  {
    m_type = kMeshComponent;
  }

  COMPONENT_TYPE::E 
  MeshComponent::getComponentType()
  {
    return m_type;
  }

  void
  MeshComponent::loadMesh(String path)
  {
    m_resource = ResourceManager::instance().loadModelFromFile(path);
  }

  void 
  MeshComponent::update()
  {
    ResourceManager::instance().drawModel(m_resource);
  }

  void 
  MeshComponent::changeMaterial(Material & Material)
  {
    ResourceManager::instance().changeMaterial(m_resource, Material);
  }
}
