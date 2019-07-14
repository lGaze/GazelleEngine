/**************************************************************************/
/* @filename gzTransform.h
/* @author Victor Flores 
/* @date 2019/07/13
/**************************************************************************/
#pragma once
#include "gzPrerequisitesCore.h"

namespace gzEngineSDK {
  struct Transform
  {
     Vector3f m_position;
     Vector3f m_rotation;
     Vector4f m_scale;
  };
}

