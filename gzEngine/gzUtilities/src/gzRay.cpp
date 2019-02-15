#include "gzRay.h"

namespace gzEngineSDK {
  
  Ray::Ray(const Vector3f & OriginPos, const Vector3f & Direction)
  {
    originPos = OriginPos;
    direction = Direction;
  }
}