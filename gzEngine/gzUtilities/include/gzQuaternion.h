/**************************************************************************/
/* @filename gzQuaternion.h
/* @author Victor Flores 
/* @date 2019/10/15
/* @brief This file can be used for create and use a Quaternion
/**************************************************************************/
#pragma once

#include "gzPrerequisitesUtilities.h"
#include "gzMath.h"

namespace gzEngineSDK {
class GZ_UTILITY_EXPORT Quaternion
{
 public:
 
  /**
   * @brief default constructor
   */
  Quaternion();

  /**
   * @brief default destructor
   */
  ~Quaternion() = default;

  /************************************************************************/
  /* Quaternion functions                                                 */
  /************************************************************************/

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 public:


  // X value in the Quaternion
  float x;

  // Y value in the Quaternion
  float y;

  // Z value in the Quaternion
  float z;

  // Imaginary value in the Quaternion
  float w;

 };
}
