/***************************************************************************/
/* @filename gzRay.cpp
/* @author Victor Flores 
/* @date 2019/02/15
/* @brief 
/***************************************************************************/
#include "gzRay.h"

namespace gzEngineSDK {
  
  Ray::Ray(const Vector3f & OriginPos, const Vector3f & Direction) 
    : originPos(OriginPos),
      direction(Direction) 
  {}

}