/**************************************************************************/
/* @filename gzDXBuffer.cpp
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/*************************************************************************/

#include "gzDXBuffer.h"

namespace gzEngineSDK {

  Buffer::Buffer() : m_pBuffer(nullptr) { }

  void 
  Buffer::CreateBufferDesc( uint32 usage,
                            uint32 bytewidth,
                            uint32 buffertype,
                            uint32 cpuflags )
  {

    ZeroMemory( &m_BufferDesc, sizeof( m_BufferDesc ) );
    m_Usage = static_cast< D3D11_USAGE >( usage );
    m_BindFlag = static_cast< D3D11_BIND_FLAG >( buffertype );

    m_BufferDesc.Usage = m_Usage;
    m_BufferDesc.ByteWidth = bytewidth;
    m_BufferDesc.BindFlags = m_BindFlag;
    m_BufferDesc.CPUAccessFlags = cpuflags;
    m_BufferDesc.MiscFlags = 0;

  }
}