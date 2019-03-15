/**************************************************************************/
/* @filename gzWindow.cpp
/* @author Victor Flores 
/* @date 2019/03/02
/* @brief 
/**************************************************************************/

#include "gzWindow.h"

namespace gzEngineSDK {

  bool 
  Window::initWindow( uint32 width,
                      uint32 height,
                      String windowName,
                      uint32 posX,
                      uint32 posY)
  {
    //register class
    WNDCLASSEX wndclass;
    wndclass.cbSize = sizeof( WNDCLASSEX );
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = GetModuleHandle( 0 );
    wndclass.hIcon = LoadIcon( 0, IDI_APPLICATION );
    wndclass.hCursor = LoadCursor( 0, IDC_ARROW );
    wndclass.hbrBackground = ( HBRUSH ) ( COLOR_WINDOW + 1 );
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = windowName.c_str();
    wndclass.hIconSm = LoadIcon( 0, IDI_APPLICATION );
    if ( !RegisterClassEx( &wndclass ) )
      return false;

    //Create window

    m_hWnd = CreateWindowEx( 0, windowName.c_str(), windowName.c_str(),
                             WS_OVERLAPPEDWINDOW, posX, posY,
                             width, height, 0, 0,
                             GetModuleHandle( 0 ), 0 );

    if ( !m_hWnd )
      return false;

    ShowWindow( m_hWnd, SW_SHOWDEFAULT );

    return true;
  }

  void
  Window::messageHandler()
  {
    MSG msg = { 0 };

    while( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
    {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }
  }

  LRESULT 
  Window::WndProc( HWND window, UINT message, WPARAM wParam, LPARAM lParam )
  {
    PAINTSTRUCT ps;
    HDC hdc;

    switch ( message )
    {
    case WM_PAINT:
      hdc = BeginPaint( window, &ps );
      EndPaint( window, &ps );
      break;

    case WM_DESTROY:
      PostQuitMessage( 0 );
      break;

    default:
      return DefWindowProc( window, message, wParam, lParam );
    }
    return 0;
  }
}
