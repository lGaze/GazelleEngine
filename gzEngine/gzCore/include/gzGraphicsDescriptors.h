/**************************************************************************/
/* @filename gzGraphicsDescriptors.h
/* @author Victor Flores 
/* @date 2019/03/17
/* @brief 
/**************************************************************************/

#pragma once

#include "gzPrerequisitesCore.h"

namespace gzEngineSDK {

struct TEXTURE2D_DESCRIPTOR
{
  uint32 Width;
  uint32 Height;
  uint32 MipLevels;
  uint32 ArraySize;
  uint32 Format;
  //DXGI_SAMPLE_DESC SampleDesc;
  uint32 Usage;
  uint32 BindFlags;
  uint32 CPUAccessFlags;
  uint32 MiscFlags;
};

struct DEPTH_STENCIL_VIEW_DESCRIPTOR
{
  uint32 Format;
  uint32 ViewDimension;
  uint32 Flags;
};

struct VIEWPORT_DESCRIPTOR
{
  float TopLeftX;
  float TopLeftY;
  float Width;
  float Height;
  float MinDepth;
  float MaxDepth;
};


enum TEXTURE_FORMATS
{
  FORMAT_UNKNOWN           = 0,
  FORMAT_D24_UNORM_S8_UINT = 45,

};

enum USAGES
{
  USAGE_DEFAULT   = 0,
  USAGE_IMMUTABLE = 1,
  USAGE_DYNAMIC   = 2,
  USAGE_STAGING   = 3

};

enum BIND_FLAGS
{
  BIND_VERTEX_BUFFER    = 1,
  BIND_INDEX_BUFFER     = 2,
  BIND_CONSTANT_BUFFER  = 4,
  BIND_SHADER_RESOURCE  = 8,
  BIND_STREAM_OUTPUT    = 16,
  BIND_RENDER_TARGET    = 32,
  BIND_DEPTH_STENCIL    = 64,
  BIND_UNORDERED_ACCESS = 128

};

enum DSV_DIMENSIONS
{
  DSV_DIMENSION_UNKNOWN          = 0,
  DSV_DIMENSION_TEXTURE1D        = 1,
  DSV_DIMENSION_TEXTURE1DARRAY   = 2,
  DSV_DIMENSION_TEXTURE2D        = 3,
  DSV_DIMENSION_TEXTURE2DARRAY   = 4,
  DSV_DIMENSION_TEXTURE2DMS      = 5,
  DSV_DIMENSION_TEXTURE2DMSARRAY = 6

};

enum CLEAR_DSV_FLAGS
{
  CLEAR_DEPTH   = 1,
  CLEAR_STENCIL = 2
};


}