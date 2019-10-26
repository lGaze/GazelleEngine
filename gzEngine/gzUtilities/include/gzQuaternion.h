/**************************************************************************/
/* @filename gzQuaternion.h
/* @author Victor Flores
/* @date 2019/10/15
/* @brief This file can be used for create and use a Quaternion
/**************************************************************************/
#pragma once

#include "gzPrerequisitesUtilities.h"
#include "gzMath.h"

namespace gzEngineSDK {
  class GZ_UTILITY_EXPORT Quaternion
  {
  public:

    /**
     * @brief default constructor
     */
    Quaternion();

    /**
     * @brief Specialized constructor
     * @param Float value wich indicates the x value of the quaternion
     * @param Float value wich indicates the y value of the quaternion
     * @param Float value wich indicates the z value of the quaternion
     */
    Quaternion(float x, float y, float z, float w);

    /**
     * @brief Specialized constructor
     * @param Vector3f wich indicates the axis of the quaternion
     * @param Float value wich indicates the angle of the quaternion (w component)
     */
    Quaternion(Vector3f axis, float angle);

    /**
     * @brief Specialized constructor
     * @param Vector3f wich indicates the axis of the quaternion
     */
    Quaternion(Vector3f v3);

    /**
     * @brief default destructor
     */
    ~Quaternion() = default;

    /************************************************************************/
    /* Overloaded operators                                                 */
    /************************************************************************/

    /**
     * @brief Overload of the * operator
     * @brief Reference to the Quaternion with wich the multiplication will be made.
     * @return Quaternion with the multiplication result .
     */
    Quaternion
    operator*(const Quaternion& quaternion) const;


    /************************************************************************/
    /* Quaternion functions                                                 */
    /************************************************************************/

    /**
     * @brief Normalizes the quaternion
     */
    void
    normalize();

    /**
     * @brief Lenght of the Quaternion
     */
    float
    magnitude();

    /**
     * @brief Conjugates the Quaternion
     */
    Quaternion
    conjuate();

    /************************************************************************/
    /* Member declarations                                                  */
    /************************************************************************/

  public:

    // X value in the Quaternion
    float m_x;

    // Y value in the Quaternion
    float m_y;

    // Z value in the Quaternion
    float m_z;

    // w value in the Quaternion
    float m_w;

  };
}
