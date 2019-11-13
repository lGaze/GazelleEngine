/**************************************************************************/
/* @filename gzColor.cpp
/* @author Victor Flores 
/* @date 2019/11/12
/**************************************************************************/

#include "gzColor.h"

namespace gzEngineSDK {

  LinearColor::LinearColor(float r, float g, float b, float a) {
    channel.m_r = r;
    channel.m_g = g;
    channel.m_b = b;
    channel.m_a = a;
  }

  const LinearColor LinearColor::Transparent(0.0, 0.0, 0.0, 0.0);
  const LinearColor LinearColor::Black(0.0f, 0.0f, 0.0f);
  const LinearColor LinearColor::White(1.0f, 1.0f, 1.0f);
  const LinearColor LinearColor::Red(1.0f, 0.0f, 0.0f);
  const LinearColor LinearColor::Green(0.0f, 1.0f, 0.0f);
  const LinearColor LinearColor::Blue(0.0f, 0.0f, 1.0f);
  const LinearColor LinearColor::Pink(1.0f, 0.0f, 1.0f);
  const LinearColor LinearColor::Orange(1.0f, 0.5f, 0.0f);
  const LinearColor LinearColor::Yellow(1.0f, 1.0f, 0.0f);
  const LinearColor LinearColor::Purple(0.5f, 0.0f, 1.0f);
}