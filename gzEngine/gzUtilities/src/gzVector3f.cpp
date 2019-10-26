/****************************************************************************
/* @filename gzVector3f.cpp
/* @author Victor Flores
/* @date 2019/02/06
/* @brief 
/*****************************************************************************/


#include "gzVector3f.h"
#include "gzQuaternion.h"

namespace gzEngineSDK {

  Vector3f::Vector3f() : x(0.0f), y(0.0f), z(0.0f) {}
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

  void
  Vector3f::rotateq(float angle, Vector3f axis)
  {
    Quaternion p(*this);
    float sinHalf = Math::sin(angle / 2);
    float cosHalf = Math::cos(angle / 2);

    float x_ = axis.x * sinHalf;
    float y_ = axis.y * sinHalf;
    float z_ = axis.z * sinHalf;
    float w_ = cosHalf;

    Quaternion q(x_, y_, z_, w_);

    Quaternion res = q*p*q.conjuate();

    x = res.m_x;
    y = res.m_y;
    z = res.m_z;
  }

  void
  Vector3f::rotate(float angle, Vector3f axis)
  {
    float sinAngle = Math::sin(-angle);
    float cosAngle = Math::cos(-angle);

    this->crossProduct(axis*sinAngle + *this*cosAngle + axis * (this->dot(axis*(1 - cosAngle))));
  }
}