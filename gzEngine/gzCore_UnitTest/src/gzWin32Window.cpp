/**************************************************************************/
/* @filename gzWin32Window.cpp
/* @author Victor Flores 
/* @date 2019/09/27
/* @brief 
/**************************************************************************/

#include "gzWin32Window.h"
#include <gzCameraManager.h>
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_win32.h>
#include <ImGui/imgui_impl_dx11.h>

static bool g_WantUpdateHasGamepad = true;
namespace gzEngineSDK {
  
  void * 
  Win32Window::getHandle()
  {
    return reinterpret_cast<void *>(m_hWnd);
  }

  bool
  Win32Window::initWindow(uint32 width,
                          uint32 height,
                          String windowName,
                          uint32 posX,
                          uint32 posY)
  {
    //register class
    WNDCLASSEX wndclass;
    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = GetModuleHandle(0);
    wndclass.hIcon = LoadIcon(0, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(0, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = windowName.c_str();
    wndclass.hIconSm = LoadIcon(0, IDI_APPLICATION);
    if (!RegisterClassEx(&wndclass))
      return false;

    //Create window
    RECT rc = { 0, 0, width, height };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
    m_hWnd = CreateWindowEx(0, windowName.c_str(), windowName.c_str(),
                            WS_OVERLAPPEDWINDOW, posX, posY,
                            rc.right - rc.left, rc.bottom - rc.top, 0, 0,
                            GetModuleHandle(0), 0);
    GetClientRect(m_hWnd, &rc);
    m_windowWidthRect = rc.right - rc.left;
    m_windowHeightRect = rc.bottom - rc.top;
    m_windowPosX = posX;
    m_windowPosY = posY;
    m_windowName = windowName;

    if (!m_hWnd)
      return false;

    ShowWindow(m_hWnd, SW_SHOWDEFAULT);

    return true;
  }

  void
  Win32Window::messageHandler()
  {
    MSG msg = { 0 };

    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  static bool 
  ImGui_ImplWin32_UpdateMouseCursor()
  {
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)
      return false;

    ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
    if (imgui_cursor == ImGuiMouseCursor_None || io.MouseDrawCursor)
    {
      // Hide OS mouse cursor if imgui is drawing it or if it wants no cursor
      ::SetCursor(NULL);
    }
    else
    {
      // Show OS mouse cursor
      LPTSTR win32_cursor = IDC_ARROW;
      switch (imgui_cursor)
      {
      case ImGuiMouseCursor_Arrow:        win32_cursor = IDC_ARROW; break;
      case ImGuiMouseCursor_TextInput:    win32_cursor = IDC_IBEAM; break;
      case ImGuiMouseCursor_ResizeAll:    win32_cursor = IDC_SIZEALL; break;
      case ImGuiMouseCursor_ResizeEW:     win32_cursor = IDC_SIZEWE; break;
      case ImGuiMouseCursor_ResizeNS:     win32_cursor = IDC_SIZENS; break;
      case ImGuiMouseCursor_ResizeNESW:   win32_cursor = IDC_SIZENESW; break;
      case ImGuiMouseCursor_ResizeNWSE:   win32_cursor = IDC_SIZENWSE; break;
      case ImGuiMouseCursor_Hand:         win32_cursor = IDC_HAND; break;
      }
      ::SetCursor(::LoadCursor(NULL, win32_cursor));
    }
    return true;
  }

  LRESULT 
  ImGui_ImplWin32_WndProcHandler(HWND hwnd, 
                                 UINT msg, 
                                 WPARAM wParam, 
                                 LPARAM lParam)
  {
    if (ImGui::GetCurrentContext() == NULL)
      return 0;

    ImGuiIO& io = ImGui::GetIO();
    switch (msg)
    {
    case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
    case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
    case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
    case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK:
    {
      int button = 0;
      if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONDBLCLK) { button = 0; }
      if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONDBLCLK) { button = 1; }
      if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONDBLCLK) { button = 2; }
      if (msg == WM_XBUTTONDOWN || msg == WM_XBUTTONDBLCLK) { button = (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? 3 : 4; }
      if (!ImGui::IsAnyMouseDown() && ::GetCapture() == NULL)
        ::SetCapture(hwnd);
      io.MouseDown[button] = true;
      return 0;
    }
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    case WM_XBUTTONUP:
    {
      int button = 0;
      if (msg == WM_LBUTTONUP) { button = 0; }
      if (msg == WM_RBUTTONUP) { button = 1; }
      if (msg == WM_MBUTTONUP) { button = 2; }
      if (msg == WM_XBUTTONUP) { button = (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? 3 : 4; }
      io.MouseDown[button] = false;
      if (!ImGui::IsAnyMouseDown() && ::GetCapture() == hwnd)
        ::ReleaseCapture();
      return 0;
    }
    case WM_MOUSEWHEEL:
      io.MouseWheel += (float)GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA;
      return 0;
    case WM_MOUSEHWHEEL:
      io.MouseWheelH += (float)GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA;
      return 0;
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
      if (wParam < 256)
        io.KeysDown[wParam] = 1;
      return 0;
    case WM_KEYUP:
    case WM_SYSKEYUP:
      if (wParam < 256)
        io.KeysDown[wParam] = 0;
      return 0;
    case WM_CHAR:
      // You can also use ToAscii()+GetKeyboardState() to retrieve characters.
      io.AddInputCharacter((unsigned int)wParam);
      return 0;
    case WM_SETCURSOR:
      if (LOWORD(lParam) == HTCLIENT && ImGui_ImplWin32_UpdateMouseCursor())
        return 1;
      return 0;
    case WM_DEVICECHANGE:
      if ((UINT)wParam == 0x0007)
        g_WantUpdateHasGamepad = true;
      return 0;
    }
    return 0;
  }

  LRESULT
  Win32Window::WndProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
  {
    PAINTSTRUCT ps;
    HDC hdc;

    if (ImGui_ImplWin32_WndProcHandler(window, message, wParam, lParam)) {
      return true;
    }

    switch (message)
    {
    case WM_PAINT:
      hdc = BeginPaint(window, &ps);
      EndPaint(window, &ps);
      break;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    case WM_KEYDOWN:
      switch (wParam)
      {
      case 'A':
        CameraManager::instance().moveActiveCamera(CAMERA_MOVEMENT::E::LEFT);
        break;
      case 'D':
        CameraManager::instance().moveActiveCamera(CAMERA_MOVEMENT::E::RIGHT);
        break;
      case 'S':
        CameraManager::instance().moveActiveCamera(CAMERA_MOVEMENT::E::BACKWARD);
        break;
      case 'W':
        CameraManager::instance().moveActiveCamera(CAMERA_MOVEMENT::E::FORWARD);
        break;
      }
      break;
    default:
      return DefWindowProc(window, message, wParam, lParam);
    }
    return 0;
  }
}