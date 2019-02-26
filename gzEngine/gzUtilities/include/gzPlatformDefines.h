#pragma once
#define GZ_PLATFORM_WIN32       1     //Windows Platform
#define GZ_PLATFORM_LINUX       2     //Linux Platform
#define GZ_PLATFORM_OSX         3     //Apple Platform
#define GZ_PLATFORM_IOS         4     //Iphone Platform
#define GZ_PLATFORM_ANDROID     5     //Andoid Platform
                                
#define GZ_COMPILER_MSVC        1     //Visual Studio Compiler
#define GZ_COMPILER_GNUC        2     //GCC Compiler
#define GZ_COMPILER_INTEL       3     //Intel Compiler
#define GZ_COMPILER_CLANG       4     //Clang Studio Compiler

#define GZ_ARCHITECTURE_X86_32  1     //Intel x86 32 bits
#define GZ_ARCHITECTURE_X86_32  2     //Intel x86 64 bits

#define GZ_ENDIAN_LITTLE        1     //little Endian
#define GZ_ENDIAN_BIG           2     //Big Endian

//Define the actual endian type (little endian for Windows, Linux and Apple)
#define GZ_ENDIAN GZ_ENDIAN_LITTLE

#define GZ_VERSION_MAJOR        0     //Engine version mayor value   
#define GZ_VERSION_MINOR        4     //Engine version minor value   
#define GZ_VERSION_PATCH        0     //Engine version patch value   
#define GZ_VERSION_BUILD        0     //This is an Editor Build  

//Define if on a crash we want to report warnings on unknown symbols
#define GZ_DEBUG_DETAILED_SYMBOLS  1

/************************************************************************/
/* Compiler type and version.                                                                   
/************************************************************************/ 

#if defined(__clang__)
# define GZ_COMPILER GZ_COMPILER_CLANG
# define GZ_THREADLOCAL __thread
# define GZ_STDCALL __attribute__((stdcall))
# define GZ_CDECL __attribute__((cdecl))
# define GZ_FALLTHROUGH [[clang::fallthrough]];
#elif defined(__GNUC__)
# define GZ_COMPILER GZ_COMPILER_GNUC
# define GZ_COMP_VER (((__GNUC__)*100)+(__GNUC_MINOR__*10)+__GNUC_PATCHLEVEL__)
# define GZ_THREADLOCAL __thread
# define GZ_STDCALL __attribute__((stdcall))
# define GZ_CDECL __attribute__((cdecl))
# define GZ_FALLTHROUGH __attribute__((fallthrough));
#elif defined(__INTEL_COMPILER)
# define GZ_COMPILER GZ_COMPILER_INTEL
# define GZ_COMP_VER __INTEL_COMPILER
# define GZ_STDCALL __stdcall
# define GZ_CDECL __cdecl
# define GZ_FALLTHROUGH

/**
 * 
 *
 */

//
#elif defined(_MSC_VER)
# define GZ_COMPILER GZ_COMPILER_MSVC
# define GZ_COMP_VER _MSC_VER
# define GZ_THREADLOCAL __declspec(thread)
# define GZ_STDCALL __stdcall
# define GZ_CDECL __cdecl
# define GZ_FALLTHROUGH
# undef __PRETTY_FUNCTION__
# define __PRETTY_FUNCTION__ __FUNCSIG__
#else
//No known compiler found, send the error to the output(if any)
# pragma error "No known compiler."
#endif

/************************************************************************/
/* See if we can use __forceinline or if we need to use __inline instead                                                                  
/************************************************************************/

#if GZ_COMPILER == GZ_COMPILER_MSVC     //If we are compiling on Visual Studio
# if GZ_COMP_VER >= 1200                //If we are on Visual Studio 6 or higher
#  define FORCEINLINE __forceinline     //Set __forceinline
#  ifndef RESTRICT
#   define RESTRICT __restrict          //No alias hint
#  endif
# endif
#elif defined(__MINGW32__)              //If we are on a Unix type system
# if !defined(FORCEINLINE)
#  define FORCEINLINE __inline          //Set __inline
#  ifndef RESTRICT
#   define RESTRICT                     //No alias hint
#  endif
# endif
#else                                   //Any other compiler
#  define FORCEINLINE __inline          //Set inline
#  ifndef RESTRICT
#   define RESTRICT __restrict
#  endif
#endif

/************************************************************************/
/* Finds the current platform                                                                    
/************************************************************************/

#if defined(__WIN32__) || defined(_WIN32)	 //If its a Windows platform
# define GZ_PLATFORM GZ_PLATFORM_WIN32
#elif defined( __APPLE_CC__ )	 //if its a Apple platform
# define GZ_PLATFORM GZ_PLATFORM_OSX
#else 	//Will consider it as a Linux platform
# define GZ_PLATFORM GZ_PLATFORM_LINUX
#endif

