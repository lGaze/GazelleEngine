/****************************************************************************
/* @filename gzVector2f.cpp
/* @author Gazelle
/* @date 2019/02/06
/* @brief 
/****************************************************************************/

#include "gzVector2f.h"

namespace gzEngineSDK {

  Vector2f::Vector2f(float X, float Y) : x(X), y(Y) {}

  FORCEINLINE Vector2f
  Vector2f::operator+(const Vector2f& Vector) const {
    return Vector2f(x + Vector.x, y + Vector.y);
  }

  FORCEINLINE Vector2f
  Vector2f::operator-(const Vector2f& Vector) const {
    return Vector2f(x - Vector.x, y - Vector.y);
  }

  FORCEINLINE Vector2f
  Vector2f::operator*(float Scalar) const {
    return Vector2f(x * Scalar, y * Scalar);
  }

  FORCEINLINE Vector2f
  Vector2f::operator*(const Vector2f& Vector) const {
    return Vector2f(x * Vector.x, y * Vector.y);
  }

  FORCEINLINE Vector2f
  Vector2f::operator/(float Scalar) const {
    return Vector2f(x / Scalar, y / Scalar);
  }

  FORCEINLINE Vector2f
  Vector2f::operator/(const Vector2f& Vector) const {
    return Vector2f(x / Vector.x, y / Vector.y);
  }

  FORCEINLINE Vector2f 
  Vector2f::operator+=(const Vector2f& Vector) {
    x += Vector.x;
    y += Vector.y;
    return *this;
  }

  FORCEINLINE Vector2f
  Vector2f::operator-=(const Vector2f& Vector) {
    x -= Vector.x;
    y -= Vector.y;
    return *this;
  }

  FORCEINLINE Vector2f
  Vector2f::operator*=(float Scalar) {
    x *= Scalar;
    y *= Scalar;
    return *this;
  }

  FORCEINLINE Vector2f 
  Vector2f::operator/=(float Scalar) {
    x /= Scalar;
    y /= Scalar;
    return *this;
  }

  FORCEINLINE float
  Vector2f::dot(const Vector2f& Vector) {
    return x * Vector.x + y * Vector.y;
  }

  FORCEINLINE float
  Vector2f::crossProduct(const Vector2f & Vector)
  {
    return x * Vector.y - y * Vector.x;
  }

  FORCEINLINE Vector2f 
  Vector2f::getNormalized() {
    float mag = magitude();
    return Vector2f(x / mag, y / mag);
  }

  void
  Vector2f::normalize() {
    float mag = magitude();
    x /= mag;
    y /= mag;
  }

  float 
  Vector2f::magitude() const {
    return Math::sqrt((x*x) + (y*y));
  }
}