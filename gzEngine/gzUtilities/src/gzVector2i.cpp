/****************************************************************************
/* @filename Vector2i.cpp
/* @author Victor Flores
/* @date 2019/02/06
/* @brief
/****************************************************************************/

#include "gzVector2i.h"

namespace gzEngineSDK {

  Vector2i::Vector2i() : x(0), y(0) { }

  Vector2i::Vector2i(uint32 X, uint32 Y) : x(X), y(Y) {}

  Vector2i
  Vector2i::operator+(const Vector2i& Vector) const {
    return Vector2i(x + Vector.x, y + Vector.y);
  }

  Vector2i
  Vector2i::operator-(const Vector2i& Vector) const {
    return Vector2i(x - Vector.x, y - Vector.y);
  }

  Vector2i
  Vector2i::operator*(uint32 Scalar) const {
    return Vector2i(x * Scalar, y * Scalar);
  }

  Vector2i
  Vector2i::operator*(const Vector2i& Vector) const {
    return Vector2i(x * Vector.x, y * Vector.y);
  }

  Vector2i
  Vector2i::operator/(uint32 Scalar) const {
    return Vector2i(x / Scalar, y / Scalar);
  }

  Vector2i
  Vector2i::operator/(const Vector2i& Vector) const {
    return Vector2i(x / Vector.x, y / Vector.y);
  }

  Vector2i
  Vector2i::operator+=(const Vector2i& Vector) {
    x += Vector.x;
    y += Vector.y;
    return *this;
  }

  Vector2i
  Vector2i::operator-=(const Vector2i& Vector) {
    x -= Vector.x;
    y -= Vector.y;
    return *this;
  }

  Vector2i
  Vector2i::operator*=(uint32 Scalar) {
    x *= Scalar;
    y *= Scalar;
    return *this;
  }

  Vector2i
  Vector2i::operator/=(uint32 Scalar) {
    x /= Scalar;
    y /= Scalar;
    return *this;
  }

  FORCEINLINE uint32
  Vector2i::dot(const Vector2i& Vector) {
    return x * Vector.x + y * Vector.y;
  }
}