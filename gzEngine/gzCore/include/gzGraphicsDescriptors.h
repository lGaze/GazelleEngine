/**************************************************************************/
/* @filename gzGraphicsDescriptors.h
/* @author Victor Flores 
/* @date 2019/03/17
/* @brief 
/**************************************************************************/

#pragma once

#include "gzPrerequisitesCore.h"
#include <gzVector3f.h>
#include <gzVector2f.h>
#include <gzVector4f.h>


namespace gzEngineSDK {

struct VERTEX {
    Vector3f position;
    Vector3f normal;
    Vector2f texcoord;
};

struct TEXTURE2D_DESCRIPTOR {
  uint32 Width;
  uint32 Height;
  uint32 MipLevels;
  uint32 ArraySize;
  uint32 Format;
  uint32 Usage;
  uint32 BindFlags;
  uint32 CPUAccessFlags;
  uint32 MiscFlags;
};

struct DEPTH_STENCIL_VIEW_DESCRIPTOR {
  uint32 Format;
  uint32 ViewDimension;
  uint32 Flags;
};

struct SHADER_RESOURCE_VIEW_DESC {
  uint32 Format;
  uint32 ViewDimension;
};

struct RENDER_TARGET_VIEW_DESC {
  uint32 Format;
  uint32 ViewDimension;
};

struct VIEWPORT_DESCRIPTOR {
  float TopLeftX;
  float TopLeftY;
  float Width;
  float Height;
  float MinDepth;
  float MaxDepth;
};

struct BUFFER_DESCRIPTOR {
  uint32 ByteWidth;
  uint32 Usage;
  uint32 BindFlags;
  uint32 CPUAccessFlags = 0;
  uint32 MiscFlags = 0;
  uint32 StructureByteStride;
};

struct SUBRESOUCE_DATA {
  const void *pSysMem;
  uint32 SysMemPitch;
  uint32 SysMemSlicePitch;
};

struct SAMPLER_DESCRIPTOR {
  uint32 Filter;
  uint32 AddressU;
  uint32 AddressY;
  uint32 AddressW;
  float MipLODBias;
  uint32 MaxAnisotropy;
  uint32 ComparisonFunc;
  float BorderColor[4];
  float MinLOD;
  float MaxLOD;
};

struct INPUT_LAYOUT_DESCRIPTOR {
  String * SemanticName;
  uint32 SemanticIndex;
  uint32 Format;
  uint32 InputSlot;
  uint32 AlignedByteOffset;
  uint32 InputSlotClass;
  uint32 InstanceDataStepRate;
};

struct RASTERIZER_DESCRIPTOR {
  int32 FillMode;
  int32 CullMode;
  bool FrontCounterClockWise;
  int32 DepthBias;
  float DepthBiasClamp;
  float SlopeScaledDepthBias;
  bool  DepthClipEnable;
  bool  ScissorEnable;
  bool  MultisampleEnable;
  bool  AntialiasedLineEnable;
};


enum CULL_MODE
{
  CULL_NONE = 1,
  CULL_FRONT = 2,
  CULL_BACK = 3
};

enum FILL_MODE
{
  FILL_WIREFRAME = 2,
  FILL_SOLID = 3
};

enum FORMATS
{
  FORMAT_UNKNOWN           = 0,
  FORMAT_R32G32B32_FLOAT   = 6,
  FORMAT_R16G16B16A16_FLOAT = 10,
  FORMAT_R32G32_FLOAT      = 16,
  FORMAT_D24_UNORM_S8_UINT = 45,
  FORMAT_R32_UINT          = 42,
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
  BIND_VERTEX_BUFFER    = 0x1L, 
  BIND_INDEX_BUFFER     = 0x2L,
  BIND_CONSTANT_BUFFER  = 0x4L,
  BIND_SHADER_RESOURCE  = 0x8L,
  BIND_STREAM_OUTPUT    = 0x10L,
  BIND_RENDER_TARGET    = 0x20L,
  BIND_DEPTH_STENCIL    = 0x40L,
  BIND_UNORDERED_ACCESS = 0x80L

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

enum FILTER
{
  FILTER_MIN_MAG_MIP_POINT                           = 0,
  FILTER_MIN_MAG_POINT_MIP_LINEAR                    = 1,
  FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT              = 4,
  FILTER_MIN_POINT_MAG_MIP_LINEAR                    = 5,
  FILTER_MIN_LINEAR_MAG_MIP_POINT                    = 16,
  FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR             = 17,
  FILTER_MIN_MAG_LINEAR_MIP_POINT                    = 20,
  FILTER_MIN_MAG_MIP_LINEAR                          = 21,
  FILTER_ANISOTROPIC                                 = 85,
  FILTER_COMPARISON_MIN_MAG_MIP_POINT                = 128,
  FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR         = 129,
  FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT   = 132,
  FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR         = 133,
  FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT         = 144,
  FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR  = 145,
  FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT         = 148,
  FILTER_COMPARISON_MIN_MAG_MIP_LINEAR               = 149,
  FILTER_COMPARISON_ANISOTROPIC                      = 213,
  FILTER_MINIMUM_MIN_MAG_MIP_POINT                   = 256,
  FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR            = 257,
  FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT      = 260,
  FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR            = 261,
  FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT            = 272,
  FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR     = 273,
  FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT            = 276,
  FILTER_MINIMUM_MIN_MAG_MIP_LINEAR                  = 277,
  FILTER_MINIMUM_ANISOTROPIC                         = 341,
  FILTER_MAXIMUM_MIN_MAG_MIP_POINT                   = 384,
  FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR            = 385,
  FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT      = 388,
  FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR            = 389,
  FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT            = 400,
  FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR     = 401,
  FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT            = 404,
  FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR                  = 405,
  FILTER_MAXIMUM_ANISOTROPIC                         = 469
};

enum ADDRESS_MODE
{
  TEXTURE_ADDRESS_WRAP        = 1,
  TEXTURE_ADDRESS_MIRROR      = 2,
  TEXTURE_ADDRESS_CLAMP       = 3,
  TEXTURE_ADDRESS_BORDER      = 4,
  TEXTURE_ADDRESS_MIRROR_ONCE = 5
};

enum COMPARISON_FUNC
{
  COMPARISON_NEVER         = 1,
  COMPARISON_LESS          = 2,
  COMPARISON_EQUAL         = 3,
  COMPARISON_LESS_EQUAL    = 4,
  COMPARISON_GREATER       = 5,
  COMPARISON_NOT_EQUAL     = 6,
  COMPARISON_GREATER_EQUAL = 7,
  COMPARISON_ALWAYS        = 8
};

enum INPUT_CLASSIFICATION
{
  INPUT_PER_VERTEX_DATA   = 0,
  INPUT_PER_INSTANCE_DATA = 1
};

}