/**************************************************************************/
/* @filename gzQuaternion.cpp
/* @author Victor Flores
/* @date 2019/10/15
/* @brief
/**************************************************************************/

#include "gzQuaternion.h"
#include "gzVector3f.h"

namespace gzEngineSDK {
  Quaternion::Quaternion() : m_x(0.0f), m_y(0.0f), m_z(0.0f), m_w(1.0f) {}
  Quaternion::Quaternion(float x, float y, float z, float w) :
    m_x(x), m_y(y), m_z(z), m_w(w) {}

  Quaternion::Quaternion(Vector3f axis, float angle) {

    float sinHalf = Math::sin(angle / 2);
    float cosHalf = Math::cos(angle / 2);

    m_x = axis.x * sinHalf;
    m_y = axis.y * sinHalf;
    m_z = axis.z * sinHalf;
    m_w = cosHalf;
  }


  Quaternion
  Quaternion::operator*(const Quaternion & quaternion) const {
    Quaternion res;

    res.m_w =
      ((m_w * quaternion.m_w) -
      (m_x * quaternion.m_x) -
       (m_y * quaternion.m_y) -
       (m_z * quaternion.m_z));

    res.m_x =
      ((m_w * quaternion.m_x) +
      (m_x * quaternion.m_w) +
       (m_y * quaternion.m_z) -
       (m_z * quaternion.m_y));

    res.m_y =
      ((m_w * quaternion.m_y) -
      (m_x * quaternion.m_z) +
       (m_y * quaternion.m_w) +
       (m_z * quaternion.m_x));

    res.m_z =
      ((m_w * quaternion.m_z) +
      (m_x * quaternion.m_y) -
       (m_y * quaternion.m_x) +
       (m_z * quaternion.m_w));

    return res;
  }

  void
  Quaternion::normalize() {
    float mag = magnitude();
    m_w /= mag;
    m_x /= mag;
    m_y /= mag;
    m_z /= mag;
  }

  float
  Quaternion::magnitude() {
    return Math::sqrt((m_w * m_w) + (m_x * m_x) + (m_y * m_y) + (m_z * m_z));
  }

  Quaternion
  Quaternion::conjuate() {
    Quaternion res(-m_x, -m_y, -m_z, m_w);
    return res;
  }
}