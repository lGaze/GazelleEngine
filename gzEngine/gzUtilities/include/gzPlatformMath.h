/****************************************************************************
/* @filename gzPlatformMath
/* @author Gazelle
/* @date 2019/02/05
/* @brief General Math Library
/*****************************************************************************/
#pragma once

#include "gzPrerequisitesUtilities.h"

namespace gzEngineSDK {
  class GZ_UTILITY_EXPORT PlatformMath
  {
   public:

    PlatformMath() = default;
    ~PlatformMath() = default;

    /**
     * @brief Cosine function
     * @param Float value to get cosine
     * @return Cosine of the value
     */
    static FORCEINLINE float
    cos(float Value) {
      return std::cosf(Value);
    }
    
    /**
     * @brief Sine function
     * @param Float value to get sine
     * @return Sine of the value
     */
    static FORCEINLINE float
    sin(float Value) {
      return std::sinf(Value);
    }

    /**
     * @brief Tangent function
     * @param Float value to get tangent
     * @return Tangent of the value
     */
    static FORCEINLINE float
    tan(float Value) {
      return std::tanf(Value);
    }

    /**
     * @brief Arc cosine function
     * @param Float value to get arc cosine
     * @return Arc cosine of the value
     */
    static FORCEINLINE float
    acos(float Value) {
      return std::acosf(Value);
    }

    /**
     * @brief Arc sine function
     * @param Float value to get arc sine
     * @return Arc sine of the value
     */
    static FORCEINLINE float
    asin(float Value) {
      return std::asinf(Value);
    }

    /**
     * @brief Arc tangent function
     * @param Float value to get arc tangent
     * @return Arc tangent of the value
     */
    static FORCEINLINE float
    atan(float Value) {
      return std::atanf(Value);
    }

    /**
     * @brief Hyperbolic cosine function
     * @param Float value to get hyperbolic cosine
     * @return Hyperbolic cosine of the value
     */
    static FORCEINLINE float
    cosh(float Value) {
      return std::coshf(Value);
    }

    /**
     * @brief Hyperbolic sine function
     * @param Float value to get hyperbolic sine
     * @return Hyperbolic sine of the value
     */
    static FORCEINLINE float
    sinh(float Value) {
      return std::sinhf(Value);
    }

    /**
     * @brief Hyperbolic tangent function
     * @param Float value to get hyperbolic tangent
     * @return Hyperbolic tangent of the value
     */
    static FORCEINLINE float
    tanh(float Value) {
      return std::tanhf(Value);
    }

    /**
     * @brief Hyperbolic arc cosine function
     * @param Float value to get hyperbolic arc cosine
     * @return Hyperbolic arc cosine of the value
     */
    static FORCEINLINE float
    acosh(float Value) {
      return std::acoshf(Value);
    }

    /**
     * @brief Hyperbolic arc sine function
     * @param Float value to get hyperbolic arc sine
     * @return Hyperbolic arc sine of the value
     */
    static FORCEINLINE float
    asinh(float Value) {
      return std::asinhf(Value);
    }

    /**
     * @brief Hyperbolic arc tangent function
     * @param Float value to get hyperbolic arc tangent
     * @return Hyperbolic arc tangent of the value
     */
    static FORCEINLINE float
    atanh(float Value) {
      return std::atanhf(Value);
    }

    /**
     * @brief Cotangent function
     * @param Float value to get the cotangent
     * @return Cotangent of the value
     */
    static FORCEINLINE float
    cot(float value) {
      return 1 / tan( value );
    }

    /**
     * @brief Exponential function
     * @param Float value of the exponent
     * @return Exponential value of the value
     */
    static FORCEINLINE float
    exp(float Value) {
      return std::expf(Value);
    }

    /**
     * @brief Natural logarithm function
     * @param Float value whose logarithm is calculated
     * @return Natural logarithm of the value
     */
    static FORCEINLINE float
    log(float Value) {
      return std::logf(Value);
    }

    /**
     * @brief Common logarithm function
     * @param Float value whose logarithm is calculated
     * @return Return common logarithm of the value
     */
    static FORCEINLINE float
    log10(float Value) {
      return std::log10f(Value);
    }

    /**
     * @brief Power function
     * @param Float base value
     * @param Float exponent value
     * @return Return base value raised to the exponent value
     */
    static FORCEINLINE float
    pow(float Value, float Exponent) {
      return std::powf(Value, Exponent);
    }

    /**
     * @brief Square function
     * @param Float value whose square is calculated.
     * @return Return the square of the value
     */
     static FORCEINLINE float
     sqrt(float Value) {
       return std::sqrt(Value);
     }

     /**
      * @brief Round up the value 
      * @param Float value to round up
      * @return Round up of the value
      */
     static FORCEINLINE float
     ceil(float Value) {
       return std::ceilf(Value);
     }

     /**
      * @brief Round down the value 
      * @param Float value to round down
      * @return The value rounded downwards
      */
     static FORCEINLINE float
     floor(float Value) {
       return std::floorf(Value);
     }

     /**
      * @brief 
      */
     static FORCEINLINE float
     trunc(float Value) {
       return std::truncf(Value);
     }

     /**
      * @brief Round the value to the nearest
      * @param Float value to round
      * @return The rounded value
      */
     static FORCEINLINE float
     round(float Value) {
       return std::roundf(Value);
     }
     
     /**
      * @brief Maximum value between 2 values
      * @param Float Value 1
      * @param Float Value 2
      * @return The maximum value
      */
     static FORCEINLINE float
     max(float Value1, float Value2 ) {
       return std::fmaxf(Value1, Value2);
     }

     /**
      * @brief Minimum value between 2 values
      * @param Float value 1
      * @param Float value 2
      * @return The minimum value
      */
     static FORCEINLINE float
     min(float Value1, float Value2) {
       return std::fminf(Value1, Value2);
     }

     /**
      * @brief Lerp function between 2 Values and a Scale
      * @param Float value 1
      * @param Float value 2
      * @param Float scale value of the lerp
      * @return Lerp value
      */
     static FORCEINLINE float
     lerp( float ValueA, float ValueB, float Scale) {
       return (ValueA * (1.0f - Scale)) + (ValueB * Scale);
     }

     /**
      * @brief Compute the absolute value
      * @param Float Value whose absolute value is returned
      * @return The absolute value
      */
     template<typename T>
     static T abs( T Value) {
       return std::abs(Value);
     }

  };
}
