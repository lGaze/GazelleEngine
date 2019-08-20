/**************************************************************************/
/* @filename gzResource.h
/* @author Victor Flores 
/* @date 2019/07/19
/* @brief Resources header file
/**************************************************************************/
#pragma once

#include "gzPrerequisitesCore.h"

namespace gzEngineSDK {
class GZ_CORE_EXPORT Resource
{
 public:
   
  /**
   * @brief default constructor
   */
  Resource() = default;

  /**
   * @brief default destructor
   */
  virtual
  ~Resource() = default;

  /************************************************************************/
  /* Resource functions                                                   */
  /************************************************************************/

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 public:

   String name;
   
 };
}
