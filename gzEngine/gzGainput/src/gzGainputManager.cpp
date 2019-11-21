/**************************************************************************/
/* @filename gzGainputManager.cpp
/* @author Victor Flores 
/* @date 2019/10/13
/* @brief 
/**************************************************************************/

#include "gzGainputManager.h"
#include <Windows.h>
#include <gzBaseApp.h>

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
    return m_map->GetBool(button);
  }

  void 
  GainputManager::handleMesage(void * mesage) {
    MSG* msg = static_cast<MSG*>(mesage);
    m_inputManager.HandleMessage(*msg);
  }

  void
  GainputManager::initGainput() {
    m_keyboardId =
      m_inputManager.CreateDevice<gainput::InputDeviceKeyboard>();
    m_inputManager.SetDisplaySize(
      static_cast<uint32>( g_GraphicsManager().getViewportDimensions().x),
      static_cast<uint32>( g_GraphicsManager().getViewportDimensions().y));

    m_map = new gainput::InputMap(m_inputManager);
    m_map->MapBool(KEYBOARDBUTTONS::kKeyW, m_keyboardId, gainput::KeyW);
    m_map->MapBool(KEYBOARDBUTTONS::kKeyA, m_keyboardId, gainput::KeyA);
    m_map->MapBool(KEYBOARDBUTTONS::kKeyS, m_keyboardId, gainput::KeyS);
    m_map->MapBool(KEYBOARDBUTTONS::kKeyD, m_keyboardId, gainput::KeyD);
    m_map->MapBool(KEYBOARDBUTTONS::kArrowUp, m_keyboardId, gainput::KeyUp);
    m_map->MapBool(KEYBOARDBUTTONS::kArrowDown, m_keyboardId, gainput::KeyDown);
    m_map->MapBool(KEYBOARDBUTTONS::kArrowLeft, m_keyboardId, gainput::KeyLeft);
    m_map->MapBool(KEYBOARDBUTTONS::kArrowRight, m_keyboardId, gainput::KeyRight);
  }

}