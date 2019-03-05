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
  InputLayout::AddToLayout( std::string * semanticName,
                            unsigned int semanticIndex,
                            int format,
                            unsigned int inputSlot,
                            unsigned int alignedByteOffset,
                            int inputSlotClass,
                            unsigned int instanceDataStepRate )
  {
    D3D11_INPUT_ELEMENT_DESC toPush;
    ZeroMemory( &toPush, sizeof( toPush ) );
    toPush.SemanticName = semanticName->c_str();
    toPush.SemanticIndex = semanticIndex;
    toPush.Format = ( DXGI_FORMAT ) format;
    toPush.InputSlot = inputSlot;
    toPush.AlignedByteOffset = alignedByteOffset;
    toPush.InputSlotClass = ( D3D11_INPUT_CLASSIFICATION ) inputSlotClass;
    toPush.InstanceDataStepRate = instanceDataStepRate;

    m_vLayout.push_back( toPush );
  }

}