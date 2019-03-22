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
  DXDepth::CreateDepthStencilViewDesc( D3D11_TEXTURE2D_DESC descDepth )
  {
    ZeroMemory( &m_DescDSV, sizeof( m_DescDSV ) );
    m_DescDSV.Format = descDepth.Format;
    m_DescDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    m_DescDSV.Texture2D.MipSlice = 0;
  }


}