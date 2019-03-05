/**************************************************************************/
/* @filename gzDXTexture.cpp
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#include "gzDXPrerequisites.h"
#include "..\include\gzDXTexture.h"

namespace gzEngineSDK {

  Texture::Texture()
  {
    m_ptex = nullptr;
  }
  void 
  Texture::CreateTextureDesc( uint32 width, 
                              uint32 height, 
                              uint32 format, 
                              uint32 usage )
  {
    m_format = ( DXGI_FORMAT ) format;
    m_usage = ( D3D11_USAGE ) usage;

    m_desc.Width = width;
    m_desc.Height = height;
    m_desc.MipLevels = 1;
    m_desc.ArraySize = 1;
    m_desc.Format = m_format;
    m_desc.SampleDesc.Count = 1;
    m_desc.SampleDesc.Quality = 0;
    m_desc.Usage = m_usage;
    m_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    m_desc.CPUAccessFlags = 0;
    m_desc.MiscFlags = 0;
  }
}