/**************************************************************************/
/* @filename gzPBRRederer.cpp
/* @author Victor Flores 
/* @date 2019/08/10
/* @brief 
/**************************************************************************/

#include "gzPBRRenderer.h"
#include <gzRasterizerState.h>
#include <gzTexture.h>
#include <gzResourceManager.h>

namespace gzEngineSDK {

  PBRRenderer::PBRRenderer()
  {
    initRenderer();
  }

  void 
  PBRRenderer::render()
  {
    createGBuffer();
    SceneManager::instance().update();

    //Pass 2
    GraphicsManager::instance().setRasterizerState(m_rasterizerState);
    GraphicsManager::instance().present(0, 0);
  }

  void 
  PBRRenderer::createGBuffer()
  {
    float ClearColor1[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //Gris
    GraphicsManager::instance().clearRenderTargetView(ClearColor1, m_positionsRT);
    GraphicsManager::instance().clearRenderTargetView(ClearColor1, m_albedoRT);
    GraphicsManager::instance().clearRenderTargetView(ClearColor1, m_normalsRT);
    GraphicsManager::instance().clearRenderTargetView(ClearColor1, m_emissiveRT);
    GraphicsManager::instance().setRenderTargets(m_gbufferRTTextures);

    m_gbufferVertexShader = GraphicsManager::instance().CreateVertexShader(
      L"Shaders\\common.hlsl",
      "vs_main",
      "vs_4_0");

    m_gbufferLayout = 
      GraphicsManager::instance().createInputLayout(m_gbufferVertexShader);

    m_gbufferPixelShader = GraphicsManager::instance().createPixelShader(
      L"Shaders\\GBuffer.hlsl",
      "ps_main",
      "ps_4_0");

    GraphicsManager::instance().setInputLayout(m_gbufferLayout);
    GraphicsManager::instance().setVertexShader(m_gbufferVertexShader);
    GraphicsManager::instance().setPixelShader(m_gbufferPixelShader);
    GraphicsManager::instance().setSamplerState(0, m_samplerState, 1);

  }

  void PBRRenderer::initRenderer()
  {
    RASTERIZER_DESCRIPTOR rasterizerDes;
    memset(&rasterizerDes, 0, sizeof(rasterizerDes));
    rasterizerDes.CullMode = CULL_MODE::E::CULL_NONE;
    rasterizerDes.FillMode = FILL_MODE::E::FILL_SOLID;

    m_rasterizerState = GraphicsManager::instance().createRasterizerState(rasterizerDes);

    SAMPLER_DESCRIPTOR samplerDesc;
    memset(&samplerDesc, 0, sizeof(samplerDesc));
    samplerDesc.Filter = FILTER::E::FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = ADDRESS_MODE::E::TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressY = ADDRESS_MODE::E::TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = ADDRESS_MODE::E::TEXTURE_ADDRESS_WRAP;
    samplerDesc.ComparisonFunc = COMPARISON_FUNC::E::COMPARISON_NEVER;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = 3.402823466e+38f;

    m_samplerState = GraphicsManager::instance().createSamplerState(samplerDesc);

    //Albedo Texture
    TEXTURE2D_DESCRIPTOR renderTexDesc;
    memset(&renderTexDesc, 0, sizeof(renderTexDesc));
    renderTexDesc.Height = 480;
    renderTexDesc.Width = 640;
    renderTexDesc.MipLevels = 4;
    renderTexDesc.ArraySize = 1;
    renderTexDesc.Format = FORMATS::E::FORMAT_R16G16B16A16_FLOAT;
    renderTexDesc.Usage = USAGES::E::USAGE_DEFAULT;
    renderTexDesc.BindFlags = BIND_FLAGS::E::BIND_SHADER_RESOURCE | BIND_FLAGS::E::BIND_RENDER_TARGET;
    renderTexDesc.CPUAccessFlags = 0;
    renderTexDesc.MiscFlags = 0;

    m_positionsRT = GraphicsManager::instance().createTexture2D(renderTexDesc);
    m_gbufferRTTextures.push_back(m_positionsRT);
    m_normalsRT = GraphicsManager::instance().createTexture2D(renderTexDesc);
    m_gbufferRTTextures.push_back(m_normalsRT);
    m_albedoRT = GraphicsManager::instance().createTexture2D(renderTexDesc);
    m_gbufferRTTextures.push_back(m_albedoRT);
    m_emissiveRT = GraphicsManager::instance().createTexture2D(renderTexDesc);
    m_gbufferRTTextures.push_back(m_emissiveRT);

    //quad->Load("Meshes\\QuadPerron.obj");
  }

}
