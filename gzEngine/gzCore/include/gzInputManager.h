/**************************************************************************/
/* @filename gzInputManager.h
/* @author Victor Flores 
/* @date 2019/10/13
/* @brief This file works as an interface for inputs
/**************************************************************************/
#pragma once

#include "gzPrerequisitesCore.h"
#include <gzModule.h>

namespace KEYBOARDBUTTONS {
  enum e
  {
    kKeyA,
    kKeyB,
    kKeyC,
    kKeyD,
    kKeyE,
    kKeyF,
    kKeyG,
    kKeyH,
    kKeyI,
    kKeyJ,
    kKeyK,
    kKeyL,
    kKeyM,
    kKeyN,
    kKeyO,
    kKeyP,
    kKeyQ,
    kKeyR,
    kKeyS,
    kKeyT,
    kKeyU,
    kKeyV,
    kKeyW,
    kKeyX,
    kKeyY,
    kKeyZ,
    kKeySpace,
    kArrowUp,
    kArrowDown,
    kArrowLeft,
    kArrowRight
  };
}

namespace MOUSEBUTTONS {
  enum e {
    kMouseButtonLeft,
    kMouseButtonMiddle,
    kMouseButtonRight,
    kMouseButtonWheelDown,
    kMouseButtonWheelUp,
  };
}

namespace gzEngineSDK {
class GZ_CORE_EXPORT InputManager : public Module<InputManager>
{
 public:
 
  /**
   * @brief default constructor
   */
  InputManager() = default;

  /**
   * @brief default destructor
   */
  ~InputManager() = default;

  /************************************************************************/
  /* inputManager functions                                               */
  /************************************************************************/

  /**
   * @brief This function checks if the given button was pressed
   */
  virtual bool
  wasButtonPressed(KEYBOARDBUTTONS::e) = 0;

  /**
   * @brief This function update the inputs
   */
  virtual void
  update() = 0;

  /**
   * @brief 
   */
  virtual void
  handleMesage(void * mesage) = 0;

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 public:
   
 };

GZ_CORE_EXPORT InputManager& 
g_InputManager();
}
