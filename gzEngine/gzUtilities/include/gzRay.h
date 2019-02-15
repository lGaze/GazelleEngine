/***************************************************************************/
/* @filename gzRay
/* @author Victor Flores
/* @date 2019/02/15
/* @brief 
/***************************************************************************/

#pragma once

#include "gzPrerequisitesUtilities.h"
#include "gzVector3f.h"

namespace gzEngineSDK {
  class GZ_UTILITY_EXPORT Ray
  {
   public:
     /**
      * @brief Default constructor
      */
    Ray() = default;

    /**
     * @brief 
     */
    Ray(const Vector3f& OriginPos, const Vector3f& Direction);

    /**
     * @brief Default destructor
     */
    ~Ray() = default;

    /************************************************************************/
    /* Member declaration                                                   */
    /************************************************************************/
   public:

     /**
      * @brief 
      */
     Vector3f originPos;

     /**
      * @brief 
      */
     Vector3f direction;
  };
}