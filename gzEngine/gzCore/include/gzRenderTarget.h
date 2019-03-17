/**************************************************************************/
/* @filename gzRenderTarget.h
/* @author Victor Flores 
/* @date 2019/03/16
/* @brief 
/**************************************************************************/

#pragma once

#include "gzPrerequisitesCore.h"


namespace gzEngineSDK {
class GZ_CORE_EXPORT RenderTarget
{
 public:
   
  /**
   * @brief default constructor
   */
  RenderTarget() = default;
	
  /**
   * @brief default destructor
   */
  virtual 
  ~RenderTarget() = default;
	
  /************************************************************************/
  /* RenderTarget functions                                               */
  /************************************************************************/
	
  /**
   * @brief This function creates a new RederTarget
   */
  virtual bool
  createRenderTarget() = 0;

  /**
   * @brief This function creates a Render target for backBuffer
   */
  virtual bool
  createBackBuffer() = 0;

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
	
 public:
   
 };
}