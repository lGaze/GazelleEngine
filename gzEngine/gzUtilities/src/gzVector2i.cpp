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

  FORCEINLINE Vector2i
  Vector2i::operator+(const Vector2i& Vector) const {
    return Vector2i(x + Vector.x, y + Vector.y);
  }

  FORCEINLINE Vector2i
  Vector2i::operator-(const Vector2i& Vector) const {
    return Vector2i(x - Vector.x, y - Vector.y);
  }

  FORCEINLINE Vector2i
  Vector2i::operator*(float Scalar) const {
    return Vector2i(x * Scalar, y * Scalar);
  }

  FORCEINLINE Vector2i
  Vector2i::operator*(const Vector2i& Vector) const {
    return Vector2i(x * Vector.x, y * Vector.y);
  }

  FORCEINLINE Vector2i
    Vector2i::operator/(float Scalar) const {
    return Vector2i(x / Scalar, y / Scalar);
  }

  FORCEINLINE Vector2i
  Vector2i::operator/(const Vector2i& Vector) const {
    return Vector2i(x / Vector.x, y / Vector.y);
  }

  FORCEINLINE Vector2i
  Vector2i::operator+=(const Vector2i& Vector) {
    x += Vector.x;
    y += Vector.y;
    return *this;
  }

  FORCEINLINE Vector2i
  Vector2i::operator-=(const Vector2i& Vector) {
    x -= Vector.x;
    y -= Vector.y;
    return *this;
  }

  FORCEINLINE Vector2i
  Vector2i::operator*=(float Scalar) {
    x *= Scalar;
    y *= Scalar;
    return *this;
  }

  FORCEINLINE Vector2i
  Vector2i::operator/=(float Scalar) {
    x /= Scalar;
    y /= Scalar;
    return *this;
  }

  FORCEINLINE float
  Vector2i::dot(const Vector2i& Vector) {
    return x * Vector.x + y * Vector.y;
  }

  FORCEINLINE float
  Vector2i::crossProduct(const Vector2i & Vector)
  {
    return x * Vector.y - y * Vector.x;
  }

  FORCEINLINE Vector2i
  Vector2i::getNormalized() {
    float mag = magitude();
    return Vector2i(x / mag, y / mag);
  }

  void
  Vector2i::normalize() {
    float mag = magitude();
    x /= mag;
    y /= mag;
  }

  float
  Vector2i::magitude() const {
    return Math::sqrt((x*x) + (y*y));
  }
}