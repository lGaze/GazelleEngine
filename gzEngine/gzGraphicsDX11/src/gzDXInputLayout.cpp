/**************************************************************************/
/* @filename gzDXInputLayout.cpp
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#include "gzDXInputLayout.h"

namespace gzEngineSDK {

  InputLayout::InputLayout() : m_pInputlayout(nullptr) { }

  void 
  InputLayout::AddToLayout( INPUT_LAYOUT_DESCRIPTOR &inputLayoutDesc )
  {

    D3D11_INPUT_ELEMENT_DESC toPush;
    ZeroMemory( &toPush, sizeof( toPush ) );
    toPush.SemanticName = inputLayoutDesc.SemanticName->c_str();
    toPush.SemanticIndex = inputLayoutDesc.SemanticIndex;
    toPush.Format = static_cast< DXGI_FORMAT >( inputLayoutDesc.Format );
    toPush.InputSlot = inputLayoutDesc.InputSlot;
    toPush.AlignedByteOffset = inputLayoutDesc.AlignedByteOffset;
    toPush.InputSlotClass = 
      static_cast< D3D11_INPUT_CLASSIFICATION > (inputLayoutDesc.InputSlotClass);
    toPush.InstanceDataStepRate = inputLayoutDesc.InstanceDataStepRate;
    m_vLayout.push_back( toPush );
  }

}