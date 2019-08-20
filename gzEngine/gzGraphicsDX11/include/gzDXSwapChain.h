/**************************************************************************/
/* @filename gzDXSwapChain.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/
#pragma once

#include "gzDXPrerequisites.h"

namespace gzEngineSDK {
class SwapChain
{
 public:
   
  /**
   * @brief default constructor
   */
  SwapChain();

  /**
   * @brief default destructor
   */
  ~SwapChain() = default;

  /************************************************************************/
  /* SwapChain functions                                                  */
  /************************************************************************/

  /**
   * @brief Create a Description for the current Swapchain
   */
  void
  CreateSwapChainDesc( uint32 Width, uint32 Height, void* hWnd );

  /**
   * @brief 
   */
  bool
  getBuffer( uint32 buffer, REFIID riid, void** ppSurface );

  /**
   * @brief 
   */
  bool
  Present( uint32 SyncInterval, uint32 Flags );

  /**
   * @brief Gets the swapchain interface
   */
  FORCEINLINE IDXGISwapChain**
  getSwapChainInterface() {
    return &m_pSwapChain;
  }

  /**
   * @brief Gets the current Swapchain description
   */
  FORCEINLINE DXGI_SWAP_CHAIN_DESC
  getCurrentSCD() {
    return m_currentSCD;
  }

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:

  /**
   * @brief 
   */
  IDXGISwapChain * m_pSwapChain;

  /**
   * @brief 
   */
  DXGI_SWAP_CHAIN_DESC m_currentSCD;
   
 };
}
