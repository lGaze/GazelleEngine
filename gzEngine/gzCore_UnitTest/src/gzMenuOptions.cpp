/**************************************************************************/
/* @filename gzMenuOptions.cpp
/* @author Victor Flores 
/* @date 2019/09/28
/* @brief 
/**************************************************************************/
#include "gzMenuOptions.h"
#include <gzVector4f.h>

int32 MenuOptions::s_testCounter = 0;
float MenuOptions::s_lightPosition[3];
float MenuOptions::s_color[4] = { 1.0f, 0.3f, 0.0f ,0.0f };
int32 MenuOptions::s_rotation = 0;
float MenuOptions::s_SampeRadiusValue = 22;
float MenuOptions::s_intensityValue = 15;
float MenuOptions::s_scaleValue = 0.4;
float MenuOptions::s_biasValue = 0.3;

MenuOptions & g_menuOptions() {
  return MenuOptions::instance();
}