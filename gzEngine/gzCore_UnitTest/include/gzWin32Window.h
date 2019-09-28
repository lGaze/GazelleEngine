/**************************************************************************/
/* @filename gzWin32Window.h
/* @author Victor Flores 
/* @date 2019/09/27
/* @brief 
/**************************************************************************/
#pragma once
#include <gzWindow.h>

namespace gzEngineSDK {
class Win32Window : public Window
{
 public:
 
  /**
   * @brief default constructor
   */
  Win32Window() = default;

  /**
   * @brief default destructor
   */
  ~Win32Window() = default;



  /************************************************************************/
  /* Win32Window functions                                               */
  /************************************************************************/
 protected:

  /**
   * @brief Function which initializates the window
   * @returns Bool value which indicates if the initialization of the window succeed
   */
  virtual bool
  initWindow(uint32 width,
             uint32 height,
             String windowName,
             uint32 posX,
             uint32 posY) override;

  /**
   * @brief Dispaches all the messages
   */
  virtual void 
  messageHandler() override;


  /**
   * @brief WndProc
   */
  static LRESULT
  CALLBACK WndProc(HWND window,
                   UINT message,
                   WPARAM wParam,
                   LPARAM lParam);

 public:

  /**
   * @brief Gets the handler of the window
   * @return handle of the window
   */
  virtual void * 
  getHandle() override;


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
