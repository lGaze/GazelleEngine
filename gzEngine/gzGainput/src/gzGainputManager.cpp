/**************************************************************************/
/* @filename gzGainputManager.cpp
/* @author Victor Flores 
/* @date 2019/10/13
/* @brief 
/**************************************************************************/

#include "gzGainputManager.h"

namespace gzEngineSDK {

  GainputManager::GainputManager(){
    initGainput();
  }

  void 
  GainputManager::update() {
    m_inputManager.Update();
  }

  bool 
  GainputManager::wasButtonPressed(KEYBOARDBUTTONS::e button){
    return m_map->GetBoolWasDown(button);
  }

  void
  GainputManager::initGainput() {
    m_keyboardId =
      m_inputManager.CreateDevice<gainput::InputDeviceKeyboard>();
    m_map = new gainput::InputMap(m_inputManager);
    m_map->MapBool(KEYBOARDBUTTONS::kKeyW, m_keyboardId, gainput::KeyW);
    m_map->MapBool(KEYBOARDBUTTONS::kKeyA, m_keyboardId, gainput::KeyA);
    m_map->MapBool(KEYBOARDBUTTONS::kKeyS, m_keyboardId, gainput::KeyS);
    m_map->MapBool(KEYBOARDBUTTONS::kKeyD, m_keyboardId, gainput::KeyD);
  }

}