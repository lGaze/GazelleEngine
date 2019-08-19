/**************************************************************************/
/* @filename gzBox2D.h
/* @author Victor Flores 
/* @date 2019/02/15
/* @brief This file can be used for create 2D Boxes
/**************************************************************************/

#pragma once

#include "gzPrerequisitesUtilities.h"
#include "gzVector2f.h"

namespace gzEngineSDK {
  class GZ_UTILITY_EXPORT Box2D
  {
   public:
   
    /**
     * @brief Default constructor.
     */
    Box2D() = default;

    /**
     * @brief This constructor generate a 2D box with the given center, width and height.
     * @param Vector2f wich indicates the given center of the 2D Box.
     * @param Float value wich indicates the given height of the 2D Box.
     * @param Floar value wich inicates the given width of the 2D Box.
     */
    Box2D(const Vector2f& centerPos, const float height, const float width);

    /**
     * @brief Default destructor.
     */
    ~Box2D() = default;

    /************************************************************************/
    /* Box2D functions                                                      */
    /************************************************************************/

    /************************************************************************/
    /* Member declarations                                                  */
    /************************************************************************/

   public:

     /**
      * @brief Indicates the center of the Box
      */
     Vector2f boxCenter;

     /**
      * @brief Indicates the Height of the Box
      */
     float boxHeight;

     /**
      * @brief Indicates the Width of the Box
      */
     float boxWidth;
   
  };
}
