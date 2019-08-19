/****************************************************************************
/* @filename gzVector4f.h
/* @author Gazelle
/* @date 2019/02/06
/* @brief This file can be used for create Vector4f
/****************************************************************************/

#pragma once

#include "gzPrerequisitesUtilities.h"
#include "gzMath.h"


namespace gzEngineSDK {
  class GZ_UTILITY_EXPORT Vector4f
  {
  public:

    /**
    * @brief Default Constructor
    */
    FORCEINLINE Vector4f() = default;

    /**
    * @brief This Constructor generates a Vector4f with the given values
    * @param Float value wich indicates the X value in the vector
    * @param Float value wich indicates the Y value in the vector
    * @param Float value wich indicates the Z value in the vector
    * @param Float value wich indicates the w value in the vector
    */
    FORCEINLINE Vector4f(float X, float Y, float Z, float W);

    /**
     * @brief Default Destructor
     */
    ~Vector4f() = default;

    /************************************************************************/
    /* Overloaded operators                                                 */
    /************************************************************************/

    /**
     * @brief Overlad of the + operator
     * @param Reference to the Vector4f with which the addition will be made.
     * @return Vector4f with the result of the addition.
     */
    FORCEINLINE Vector4f
    operator+(const Vector4f& Vector) const;

    /**
     * @brief Overlad of the - operator
     * @param Reference to the Vector4f with which the substraction will be made.
     * @return Vector4f with the result of the substraction.
     */
    FORCEINLINE Vector4f
    operator-(const Vector4f& Vector) const;

    /**
     * @brief Overlad of the * operator
     * @param Float value whic indicates the Scalar with which the multiplication will be made.
     * @return Vector4f with the result of the multiplication.
     */
    FORCEINLINE Vector4f
    operator*(float Scalar) const;

    /**
     * @brief Overlad of the * operator
     * @param Reference to the Vector4f with which the multiplication will be made.
     * @return Vector4f with the result of the multiplication.
     */
    FORCEINLINE Vector4f
    operator*(const Vector4f& Vector) const;

    /**
     * @brief Overlad of the / operator
     * @param Float value whic indicates the Scalar with which the division will be made.
     * @return Vector4f with the result of the division.
     */
    FORCEINLINE Vector4f
    operator/(float Scalar) const;

    /**
     * @brief Overlad of the / operator
     * @param Reference to the Vector4f with which the division will be made.
     * @return Vector4f with the result of the division.
     */
    FORCEINLINE Vector4f
    operator/(const Vector4f& Vector) const;

    /**
     * @brief Overlad of the += operator
     * @param Vector4f with which the adition will be made.
     * @return Vector4f with the addition result values.
     */
    FORCEINLINE Vector4f
    operator+=(const Vector4f& Vector);

    /**
     * @brief Overlad of the -= operator
     * @param Vector4f with which the substraction will be made.
     * @return Vector4f with the substraction result values.
     */
    FORCEINLINE Vector4f
    operator-=(const Vector4f& Vector);

    /**
     * @brief Overlad of the *= operator
     * @param Vector4f with which the multiplication will be made.
     * @return Vector4f with the multiplication result values.
     */
    FORCEINLINE Vector4f
    operator*=(float Scalar);

    /**
     * @brief Overlad of the /= operator
     * @param Vector4f with which the division will be made.
     * @return Vector4f with the division result values.
     */
    FORCEINLINE Vector4f
    operator/=(float Scalar);


    /************************************************************************/
    /* Vector2 functions                                                    */
    /************************************************************************/

    /**
     * @brief This function computes a Dot Product
     * @param Vector4f with wich the Dot Product will be calculated
     * @return Float value wich indicates the result of the operation
     */
    FORCEINLINE float
    dot(const Vector4f& Vector);

    /**
     * @brief This function computes a Cross Product
     * @param Vector4f with wich the Cross Product will be calculated
     * @return Vector4f wich indicates the result of the operation
     */
    FORCEINLINE Vector4f
    crossProduct(const Vector4f& Vector);

    /**
     * @brief This function normalizes the Vector4f
     * @return Normalized Vector4f
     */
    FORCEINLINE Vector4f
    getNormalized();

    /**
     * @brief This function normalizes the Vector4f
     */
    void
    normalize();

    /**
     * @brief This function gets the magnitude of the Vector4f
     * @param Float value wich indicates the magnitude of the Vector4f
     */
    float
    magitude() const;

    /************************************************************************/
    /* Member declarations                                                  */
    /************************************************************************/

    /**
     * @brief X value in the vector
     */
    float x;

    /**
     * @brief Y value in the vector
     */
    float y;

    /**
     * @brief Z value in the vector
     */
    float z;

    /**
     * @brief W value in the vector
     */
    float w;

  };
}

