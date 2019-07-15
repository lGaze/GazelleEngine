/**************************************************************************/
/* @filename gzMeshComponent.cpp
/* @author Victor Flores 
/* @date 2019/07/14
/* @brief MeshComponent implementation file
/**************************************************************************/

#include "gzMeshComponent.h"
#include "gzModel.h"


namespace gzEngineSDK {

  using namespace COMPONENT_TYPE;

  MeshComponent::MeshComponent()
  {
    m_type = kMeshComponent;
    m_model = new Model();
  }

  COMPONENT_TYPE::E 
  MeshComponent::getComponentType()
  {
    return m_type;
  }
}
