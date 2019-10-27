/**************************************************************************/
/* @filename gzMenuOptions.h
/* @author Victor Flores 
/* @date 2019/09/28
/* @brief 
/**************************************************************************/
#pragma once
#include <gzModule.h>

using namespace gzEngineSDK;

class MenuOptions : public Module<MenuOptions>
{
 public:
   static int32 s_testCounter;
   static float s_lightPosition[3];
   static float s_color[4];
   static int32 s_rotation;
   static float s_SampeRadiusValue;
   static float s_intensityValue;
   static float s_scaleValue;
   static float s_biasValue;
};
MenuOptions&
g_menuOptions();

