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

}