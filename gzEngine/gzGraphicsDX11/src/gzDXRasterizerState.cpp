/**************************************************************************/
/* @filename gzDXRasterizerState.cpp
/* @author Victor Flores 
/* @date 2019/04/08
/* @brief 
/**************************************************************************/

#include "gzDXRasterizerState.h"
namespace gzEngineSDK {
  DXRasterizerState::DXRasterizerState() { }

  void 
  DXRasterizerState::createRasterizerStateDesc( 
    RASTERIZER_DESCRIPTOR rasterizerDesc )
  {
    memset( &m_rasterizerDesc, 0, sizeof( m_rasterizerDesc ) );

    m_rasterizerDesc.FillMode =
      static_cast< D3D11_FILL_MODE >( rasterizerDesc.FillMode );
    m_rasterizerDesc.CullMode = 
      static_cast< D3D11_CULL_MODE >( rasterizerDesc.CullMode );
    m_rasterizerDesc.FrontCounterClockwise = 
      rasterizerDesc.FrontCounterClockWise;
    m_rasterizerDesc.DepthBias = rasterizerDesc.DepthBias;
    m_rasterizerDesc.DepthBiasClamp = rasterizerDesc.DepthBiasClamp;
    m_rasterizerDesc.SlopeScaledDepthBias = rasterizerDesc.SlopeScaledDepthBias;
    m_rasterizerDesc.DepthClipEnable = rasterizerDesc.DepthClipEnable;
    m_rasterizerDesc.ScissorEnable = rasterizerDesc.ScissorEnable;
    m_rasterizerDesc.MultisampleEnable = rasterizerDesc.MultisampleEnable;
    m_rasterizerDesc.AntialiasedLineEnable = 
      rasterizerDesc.AntialiasedLineEnable;

  }
}