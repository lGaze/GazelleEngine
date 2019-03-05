/**************************************************************************/
/* @filename gzDXDeviceContext.cpp
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#include "gzDXDeviceContext.h"

namespace gzEngineSDK {

  DeviceContext::DeviceContext() : m_pDeviceContext(nullptr) { }

  void 
  DeviceContext::SetRenderTargets( uint32 NumViews, 
                                   ID3D11RenderTargetView * const * ppRenderTargetViews,
                                   ID3D11DepthStencilView * pDepthStencilView )
  {
    m_pDeviceContext->OMSetRenderTargets( NumViews,
                                          ppRenderTargetViews,
                                          pDepthStencilView );
  }

  void 
  DeviceContext::SetViewports( uint32 NumViewports, 
                               const D3D11_VIEWPORT * pViewports )
  {
    m_pDeviceContext->RSSetViewports( NumViewports,
                                      pViewports );
  }

  void 
  DeviceContext::SetInputLayout( ID3D11InputLayout * pInputLayout )
  {
    m_pDeviceContext->IASetInputLayout( pInputLayout );
  }

  void 
  DeviceContext::SetVertexBuffers( uint32 StartSlot,
                                   uint32 NumBuffers, 
                                   ID3D11Buffer * const * ppVertexBuffers, 
                                   const uint32 * pStrides, 
                                   const uint32 * pOffsets )
  {
    m_pDeviceContext->IASetVertexBuffers( StartSlot,
                                          NumBuffers,
                                          ppVertexBuffers,
                                          pStrides,
                                          pOffsets );
  }

  void 
  DeviceContext::SetIndexBuffer( ID3D11Buffer * pIndexBuffer, 
                                 DXGI_FORMAT Format, 
                                 uint32 Offset )
  {
    m_pDeviceContext->IASetIndexBuffer( pIndexBuffer,
                                        Format,
                                        Offset );
  }

  void 
  DeviceContext::SetPrimitiveTopology( uint32 Topology )
  {
    m_Topology = ( D3D11_PRIMITIVE_TOPOLOGY ) Topology;
    m_pDeviceContext->IASetPrimitiveTopology( m_Topology );
  }

  void 
  DeviceContext::UpdateSubresource( ID3D11Resource * pDstResource, 
                                    uint32 DstSubresource, 
                                    const D3D11_BOX * pDstBox, 
                                    const void * pSrcData, 
                                    uint32 SrcRowPitch, 
                                    uint32 SrcDepthPitch )
  {
    m_pDeviceContext->UpdateSubresource( pDstResource,
                                         DstSubresource,
                                         pDstBox,
                                         pSrcData,
                                         SrcRowPitch,
                                         SrcDepthPitch );
  }

  void 
  DeviceContext::ClearRenderTargetView( ID3D11RenderTargetView * pRenderTargetView,
                                        const FLOAT ColorRGBA[4] )
  {
    m_pDeviceContext->ClearRenderTargetView( pRenderTargetView, ColorRGBA );
  }

  void 
  DeviceContext::ClearDepthStencilView( ID3D11DepthStencilView * pDepthStencilView, 
                                        uint32 ClearFlags, 
                                        FLOAT Depth, 
                                        uint8 Stencil )
  {
    m_pDeviceContext->ClearDepthStencilView( pDepthStencilView,
                                             ClearFlags,
                                             Depth,
                                             Stencil );
  }

  void 
  DeviceContext::SetVertexShader( ID3D11VertexShader * pVertexShader, 
                                  ID3D11ClassInstance * const * ppClassInstances,
                                  uint32 NumClassInstances )
  {
    m_pDeviceContext->VSSetShader( pVertexShader,
                                   ppClassInstances,
                                   NumClassInstances );
  }

  void 
  DeviceContext::SetVSConstantBuffers( uint32 StartSlot, 
                                       uint32 NumBuffers, 
                                       ID3D11Buffer * const * ppConstantBuffers )
  {
    m_pDeviceContext->VSSetConstantBuffers( StartSlot,
                                            NumBuffers,
                                            ppConstantBuffers );
  }

  void 
  DeviceContext::SetPixelShader( ID3D11PixelShader * pPixelShader, 
                                 ID3D11ClassInstance * const * ppClassInstances, 
                                 uint32 NumClassInstances )
  {
    m_pDeviceContext->PSSetShader( pPixelShader,
                                   ppClassInstances,
                                   NumClassInstances );
  }

  void
  DeviceContext::SetPSConstantBuffers( uint32 StartSlot,
                                       uint32 NumBuffers, 
                                       ID3D11Buffer * const * ppConstantBuffers )
  {
    m_pDeviceContext->PSSetConstantBuffers( StartSlot,
                                            NumBuffers,
                                            ppConstantBuffers );
  }

  void 
  DeviceContext::SetShaderResources( uint32 StartSlot, 
                                     uint32 NumViews, 
                                     ID3D11ShaderResourceView * const * ppShaderResourceViews)
  {
    m_pDeviceContext->PSSetShaderResources( StartSlot,
                                            NumViews,
                                            ppShaderResourceViews );
  }

  void 
  DeviceContext::SetSamplers( uint32 StartSlot, 
                              uint32 NumSamplers,
                              ID3D11SamplerState * const * ppSamplers )
  {
    m_pDeviceContext->PSSetSamplers( StartSlot,
                                     NumSamplers,
                                     ppSamplers );
  }

  void 
  DeviceContext::DrawIndexed( uint32 IndexCount, 
                               uint32 StartIndexLocation,
                               INT BaseVertexLocation )
  {
    m_pDeviceContext->DrawIndexed( IndexCount,
                                   StartIndexLocation,
                                   BaseVertexLocation );
  }
}