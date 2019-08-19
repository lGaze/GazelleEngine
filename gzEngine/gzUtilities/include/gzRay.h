/***************************************************************************/
/* @filename gzRay.h
/* @author Victor Flores
/* @date 2019/02/15
/* @brief This file can be used for create Rays
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
     * @brief This Constructor generates a Ray from the given values
     * @param Vector3f wich indicates the given origin position of the ray
     * @param Vector3f wich indicates the given direction of the ray 
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
      * @brief The origin position of th ray
      */
    Vector3f originPos;

     /**
      * @brief The direction of the ray 
      */
    Vector3f direction;
  };
}