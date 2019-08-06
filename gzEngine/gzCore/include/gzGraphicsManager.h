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
  virtual VertexShader*
  CreateVertexShader( const WString & fileName,
                      const String & EntryPoint,
                      const String & ShaderModel ) = 0;

  /**
   * @brief 
   */
  virtual InputLayout*
  createInputLayout( VertexShader * vertexShader ) = 0;


  /**
   * @brief 
   */
  virtual PixelShader*
  createPixelShader( const WString & fileName,
                     const String & EntryPoint,
                     const String & ShaderModel ) = 0;

  /**
   * @brief 
   */
  virtual Buffer*
  createBuffer( BUFFER_DESCRIPTOR &bufferDesc,
                const SUBRESOUCE_DATA * pInitialData ) = 0;

  /**
   * @brief 
   */
  virtual SamplerState*
  createSamplerState( SAMPLER_DESCRIPTOR &samplerDesc ) = 0;

  /**
   * @brief This function sets the rendet target view
   */
  virtual void
  setRenderTargets( uint32 NumViews, 
                    Texture * renderTarget, 
                    Texture * depth ) = 0;

  /**
   * @brief This function sets the viewport
   */
  virtual void 
  setViewports( uint32 NumViewports, VIEWPORT_DESCRIPTOR &viewportDesc ) = 0;

  /**
   * @brief
   */
  virtual void 
  setInputLayout( InputLayout * inputLayout ) = 0;

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
   */
  virtual void 
  setPrimitiveTopology( uint32 Topology ) = 0;

  /**
   * @brief
   */
  virtual void
  updateSubresource( Buffer * buffer, const void *pSrcData ) = 0;

  /**
   * @brief
   */
  virtual void 
  clearRenderTargetView( const float ColorRGBA[4],
                         Texture * renderTarget ) = 0;

  /**
   * @brief
   */
  virtual void
  clearDepthStencilView( uint32 ClearFlags,
                         float Depthf,
                         uint8 Stencil,
                         Texture * depth) = 0;


  /**
   * @brief
   */
  virtual void
  setVertexShader( VertexShader * vertexShader ) = 0;

  /**
   * @brief
   */
  virtual void
  setVSConstantBuffers( Buffer * buffer,
                        uint32 StartSlot,
                        uint32 NumBuffers ) = 0;

  /**
   * @brief
   */
  virtual void
  setPixelShader( PixelShader * pixelShader ) = 0;

  /**
   * @brief
   */
  virtual void
  setPSConstantBuffers( Buffer * buffer,
                        uint32 StartSlot,
                        uint32 NumBuffers ) = 0;

  /**
   * @brief
   */
  virtual void
  setShaderResources( Texture*texture,
                      uint32 StartSlot,
                      uint32 NumViews ) = 0;

  /**
   * @brief
   */
  virtual void
  setSamplerState( uint32 startSlot, 
                   SamplerState* sampler, 
                   uint32 numSamplers   ) = 0;


  //TODO: Make it better with the mesh 

  /**
   * @brief
   */
  virtual void
  drawIndexed( uint32 indexCount,
               uint32 StartIndexLocation,
               int32 BaseVertexLocation ) = 0;

  /**
   * @brief
   */
  virtual bool 
  present( uint32 SyncInterval, uint32 Flags ) = 0;

  /**
   * @brief 
   */
  virtual Texture *
  LoadTextureFromFile( const String filename ) = 0;

  /**
   * @brief 
   */
  virtual Texture *
  createTextureFromBackBuffer() = 0;

  /**
   * @brief 
   */
  virtual RasterizerState *
  createRasterizerState(RASTERIZER_DESCRIPTOR desc) = 0;

  /**
   * @brief 
   */
  virtual void
  setRasterizerState( RasterizerState * rasterizerState ) = 0;

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

  protected:

  //TODO: Move this to the resource manager
   Map<String, Texture *> m_textureMap;
  
 };

/*
 GraphicsManager&
 g_GraphicsManager() {
   return GraphicsManager::instance();
 }*/

}