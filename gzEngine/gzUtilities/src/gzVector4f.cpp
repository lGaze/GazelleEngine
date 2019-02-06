/****************************************************************************
/* @filename gzVector4f.cpp
/* @author Gazelle
/* @date 2019/02/06
/* @brief 
/*****************************************************************************/


#include "gzVector4f.h"

namespace gzEngineSDK {

  Vector4f::Vector4f(float X, float Y, float Z, float W) : x(X), y(Y), z(Z), w(W) {}

  FORCEINLINE Vector4f
  Vector4f::operator+(const Vector4f& Vector) const {
    return Vector4f(x + Vector.x, y + Vector.y, z + Vector.z, w + Vector.w);
  }

  FORCEINLINE Vector4f
  Vector4f::operator-(const Vector4f& Vector) const {
    return Vector4f(x - Vector.x, y - Vector.y, z - Vector.z, w - Vector.w);
  }

  FORCEINLINE Vector4f
  Vector4f::operator*(float Scalar) const {
    return Vector4f(x * Scalar, y * Scalar, z *Scalar, w * Scalar);
  }

  FORCEINLINE Vector4f
  Vector4f::operator*(const Vector4f& Vector) const {
    return Vector4f(x * Vector.x, y * Vector.y, z * Vector.z, w * Vector.w);
  }

  FORCEINLINE Vector4f
  Vector4f::operator/(float Scalar) const {
    return Vector4f(x / Scalar, y / Scalar, z / Scalar, w / Scalar);
  }

  FORCEINLINE Vector4f
  Vector4f::operator/(const Vector4f& Vector) const {
    return Vector4f(x / Vector.x, y / Vector.y, z / Vector.z, w / Vector.w);
  }

  FORCEINLINE Vector4f
  Vector4f::operator+=(const Vector4f& Vector) {
    x += Vector.x;
    y += Vector.y;
    z += Vector.z;
    w += Vector.w;
    return *this;
  }

  FORCEINLINE Vector4f
  Vector4f::operator-=(const Vector4f& Vector) {
    x -= Vector.x;
    y -= Vector.y;
    z -= Vector.z;
    w -= Vector.w;
    return *this;
  }

  FORCEINLINE Vector4f
  Vector4f::operator*=(float Scalar) {
    x *= Scalar;
    y *= Scalar;
    z *= Scalar;
    w *= Scalar;
    return *this;
  }

  FORCEINLINE Vector4f
  Vector4f::operator/=(float Scalar) {
    x /= Scalar;
    y /= Scalar;
    z /= Scalar;
    w /= Scalar;
    return *this;
  }

  FORCEINLINE float
  Vector4f::dot(const Vector4f& Vector) {
    return x * Vector.x + y * Vector.y + z * Vector.z + w * Vector.w;
  }

  FORCEINLINE Vector4f
  Vector4f::crossProduct(const Vector4f & Vector)
  {
    return Vector4f(
      y*Vector.z - z * Vector.y,
      z*Vector.x - x * Vector.z,
      x*Vector.y - y * Vector.x,
      0.0f);
  }

  FORCEINLINE Vector4f
  Vector4f::getNormalized() {
    float inv = 1.0f / magitude();
    return Vector4f(x * inv, y * inv, z * inv, w * inv);
  }

  void
  Vector4f::normalize() {
    float inv = 1.0f / magitude();
    x *= inv;
    y *= inv;
    z *= inv;
    w *= inv;
  }

  float
  Vector4f::magitude() const {
    return Math::sqrt((x*x) + (y*y) + (z*z) + (w*w));
  }
}