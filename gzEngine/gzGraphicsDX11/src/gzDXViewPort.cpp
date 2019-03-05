/**************************************************************************/
/* @filename gzDXViewPort.cpp
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#include "gzDXViewPort.h"

namespace gzEngineSDK {

  void
  ViewPort::SetViewPort( uint32 width, uint32 height )
  {
    m_ViewPort.Width = ( FLOAT ) width;
    m_ViewPort.Height = ( FLOAT ) height;
    m_ViewPort.MinDepth = 0.0f;
    m_ViewPort.MaxDepth = 1.0f;
    m_ViewPort.TopLeftX = 0;
    m_ViewPort.TopLeftY = 0;
  }
}