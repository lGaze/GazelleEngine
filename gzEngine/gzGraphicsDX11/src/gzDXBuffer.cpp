/**************************************************************************/
/* @filename gzDXBuffer.cpp
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/*************************************************************************/

#include "gzDXBuffer.h"

namespace gzEngineSDK {

  DXBuffer::DXBuffer() : m_pBuffer(nullptr) { }

  void 
  DXBuffer::CreateBufferDesc( BUFFER_DESCRIPTOR &bufferDesc )
  {

    ZeroMemory( &m_BufferDesc, sizeof( m_BufferDesc ) );

    m_BufferDesc.Usage = static_cast< D3D11_USAGE >( bufferDesc.Usage );
    m_BufferDesc.ByteWidth = bufferDesc.ByteWidth;
    m_BufferDesc.BindFlags = bufferDesc.BindFlags;
    m_BufferDesc.CPUAccessFlags = bufferDesc.CPUAccessFlags;
    m_BufferDesc.MiscFlags = bufferDesc.MiscFlags;

  }
}