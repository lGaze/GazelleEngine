/**************************************************************************/
/* @filename gzSphere.h
/* @author Victor Flores 
/* @date 2019/02/15
/* @brief This file can be used for create spheres 
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
     * @brief The radius size of the sphere
     */
    float radiusSize;

    /**
     * @brief The center Position of the sphere
     */
    Vector3f centerPos;

  };
}
