/**************************************************************************/
/* @filename gzBox2D.cpp
/* @author Victor Flores 
/* @date 2019/02/15
/* @brief 
/**************************************************************************/

#include "gzBox2D.h"

namespace gzEngineSDK {

  Box2D::Box2D(const Vector2f & centerPos, const float height, const float width) 
    : boxCenter(centerPos), 
      boxHeight(height),
      boxWidth(width)
  {}
}
