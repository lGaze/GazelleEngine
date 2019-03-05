/**************************************************************************/
/* @filename gzDXBuffer.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/
#pragma once

#include "gzDXPrerequisites.h"

namespace gzEngineSDK {
class Buffer
{
 public:
   
  /**
   * @brief default constructor
   */
  Buffer();
	
  /**
   * @brief default destructor
   */
  ~Buffer() = default;
	
  /************************************************************************/
  /* Buffer functions                                                    */
  /************************************************************************/
	
  /**
   * @brief Create a Description for the buffer
   */
  void
  CreateBufferDesc( uint32 usage,
                    uint32 bytewidth,
                    uint32 buffertype,
                    uint32 cpuflags );

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

  /**
   * @brief 
   */
  D3D11_USAGE m_Usage;

  /**
   * @brief
   */
  D3D11_BIND_FLAG m_BindFlag;

   
 };
}