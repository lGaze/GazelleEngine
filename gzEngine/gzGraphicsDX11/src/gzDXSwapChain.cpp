/**************************************************************************/
/* @filename gzDXSwapChain.cpp
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#include "gzDXSwapChain.h"

namespace gzEngineSDK {

  SwapChain::SwapChain()
  {
    m_pSwapChain = nullptr;
  }

  void
  SwapChain::CreateSwapChainDesc( uint32 Width, uint32 Height, void * hWnd )
  {
    HWND handler = static_cast< HWND >(hWnd);
    ZeroMemory( &m_currentSCD, sizeof( m_currentSCD ) );
    m_currentSCD.BufferCount = 1;
    m_currentSCD.BufferDesc.Width = Width;
    m_currentSCD.BufferDesc.Height = Height;
    m_currentSCD.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    m_currentSCD.BufferDesc.RefreshRate.Numerator = 60;
    m_currentSCD.BufferDesc.RefreshRate.Denominator = 1;
    m_currentSCD.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    m_currentSCD.OutputWindow = handler;
    m_currentSCD.SampleDesc.Count = 1;
    m_currentSCD.SampleDesc.Quality = 0;
    m_currentSCD.Windowed = TRUE;
  }

  bool 
  SwapChain::getBuffer( uint32 buffer, REFIID riid, void ** ppSurface )
  {
    bool result = true;

    result = m_pSwapChain->GetBuffer( buffer, riid, ppSurface );

    return result;
  }
}