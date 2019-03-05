/**************************************************************************/
/* @filename gzDXDeviceContext.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#pragma once

#include "gzDXPrerequisites.h"

namespace gzEngineSDK {
class DeviceContext
{
 public:
   
  /**
   * @brief default constructor
   */
   DeviceContext();
	
  /**
   * @brief default destructor
   */
  ~ DeviceContext() = default;
	
  /************************************************************************/
  /*  DeviceContext functions                                             */
  /************************************************************************/
	
  /**
   * @brief 
   */
  FORCEINLINE ID3D11DeviceContext**
  getDeviceContextInterface() {
    return &m_pDeviceContext;
  };

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
	
 private:
   
   /**
    * @brief DeviceContext interface
    */
   ID3D11DeviceContext* m_pDeviceContext;

   D3D11_PRIMITIVE_TOPOLOGY m_Topology;
   
 };
}
