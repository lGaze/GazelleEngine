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
   static bool s_rotationX;
   static bool s_rotationY;
};
MenuOptions&
g_menuOptions();

