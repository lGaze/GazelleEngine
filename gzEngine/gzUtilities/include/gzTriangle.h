/**************************************************************************/
/* @filename gzTriangle.h
/* @author Victor Flores 
/* @date 2019/02/15
/* @brief 
/**************************************************************************/

#pragma once

#include "gzPrerequisitesUtilities.h"
#include "gzVector3f.h"

namespace gzEngineSDK {
  class GZ_UTILITY_EXPORT Triangle
  {
   public:
   
    /**
     * @brief default constructor
     */
    Triangle() = default;
	  
    /**
     * @brief 
     */
    Triangle(const Vector3f& vertex1, const Vector3f& vertex2, const Vector3f& vertex3);

    /**
     * @brief default destructor
     */
    ~Triangle() = default;
	
	  /************************************************************************/
    /* Triangle functions                                                   */
    /************************************************************************/
	
	  /************************************************************************/
    /* Member declarations                                                  */
    /************************************************************************/
	
   public:

    /**
     * @brief 
     */
    Vector3f triangleVert1;    
    
    /**
     * @brief 
     */
    Vector3f triangleVert2;   
    
    /**
     * @brief 
     */
    Vector3f triangleVert3;

  };
}