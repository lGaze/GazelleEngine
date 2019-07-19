/**************************************************************************/
/* @filename gzPrerequisitesCore.h
/* @author Victor Flores
/* @date 2019/02/26
/* @brief
/**************************************************************************/
#pragma once

#include <gzPrerequisitesUtilities.h>
#include "gzGraphicsDescriptors.h"
#include <gzMatrix4.h>
#include <gzVector3f.h>
#include <gzVector2f.h>
#include <gzVector4f.h>



namespace gzEngineSDK {

  class Texture;
  class ViewPort;
  class Buffer;
  class SamplerState;
  class Shader;
  class VertexShader;
  class PixelShader;
  class InputLayout;
  class RasterizerState;
  class Model;
  class Component;
  class GameObject;
  class Camera;
}

//DLL export
#if GZ_PLATFORM == GZ_PLATFORM_WIN32
# if GZ_COMPILER == GZ_COMPILER_MSVC
#   if defined( GZ_STATIC_LIB )
#     define GZ_CORE_EXPORT
#   else
#     if defined( GZ_CORE_EXPORTS )
#       define GZ_CORE_EXPORT __declspec( dllexport )
#     else
#       define GZ_CORE_EXPORT __declspec( dllimport )
#     endif
#   endif
# else  //Any other Compiler
#   if defined( GZ_STATIC_LIB )
#     define GZ_CORE_EXPORT
#   else
#     if defined( GZ_CORE_EXPORTS )
#       define GZ_CORE_EXPORT __attribute__ ((dllexport))
#     else
#       define GZ_CORE_EXPORT __attribute__ ((dllimport))
#     endif
#   endif
# endif
# define GZ_CORE_HIDDEN
#else //Linux/Mac settings
# define GZ_CORE_EXPORT __attribute__ ((visibility ("default")))
# define GZ_CORE_HIDDEN __attribute__ ((visibility ("hidden")))
#endif