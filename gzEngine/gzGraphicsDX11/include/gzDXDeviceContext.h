/**************************************************************************/
/* @filename gzDXDeviceContext.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#pragma once

#include "gzDXPrerequisites.h"

namespace gzEngineSDK {
class DeviceContext
{
 public:
   
  /**
   * @brief default constructor
   */
   DeviceContext();

  /**
   * @brief default destructor
   */
  ~ DeviceContext() = default;

  /************************************************************************/
  /*  DeviceContext functions                                             */
  /************************************************************************/

   /**
   * @brief
   */
  void
  SetRenderTargets( uint32 NumViews,
                    ID3D11RenderTargetView *const *ppRenderTargetViews,
                    ID3D11DepthStencilView *pDepthStencilView );

  /**
   * @brief
   */
  void 
  SetViewports( uint32 NumViewports,
                const D3D11_VIEWPORT *pViewports );

  /**
   * @brief
   */
  void
  SetInputLayout( ID3D11InputLayout *pInputLayout );

  /**
   * @brief
   */
  void 
  SetVertexBuffers( uint32 StartSlot,
                    uint32 NumBuffers,
                    ID3D11Buffer *const *ppVertexBuffers,
                    const uint32 *pStrides,
                    const uint32 *pOffsets );

  /**
   * @brief
   */
  void 
  SetIndexBuffer( ID3D11Buffer *pIndexBuffer,
                  DXGI_FORMAT Format,
                  uint32 Offset );

  /**
   * @brief
   */
  void 
  SetPrimitiveTopology( uint32 Topology );


  /**
   * @brief
   */
  void 
  UpdateSubresource( ID3D11Resource *pDstResource,
                     uint32 DstSubresource,
                     const D3D11_BOX *pDstBox,
                     const void *pSrcData,
                     uint32 SrcRowPitch,
                     uint32 SrcDepthPitch );

  /**
   * @brief
   */
  void 
  ClearRenderTargetView( ID3D11RenderTargetView *pRenderTargetView,
                         const FLOAT ColorRGBA[4] );

  /**
   * @brief
   */
  void 
  ClearDepthStencilView( ID3D11DepthStencilView *pDepthStencilView,
                         uint32 ClearFlags,
                         FLOAT Depth,
                         uint8 Stencil );

  /**
   * @brief
   */
  void 
  SetVertexShader( ID3D11VertexShader *pVertexShader,
                   ID3D11ClassInstance *const *ppClassInstances,
                   uint32 NumClassInstances );

  /**
   * @brief
   */
  void 
  SetVSConstantBuffers( uint32 StartSlot,
                        uint32 NumBuffers,
                        ID3D11Buffer *const *ppConstantBuffers );

  /**
   * @brief
   */
  void 
  SetPixelShader( ID3D11PixelShader *pPixelShader,
                  ID3D11ClassInstance *const *ppClassInstances,
                  uint32 NumClassInstances );

  /**
   * @brief
   */
  void 
  SetPSConstantBuffers( uint32 StartSlot,
                        uint32 NumBuffers,
                        ID3D11Buffer *const *ppConstantBuffers );

  /**
   * @brief
   */
  void 
  SetShaderResources( uint32 StartSlot,
                      uint32 NumViews,
                      ID3D11ShaderResourceView *const *ppShaderResourceViews );

  /**
   * @brief
   */
  void 
  SetSamplers( uint32 StartSlot,
               uint32 NumSamplers,
               ID3D11SamplerState *const *ppSamplers );

  /**
   * @brief
   */
  void 
  DrawIndexed( uint32 IndexCount,
                uint32 StartIndexLocation,
                INT BaseVertexLocation );

  /**
   * @brief 
   */
  void
  SetRasterizerState( ID3D11RasterizerState* RasterizerState );

  /**
   * @brief Gets the DeviceContext Interface
   */
  FORCEINLINE ID3D11DeviceContext**
  getDeviceContextInterface() {
    return &m_pDeviceContext;
  };

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:
   
   /**
    * @brief DeviceContext interface
    */
   ID3D11DeviceContext* m_pDeviceContext;

   D3D11_PRIMITIVE_TOPOLOGY m_Topology;
   
 };
}
