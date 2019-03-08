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
                const void * pInitialData ) override;

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

  /**
   * @brief 
   */
  virtual void
  SetRenderTargets( uint32 NumViews ) override;

  /**
   * @brief 
   */
  virtual void
  SetViewports( uint32 NumViewports ) override;

  /**
   * @brief 
   */
  virtual void
  SetInputLayout() override;

  /**
   * @brief 
   */
  virtual void
  SetVertexBuffers( uint32 StartSlot,
                    uint32 NumBuffers,
                    const uint32 *pStrides,
                    const uint32 *pOffsets ) override;

  /**
   * @brief 
   */
  virtual void
  SetIndexBuffer( int32 Format, uint32 Offset ) override;

  /**
   * @brief 
   */
  virtual void
  SetPrimitiveTopology( uint32 Topology ) override;

  /**
   * @brief 
   */
  virtual void
  UpdateSubresource( uint32 BufferIndex,
                     uint32 DstSubresource,
                     const void *pDstBox,
                     const void *pSrcData, 
                     uint32 SrcRowPitch, 
                     uint32 SrcDepthPitch ) override;


  /**
   * @brief 
   */
  virtual void
  ClearRenderTargetView( const float ColorRGBA[4] ) override;

  /**
   * @brief 
   */
  virtual void
  ClearDepthStencilView( uint32 ClearFlags, float Depth, uint8 Stencil ) override;

  /**
   * @brief 
   */
  virtual void
  SetVertexShader( void *const *ppClassInstances,
                   uint32 NumClassInstances ) override;


  /**
   * @brief 
   */
  virtual void
  SetVSConstantBuffers( uint32 BufferIndex, 
                        uint32 StartSlot, 
                        uint32 NumBuffers ) override;

  /**
   * @brief 
   */
  virtual void 
  SetPixelShader( void *const *ppClassInstances,
                  uint32 NumClassInstances ) override;

  /**
   * @brief 
   */
  virtual void 
  SetPSConstantBuffers( uint32 BufferIndex, uint32 StartSlot, uint32 NumBuffers ) override;

  /**
   * @brief 
   */
  virtual void 
  SetShaderResources( uint32 StartSlot, uint32 NumViews ) override;

  /**
   * @brief 
   */
  virtual void
  SetSamplers( uint32 StartSlot, uint32 NumSamplers ) override;

  /**
   * @brief 
   */
  virtual void
  DrawIndexed(uint32 indexCount,
               uint32 StartIndexLocation, 
               int32 BaseVertexLocation ) override;

  /**
   * @brief 
   */
  virtual bool
  GetBuffer( uint32 Buffer ) override;

  /**
   * @brief 
   */
  virtual bool 
  Present( uint32 SyncInterval, uint32 Flags ) override;

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
    * @brief Vector of constantBuffers
    */
   Vector<Buffer*> m_constantBuffers;

 };
}