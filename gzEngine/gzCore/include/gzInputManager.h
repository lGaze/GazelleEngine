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
    key0,
    key1,
    key2,
    key3,
    key4,
    key5, 
    key6,
    key7,
    key8,
    key9,
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
  wasButtonPressed();

  /**
   * @brief This function update the inputs
   */
  virtual void
  update() = 0;

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 public:
   
 };
}
