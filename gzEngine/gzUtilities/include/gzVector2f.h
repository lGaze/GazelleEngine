/***************************************************************************/
/* @filename gzVector2f.h
/* @author Gazelle
/* @date 2019/02/05
/* @brief 
/***************************************************************************/

#pragma once

#include "gzPrerequisitesUtilities.h"

namespace gzEngineSDK {
  class GZ_UTILITY_EXPORT Vector2f
  {
  public:

    /**
     * @brief 
     */
   FORCEINLINE Vector2f() = default;

   /**
    * @brief 
    */
   FORCEINLINE Vector2f(float X, float Y);

   ~Vector2f() = default;

   /************************************************************************/  
   /* Overloaded operators                                                 */
   /************************************************************************/

   /**
    * @brief 
    */
   FORCEINLINE Vector2f
   operator+(const Vector2f& Vector) const;

   /**
    * @brief 
    */
   FORCEINLINE Vector2f
   operator-(const Vector2f& Vector) const;

   /**
    * @brief 
    */
   FORCEINLINE Vector2f
   operator*(float Scalar) const;

   /**
    * @brief 
    */
   FORCEINLINE Vector2f
   operator*(const Vector2f& Vector) const;

   /**
    * @brief 
    */
   FORCEINLINE Vector2f
   operator/(float Scalar) const;

   /**
    * @brief 
    */
   FORCEINLINE Vector2f
   operator/(const Vector2f& Vector) const;

   /**
    * @brief 
    */
   FORCEINLINE Vector2f
   operator+=(const Vector2f& Vector);

   /**
    * @brief 
    */
   FORCEINLINE Vector2f
   operator-=(const Vector2f& Vector);

   /**
    * @brief 
    */
   FORCEINLINE Vector2f
   operator*=(float Scalar);

   /**
    * @brief 
    */
   FORCEINLINE Vector2f
   operator/=(float Scalar);


   /************************************************************************/
   /* Vector2 functions                                                    */
   /************************************************************************/

   /**
    * @brief 
    */
   FORCEINLINE float
   dot(const Vector2f& Vector);

   /**
    * @brief 
    */
   FORCEINLINE float
   crossProduct(const Vector2f& Vector);

   /**
    * @brief 
    */
   FORCEINLINE Vector2f
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

  };
}