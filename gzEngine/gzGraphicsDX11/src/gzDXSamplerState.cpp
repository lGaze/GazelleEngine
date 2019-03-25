/**************************************************************************/
/* @filename gzDXSamplerState.cpp
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#include "gzDXSamplerState.h"

namespace gzEngineSDK {
  DXSamplerState::DXSamplerState() : m_pSamplerLinear(nullptr) 
  { 
    ZeroMemory( &m_SamplerDesc, sizeof( m_SamplerDesc ) );
  }

  //TODO: Arreglar esta descripcion
  void DXSamplerState::CreateSamplerDesc( SAMPLER_DESC &samplerDesc )
  {

    m_SamplerDesc.Filter = static_cast< D3D11_FILTER >( samplerDesc.Filter );
    m_SamplerDesc.AddressU = 
      static_cast<D3D11_TEXTURE_ADDRESS_MODE> (samplerDesc.AddressU);
    m_SamplerDesc.AddressV = 
      static_cast< D3D11_TEXTURE_ADDRESS_MODE > ( samplerDesc.AddressY );
    m_SamplerDesc.AddressW = 
      static_cast< D3D11_TEXTURE_ADDRESS_MODE > ( samplerDesc.AddressW );
    m_SamplerDesc.MipLODBias = samplerDesc.MipLODBias;
    m_SamplerDesc.MaxAnisotropy = samplerDesc.MaxAnisotropy;
    m_SamplerDesc.ComparisonFunc = 
      static_cast<D3D11_COMPARISON_FUNC> (samplerDesc.ComparisonFunc);
    m_SamplerDesc.BorderColor[0] = samplerDesc.BorderColor[0];
    m_SamplerDesc.BorderColor[1] = samplerDesc.BorderColor[1];
    m_SamplerDesc.BorderColor[2] = samplerDesc.BorderColor[2];
    m_SamplerDesc.BorderColor[3] = samplerDesc.BorderColor[3];
    m_SamplerDesc.MinLOD = samplerDesc.MinLOD;
    m_SamplerDesc.MaxLOD = samplerDesc.MinLOD;
  }

}