/****************************************************************************
/* @filename gzPlatformMath
/* @author Gazelle
/* @date 2019/02/05
/* @brief 
/*****************************************************************************/
#pragma once

#include "gzPrerequisitesUtilities.h"
#include <cmath>

namespace gzEngineSDK {
  class GZ_UTILITY_EXPORT PlatformMath
  {
   public:

    PlatformMath() = default;
    ~PlatformMath() = default;

    /************************************************************************/
    /* Trigonometric Functions.                                             */
    /************************************************************************/

    /**
     * @brief 
     */
    static FORCEINLINE float
    cos(float Value) {
      return std::cosf(Value);
    }
    
    /**
     * @brief 
     */
    static FORCEINLINE float
    sin(float Value) {
      return std::sinf(Value);
    }

    /**
     * @brief 
     */
    static FORCEINLINE float
    tan(float Value) {
      return std::tanf(Value);
    }

    /**
     * @brief 
     */
    static FORCEINLINE float
    acos(float Value) {
      return std::acosf(Value);
    }

    /**
     * @brief 
     */
    static FORCEINLINE float
    asin(float Value) {
      return std::asinf(Value);
    }

    /**
     * @brief 
     */
    static FORCEINLINE float
    atan(float Value) {
      return std::atanf(Value);
    }

    /************************************************************************/
    /* Hyperbolic Functions.                                                */
    /************************************************************************/

    /**
     * @brief 
     */
    static FORCEINLINE float
    cosh(float Value) {
      return std::coshf(Value);
    }

    /**
     * @brief 
     */
    static FORCEINLINE float
    sinh(float Value) {
      return std::sinhf(Value);
    }

    /**
     * @brief 
     */
    static FORCEINLINE float
    tanh(float Value) {
      return std::tanhf(Value);
    }

    /**
     * @brief 
     */
    static FORCEINLINE float
    acosh(float Value) {
      return std::acoshf(Value);
    }

    /**
     * @brief 
     */
    static FORCEINLINE float
    asinh(float Value) {
      return std::asinhf(Value);
    }

    /**
     * @brief 
     */
    static FORCEINLINE float
    atanh(float Value) {
      return std::atanhf(Value);
    }

    /************************************************************************/
    /* Exponential and Logarithmic functions                                */
    /************************************************************************/

    /**
     * @brief 
     */
    static FORCEINLINE float
    exp(float Value) {
      return std::expf(Value);
    }

    /**
     * @brief 
     */
    static FORCEINLINE float
    log(float Value) {
      return std::logf(Value);
    }

    /**
     * @brief 
     */
    static FORCEINLINE float
    log10(float Value) {
      return std::log10f(Value);
    }

    /************************************************************************/
    /* Power functions                                                      */
    /************************************************************************/

    /**
     * @brief 
     */
    static FORCEINLINE float
    pow(float Value, float Exponent) {
      return std::powf(Value, Exponent);
    }

    /**
     * @brief 
     */
     static FORCEINLINE float
     sqrt(float Value) {
       return std::sqrt(Value);
     }

     /************************************************************************/
     /* Rounding functions                                                   */
     /************************************************************************/

     /**
      * @brief 
      */
     static FORCEINLINE float
     ceil(float Value) {
       return std::ceilf(Value);
     }

     /**
      * @brief 
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
      * @brief 
      */
     static FORCEINLINE float
     round(float Value) {
       return std::roundf(Value);
     }

     /************************************************************************/
     /* Minimum and Maximum functions                                        */
     /************************************************************************/
     
     /**
      * @brief 
      */
     static FORCEINLINE float
     max(float Value1, float Value2 ) {
       return std::fmaxf(Value1, Value2);
     }

     /**
      * @brief 
      */
     static FORCEINLINE float
     min(float Value1, float Value2) {
     return std::fminf(Value1, Value2);
     }

  };
}
