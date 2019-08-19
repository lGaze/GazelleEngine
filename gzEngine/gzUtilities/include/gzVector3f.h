
/****************************************************************************
/* @filename gzVector3f.h
/* @author Gazelle
/* @date 2019/02/06
/* @brief This file can be used for create Vector3f
/****************************************************************************/

#pragma once

#include "gzPrerequisitesUtilities.h"
#include "gzMath.h"

namespace gzEngineSDK {
  class GZ_UTILITY_EXPORT Vector3f
  {
  public:

    /**
     * @brief Default Constructor
     */
    Vector3f();

    /**
     * @brief This Constructor generates a Vector3f with the given values
     * @param Float value wich indicates the X value in the vector
     * @param Float value wich indicates the Y value in the vector
     * @param Float value wich indicates the Z value in the vector
     */
    FORCEINLINE Vector3f(float X, float Y, float Z);

    /**
     * @brief Default Destructor
     */
    ~Vector3f() = default;

    /************************************************************************/
    /* Overloaded operators                                                 */
    /************************************************************************/

    /**
     * @brief Overlad of the + operator
     * @param Reference to the Vector3f with which the addition will be made.
     * @return Vector3f with the result of the addition.
     */
    FORCEINLINE Vector3f
    operator+(const Vector3f& Vector) const;


    /**
     * @brief Overlad of the - operator
     * @param Reference to the Vector3f with which the substraction will be made.
     * @return Vector3f with the result of the substraction.
     */
    FORCEINLINE Vector3f
    operator-(const Vector3f& Vector) const;

    /**
     * @brief Overlad of the * operator
     * @param Float value whic indicates the Scalar with which the multiplication will be made.
     * @return Vector3f with the result of the multiplication.
     */
    FORCEINLINE Vector3f
    operator*(float Scalar) const;

    /**
     * @brief Overlad of the * operator
     * @param Reference to the Vector3f with which the multiplication will be made.
     * @return Vector3f with the result of the multiplication.
     */
    FORCEINLINE Vector3f
    operator*(const Vector3f& Vector) const;

    /**
     * @brief Overlad of the / operator
     * @param Float value whic indicates the Scalar with which the division will be made.
     * @return Vector3f with the result of the division.
     */
    FORCEINLINE Vector3f
    operator/(float Scalar) const;

    /**
     * @brief Overlad of the / operator
     * @param Reference to the Vector3f with which the division will be made.
     * @return Vector3f with the result of the division.
     */
    FORCEINLINE Vector3f
    operator/(const Vector3f& Vector) const;

    /**
     * @brief Overlad of the += operator
     * @param Vector3f with which the adition will be made.
     * @return Vector3f with the addition result values.
     */
    FORCEINLINE Vector3f
    operator+=(const Vector3f& Vector);

    /**
     * @brief Overlad of the -= operator
     * @param Vector3f with which the substraction will be made.
     * @return Vector3f with the substraction result values.
     */
    FORCEINLINE Vector3f
    operator-=(const Vector3f& Vector);

    /**
     * @brief Overlad of the *= operator
     * @param Vector3f with which the multiplication will be made.
     * @return Vector3f with the multiplication result values.
     */
    FORCEINLINE Vector3f
    operator*=(float Scalar);

    /**
     * @brief Overlad of the /= operator
     * @param Vector3f with which the division will be made.
     * @return Vector3f with the division result values.
     */
    FORCEINLINE Vector3f
    operator/=(float Scalar);


    /************************************************************************/
    /* Vector3 functions                                                    */
    /************************************************************************/

    /**
     * @brief This function computes a Dot Product
     * @param Vector3f with wich the Dot Product will be calculated
     * @return Float value wich indicates the result of the operation
     */
    FORCEINLINE float
    dot(const Vector3f& Vector);

    /**
     * @brief This function computes a Cross Product
     * @param Vector3f with wich the Cross Product will be calculated
     * @return Vector3f wich indicates the result of the operation
     */ 
    FORCEINLINE Vector3f
    crossProduct(const Vector3f& Vector);

    /**
     * @brief This function normalizes the Vector3f
     * @return Normalized Vector3f
     */ 
    FORCEINLINE Vector3f
    getNormalized();

    /**
     * @brief This function normalizes the Vector3f
     */
    void
    normalize();

    /**
     * @brief This function gets the magnitude of the Vector3f
     * @param Float value wich indicates the magnitude of the Vector3f
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

  };
}
