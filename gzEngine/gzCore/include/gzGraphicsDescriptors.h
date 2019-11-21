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

}