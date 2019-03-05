/**************************************************************************/
/* @filename gzDXSamplerState.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/
#pragma once

#include "gzDXPrerequisites.h"

namespace gzEngineSDK {
class SamplerState
{
 public:
   
  /**
   * @brief default constructor
   */
  SamplerState();
	
  /**
   * @brief default destructor
   */
  ~SamplerState() = default;
	
  /************************************************************************/
  /* SamplerState functions                                               */
  /************************************************************************/
	
  /**
   * @brief Creates Sampler description
   */
  void
  CreateSamplerDesc();

  /**
   * @brief Gets the sampler description
   */
  FORCEINLINE D3D11_SAMPLER_DESC
  getSamplerDesc() {
    return m_SamplerDesc;
  }

  /**
   * @brief Gets the sampler interface
   */
  FORCEINLINE ID3D11SamplerState**
  getSamplerInterface() {
    return &m_pSamplerLinear;
  }

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

	
 private:
   
   /**
    * @brief 
    */
   D3D11_SAMPLER_DESC m_SamplerDesc;

   /**
    * @brief 
    */
   ID3D11SamplerState * m_pSamplerLinear;

 };
}