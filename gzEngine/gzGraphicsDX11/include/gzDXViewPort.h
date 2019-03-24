/**************************************************************************/
/* @filename gzDXViewPort.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/
#pragma once

#include "gzDXPrerequisites.h"
#include <gzViewPort.h>

namespace gzEngineSDK {
class DXViewPort : public ViewPort
{
 public:
   
  /**
   * @brief default constructor
   */
  DXViewPort();
	
  /**
   * @brief default destructor
   */
  ~DXViewPort() = default;
	
  /************************************************************************/
  /* ViewPort functions                                                   */
  /************************************************************************/
	
  /**
   * @brief Sets the ViewPort
   */
  void
  SetViewPort( VIEWPORT_DESCRIPTOR viewportDesc );

  /**
   * @brief Gets the ViewPort interface
   */
  FORCEINLINE D3D11_VIEWPORT
  getVewPortDesc() {
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
