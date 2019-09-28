/**************************************************************************/
/* @filename gzWindow.h
/* @author Victor Flores 
/* @date 2019/03/02
/* @brief This is the window header file, in this file are the main functions
/* of a winddow
/**************************************************************************/
#pragma once

#include "gzPrerequisitesCore.h"
#include <windows.h>

namespace gzEngineSDK {
class GZ_CORE_EXPORT Window
{
 public:
   
  /**
   * @brief Default Constructor
   */
  Window() = default;

  /**
   * @brief Default Destructor
   */
  ~Window() = default;

  /************************************************************************/
  /* Window functions                                                     */
  /************************************************************************/

 public:

  /**
   * @brief Function which initializates the window
   * @returns Bool value which indicates if the initialization of the window succeed
   */
  virtual bool
  initWindow( uint32 width,
              uint32 height,
              String windowName,
              uint32 posX,
              uint32 posY ) = 0;

  /**
   * @brief Dispaches all the messages
   */
  virtual void
  messageHandler() = 0;

  virtual void *
  getHandle() = 0;

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 public:

  /**
   * @brief
   */
  uint32 m_windowWidthRect;

  /**
   * @brief
   */
  uint32 m_windowHeightRect;

  /**
   * @brief
   */
  String m_windowName;

  /**
   * @brief
   */
  uint32 m_windowPosX;

  /**
   * @brief
   */
  uint32 m_windowPosY;

 };
}