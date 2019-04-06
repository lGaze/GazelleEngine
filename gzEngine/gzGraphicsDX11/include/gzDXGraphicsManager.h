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


  /**
   * @brief 
   */
  virtual RenderTarget* 
  createRenderTarget( Texture * texture ) override;


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

  /**
   * @brief 
   */
  virtual void 
  clearDepthStencilView( uint32 ClearFlags, 
                         float Depthf, 
                         uint8 Stencil, 
                         Depth * depth ) override;

  /**
   * @brief 
   */
  virtual void 
  setViewports( uint32 NumViewports, 
                VIEWPORT_DESCRIPTOR &viewportDesc ) override;

  /**
   * @brief 
   */
  virtual Buffer*
  createBuffer( BUFFER_DESCRIPTOR &bufferDesc, 
                const SUBRESOUCE_DATA * pInitialData ) override;


  /**
   * @brief 
   */
  virtual void 
  setVertexBuffers( uint32 StartSlot, 
                    uint32 NumBuffers, 
                    Buffer * buffer, 
                    const uint32 *pStrides, 
                    const uint32 *pOffsets ) override;

  /**
   * @brief 
   */
  virtual void 
  setIndexBuffer( int32 Format, Buffer * buffer, uint32 Offset ) override;


  /**
   * @brief 
   */
  virtual SamplerState* 
  createSamplerState( SAMPLER_DESCRIPTOR &samplerDesc ) override;


  

  /**
   * @brief 
   */
  virtual void 
  setSamplerState( uint32 startSlot, 
                   SamplerState* sampler, 
                   uint32 numSamplers ) override;


  /**
   * @brief 
   */
  virtual VertexShader* 
  CreateVertexShader( const WString & fileName,
                      const String & EntryPoint,
                      const String & ShaderModel ) override;

  /**
   * @brief 
   */
  virtual void 
  setVertexShader( VertexShader * vertexShader ) override;

  /**
   * @brief 
   */
  virtual PixelShader*
  createPixelShader( const WString & fileName,
                     const String & EntryPoint,
                     const String & ShaderModel ) override;

  /**
   * @brief 
   */
  virtual void 
  setPixelShader( PixelShader * pixelShader ) override;

  /**
   * @brief 
   */
  virtual InputLayout*
  createInputLayout( VertexShader * vertexShader ) override;

  /**
   * @brief Sets the given inputLayout
   */
  virtual void 
  setInputLayout( InputLayout * inputLayout ) override;

  /**
   * @brief Sets the Primitive topology with the given Topology
   */
  virtual void 
  setPrimitiveTopology( uint32 Topology ) override;

  /**
   * @brief Sets the given buffer as constant in the vertex shader
   */
  virtual void 
  setVSConstantBuffers( Buffer * buffer,
                        uint32 StartSlot, 
                        uint32 NumBuffers ) override;

  /**
   * @brief Sets the given buffer as a constant in the pixel shader
   */
  virtual void 
  setPSConstantBuffers( Buffer * buffer,
                        uint32 StartSlot, 
                        uint32 NumBuffers ) override;


  /**
   * @brief 
   */
  virtual void 
  drawIndexed( uint32 indexCount,
               uint32 StartIndexLocation, 
               int32 BaseVertexLocation ) override;


  /**
   * @brief 

   */
  virtual void 
  updateSubresource( Buffer * buffer, const void *pSrcData ) override;

  /**
   * @brief 
   */
  virtual Texture * 
  LoadTextureFromFile( const String filename, uint32 mipMaps ) override;

  /**
   * @brief 
   */
  virtual void 
  setShaderResources( Texture* texture, 
                      uint32 StartSlot, 
                      uint32 NumViews ) override;

  /**
   * @brief 
   */
  virtual Texture * 
  CreateShaderResourceViewFromFile( const String filenme,
                                    SHADER_RESOURCE_VIEW_DESC & desc ) override;

  /**
   * @brief 
   */
  virtual Texture *
  CreateShaderResourceView( Texture * texture, 
                            SHADER_RESOURCE_VIEW_DESC & desc ) override;


  virtual Texture * 
  createTextureFromBackBuffer() override;

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
  DXInputLayout * m_pinputLayout;

  /**
   * @brief Pointer to the Vertex Shader Class
   */
  DXVertexShader * m_pvertexShader;

  /**
   * @brief Pointer to the Pixel Shader Class
   */
  DXPixelShader * m_ppixelShader;

  /**
   * @brief Pointer to the Shader Class
   */
  DXShader * m_pShader;

  /**
   * @brief Pointer to the View Port Class
   */
  DXViewPort * m_pviewPort;

  /**
   * @brief Pointer to the Sampler State Class
   */
  DXSamplerState * m_psamplerState;

  /**
   * @brief 
   */
  DXBuffer * m_pBuffer;

 };
}