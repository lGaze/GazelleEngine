/**************************************************************************/
/* @filename gzGraphicsDescriptors.h
/* @author Victor Flores 
/* @date 2019/03/17
/* @brief File that contains all the grafic descriptors 
/**************************************************************************/

#pragma once

#include "gzPrerequisitesCore.h"
#include <gzVector3f.h>
#include <gzVector2f.h>
#include <gzVector4f.h>

namespace gzEngineSDK {

struct VERTEX {
  Vector3f position;
  Vector2f texcoord;
  Vector3f normal;
  Vector3f binormal;
  Vector3f tangent;
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

namespace CULL_MODE {
  enum E
  {
    CULL_NONE = 1,
    CULL_FRONT = 2,
    CULL_BACK = 3
  };
}

namespace FILL_MODE{
  enum E
  {
    FILL_WIREFRAME = 2,
    FILL_SOLID = 3
  };
}

namespace FORMATS {
  enum E
  {
    FORMAT_UNKNOWN = 0,
    FORMAT_R32G32B32A32_TYPELESS = 1,
    FORMAT_R32G32B32A32_FLOAT = 2,
    FORMAT_R32G32B32A32_UINT = 3,
    FORMAT_R32G32B32A32_SINT = 4,
    FORMAT_R32G32B32_TYPELESS = 5,
    FORMAT_R32G32B32_FLOAT = 6,
    FORMAT_R32G32B32_UINT = 7,
    FORMAT_R32G32B32_SINT = 8,
    FORMAT_R16G16B16A16_TYPELESS = 9,
    FORMAT_R16G16B16A16_FLOAT = 10,
    FORMAT_R16G16B16A16_UNORM = 11,
    FORMAT_R16G16B16A16_UINT = 12,
    FORMAT_R16G16B16A16_SNORM = 13,
    FORMAT_R16G16B16A16_SINT = 14,
    FORMAT_R32G32_TYPELESS = 15,
    FORMAT_R32G32_FLOAT = 16,
    FORMAT_R32G32_UINT = 17,
    FORMAT_R32G32_SINT = 18,
    FORMAT_R32G8X24_TYPELESS = 19,
    FORMAT_D32_FLOAT_S8X24_UINT = 20,
    FORMAT_R32_FLOAT_X8X24_TYPELESS = 21,
    FORMAT_X32_TYPELESS_G8X24_UINT = 22,
    FORMAT_R10G10B10A2_TYPELESS = 23,
    FORMAT_R10G10B10A2_UNORM = 24,
    FORMAT_R10G10B10A2_UINT = 25,
    FORMAT_R11G11B10_FLOAT = 26,
    FORMAT_R8G8B8A8_TYPELESS = 27,
    FORMAT_R8G8B8A8_UNORM = 28,
    FORMAT_R8G8B8A8_UNORM_SRGB = 29,
    FORMAT_R8G8B8A8_UINT = 30,
    FORMAT_R8G8B8A8_SNORM = 31,
    FORMAT_R8G8B8A8_SINT = 32,
    FORMAT_R16G16_TYPELESS = 33,
    FORMAT_R16G16_FLOAT = 34,
    FORMAT_R16G16_UNORM = 35,
    FORMAT_R16G16_UINT = 36,
    FORMAT_R16G16_SNORM = 37,
    FORMAT_R16G16_SINT = 38,
    FORMAT_R32_TYPELESS = 39,
    FORMAT_D32_FLOAT = 40,
    FORMAT_R32_FLOAT = 41,
    FORMAT_R32_UINT = 42,
    FORMAT_R32_SINT = 43,
    FORMAT_R24G8_TYPELESS = 44,
    FORMAT_D24_UNORM_S8_UINT = 45,
    FORMAT_R24_UNORM_X8_TYPELESS = 46,
    FORMAT_X24_TYPELESS_G8_UINT = 47,
    FORMAT_R8G8_TYPELESS = 48,
    FORMAT_R8G8_UNORM = 49,
    FORMAT_R8G8_UINT = 50,
    FORMAT_R8G8_SNORM = 51,
    FORMAT_R8G8_SINT = 52,
    FORMAT_R16_TYPELESS = 53,
    FORMAT_R16_FLOAT = 54,
    FORMAT_D16_UNORM = 55,
    FORMAT_R16_UNORM = 56,
    FORMAT_R16_UINT = 57,
    FORMAT_R16_SNORM = 58,
    FORMAT_R16_SINT = 59,
    FORMAT_R8_TYPELESS = 60,
    FORMAT_R8_UNORM = 61,
    FORMAT_R8_UINT = 62,
    FORMAT_R8_SNORM = 63,
    FORMAT_R8_SINT = 64,
    FORMAT_A8_UNORM = 65,
    FORMAT_R1_UNORM = 66,
    FORMAT_R9G9B9E5_SHAREDEXP = 67,
    FORMAT_R8G8_B8G8_UNORM = 68,
    FORMAT_G8R8_G8B8_UNORM = 69,
    FORMAT_BC1_TYPELESS = 70,
    FORMAT_BC1_UNORM = 71,
    FORMAT_BC1_UNORM_SRGB = 72,
    FORMAT_BC2_TYPELESS = 73,
    FORMAT_BC2_UNORM = 74,
    FORMAT_BC2_UNORM_SRGB = 75,
    FORMAT_BC3_TYPELESS = 76,
    FORMAT_BC3_UNORM = 77,
    FORMAT_BC3_UNORM_SRGB = 78,
    FORMAT_BC4_TYPELESS = 79,
    FORMAT_BC4_UNORM = 80,
    FORMAT_BC4_SNORM = 81,
    FORMAT_BC5_TYPELESS = 82,
    FORMAT_BC5_UNORM = 83,
    FORMAT_BC5_SNORM = 84,
    FORMAT_B5G6R5_UNORM = 85,
    FORMAT_B5G5R5A1_UNORM = 86,
    FORMAT_B8G8R8A8_UNORM = 87,
    FORMAT_B8G8R8X8_UNORM = 88,
    FORMAT_R10G10B10_XR_BIAS_A2_UNORM = 89,
    FORMAT_B8G8R8A8_TYPELESS = 90,
    FORMAT_B8G8R8A8_UNORM_SRGB = 91,
    FORMAT_B8G8R8X8_TYPELESS = 92,
    FORMAT_B8G8R8X8_UNORM_SRGB = 93,
    FORMAT_BC6H_TYPELESS = 94,
    FORMAT_BC6H_UF16 = 95,
    FORMAT_BC6H_SF16 = 96,
    FORMAT_BC7_TYPELESS = 97,
    FORMAT_BC7_UNORM = 98,
    FORMAT_BC7_UNORM_SRGB = 99,
    FORMAT_AYUV = 100,
    FORMAT_Y410 = 101,
    FORMAT_Y416 = 102,
    FORMAT_NV12 = 103,
    FORMAT_P010 = 104,
    FORMAT_P016 = 105,
    FORMAT_420_OPAQUE = 106,
    FORMAT_YUY2 = 107,
    FORMAT_Y210 = 108,
    FORMAT_Y216 = 109,
    FORMAT_NV11 = 110,
    FORMAT_AI44 = 111,
    FORMAT_IA44 = 112,
    FORMAT_P8 = 113,
    FORMAT_A8P8 = 114,
    FORMAT_B4G4R4A4_UNORM = 115,

