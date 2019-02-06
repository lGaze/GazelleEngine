/****************************************************************************
/* @filename gzMatrix4.h
/* @author Gazelle
/* @date 2019/02/06
/* @brief 
/*****************************************************************************/

#pragma once

#include "gzPrerequisitesUtilities.h"
#include "gzMath.h"
#include "gzVector3f.h"
#include "gzVector4f.h"

namespace gzEngineSDK {
  class GZ_UTILITY_EXPORT Matrix4
  {
  public:

    /**
     * @brief 
     */
    FORCEINLINE Matrix4() = default;

    /**
     * @brief 
     */
    Matrix4(
      float m00, float m01, float m02, float m03,
      float m10, float m11, float m12, float m13,
      float m20, float m21, float m22, float m23,
      float m30, float m31, float m32, float m33
    );

    /**
     * @brief 
     */
    Matrix4(const Matrix4& Matrix);

    /**
     * @brief 
     */
    Matrix4( Vector4f VectorA, Vector4f VectorB, Vector4f VectorC, Vector4f VectorD);

   /************************************************************************/
   /* Overloaded operators                                                 */
   /************************************************************************/
    
    FORCEINLINE Matrix4
    operator+(const Matrix4& Matrix); 

    /**
     * @brief 
     */
    FORCEINLINE Matrix4
    operator-(const Matrix4& Matrix);

    /**
     * @brief 
     */
    FORCEINLINE Matrix4
    operator*(const Matrix4& Matrix);

    /**
     * @brief 
     */
    FORCEINLINE Matrix4
    operator*(const float& Scalar);

    /**
     * @brief 
     */
    Matrix4&
    operator+=(const Matrix4& Matrix);

    /**
     * @brief 
     */
    Matrix4&
    operator-=(const Matrix4& Matrix);

    /**
     * @brief 
     */
    Matrix4&
    operator*=(const Matrix4& Matrix);

    /************************************************************************/
    /* Matrix functions                                                     */
    /************************************************************************/

    /**
     * @brief 
     */
    void
    identity();

    /**
     * @brief 
     */
    void
    transposed();

    /************************************************************************/
    /* Member declaration                                                   */
    /************************************************************************/
  public:

    union {

      struct {
        float m00, m01, m02, m03,
              m10, m11, m12, m13,
              m20, m21, m22, m23,
              m30, m31, m32, m33;
      }matrix;
      float m[4][4];
    };
  

  };
}