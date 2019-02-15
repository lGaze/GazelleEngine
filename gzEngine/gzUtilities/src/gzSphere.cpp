/**************************************************************************/
/* @filename gzSphere.cpp
/* @author Victor Flores 
/* @date 2019/02/15
/* @brief 
/**************************************************************************/

#include "gzSphere.h"

namespace gzEngineSDK {
 
  Sphere::Sphere(const Vector3f & position, float radius)
    : centerPos(position), 
      radiusSize(radius) 
  {}
  
}