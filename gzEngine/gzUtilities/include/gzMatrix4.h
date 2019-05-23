/****************************************************************************
/* @filename gzMatrix4.h
/* @author Victor Flores
/* @date 2019/02/06
/* @brief 
/*****************************************************************************/

#pragma once

#include "gzPrerequisitesUtilities.h"
#include "gzVector3f.h"
#include "gzVector4f.h"

namespace gzEngineSDK {
  class GZ_UTILITY_EXPORT Matrix4
  {
   public:

    /**
     * @brief 
     */
    FORCEINLINE Matrix4();

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
    Matrix4( Vector4f VectorA,
             Vector4f VectorB,
             Vector4f VectorC,
             Vector4f VectorD );

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

    /**
     * @brief 
     */
    bool
    operator==( const Matrix4& Matrix ) const;

    /**
     * @brief
     */
    bool
    operator!=( const Matrix4& Matrix ) const;

    /************************************************************************/
    /* Matrix functions                                                     */
    /************************************************************************/

    /**
     * @brief This function sets the Matrix to an identity Matrix 
     */
    void
    identity();

    /**
     * @brief 
     */
    void
    transpose();

    /**
     * @brief This function sets all the elements of the matrix to 0
     */
    void
    zeroMatrix();

    /**
     * @brief This function builds a left handed
     */
    Matrix4&
    matrixLookAtLH( Vector3f eyePosition,
                    Vector3f atPosition,
                    Vector3f upDirection ); 

    /**
     * @brief This function builds a left handed perspective projection matrix.
     */
    Matrix4&
    matrixPerspectiveFovLH( float fovy,
                            float aspect,
                            float znear,
                            float zfar );
    
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