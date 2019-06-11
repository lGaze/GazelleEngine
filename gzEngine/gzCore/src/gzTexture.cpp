/**************************************************************************/
/* @filename gzTexture.cpp
/* @author Victor Flores 
/* @date 2019/03/21
/* @brief 
/**************************************************************************/

#include "gzTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace gzEngineSDK {

  Texture::Texture() { }
  Texture::~Texture() { }

  void 
  Texture::loadTextureFromFile( const String filepath )
  {
    m_Width = 0;
    m_Height = 0;
    m_Channels = 0;

    auto textureInfo = stbi_load( filepath.c_str(),
                                  &m_Width,
                                  &m_Height,
                                  &m_Channels,
                                  4 );

    m_textureInfo.push_back( textureInfo );

  }

}