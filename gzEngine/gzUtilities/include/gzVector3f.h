
/****************************************************************************
/* @filename gzVector3f.h
/* @author Gazelle
/* @date 2019/02/06
/* @brief 
/****************************************************************************/

#pragma once

#include "gzPrerequisitesUtilities.h"

namespace gzEngineSDK {
  class GZ_UTILITY_EXPORT Vector3f
  {
  public:

    /**
     * @brief
     */
    FORCEINLINE Vector3f() = default;

    /**
     * @brief
     */
    FORCEINLINE Vector3f(float X, float Y, float Z);

    ~Vector3f() = default;

    /************************************************************************/
    /* Overloaded operators                                                 */
    /************************************************************************/

    /**
     * @brief
     */
    FORCEINLINE Vector3f
    operator+(const Vector3f& Vector) const;

    /**
     * @brief
     */
    FORCEINLINE Vector3f
    operator-(const Vector3f& Vector) const;

    /**
     * @brief
     */
    FORCEINLINE Vector3f
    operator*(float Scalar) const;

    /**
     * @brief
     */
    FORCEINLINE Vector3f
    operator*(const Vector3f& Vector) const;

    /**
     * @brief
     */
    FORCEINLINE Vector3f
    operator/(float Scalar) const;

    /**
     * @brief
     */
    FORCEINLINE Vector3f
    operator/(const Vector3f& Vector) const;

    /**
     * @brief
     */
    FORCEINLINE Vector3f
    operator+=(const Vector3f& Vector);

    /**
     * @brief
     */
    FORCEINLINE Vector3f
    operator-=(const Vector3f& Vector);

    /**
     * @brief
     */
    FORCEINLINE Vector3f
    operator*=(float Scalar);

    /**
     * @brief
     */
    FORCEINLINE Vector3f
    operator/=(float Scalar);


    /************************************************************************/
    /* Vector2 functions                                                    */
    /************************************************************************/

    /**
     * @brief
     */
    FORCEINLINE float
    dot(const Vector3f& Vector);

    /**
     * @brief
     */

    FORCEINLINE Vector3f
    crossProduct(const Vector3f& Vector);

    /**
     * @brief
     */
    FORCEINLINE Vector3f
    getNormalized();

    /**
     * @brief
     */
    void
    normalize();

    /**
     * @brief
     */
    float
    magitude() const;

    /************************************************************************/
    /* Member declarations                                                  */
    /************************************************************************/

    /**
     * @brief
     */
    float x;

    /**
     * @brief
     */
    float y;

    /**
     * @brief
     */
    float z;

  };
}
