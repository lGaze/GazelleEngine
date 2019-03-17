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
  initGraphicsManager(void* hWnd, int32 width, int32 heigh) override;

  /**
   * @brief 
   */
  virtual bool
  createRenderTarget() override;

  /**
   * @brief 
   */
  virtual bool 
  createTexture2D( uint32 width,
                   uint32 height,
                   uint32 format,
                   uint32 usage ) override;

  /**
   * @brief 
   */
  virtual bool 
  createDepthStencilView() override;

  /**
   * @brief 
   */
  virtual bool 
  createVertexShader() override;

  /**
   * @brief 
   */
  virtual bool 
  createInputLayout() override;

  /**
   * @brief 
   */
  virtual bool 
  createPixelShader() override;

  /**
   * @brief 
   */
  virtual bool
  createBuffer( uint32 usage,
                uint32 bytewidth,
                uint32 bufferType,
                uint32 cpuflags,
                const void * pInitialData ) override;

  /**
   * @brief 
   */
  virtual bool 
  createVertexAndIndexBufferFromFile( std::string file ) override;

  /**
   * @brief 
   */
  virtual bool 
  createSamplerState() override;

  /**
   * @brief 
   */
  virtual void
  setRenderTargets( uint32 NumViews ) override;

  /**
   * @brief 
   */
  virtual void
  setViewports( uint32 NumViewports ) override;

  /**
   * @brief 
   */
  virtual void
  setInputLayout() override;

  /**
   * @brief 
   */
  virtual void
  setVertexBuffers( uint32 StartSlot,
                    uint32 NumBuffers,
                    const uint32 *pStrides,
                    const uint32 *pOffsets ) override;

  /**
   * @brief 
   */
  virtual void
  setIndexBuffer( int32 Format, uint32 Offset ) override;

  /**
   * @brief 
   */
  virtual void
  setPrimitiveTopology( uint32 Topology ) override;

  /**
   * @brief 
   */
  virtual void
  updateSubresource( uint32 BufferIndex,
                     uint32 DstSubresource,
                     const void *pDstBox,
                     const void *pSrcData, 
                     uint32 SrcRowPitch, 
                     uint32 SrcDepthPitch ) override;


  /**
   * @brief 
   */
  virtual void
  clearRenderTargetView( const float ColorRGBA[4] ) override;

  /**
   * @brief 
   */
  virtual void
  clearDepthStencilView( uint32 ClearFlags, float Depth, uint8 Stencil ) override;

  /**
   * @brief 
   */
  virtual void
  setVertexShader( void *const *ppClassInstances,
                   uint32 NumClassInstances ) override;


  /**
   * @brief 
   */
  virtual void
  setVSConstantBuffers( uint32 BufferIndex, 
                        uint32 StartSlot, 
                        uint32 NumBuffers ) override;

  /**
   * @brief 
   */
  virtual void 
  setPixelShader( void *const *ppClassInstances,
                  uint32 NumClassInstances ) override;

  /**
   * @brief 
   */
  virtual void 
  setPSConstantBuffers( uint32 BufferIndex, uint32 StartSlot, uint32 NumBuffers ) override;

  /**
   * @brief 
   */
  virtual void 
  setShaderResources( uint32 StartSlot, uint32 NumViews ) override;

  /**
   * @brief 
   */
  virtual void
  setSamplers( uint32 StartSlot, uint32 NumSamplers ) override;

  /**
   * @brief 
   */
  virtual void
  drawIndexed(uint32 indexCount,
               uint32 StartIndexLocation, 
               int32 BaseVertexLocation ) override;

  /**
   * @brief 
   */
  virtual bool
  getBuffer( uint32 Buffer ) override;

  /**
   * @brief 
   */
  virtual bool 
  present( uint32 SyncInterval, uint32 Flags ) override;

  /**
   * @brief 
   */
  virtual bool 
  creteBackBuffer() override;

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