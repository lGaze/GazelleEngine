/****************************************************************************
/* @filename gzVector4f.h
/* @author Gazelle
/* @date 2019/02/06
/* @brief 
/****************************************************************************/

#pragma once

#include "gzPrerequisitesUtilities.h"
#include "gzMath.h"


namespace gzEngineSDK {
  class GZ_UTILITY_EXPORT Vector4f
  {
  public:

    /**
     * @brief
     */
    FORCEINLINE Vector4f() = default;

    /**
     * @brief
     */
    FORCEINLINE Vector4f(float X, float Y, float Z, float W);

    ~Vector4f() = default;

    /************************************************************************/
    /* Overloaded operators                                                 */
    /************************************************************************/

    /**
     * @brief
     */
    FORCEINLINE Vector4f
    operator+(const Vector4f& Vector) const;

    /**
     * @brief
     */
    FORCEINLINE Vector4f
    operator-(const Vector4f& Vector) const;

    /**
     * @brief
     */
    FORCEINLINE Vector4f
    operator*(float Scalar) const;

    /**
     * @brief
     */
    FORCEINLINE Vector4f
    operator*(const Vector4f& Vector) const;

    /**
     * @brief
     */
    FORCEINLINE Vector4f
    operator/(float Scalar) const;

    /**
     * @brief
     */
    FORCEINLINE Vector4f
    operator/(const Vector4f& Vector) const;

    /**
     * @brief
     */
    FORCEINLINE Vector4f
    operator+=(const Vector4f& Vector);

    /**
     * @brief
     */
    FORCEINLINE Vector4f
    operator-=(const Vector4f& Vector);

    /**
     * @brief
     */
    FORCEINLINE Vector4f
    operator*=(float Scalar);

    /**
     * @brief
     */
    FORCEINLINE Vector4f
    operator/=(float Scalar);


    /************************************************************************/
    /* Vector2 functions                                                    */
    /************************************************************************/

    /**
     * @brief
     */
    FORCEINLINE float
    dot(const Vector4f& Vector);

    /**
     * @brief
     */

    FORCEINLINE Vector4f
    crossProduct(const Vector4f& Vector);

    /**
     * @brief
     */
    FORCEINLINE Vector4f
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

    /**
     * @brief 
     */
    float w;

  };
}

