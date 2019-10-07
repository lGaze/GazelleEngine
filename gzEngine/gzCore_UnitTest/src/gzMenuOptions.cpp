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
float MenuOptions::s_color[4];
bool MenuOptions::s_rotationX = false;
bool MenuOptions::s_rotationY = true;

MenuOptions & g_menuOptions() {
  return MenuOptions::instance();
}