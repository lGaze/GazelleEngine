/***************************************************************************/
/* @filename gzVector2i.h
/* @author Victor Flores
/* @date 2019/02/05
/* @brief This file can be used for create Vector2i
/***************************************************************************/

#pragma once

#include "gzPrerequisitesUtilities.h"
#include "gzMath.h"

namespace gzEngineSDK {
  class GZ_UTILITY_EXPORT Vector2i
  {
   public:

    /**
     * @brief Default Constructor
     */
    Vector2i();

    /**
     * @brief This Constructor generates a Vector2i with the given values
     * @param Float value wich indicates the X value in the vector
     * @param Float value wich indicates the Y value in the vector
     */
    FORCEINLINE Vector2i(uint32 X, uint32 Y);

    /**
     * @brief Default Destructor
     */
    ~Vector2i() = default;

    /************************************************************************/
    /* Overloaded operators                                                 */
    /************************************************************************/

    /**
     * @brief Overlad of the + operator
     * @param Reference to the Vector2i with which the addition will be made.
     * @return Vector2i with the result of the addition.
     */
    FORCEINLINE Vector2i
    operator+(const Vector2i& Vector) const;

    /**
     * @brief Overlad of the - operator
     * @param Reference to the Vector2i with which the substraction will be made.
     * @return Vector2i with the result of the substraction.
     */
    FORCEINLINE Vector2i
    operator-(const Vector2i& Vector) const;

    /**
     * @brief Overlad of the * operator
     * @param Float value whic indicates the Scalar with which the multiplication will be made.
     * @return Vector3f with the result of the multiplication.
     */
    FORCEINLINE Vector2i
    operator*(float Scalar) const;

    /**
     * @brief Overlad of the * operator
     * @param Reference to the Vector3f with which the multiplication will be made.
     * @return Vector2i with the result of the multiplication.
     */
    FORCEINLINE Vector2i
    operator*(const Vector2i& Vector) const;

    /**
     * @brief Overlad of the / operator
     * @param Float value whic indicates the Scalar with which the division will be made.
     * @return Vector2i with the result of the division.
     */
    FORCEINLINE Vector2i
    operator/(float Scalar) const;

    /**
     * @brief Overlad of the / operator
     * @param Reference to the Vector3f with which the division will be made.
     * @return Vector2i with the result of the division.
     */
    FORCEINLINE Vector2i
    operator/(const Vector2i& Vector) const;

    /**
     * @brief Overlad of the += operator
     * @param Vector2i with which the adition will be made.
     * @return Vector2i with the addition result values.
     */
    FORCEINLINE Vector2i
    operator+=(const Vector2i& Vector);

    /**
     * @brief Overlad of the -= operator
     * @param Vector2i with which the substraction will be made.
     * @return Vector2i with the substraction result values.
     */
    FORCEINLINE Vector2i
    operator-=(const Vector2i& Vector);

    /**
     * @brief Overlad of the *= operator
     * @param Vector2i with which the multiplication will be made.
     * @return Vector2i with the multiplication result values.
     */
    FORCEINLINE Vector2i
    operator*=(float Scalar);

    /**
     * @brief Overlad of the /= operator
     * @param Vector2i with which the division will be made.
     * @return Vector2i with the division result values.
     */
    FORCEINLINE Vector2i
    operator/=(float Scalar);


    /************************************************************************/
    /* Vector2 functions                                                    */
    /************************************************************************/

    /**
     * @brief This function computes a Dot Product
     * @param Vector2i with wich the Dot Product will be calculated
     * @return Float value wich indicates the result of the operation
     */
    FORCEINLINE float
    dot(const Vector2i& Vector);

    /**
     * @brief This function computes a Cross Product
     * @param Vector2i with wich the Cross Product will be calculated
     * @return Float value wich indicates the result of the operation
     */
    FORCEINLINE float
    crossProduct(const Vector2i& Vector);

    /**
     * @brief This function normalizes the Vector2i
     * @return Normalized Vector2i
     */
    FORCEINLINE Vector2i
    getNormalized();

    /**
     * @brief This function normalizes the Vector3i
     */
    void
    normalize();

    /**
     * @brief This function gets the magnitude of the Vector2i
     * @param Float value wich indicates the magnitude of the Vector2i
     */
    float
     magitude() const;

    /************************************************************************/
    /* Member declarations                                                  */
    /************************************************************************/

   public:

    /**
     * @brief X value in the vector
     */
    uint32 x;

    /**
     * @brief Y value in the vector
     */
    uint32 y;

  };
}