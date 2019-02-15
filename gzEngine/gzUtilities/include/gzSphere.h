/**************************************************************************/
/* @filename gzSphere.h
/* @author Victor Flores 
/* @date 2019/02/15
/* @brief 
/**************************************************************************/

#pragma once

#include "gzPrerequisitesUtilities.h"
#include "gzVector3f.h"

namespace gzEngineSDK {
  class GZ_UTILITY_EXPORT Sphere
  {
   public:
   
    /**
     * @brief default constructor
     */
    Sphere() = default;
	
    /**
     * @brief Constructor with position and radius parameters
     * @param Vector3 center position of the object
     * @param Float radius value of the object
     */
    Sphere(const Vector3f& position, float radius);

    /**
     * @brief default destructor
     */
    ~Sphere() = default;

    /************************************************************************/
    /* Sphere functions                                                     */
    /************************************************************************/

    /************************************************************************/
    /* Member declarations                                                  */
    /************************************************************************/

   public:

    /**
     * @brief 
     */
    float radiusSize;

    /**
     * @brief 
     */
    Vector3f centerPos;

  };
}
