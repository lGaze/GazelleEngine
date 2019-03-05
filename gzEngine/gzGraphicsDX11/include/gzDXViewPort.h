/**************************************************************************/
/* @filename gzDXViewPort.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/
#pragma once

#include "gzDXPrerequisites.h"

namespace gzEngineSDK {
class ViewPort
{
 public:
   
  /**
   * @brief default constructor
   */
  ViewPort() = default;
	
  /**
   * @brief default destructor
   */
  ~ViewPort() = default;
	
  /************************************************************************/
  /* ViewPort functions                                                   */
  /************************************************************************/
	
  /**
   * @brief Sets the ViewPort
   */
  void
  SetViewPort( uint32 width, uint32 height );

  /**
   * @brief Gets the ViewPort interface
   */
  FORCEINLINE D3D11_VIEWPORT
  getVewPortInterface() {
    return m_ViewPort;
  }

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
	
 private:

   /**
    * @brief Viewport Structure
    */
   D3D11_VIEWPORT m_ViewPort;

 };
}
