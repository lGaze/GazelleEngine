/**************************************************************************/
/* @filename gzDXBuffer.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/
#pragma once

#include "gzDXPrerequisites.h"
#include <gzBuffer.h>

namespace gzEngineSDK {
class DXBuffer : public Buffer
{
 public:
   
  /**
   * @brief default constructor
   */
  DXBuffer();
	
  /**
   * @brief default destructor
   */
  ~DXBuffer() = default;
	
  /************************************************************************/
  /* Buffer functions                                                    */
  /************************************************************************/
	
  /**
   * @brief Create a Description for the buffer
   */
  void
  CreateBufferDesc( BUFFER_DESCRIPTOR &bufferDesc );

  /**
   * @brief Gets the buffer interface
   */
  FORCEINLINE ID3D11Buffer**
  getBufferInterface() {
    return &m_pBuffer;
  }

  /**
   * @brief Gets the buffer description
   */
  FORCEINLINE D3D11_BUFFER_DESC
  getBufferDesc() {
    return m_BufferDesc;
  }

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
	
 private:

  /**
   * @brief Buffer description
   */
  D3D11_BUFFER_DESC m_BufferDesc;

  /**
   * @brief Buffer interface
   */
  ID3D11Buffer* m_pBuffer;
   
 };
}