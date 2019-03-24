/**************************************************************************/
/* @filename gzDXDepth.cpp
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/*************************************************************************/

#include "gzDXDepth.h"

namespace gzEngineSDK {
  
  DXDepth::DXDepth(): m_pDepthStencil(nullptr),
                      m_pDepthStencilView(nullptr) {}

  void 
  DXDepth::CreateDepthStencilViewDesc( DEPTH_STENCIL_VIEW_DESCRIPTOR &descDepth )
  {
    ZeroMemory( &m_DescDSV, sizeof( m_DescDSV ) );
    m_DescDSV.Format = static_cast< DXGI_FORMAT >( descDepth.Format );
    m_DescDSV.ViewDimension = 
      static_cast< D3D11_DSV_DIMENSION > ( descDepth.ViewDimension );
    //TODO: Fix this
    m_DescDSV.Texture2D.MipSlice = 0;
  }


}