/**************************************************************************/
/* @filename gzGainputManager.h
/* @author Victor Flores 
/* @date 2019/10/13
/* @brief This file works as an input manager
/**************************************************************************/
#pragma once

#include <gzPrerequisitesCore.h>
#include <gzInputManager.h>
#include <gainput/gainput.h>

namespace gzEngineSDK {
class GainputManager : public InputManager
{
 public:
 
  /**
   * @brief default constructor
   */
  GainputManager();

  /**
   * @brief default destructor
   */
  ~GainputManager() {};

  /************************************************************************/
  /* GainputManager functions                                             */
  /************************************************************************/

  /**
   * @brief This function updates the Gainput manager
   */
  virtual void
  update() override;

  /**
   * @brief This function checks if the given button was pressed
   * @return Returns true if the button was pressed
   */
  virtual bool 
  wasButtonPressed(KEYBOARDBUTTONS::e button) override;

 private:

  /**
   * @brief This function initializes all the gainput needs 
   */
  void
  initGainput();

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:

  gainput::InputManager m_inputManager;
  gainput::InputMap * m_map;
  gainput::DeviceId m_keyboardId;

 };
}
