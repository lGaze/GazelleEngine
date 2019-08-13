/**************************************************************************/
/* @filename gzRenderer.h
/* @author Victor Flores 
/* @date 2019/08/07
/* @brief 
/**************************************************************************/
#pragma once

#include "gzPrerequisitesCore.h"
#include <gzModule.h>

namespace gzEngineSDK {
class GZ_CORE_EXPORT Renderer : public Module<Renderer>
{
 public:
   
  /**
   * @brief default constructor
   */
  Renderer() = default;

  /**
   * @brief default destructor
   */
  virtual
  ~Renderer() = default;

  /************************************************************************/
  /* Renderer functions                                                   */
  /************************************************************************/

  virtual void
  render() = 0;

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 public:
   
 };
}
