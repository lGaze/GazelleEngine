/**************************************************************************/
/* @filename gzDXSamplerState.cpp
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#include "gzDXSamplerState.h"

namespace gzEngineSDK {
  SamplerState::SamplerState() : m_pSamplerLinear(nullptr) { }

  //TODO: Arreglar esta descripcion
  void SamplerState::CreateSamplerDesc()
  {
    m_SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    m_SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    m_SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    m_SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    m_SamplerDesc.MipLODBias = 0.0f;
    m_SamplerDesc.MaxAnisotropy = 0;
    m_SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    m_SamplerDesc.BorderColor;
    m_SamplerDesc.MinLOD = 0;
    m_SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
  }

}