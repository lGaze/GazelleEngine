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

  /**
   * @brief 
   */
  virtual bool 
  CreateVertexShader() override;

  /**
   * @brief 
   */
  virtual bool 
  CreateInputLayout() override;

  /**
   * @brief 
   */
  virtual bool 
  CreatePixelShader() override;

  /**
   * @brief 
   */
  virtual bool
  CreateBuffer( uint32 usage,
                uint32 bytewidth,
                uint32 bufferType,
                uint32 cpuflags,
                const D3D11_SUBRESOURCE_DATA * pInitialData ) override;

  /**
   * @brief 
   */
  virtual bool 
  CreateVertexAndIndexBufferFromFile( std::string file ) override;

  /**
   * @brief 
   */
  virtual bool 
  CreateSamplerState() override;

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
    * @brief Pointer to the Texture Class
    */
   Texture * m_ptexture;

   /**
    * @brief Pointer to the Depth Class
    */
   Depth * m_pdepth;

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
   ViewPort * m_pviewPort;

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
    * @brief 
    */
   Vector<Buffer*> m_constantBuffers;
 };
}