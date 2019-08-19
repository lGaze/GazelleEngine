/***************************************************************************/
/* @filename gzVector2f.h
/* @author Victor Flores
/* @date 2019/02/05
/* @brief This file can be used for create Vector2f
/***************************************************************************/

#pragma once

#include "gzPrerequisitesUtilities.h"
#include "gzMath.h"

namespace gzEngineSDK {
  class GZ_UTILITY_EXPORT Vector2f
  {
   public:

    /**
     * @brief Default Constructor
     */
    Vector2f();

    /**
     * @brief This Constructor generates a Vector2f with the given values
     * @param Float value wich indicates the X value in the vector
     * @param Float value wich indicates the Y value in the vector
     */
    FORCEINLINE Vector2f(float X, float Y);

    /**
     * @brief Default Destructor
     */
    ~Vector2f() = default;
    
    /************************************************************************/  
    /* Overloaded operators                                                 */
    /************************************************************************/
    
    /**
     * @brief Overlad of the + operator
     * @param Reference to the Vector2f with which the addition will be made.
     * @return Vector2f with the result of the addition.
     */
    FORCEINLINE Vector2f
    operator+(const Vector2f& Vector) const;
    
    /**
     * @brief Overlad of the - operator
     * @param Reference to the Vector2f with which the substraction will be made.
     * @return Vector2f with the result of the substraction.
     */
    FORCEINLINE Vector2f
    operator-(const Vector2f& Vector) const;
    
    /**
     * @brief Overlad of the * operator
     * @param Float value whic indicates the Scalar with which the multiplication will be made.
     * @return Vector3f with the result of the multiplication.
     */
    FORCEINLINE Vector2f
    operator*(float Scalar) const;
    
    /**
     * @brief Overlad of the * operator
     * @param Reference to the Vector3f with which the multiplication will be made.
     * @return Vector2f with the result of the multiplication.
     */
    FORCEINLINE Vector2f
    operator*(const Vector2f& Vector) const;
    
    /**
     * @brief Overlad of the / operator
     * @param Float value whic indicates the Scalar with which the division will be made.
     * @return Vector2f with the result of the division.
     */
    FORCEINLINE Vector2f
    operator/(float Scalar) const;
    
    /**
     * @brief Overlad of the / operator
     * @param Reference to the Vector3f with which the division will be made.
     * @return Vector2f with the result of the division.
     */
    FORCEINLINE Vector2f
    operator/(const Vector2f& Vector) const;
    
    /**
     * @brief Overlad of the += operator
     * @param Vector2f with which the adition will be made.
     * @return Vector2f with the addition result values.
     */
    FORCEINLINE Vector2f
    operator+=(const Vector2f& Vector);
    
    /**
     * @brief Overlad of the -= operator
     * @param Vector2f with which the substraction will be made.
     * @return Vector2f with the substraction result values.
     */
    FORCEINLINE Vector2f
    operator-=(const Vector2f& Vector);
    
    /**
     * @brief Overlad of the *= operator
     * @param Vector2f with which the multiplication will be made.
     * @return Vector2f with the multiplication result values.
     */
    FORCEINLINE Vector2f
    operator*=(float Scalar);
    
    /**
     * @brief Overlad of the /= operator
     * @param Vector2f with which the division will be made.
     * @return Vector2f with the division result values.
     */
    FORCEINLINE Vector2f
    operator/=(float Scalar);
    
    
    /************************************************************************/
    /* Vector2 functions                                                    */
    /************************************************************************/
    
    /**
     * @brief This function computes a Dot Product
     * @param Vector2f with wich the Dot Product will be calculated
     * @return Float value wich indicates the result of the operation
     */
    FORCEINLINE float
    dot(const Vector2f& Vector);
    
    /**
     * @brief This function computes a Cross Product
     * @param Vector2f with wich the Cross Product will be calculated
     * @return Float value wich indicates the result of the operation
     */
    FORCEINLINE float
    crossProduct(const Vector2f& Vector);
    
    /**
     * @brief This function normalizes the Vector3f
     * @return Normalized Vector2f
     */
    FORCEINLINE Vector2f
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

   public:

    /**
     * @brief X value in the vecto
     */
    float x;
    
    /**
     * @brief Y value in the vecto
     */
    float y;
   
  };
}