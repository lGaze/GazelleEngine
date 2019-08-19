/****************************************************************************
/* @filename gzMatrix4.h
/* @author Victor Flores
/* @date 2019/02/06
/* @brief This file can be used to create a 4x4 Matrix
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
     * @brief Default Constructor
     */
    Matrix4();

    /**
     * @brief This Constructor generates a 4x4 Matrix with the given values
     * @param Float value wich indicates the value of the position in the matrix:
     *   ______________
     *  |00, 01, 02, 03|
     *  |10, 11, 12, 13|
     *  |20, 21, 22, 23|
     *  |30, 31, 32, 33|
     *   ¯¯¯¯¯¯¯¯¯¯¯¯¯¯
     */
    Matrix4(
      float m00, float m01, float m02, float m03,
      float m10, float m11, float m12, float m13,
      float m20, float m21, float m22, float m23,
      float m30, float m31, float m32, float m33
    );

    /**
     * @brief This constructor generates a 4x4 Matrix from a given matrix
     * @param Reference of the 4x4 Matrix that is going to be used to generate the new one
     */
    Matrix4(const Matrix4& Matrix);

    /**
     * @brief This constructor generates a 4x4 Matrix from 4 Vector4f
     * @param Vector4 wich indicates teh values of the 1° row of the 4x4 Matrix
     * @param Vector4 wich indicates teh values of the 2° row of the 4x4 Matrix
     * @param Vector4 wich indicates teh values of the 3° row of the 4x4 Matrix
     * @param Vector4 wich indicates teh values of the 4° row of the 4x4 Matrix
     */
    Matrix4( Vector4f VectorA,
             Vector4f VectorB,
             Vector4f VectorC,
             Vector4f VectorD );

    /**
     * @brief Default Destructor
     */
    ~Matrix4() = default;

   /************************************************************************/
   /* Overloaded operators                                                 */
   /************************************************************************/
    
    /**
     * @brief Overlad of the + operator
     * @param Reference to the 4x4 Matrix with which the addition will be made.
     * @return Matrix 4x4 with the result of the addition.
     */
    FORCEINLINE Matrix4
    operator+(const Matrix4& Matrix); 

    /**
     * @brief Overlad of the - operator
     * @param Reference to the 4x4 Matrix with which the substraction will be made.
     * @return Matrix 4x4 with the result of the substraction.
     */
    FORCEINLINE Matrix4
    operator-(const Matrix4& Matrix);

    /**
     * @brief Overlad of the * operator
     * @param Reference to the 4x4 Matrix with which the multiplication will be made.
     * @return Matrix 4x4 with the result of the multiplication.
     */
    FORCEINLINE Matrix4
    operator*(const Matrix4& Matrix);

    /**
     * @brief Overlad of the * operator
     * @param Float value which indicates the Scalar with which the multiplication will be made.
     * @return Matrix 4x4 with the result of the multiplication.
     */
    FORCEINLINE Matrix4
    operator*(const float& Scalar);

    /**
     * @brief Overlad of the += operator
     * @param 4x4 Matrix with which the adition will be made.
     * @return Reference of the matrix with the addition result values.
     */
    Matrix4&
    operator+=(const Matrix4& Matrix);

    /**
     * @brief Overlad of the -= operator
     * @param 4x4 Matrix with which the substraction will be made.
     * @return Reference of the matrix with the substraction result values.
     */
    Matrix4&
    operator-=(const Matrix4& Matrix);

    /**
     * @brief Overlad of the *= operator
     * @param 4x4 Matrix with which the multiplication will be made.
     * @return Reference of the matrix with the multiplication result values.
     */
    Matrix4&
    operator*=(const Matrix4& Matrix);


    /**
     * @brief Overlad of the == operator
     * @param 4x4 Matrix with which the comparison will be made.
     * @return Return true if the values of the Matrices are equal.
     */
    bool
    operator==( const Matrix4& Matrix ) const;

    /**
     * @brief Overlad of the == operator
     * @param 4x4 Matrix with which the comparison will be made.
     * @return Return true if the values of the Matrices are different.
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
     * @brief This function transposes the Matrix
     */
    void
    transpose();

    /**
     * @brief This function sets all the elements of the matrix to 0
     */
    void
    zeroMatrix();

    /**
     * @brief This function builds a left handed look at Matrix
     * @param Vector3f wich indicates the eyePosition.
     * @param Vector3f wich indicates the atPosition.
     * @param Vector3f wich indicates the upDirection.
     * @return LookAt Matrix.
     */
    Matrix4
    matrixLookAtLH( Vector3f eyePosition,
                    Vector3f atPosition,
                    Vector3f upDirection ); 

    /**
     * @brief This function builds a left handed perspective projection matrix.
     * @param Float value wich indicates the Field of View
     * @param Float value wich indicates the aspect
     * @param Float value wich indicates the near value
     * @param Float value wich indicates the far value
     * @return Perspective Matrix
     */
    Matrix4
    matrixPerspectiveFovLH( float fovy,
                            float aspect,
                            float znear,
                            float zfar );
    /**
     * @brief Builds a matrix that rotates around the y-axis.
     * @param Float value wich indicates the angle of rotation
     */
    void
    matrixRotationY( float angle );

    /**
     * @brief  Builds a matrix that rotates around the x-axis.
     * @param Float value wich indicates the angle of rotation
     */
    void
    matrixRotationX(float angle);
    
    /************************************************************************/
    /* Member declaration                                                   */
    /************************************************************************/
   public:

    /**
     * @brief Values of the 4x4 Matrix
     */
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