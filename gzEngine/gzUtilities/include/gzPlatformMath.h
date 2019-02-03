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
  };
}
