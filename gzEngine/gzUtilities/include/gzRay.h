/***************************************************************************/
/* @filename gzRay.h
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
    Ray(const Vector3f& originPos, const Vector3f& direction);

    /**
     * @brief Default destructor
     */
    ~Ray() = default;

    /************************************************************************/
    /* Ray functions                                                        */
    /************************************************************************/
    

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