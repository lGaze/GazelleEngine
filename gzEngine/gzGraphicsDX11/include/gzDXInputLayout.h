/**************************************************************************/
/* @filename gzDXInputLayout.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/
#pragma once

#include "gzDXPrerequisites.h"

namespace gzEngineSDK {
class InputLayout
{
 public:
   
  /**
   * @brief default constructor
   */
   InputLayout();
	
  /**
   * @brief default destructor
   */
  ~InputLayout() = default;
	
  /************************************************************************/
  /* InputLayout functions                                                */
  /************************************************************************/
  
  /**
   * @brief Pushes the description to te vector of descriptions
   */
  void
  AddToLayout( INPUT_LAYOUT_DESCRIPTOR &inputLayoutDesc );

  /**
   * @brief Gets the InputLayout Interface
   */
  FORCEINLINE ID3D11InputLayout**
  getInputLayputInterface() {
    return &m_pInputlayout;
  }

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
	
 private:

  /**
   * @brief InputLayout interface
   */
  ID3D11InputLayout* m_pInputlayout;

 public:
  /**
   * @brief Vector with all the descriptions of the InputLayout
   */
  std::vector<D3D11_INPUT_ELEMENT_DESC> m_vLayout;
   
 };
}
