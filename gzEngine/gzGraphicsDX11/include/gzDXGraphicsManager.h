/**************************************************************************/
/* @filename gzDXGraphicsManager.h
/* @author Victor Flores 
/* @date 2019/03/03
/* @brief 
/**************************************************************************/
#pragma once

#include "gzDXPrerequisites.h"
#include <gzGraphicsManager.h>


namespace gzEngineSDK {
class DXGraphicsManager : public GraphicsManager
{
 public:
   
  /**
   * @brief default constructor
   */
  DXGraphicsManager();
	
  /**
   * @brief default destructor
   */
  ~DXGraphicsManager() = default;
	
  /************************************************************************/
  /* DXGraphicsmanager functions                                          */
  /************************************************************************/

  /**
   * @brief Initializes all the things that GraphicsManager needs
   */
  virtual bool
  InitGraphicsManager(void* hWnd, int32 width, int32 heigh) override;

  /**
   * @brief 
   */
  virtual bool
  CreateRenderTargetView() override;

  /**
   * @brief 
   */
  virtual bool 
  CreateTexture2D( uint32 width,
                   uint32 height,
                   uint32 format,
                   uint32 usage ) override;

  /**
   * @brief 
   */
  virtual bool 
  CreateDepthStencilView() override;

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
	
 public:

   /**
    * @brief Pointer to the Device Class
    */
   Device * m_pdevice;

   /**
    * @brief Pointer to the DeviceContext Class
    */
   DeviceContext * m_pdeviceContext;

   /**
    * @brief Pointer to the SwapChain Class
    */
   SwapChain * m_pswapChain;

   /**
    * @brief Pointer to the RenderTarget Class
    */
   RenderTarget * m_prenderTarget;

   /**
    * @brief 
    */
   Texture * m_ptexture;

 };
}