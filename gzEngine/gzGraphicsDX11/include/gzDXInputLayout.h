/**************************************************************************/
/* @filename gzDXInputLayout.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/
#pragma once

#include "gzDXPrerequisites.h"
#include <gzInputLayout.h>

namespace gzEngineSDK {
class DXInputLayout : public InputLayout
{
 public:
   
  /**
   * @brief default constructor
   */
   DXInputLayout();
	
  /**
   * @brief default destructor
   */
  ~DXInputLayout() = default;
	
  /************************************************************************/
  /* InputLayout functions                                                */
  /************************************************************************/

  /**
   * @brief 
   */
  void
  CreateInputLayout( ID3DBlob * pblob );


  /**
   * @brief Gets the InputLayout Interface
   */
  FORCEINLINE ID3D11InputLayout**
  getInputLayputInterface() {
    return &m_pInputlayout;
  }

  /**
   * @brief 
   */
  FORCEINLINE D3D11_INPUT_ELEMENT_DESC *
  getInputLayoutDesc() {
    return m_pInputLayoutDescArray;
  }

  /**
   * @brief 
   */
  FORCEINLINE uint32
  getnumElem() {
    return m_numElem;
  }

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
	
 private:

  /**
   * @brief InputLayout interface
   */
  ID3D11InputLayout* m_pInputlayout;

  /**
   * @brief 
   */
  D3D11_INPUT_ELEMENT_DESC * m_pInputLayoutDescArray;

  /**
   * @brief 
   */
  uint32 m_numElem;
   
 };
}
