/**************************************************************************/
/* @filename gzDXTexture.cpp
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#include "gzDXPrerequisites.h"
#include "..\include\gzDXTexture.h"
#include "gzGraphicsManager.h"

namespace gzEngineSDK {

  DXTexture::DXTexture() : m_ptex( nullptr ),
    m_pShaderResourceView( nullptr ),
    m_pDepthStencilView( nullptr ),
    m_pRenderTargetView( nullptr ) 
  {
    memset( &m_initBuffer, 0, sizeof( m_initBuffer ) );
  }

  void
  DXTexture::LoadTexture( const String filename )
  {
    Texture::loadTextureFromFile( filename );

    D3D11_TEXTURE2D_DESC tempTexDesc;
    tempTexDesc.Width = m_Width;
    tempTexDesc.Height = m_Height;
    tempTexDesc.MipLevels = 1;
    tempTexDesc.ArraySize = 1;
    tempTexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    tempTexDesc.SampleDesc.Count = 1;
    tempTexDesc.SampleDesc.Quality = 0;
    tempTexDesc.Usage = D3D11_USAGE_DEFAULT;
    tempTexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    tempTexDesc.CPUAccessFlags = 0;
    tempTexDesc.MiscFlags = 0;

    memset( &m_initBuffer, 0, sizeof( m_initBuffer ) );
    m_initBuffer.pSysMem = &m_textureInfo;
    m_initBuffer.SysMemPitch = m_Width * 4;

  }

}