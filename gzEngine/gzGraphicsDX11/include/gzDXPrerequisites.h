/**************************************************************************/
/* @filename gzDXPrerequisites.h
/* @author Victor Flores 
/* @date 2019/03/03
/* @brief 
/**************************************************************************/
#pragma once
#pragma comment(lib, "d3d11")
#pragma comment(lib, "D3DCompiler")
#pragma comment(lib, "dxguid")


#include <gzPrerequisitesCore.h>
#include <gzPrerequisitesUtilities.h>

#include <d3d11.h>
#include <d3dcompiler.h>



namespace gzEngineSDK {

  class Device;
  class DeviceContext;
  class SwapChain;
  class DXRenderTarget;
  class DXTexture;
  class DXBuffer;
  class DXDepth;
  class DXInputLayout;
  class DXPixelShader;
  class DXVertexShader;
  class DXShader;
  class DXViewPort;
  class DXSamplerState;
}

/*
#if GZ_PLATFORM == GZ_PLATFORM_WIN32
# if GZ_COMPILER == GZ_COMPILER_MSVC
#   if defined( GZ_STATIC_LIB )
#     define GZ_DIRECTX_EXPORT
#   else
#     if defined( GZ_DIRECTX_EXPORTS )
#       define GZ_DIRECTX_EXPORT __declspec( dllexport )
#     else
#       define GZ_DIRECTX_EXPORT __declspec( dllimport )
#     endif
#   endif
# else //Any other compiler
#   if defined( GZ_STATIC_LIB )
#     define GZ_DIRECTX_EXPORT
#   else
#     if defined( GZ_DIRECTX_EXPORTS )
#       define GZ_DIRECTX_EXPORT __attribute__ ((dllexport))
#     else
#       define GZ_DIRECTX_EXPORT __attribute__ ((dllimport))
#     endif
#   endif
# endif
# define GZ_DIRECTX_HIDDEN
#else //Linux/Mac Settings
# define GZ_DIRECTX_EXPORT __attribute__ ((visibility ("default")))
# define GZ_DIRECTX_HIDDEN __attribute__ ((visibility ("hidden")))
#endif*/

