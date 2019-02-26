/****************************************************************************
/* @filename gzVector3f.cpp
/* @author Victor Flores
/* @date 2019/02/06
/* @brief 
/*****************************************************************************/


#include "gzVector3f.h"

namespace gzEngineSDK {

  Vector3f::Vector3f(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

  FORCEINLINE Vector3f
  Vector3f::operator+(const Vector3f& Vector) const {
    return Vector3f(x + Vector.x, y + Vector.y, z + Vector.z);
  }

  FORCEINLINE Vector3f
  Vector3f::operator-(const Vector3f& Vector) const {
    return Vector3f(x - Vector.x, y - Vector.y, z - Vector.z);
  }

  FORCEINLINE Vector3f
  Vector3f::operator*(float Scalar) const {
    return Vector3f(x * Scalar, y * Scalar, z *Scalar);
  }

  FORCEINLINE Vector3f
  Vector3f::operator*(const Vector3f& Vector) const {
    return Vector3f(x * Vector.x, y * Vector.y, z * Vector.z);
  }

  FORCEINLINE Vector3f
  Vector3f::operator/(float Scalar) const {
    return Vector3f(x / Scalar, y / Scalar, z / Scalar);
  }

  FORCEINLINE Vector3f
  Vector3f::operator/(const Vector3f& Vector) const {
    return Vector3f(x / Vector.x, y / Vector.y, z / Vector.z);
  }

  FORCEINLINE Vector3f
  Vector3f::operator+=(const Vector3f& Vector) {
    x += Vector.x;
    y += Vector.y;
    z += Vector.z;
    return *this;
  }

  FORCEINLINE Vector3f
  Vector3f::operator-=(const Vector3f& Vector) {
    x -= Vector.x;
    y -= Vector.y;
    z -= Vector.z;
    return *this;
  }

  FORCEINLINE Vector3f
  Vector3f::operator*=(float Scalar) {
    x *= Scalar;
    y *= Scalar;
    z *= Scalar;
    return *this;
  }

  FORCEINLINE Vector3f
  Vector3f::operator/=(float Scalar) {
    x /= Scalar;
    y /= Scalar;
    z /= Scalar;
    return *this;
  }

  FORCEINLINE float
  Vector3f::dot(const Vector3f& Vector) {
    return x * Vector.x + y * Vector.y + z * Vector.z;
  }

  FORCEINLINE Vector3f
  Vector3f::crossProduct(const Vector3f & Vector)
  {
    return Vector3f(
      y*Vector.z - z * Vector.y, 
      z*Vector.x - x * Vector.z, 
      x*Vector.y - y * Vector.x);
  }

  FORCEINLINE Vector3f
  Vector3f::getNormalized() {
    float mag = magitude();
    return Vector3f(x / mag, y / mag, z / mag);
  }

  void
  Vector3f::normalize() {
    float mag = magitude();
    x /= mag;
    y /= mag;
    z /= mag;
  }

  float
  Vector3f::magitude() const {
    return Math::sqrt((x*x) + (y*y) + (z*z));
  }
}