/************************************************************************/
/* Finds the architecture type                                                                   
/************************************************************************/

#if defined(__x86_64__) || defined(_M_X64)    //
# define GZ_ARCH_TYPE GZ_ARCHITECTURE_X86_64
#else
# define GZ_ARCH_TYPE GZ_ARCHITECTURE_X86_32
#endif

/************************************************************************/
/* Memory Alignment macros
/************************************************************************/

#if GZ_COMPILER == GZ_COMPILER_MSVC      //If we are compiling on Visual Studio
# define MS_ALIGN(n) __declspec(align(n))
# ifndef GCC_PACK
#  define GCC_PACK(n)
# endif
#else 
# define MS_ALIGN(n)
# define GCC_PACK(n) __attribute__((packed, aligned(n)))
# define GCC_ALIGN(n) __attribute__((aligned(n)))
#endif

/************************************************************************/
/* For throw override (deprecated on c++11 but visual studio does
/* not have handle no exception)                                                                     
/************************************************************************/

#if GZ_COMPILER == GZ_COMPILER_MSVC
# define _NOEXCEPT noexcept
#elif GZ_COMPILER == GZ_COMPILER_INTEL
# define _NOEXCEPT noexcept
#elif GZ_COMPILER == GZ_COMPILER_GNUC
# define _NOEXCEPT noexcept
#else
# define _NOEXCEPT
#endif

/************************************************************************/
/* Library export specifics                                                                  
/************************************************************************/

#if GZ_PLATFORM == GZ_PLATFORM_WIN32
# if GZ_COMPILER == GZ_COMPILER_MSVC
#  if defined( GZ_STATIC_LIB )
#   define GZ_UTILITY_EXPORT
#  else
#   if defined( GZ_UTILITY_EXPORTS )
#    define GZ_UTILITY_EXPORT __declspec( dllexport )
#   else 
#    define GZ_UTILITY_EXPORT __declspec( dllimport )
#   endif
#  endif
# else //Any other compiler
#  if defined( GZ_STATIC_LIB )
#   define GZ_UTILITY_EXPORT
#  else
#   if defined( GZ_UTILITY_EXPORTS )
#    define XX_UTILITY_EXPORT __attribute__(( dllexport ))
#   else
#    define XX_UTILITY_EXPORT __attribute__(( dllimport ))
#   endif
#  endif
# endif
# define GZ_UTILITY_HIDDEN
#else //Linux/Mac settings
# define GZ_UTILITY_EXPORT __attribute__((visibility ("default")))
# define GZ_UTILITY_HIDDEN __attribute__((visibility ("hidden")))
#endif

//DLL export for plugins
#if GZ_PLATFORM == GZ_PLATFORM_WIN32
# if GZ_COMPILER == GZ_COMPILER_MSVC
#  define GZ_PLUGIN_EXPORT __declspec(dllexport)
# else
#  define GZ_PLUGIN_EXPORT __attribute__((dllexport))
# endif
#else //Linux/Mac settings
# define GZ_PLUGIN_EXPORT __attribute__((visibility ("default")))
#endif

/************************************************************************/
/*                                                                      */
/************************************************************************/
#if GZ_PLATFORM == GZ_PLATFORM_WIN32
# if defined(_DEBUG) || defined(DEBUG)
#   define GZ_DEBUG_MODE 1
# else
#   define GZ_DEBUG_MODE 0
# endif
# if GZ_COMPILER == GZ_COMPILER_INTEL
#   define GZ_THREADLOCAL __declspec(thread)
# endif
#endif

/************************************************************************/
/*                                                                      */
/************************************************************************/
#if GZ_PLATFORM == GZ_PLATFORM_LINUX || GZ_PLATFORM == GZ_PLATFORM_OSX
#define stricmp strcasecmp

//
# if defined(_DEBUG) || defined(DEBUG)
#   define GZ_DEBUG_MODE 1
# else
#   define GZ_DEBUG_MODE 0
# endif
# if GZ_COMPILER == GZ_COMPILER_INTEL
#   define GZ_THREADLOCAL __thread
# endif
#endif

/************************************************************************/
/*                                                                      */
/************************************************************************/
#if GZ_DEBUG_MODE
# define GZ_DEBUG_ONLY(x) x
# define GZ_ASSERT(x) assert(x)
#else
# define GZ_DEBUG_ONLY(x)
# define GZ_ASSERT(x)
#endif

/************************************************************************/
/*                                                                      */
/************************************************************************/

//
#if GZ_COMPILER == GZ_COMPILER_MSVC
/**
 * 
 */

//
# define _CRT_SECURE_NO_WARNINGS
/**
 * 
 */

#pragma  warning(disable : 4201)
#pragma  warning(disable : 4251)
#pragma  warning(disable : 4996)
#pragma  warning(disable : 4503)

#endif


