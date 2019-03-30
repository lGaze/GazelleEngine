/**************************************************************************/
/* @filename gzDXInputLayout.cpp
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#include "gzDXInputLayout.h"


namespace gzEngineSDK {

  DXInputLayout::DXInputLayout() :
    m_pInputlayout(nullptr), 
    m_pInputLayoutDescArray(nullptr),
    m_numElem(0) { }

  void 
  DXInputLayout::CreateInputLayout( ID3DBlob * pblob )
  {

    //Reflect the shader info
    ID3D11ShaderReflection * VertexShderReflection = nullptr;

    D3DReflect( pblob->GetBufferPointer(),
                pblob->GetBufferSize(),
                IID_ID3D11ShaderReflection,
                reinterpret_cast< void** >( &VertexShderReflection ) );


    //Takes the info of the shader desc
    D3D11_SHADER_DESC ShaderDesc;

    VertexShderReflection->GetDesc( &ShaderDesc );

    //Creates the array
    if ( ShaderDesc.InputParameters != 0 )
    {
      m_pInputLayoutDescArray = 
      new D3D11_INPUT_ELEMENT_DESC[ShaderDesc.InputParameters];
    }

    m_numElem = ShaderDesc.InputParameters;

    for ( uint32 i = 0; i < ShaderDesc.InputParameters; i++ )
    {
      D3D11_SIGNATURE_PARAMETER_DESC ParamDesc;
      VertexShderReflection->GetInputParameterDesc( i, &ParamDesc );

      D3D11_INPUT_ELEMENT_DESC ElementDesc;
      ElementDesc.SemanticName = ParamDesc.SemanticName;
      ElementDesc.SemanticIndex = ParamDesc.SemanticIndex;
      ElementDesc.InputSlot = 0;
      ElementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
      ElementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
      ElementDesc.InstanceDataStepRate = 0;

      // Determinates the format
      if ( ParamDesc.Mask == 1 )
      {
        if ( ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 )
          ElementDesc.Format = DXGI_FORMAT_R32_UINT;
        else if ( ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 )
          ElementDesc.Format = DXGI_FORMAT_R32_SINT;
        else if ( ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 )
          ElementDesc.Format = DXGI_FORMAT_R32_FLOAT;
      }
      else if ( ParamDesc.Mask <= 3 )
      {
        if ( ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 )
          ElementDesc.Format = DXGI_FORMAT_R32G32_UINT;
        else if ( ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 )
          ElementDesc.Format = DXGI_FORMAT_R32G32_SINT;
        else if ( ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 )
          ElementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
      }
      else if ( ParamDesc.Mask <= 7 )
      {
        if ( ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 )
          ElementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
        else if ( ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 )
          ElementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
        else if ( ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 )
          ElementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
      }
      else if ( ParamDesc.Mask <= 15 )
      {
        if ( ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 )
          ElementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
        else if ( ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 )
          ElementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
        else if ( ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 )
          ElementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
      }
      if ( ElementDesc.SemanticName[0] == 'C' )
      {
        ElementDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      }
      
      m_pInputLayoutDescArray[i] = ElementDesc;
     
    }
  }
}