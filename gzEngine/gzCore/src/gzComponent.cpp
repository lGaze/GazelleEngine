/**************************************************************************/
/* @filename gzComponent.cpp
/* @author Victor Flores 
/* @date 2019/07/14
/* @brief gzComponent implementation file
/**************************************************************************/

#include "gzPrerequisitesCore.h"
#include "gzComponent.h"

namespace gzEngineSDK {

  COMPONENT_TYPE::E
  Component::getComponentType()
  {
    return m_type;
  }
}
