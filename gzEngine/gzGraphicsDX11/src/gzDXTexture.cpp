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
    m_pRenderTargetView( nullptr )  {}

  void
  DXTexture::LoadTexture( const String filename )
  {
    Texture::loadTextureFromFile( filename );
  }
}