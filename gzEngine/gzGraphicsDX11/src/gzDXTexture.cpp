/**************************************************************************/
/* @filename gzDXTexture.cpp
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#include "gzDXPrerequisites.h"
#include "..\include\gzDXTexture.h"

namespace gzEngineSDK {

  DXTexture::DXTexture() : m_ptex(nullptr)
  {
    ZeroMemory( &m_desc, sizeof( m_desc ) );
  }

  void 
  DXTexture::create2DTextueDescriptor( TEXTURE2D_DESCRIPTOR &desc )
  {

    m_desc.Width = desc.Width;
    m_desc.Height = desc.Height;
    m_desc.MipLevels = desc.MipLevels;
    m_desc.ArraySize = desc.ArraySize;
    m_desc.Format = static_cast< DXGI_FORMAT >( desc.Format );
    m_desc.SampleDesc.Count = 1;
    m_desc.SampleDesc.Quality = 0;
    m_desc.Usage = static_cast< D3D11_USAGE >( desc.Usage );
    m_desc.BindFlags = static_cast < D3D11_BIND_FLAG > ( desc.BindFlags );
    m_desc.CPUAccessFlags = desc.CPUAccessFlags;
    m_desc.MiscFlags = desc.MiscFlags;

  }

}