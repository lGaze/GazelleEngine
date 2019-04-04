/**************************************************************************/
/* @filename gzDXTexture.cpp
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#include "gzDXPrerequisites.h"
#include "..\include\gzDXTexture.h"
#include "gzGraphicsManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace gzEngineSDK {

  DXTexture::DXTexture() : m_ptex(nullptr), m_pTextureRV(nullptr) { }

  void 
  DXTexture::create2DTextueDescriptor( TEXTURE2D_DESCRIPTOR &desc )
  {
    ZeroMemory( &m_texDesc, sizeof( m_texDesc ) );
    m_texDesc.Width = desc.Width;
    m_texDesc.Height = desc.Height;
    m_texDesc.MipLevels = desc.MipLevels;
    m_texDesc.ArraySize = desc.ArraySize;
    m_texDesc.Format = static_cast< DXGI_FORMAT >( desc.Format );
    m_texDesc.SampleDesc.Count = 1;
    m_texDesc.SampleDesc.Quality = 0;
    m_texDesc.Usage = static_cast< D3D11_USAGE >( desc.Usage );                                  
    m_texDesc.BindFlags = static_cast < D3D11_BIND_FLAG > ( desc.BindFlags );
    m_texDesc.CPUAccessFlags = desc.CPUAccessFlags;
    m_texDesc.MiscFlags = desc.MiscFlags;

  }

  void 
  DXTexture::createShaderResurceDescriptor( SHADER_RESOURCE_VIEW_DESC & desc )
  {
    memset( &m_srvDesc, 0, sizeof( m_srvDesc ) );

    m_srvDesc.Format = static_cast< DXGI_FORMAT>(desc.Format);
    m_srvDesc.ViewDimension = static_cast< D3D11_SRV_DIMENSION >( desc.ViewDimension );
    
  }

  void
  DXTexture::LoadTexture( const String filename )
  {
    ZeroMemory( &m_texDesc, sizeof( m_texDesc ) );

    int32 Width = 0;
    int32 Height = 0;
    int32 Channels = 0;
    
    unsigned char * tempInfo = stbi_load( filename.c_str(), 
                                          &Width, 
                                          &Height, 
                                          &Channels, 4 );

    m_texDesc.Width = Width;
    m_texDesc.Height = Height;
    m_texDesc.MipLevels = 1;
    m_texDesc.ArraySize = 1;
    m_texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    m_texDesc.SampleDesc.Count = 1;
    m_texDesc.SampleDesc.Quality = 0;
    m_texDesc.Usage = D3D11_USAGE_DEFAULT;
    m_texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    m_texDesc.CPUAccessFlags = 0;
    m_texDesc.MiscFlags = 0;

    memset( &initBuffer, 0, sizeof( initBuffer ) );
    initBuffer.pSysMem = tempInfo;
    initBuffer.SysMemPitch = Width * 4;

  }

}