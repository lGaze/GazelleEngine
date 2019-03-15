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
class GZ_CORE_EXPORT Window
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
  initWindow( uint32 width,
              uint32 height,
              String windowName,
              uint32 posX,
              uint32 posY );

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

  /**
   * @brief Gets the handler of the window
   */
  FORCEINLINE HWND
  getHWND() { return m_hWnd; }

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
	
 private:

   /**
    * @brief Handler of the window
    */
   HWND m_hWnd;

 };
}