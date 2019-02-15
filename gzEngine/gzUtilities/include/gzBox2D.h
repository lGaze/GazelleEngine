/**************************************************************************/
/* @filename gzBox2D.h
/* @author Victor Flores 
/* @date 2019/02/15
/* @brief 
/**************************************************************************/

#pragma once

#include "gzPrerequisitesUtilities.h"
#include "gzVector2f.h"

namespace gzEngineSDK {
  class GZ_UTILITY_EXPORT Box2D
  {
   public:
   
    /**
     * @brief default constructor
     */
    Box2D() = default;

    /**
     * @brief 
     */
    Box2D(const Vector2f& centerPos, const float height, const float width);
	
    /**
     * @brief default destructor
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
     * @brief 
     */
     Vector2f boxCenter;

     /**
      * @brief 
      */
     float boxHeight;

     /**
      * @brief 
      */
     float boxWidth;
   
  };
}
