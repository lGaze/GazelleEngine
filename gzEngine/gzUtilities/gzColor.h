/**************************************************************************/
/* @filename gzColor.h
/* @author Victor Flores 
/* @date 2019/11/12
/* @brief 
/**************************************************************************/
#pragma once
#include "gzPrerequisitesUtilities.h"

namespace gzEngineSDK {
class GZ_UTILITY_EXPORT LinearColor
{
 public:
 
  /**
   * @brief default constructor
   */
  LinearColor() = default;

  /**
   * @brief This function creates a color with 4 float values
   */
  LinearColor(float r, float g, float b, float a = 1.0f);

  /**
   * @brief default destructor
   */
  ~LinearColor() = default;

  /************************************************************************/
  /* Color functions                                                      */
  /************************************************************************/

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 public:

   union  {
     struct {
       float m_r, m_g, m_b, m_a;
     }channel; 
     float rgba[4];
   };
   
   //COLORS
   static const LinearColor Transparent;
   static const LinearColor Black;
   static const LinearColor White;
   static const LinearColor Red;
   static const LinearColor Green;
   static const LinearColor Blue;
   static const LinearColor Pink;
   static const LinearColor Orange;
   static const LinearColor Purple;
   static const LinearColor Yellow;

 };

class GZ_UTILITY_EXPORT Color
{
public:

  /**
   * @brief default constructor
   */
  Color() = default;

  /**
   * @brief This function creates a color with 4 char values
   */
  Color(char r, char g, char b, char a);

  /**
   * @brief default destructor
   */
  ~Color() = default;

};
}
