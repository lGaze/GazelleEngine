/**************************************************************************/
/* @filename gzWindow.h
/* @author Victor Flores 
/* @date 2019/03/02
/* @brief 
/**************************************************************************/
#pragma once

#include "gzPrerequisitesCore.h"
#include <windows.h>

namespace gzEngineSDK {
class GZ_UTILITY_EXPORT Window
{
 public:
   
  /**
   * @brief default constructor
   */
  Window() = default;
	
  /**
   * @brief default destructor
   */
  ~Window() = default;
	
  /************************************************************************/
  /* Window functions                                                     */
  /************************************************************************/
	
  /**
   * @brief Function which initializates the window
   * @returns Bool value which indicates if the initialization of the window succeed
   */
  bool
  initWindow();

  /**
   * @brief Dispaches all the windows messages
   */
  void
  messageHandler();

  /**
   * @brief WndProc
   */
  static LRESULT
  CALLBACK WndProc( HWND window,
                    UINT message,
                    WPARAM wParam,
                    LPARAM lParam );

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
	
 public:

   /**
    * @brief Handler of the window
    */
   HWND m_hWnd;

 };
}