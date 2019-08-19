/**************************************************************************/
/* @filename gzTriangle.h
/* @author Victor Flores 
/* @date 2019/02/15
/* @brief This file can be used for create Triangles
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
     * @brief This constructor generates a Triangle with the given values
     * @param Vector3f wich indicates the position of the 1° vertex
     * @param Vector3f wich indicates the position of the 2° vertex
     * @param Vector3f wich indicates the position of the 3° vertex
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
     * @brief Positon of the 1° Vertex
     */
    Vector3f triangleVert1;    
    
    /**
     * @brief Positon of the 2° Vertex
     */
    Vector3f triangleVert2;   
    
    /**
     * @brief Positon of the 3° Vertex
     */
    Vector3f triangleVert3;

  };
}