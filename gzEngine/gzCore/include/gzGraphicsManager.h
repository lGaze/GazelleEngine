/**************************************************************************/
/* @filename gzGraphicsManager.h
/* @author Victor Flores 
/* @date 2019/03/03
/* @brief 
/**************************************************************************/
#pragma once

#include "gzPrerequisitesCore.h"
#include <gzModule.h>


namespace gzEngineSDK {
class GZ_CORE_EXPORT GraphicsManager : public Module<GraphicsManager>
{
 public:
   
  /**
   * @brief default constructor
   */
  GraphicsManager();
	
  /**
   * @brief default destructor
   */
  virtual ~GraphicsManager();
	
  /************************************************************************/
  /* GraphicsManager functions                                            */
  /************************************************************************/
  
  /**
   * @brief 
   */
  virtual bool
  InitGraphicsManager(void* hWnd, int32 width, int32 height ) = 0;

  /**
   * @brief 
   */
  virtual bool
  CreateRenderTargetView() = 0;

  /**
   * @brief 
   */
  virtual bool
  CreateTexture2D( uint32 width,
                   uint32 height,
                   uint32 format,
                   uint32 usage ) = 0;
  /**
   * @brief 
   */
  virtual bool
  CreateDepthStencilView() = 0;

  /**
   * @brief 
   */
  virtual bool
  CreateVertexShader() = 0;

  /**
   * @brief 
   */
  virtual bool
  CreateInputLayout() = 0;

  /**
   * @brief 
   */
  virtual bool
  CreatePixelShader() = 0;

  /**
   * @brief 
   */
  virtual bool
  CreateBuffer( uint32 usage,
                uint32 bytewidth,
                uint32 bufferType,
                uint32 cpuflags,
                const void * pInitialData ) = 0;

  /**
   * @brief 
   */
  virtual bool
  CreateVertexAndIndexBufferFromFile( std::string file ) = 0;

  /**
   * @brief 
   */
  virtual bool
  CreateSamplerState() = 0;

  /**
   * @brief 
   */
  virtual void
  SetRenderTargets( uint32 NumViews ) = 0;

   /**
   * @brief
   */
  virtual void 
  SetViewports( uint32 NumViewports ) = 0;

  /**
   * @brief
   */
  virtual void 
  SetInputLayout() = 0;

  /**
   * @brief
   */
  virtual void
  SetVertexBuffers( uint32 StartSlot,
                      uint32 NumBuffers,
                      const uint32 *pStrides,
                      const uint32 *pOffsets ) = 0;

  /**
   * @brief
   */
  virtual void
  SetIndexBuffer( int32 Format,
                  uint32 Offset ) = 0;

  /**
   * @brief
   */
  virtual void 
  SetPrimitiveTopology( uint32 Topology ) = 0;

  /**
   * @brief
   */
  virtual void
  UpdateSubresource( uint32 BufferIndex,
                     uint32 DstSubresource,
                     const void *pDstBox,
                     const void *pSrcData,
                     uint32 SrcRowPitch,
                     uint32 SrcDepthPitch ) = 0;

  /**
   * @brief
   */
  virtual void 
  ClearRenderTargetView( const float ColorRGBA[4] ) = 0;

  /**
   * @brief
   */
  virtual void
  ClearDepthStencilView( uint32 ClearFlags,
                         float Depth,
                         uint8 Stencil ) = 0;

  /**
   * @brief
   */
  virtual void
  SetVertexShader( void *const *ppClassInstances,
                   uint32 NumClassInstances ) = 0;

  /**
   * @brief
   */
  virtual void
  SetVSConstantBuffers( uint32 BufferIndex,
                        uint32 StartSlot,
                        uint32 NumBuffers ) = 0;

  /**
   * @brief
   */
  virtual void
  SetPixelShader( void *const *ppClassInstances,
                  uint32 NumClassInstances ) = 0;

  /**
   * @brief
   */
  virtual void
  SetPSConstantBuffers( uint32 BufferIndex,
                        uint32 StartSlot,
                        uint32 NumBuffers ) = 0;

  /**
   * @brief
   */
  virtual void
  SetShaderResources( uint32 StartSlot,
                      uint32 NumViews ) = 0;

  /**
   * @brief
   */
  virtual void
  SetSamplers( uint32 StartSlot,
               uint32 NumSamplers ) = 0;

  /**
   * @brief
   */
  virtual void
  DrawIndexed( uint32 indexCount,
               uint32 StartIndexLocation,
               int32 BaseVertexLocation ) = 0;

  /**
   * @brief
   */
  virtual bool 
  GetBuffer( uint32 Buffer ) = 0;

  /**
   * @brief
   */
  virtual bool 
  Present( uint32 SyncInterval, uint32 Flags ) = 0;

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
	
 public:
   
 };

/*
 GraphicsManager&
 g_GraphicsManager() {
   return GraphicsManager::instance();
 }*/
}