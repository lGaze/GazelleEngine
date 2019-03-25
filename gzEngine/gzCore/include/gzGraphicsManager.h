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
  virtual 
  ~GraphicsManager();
	
  /************************************************************************/
  /* GraphicsManager functions                                            */
  /************************************************************************/
  
  /**
   * @brief 
   */
  virtual bool
  initGraphicsManager(void* hWnd, int32 width, int32 height ) = 0;

  /**
   * @brief 
   */
  virtual Texture*
  createTexture2D( TEXTURE2D_DESCRIPTOR &textureInfo ) = 0;

  /**
   * @brief 
   */
  virtual RenderTarget*
  createRenderTarget( Texture * texture ) = 0;


  /**
   * @brief 
   */
  virtual RenderTarget*
  creteRenderTargetFromBackBuffer() = 0;


  /**
   * @brief 
   */
  virtual Depth*
  createDepthStencilView( DEPTH_STENCIL_VIEW_DESCRIPTOR &desc,
                          TEXTURE2D_DESCRIPTOR &texDesc ) = 0;


/*
  / **
   * @brief 
   * /
  virtual bool
  createVertexShader() = 0;

  / **
   * @brief 
   * /
  virtual bool
  createInputLayout() = 0;

  / **
   * @brief 
   * /
  virtual bool
  createPixelShader() = 0;

  /**
   * @brief 
   */
  virtual Buffer*
  createBuffer( BUFFER_DESCRIPTOR &bufferDesc,
                const SUBRESOUCE_DATA * pInitialData ) = 0;

  /**
   * @brief 
   * /
  virtual bool
  createVertexAndIndexBufferFromFile( std::string file ) = 0;

  /**
   * @brief 
   */
  virtual SamplerState*
  createSamplerState( SAMPLER_DESC &samplerDesc ) = 0;

  /**
   * @brief This function sets the rendet target view
   */
  virtual void
  setRenderTargets( uint32 NumViews, 
                    RenderTarget * renderTarget, 
                    Depth * depth ) = 0;

  /**
   * @brief This function sets the viewport
   */
  virtual void 
  setViewports( uint32 NumViewports, VIEWPORT_DESCRIPTOR &viewportDesc ) = 0;

  /**
   * @brief
   * /
  virtual void 
  setInputLayout() = 0;

  /**
   * @brief
   */
  virtual void
  setVertexBuffers( uint32 StartSlot,
                    uint32 NumBuffers,
                    Buffer * buffer,
                    const uint32 *pStrides,
                    const uint32 *pOffsets ) = 0;

  /**
   * @brief
   */
  virtual void
  setIndexBuffer( int32 Format,
                  Buffer * buffer,
                  uint32 Offset ) = 0;

  /**
   * @brief
   * /
  virtual void 
  setPrimitiveTopology( uint32 Topology ) = 0;

  / **
   * @brief
   * /
  virtual void
  updateSubresource( uint32 BufferIndex,
                     uint32 DstSubresource,
                     const void *pDstBox,
                     const void *pSrcData,
                     uint32 SrcRowPitch,
                     uint32 SrcDepthPitch ) = 0;
*/

  /**
   * @brief
   */
  virtual void 
  clearRenderTargetView( const float ColorRGBA[4],
                         RenderTarget * renderTarget ) = 0;

  /**
   * @brief
   */
  virtual void
  clearDepthStencilView( uint32 ClearFlags,
                         float Depthf,
                         uint8 Stencil,
                         Depth * depth) = 0;


 /* / **
   * @brief
   * /
  virtual void
  setVertexShader( void *const *ppClassInstances,
                   uint32 NumClassInstances ) = 0;

  / **
   * @brief
   * /
  virtual void
  setVSConstantBuffers( uint32 BufferIndex,
                        uint32 StartSlot,
                        uint32 NumBuffers ) = 0;

  / **
   * @brief
   * /
  virtual void
  setPixelShader( void *const *ppClassInstances,
                  uint32 NumClassInstances ) = 0;

  / **
   * @brief
   * /
  virtual void
  setPSConstantBuffers( uint32 BufferIndex,
                        uint32 StartSlot,
                        uint32 NumBuffers ) = 0;

  / **
   * @brief
   * /
  virtual void
  setShaderResources( uint32 StartSlot,
                      uint32 NumViews ) = 0;

  /**
   * @brief
   */
  virtual void
  setSamplerState( uint32 startSlot, 
                   SamplerState* sampler, 
                   uint32 numSamplers   ) = 0;

  /**
   * @brief
   * /
  virtual void
  drawIndexed( uint32 indexCount,
               uint32 StartIndexLocation,
               int32 BaseVertexLocation ) = 0;
*/

/*
  / **
   * @brief
   * /
  virtual bool 
  getBuffer( uint32 Buffer ) = 0;*/

  /**
   * @brief
   */
  virtual bool 
  present( uint32 SyncInterval, uint32 Flags ) = 0;

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