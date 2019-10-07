/**************************************************************************/
/* @filename gzRenderer.h
/* @author Victor Flores 
/* @date 2019/08/07
/* @brief  This file works as an interface for rederers 
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
  render(int32 renderTarget, float clearColor[4]) = 0;

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 public:
   
 };
}