    FORMAT_P208 = 130,
    FORMAT_V208 = 131,
    FORMAT_V408 = 132,
  };
}

namespace USAGES {
  enum E
  {
    USAGE_DEFAULT = 0,
    USAGE_IMMUTABLE = 1,
    USAGE_DYNAMIC = 2,
    USAGE_STAGING = 3
  };
}

namespace BIND_FLAGS {
  enum E
  {
    BIND_VERTEX_BUFFER = 0x1L,
    BIND_INDEX_BUFFER = 0x2L,
    BIND_CONSTANT_BUFFER = 0x4L,
    BIND_SHADER_RESOURCE = 0x8L,
    BIND_STREAM_OUTPUT = 0x10L,
    BIND_RENDER_TARGET = 0x20L,
    BIND_DEPTH_STENCIL = 0x40L,
    BIND_UNORDERED_ACCESS = 0x80L
  };
}

namespace DSV_DIMENSIONS {
  enum E
  {
    DSV_DIMENSION_UNKNOWN = 0,
    DSV_DIMENSION_TEXTURE1D = 1,
    DSV_DIMENSION_TEXTURE1DARRAY = 2,
    DSV_DIMENSION_TEXTURE2D = 3,
    DSV_DIMENSION_TEXTURE2DARRAY = 4,
    DSV_DIMENSION_TEXTURE2DMS = 5,
    DSV_DIMENSION_TEXTURE2DMSARRAY = 6

  };
}

namespace CLEAR_DSV_FLAGS {
  enum E
  {
    CLEAR_DEPTH = 1,
    CLEAR_STENCIL = 2
  };
}

namespace FILTER {
  enum E
  {
    FILTER_MIN_MAG_MIP_POINT = 0,
    FILTER_MIN_MAG_POINT_MIP_LINEAR = 1,
    FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT = 4,
    FILTER_MIN_POINT_MAG_MIP_LINEAR = 5,
    FILTER_MIN_LINEAR_MAG_MIP_POINT = 16,
    FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 17,
    FILTER_MIN_MAG_LINEAR_MIP_POINT = 20,
    FILTER_MIN_MAG_MIP_LINEAR = 21,
    FILTER_ANISOTROPIC = 85,
    FILTER_COMPARISON_MIN_MAG_MIP_POINT = 128,
    FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR = 129,
    FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT = 132,
    FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR = 133,
    FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT = 144,
    FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 145,
    FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT = 148,
    FILTER_COMPARISON_MIN_MAG_MIP_LINEAR = 149,
    FILTER_COMPARISON_ANISOTROPIC = 213,
    FILTER_MINIMUM_MIN_MAG_MIP_POINT = 256,
    FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR = 257,
    FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT = 260,
    FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR = 261,
    FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT = 272,
    FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 273,
    FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT = 276,
    FILTER_MINIMUM_MIN_MAG_MIP_LINEAR = 277,
    FILTER_MINIMUM_ANISOTROPIC = 341,
    FILTER_MAXIMUM_MIN_MAG_MIP_POINT = 384,
    FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR = 385,
    FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT = 388,
    FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR = 389,
    FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT = 400,
    FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 401,
    FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT = 404,
    FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR = 405,
    FILTER_MAXIMUM_ANISOTROPIC = 469
  };
}

namespace ADDRESS_MODE {
  enum E
  {
    TEXTURE_ADDRESS_WRAP = 1,
    TEXTURE_ADDRESS_MIRROR = 2,
    TEXTURE_ADDRESS_CLAMP = 3,
    TEXTURE_ADDRESS_BORDER = 4,
    TEXTURE_ADDRESS_MIRROR_ONCE = 5
  };
}

namespace COMPARISON_FUNC {
  enum E
  {
    COMPARISON_NEVER = 1,
    COMPARISON_LESS = 2,
    COMPARISON_EQUAL = 3,
    COMPARISON_LESS_EQUAL = 4,
    COMPARISON_GREATER = 5,
    COMPARISON_NOT_EQUAL = 6,
    COMPARISON_GREATER_EQUAL = 7,
    COMPARISON_ALWAYS = 8
  };
}

namespace INPUT_CLASSIFICATION {
  enum E
  {
    INPUT_PER_VERTEX_DATA = 0,
    INPUT_PER_INSTANCE_DATA = 1
  };
}


namespace COMPONENT_TYPE {
  enum E
  {
    kMeshComponent = 0,
  };
}

}