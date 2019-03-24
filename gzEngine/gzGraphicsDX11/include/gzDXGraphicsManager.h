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
  virtual ~DXGraphicsManager() {} 
	
  /************************************************************************/
  /* DXGraphicsmanager functions                                          */
  /************************************************************************/

  /**
   * @brief Initializes the Graphics Device, SwapChain and DeviceContext
   */
  virtual bool 
  initGraphicsManager( void* hWnd, int32 width, int32 height ) override;

  /**
   * @brief Creates a Texture2D from a Descriptor
   */
  virtual Texture* 
  createTexture2D( TEXTURE2D_DESCRIPTOR &textureInfo ) override;



  virtual RenderTarget* 
  createRenderTarget( Texture * texture ) override;


  /**
   * @brief Creates a RenderTarget from back buffer
   */
  virtual RenderTarget* 
  creteRenderTargetFromBackBuffer() override;


  /**
   * @brief Sets the render target with the given render taget
   */
  virtual void
  setRenderTargets( uint32 NumViews,
                    RenderTarget * renderTarget, 
                    Depth * depth ) override;


  /**
   * @brief Clears the given render target with the given color
   */
  virtual void 
  clearRenderTargetView( const float ColorRGBA[4], 
                         RenderTarget * renderTarget ) override;

  /**
   * @brief 
   */
  virtual bool 
  present( uint32 SyncInterval, uint32 Flags ) override;

  /**
   * @brief Creates a DepthStencil with the given descriptor
   */
  virtual Depth* 
  createDepthStencilView( DEPTH_STENCIL_VIEW_DESCRIPTOR &desc,
                          TEXTURE2D_DESCRIPTOR &texDesc ) override;


  virtual void 
  clearDepthStencilView( uint32 ClearFlags, 
                         float Depthf, 
                         uint8 Stencil, 
                         Depth * depth ) override;


  virtual void 
  setViewports( uint32 NumViewports, 
                VIEWPORT_DESCRIPTOR &viewportDesc ) override;

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
  DXRenderTarget * m_prenderTarget;

  /**
   * @brief Pointer to the Texture Class
   */
  DXTexture * m_ptexture;

  /**
   * @brief Pointer to the Depth Class
   */
  DXDepth * m_pdepth;

  /**
   * @brief Pointer to the InputLayput Class
   */
  InputLayout * m_pinputLayout;

  /**
   * @brief Pointer to the Vertex Shader Class
   */
  VertexShader * m_pvertexShader;

  /**
   * @brief Pointer to the Pixel Shader Class
   */
  PixelShader * m_ppixelShader;

  /**
   * @brief Pointer to the Shader Class
   */
  Shader * m_pshader;

  /**
   * @brief Pointer to the View Port Class
   */
  DXViewPort * m_pviewPort;

  /**
   * @brief Pointer to the Sampler State Class
   */
  SamplerState * m_psamplerState;

  /**
   * @brief 
   */
  Buffer * m_pvertexBuffer;

  /**
   * @brief 
   */
  Buffer * m_pindexBuffer;

  /**
   * @brief Vector of constantBuffers
   */
  Vector<Buffer*> m_constantBuffers;

 };
}