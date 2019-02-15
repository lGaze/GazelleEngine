/**************************************************************************/
/* @filename gzTriangle.cpp
/* @author Victor Flores 
/* @date 2019/02/15
/* @brief 
/**************************************************************************/

#include "gzTriangle.h"

namespace gzEngineSDK {

  Triangle::Triangle(
    const Vector3f & vertex1, 
    const Vector3f & vertex2, 
    const Vector3f & vertex3) 
    : triangleVert1(vertex1),
      triangleVert2(vertex2),
      triangleVert3(vertex3) 
  {}

}