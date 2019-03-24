/**************************************************************************/
/* @filename gzDXViewPort.cpp
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#include "gzDXViewPort.h"

namespace gzEngineSDK {

  DXViewPort::DXViewPort()
  {
    ZeroMemory( &m_ViewPort, sizeof( m_ViewPort ) );
  }

  void
  DXViewPort::SetViewPort( VIEWPORT_DESCRIPTOR viewportDesc )
  {
    m_ViewPort.Width    = viewportDesc.Width;
    m_ViewPort.Height   = viewportDesc.Height;
    m_ViewPort.MinDepth = viewportDesc.MinDepth;
    m_ViewPort.MaxDepth = viewportDesc.MaxDepth;
    m_ViewPort.TopLeftX = viewportDesc.TopLeftX;
    m_ViewPort.TopLeftY = viewportDesc.TopLeftY;
  }
}