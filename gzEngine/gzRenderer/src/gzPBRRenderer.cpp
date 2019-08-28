/**************************************************************************/
/* @filename gzPBRRederer.cpp
/* @author Victor Flores 
/* @date 2019/08/10
/* @brief 
/**************************************************************************/

#include "gzPBRRenderer.h"
#include <gzRasterizerState.h>
#include <gzTexture.h>
#include <gzModel.h>
#include <gzBaseApp.h>


namespace gzEngineSDK {

  PBRRenderer::PBRRenderer()
  {
    initRenderer();
  }

  void 
  PBRRenderer::render()
  {
    GraphicsManager::instance().clearDepthStencilView(CLEAR_DSV_FLAGS::E::CLEAR_DEPTH,
                                                      1.0f,
                                                      0);
    createGBuffer();
    SceneManager::instance().update();

    uint32 stride = sizeof(VERTEX);
    uint32 offset = 0;

    //Pass 2
    m_lightCBuffer = BaseApp::instance().constantLightBuffer;
    GraphicsManager::instance().setRenderTarget(m_pbrRT);

    float ClearColor1[4] = { .5, .5, .5, 1 };
    GraphicsManager::instance().clearRenderTargetView(ClearColor1, m_pbrRT);
    GraphicsManager::instance().setRasterizerState(m_rasterizerState);
    GraphicsManager::instance().setInputLayout(m_pbrLayout);
    GraphicsManager::instance().setVertexShader(m_pbrVertexShader);
    GraphicsManager::instance().setPSConstantBuffers(m_lightCBuffer, 0, 1);
    GraphicsManager::instance().setPixelShader(m_pbrPixelShader);
    GraphicsManager::instance().setVertexBuffers(0,
                                                 1,
                                                 quad->m_vertexBuffer,
                                                 &stride,
                                                 &offset);

    GraphicsManager::instance().setIndexBuffer(FORMATS::E::FORMAT_R32_UINT,
                                               quad->m_indexBuffer,
                                               offset);


    GraphicsManager::instance().setShaderResources(m_positionsRT,
                                                   0,
                                                   1);

    GraphicsManager::instance().setShaderResources(m_albedoRT,
                                                   1,
                                                   1);

    GraphicsManager::instance().setShaderResources(m_normalsRT,
                                                   2,
                                                   1);

    GraphicsManager::instance().setShaderResources(m_emissiveRT,
                                                   3,
                                                   1);

    GraphicsManager::instance().drawIndexed(quad->m_mesh[0].numIndex,
                                            quad->m_mesh[0].indexBase,
                                            0);

    //Pass3
    GraphicsManager::instance().clearRenderTargetView(ClearColor1, m_backBufferRT);
    GraphicsManager::instance().clearDepthStencilView(CLEAR_DSV_FLAGS::E::CLEAR_DEPTH,
                                                      1.0f,
                                                      0);
    GraphicsManager::instance().setRenderTarget(m_backBufferRT);
    GraphicsManager::instance().setRasterizerState(m_rasterizerState);
    GraphicsManager::instance().setInputLayout(m_pbrLayout);
    GraphicsManager::instance().setVertexShader(m_pbrVertexShader);
    GraphicsManager::instance().setPixelShader(m_toneMapPixelShader);
    GraphicsManager::instance().setShaderResources(m_pbrRT, 0, 1);
    GraphicsManager::instance().setVertexBuffers(0,
                                                 1,
                                                 quad->m_vertexBuffer,
                                                 &stride,
                                                 &offset);

    GraphicsManager::instance().setIndexBuffer(FORMATS::E::FORMAT_R32_UINT,
                                               quad->m_indexBuffer,
                                               offset);

    GraphicsManager::instance().drawIndexed(quad->m_mesh[0].numIndex,
                                            quad->m_mesh[0].indexBase,
                                            0);


    GraphicsManager::instance().present(0, 0);
  }

  void 
    PBRRenderer::createGBuffer()
  {

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

    m_viewport = GraphicsManager::instance().getViewport();

    GraphicsManager::instance().setViewports(1, m_viewport);

    Vector2f vpDimensions = GraphicsManager::instance().getViewportDimensions();

    //Albedo Texture
    TEXTURE2D_DESCRIPTOR renderTexDesc;
    memset(&renderTexDesc, 0, sizeof(renderTexDesc));
    renderTexDesc.Height = vpDimensions.y;
    renderTexDesc.Width = vpDimensions.x;
    renderTexDesc.MipLevels = 1;
    renderTexDesc.ArraySize = 1;
    renderTexDesc.Format = 2;
    renderTexDesc.Usage = USAGES::E::USAGE_DEFAULT;
    renderTexDesc.BindFlags = BIND_FLAGS::E::BIND_SHADER_RESOURCE | BIND_FLAGS::E::BIND_RENDER_TARGET;
    renderTexDesc.CPUAccessFlags = 0;
    renderTexDesc.MiscFlags = 0;

    m_positionsRT = GraphicsManager::instance().createTexture2D(renderTexDesc);
    m_gbufferRTTextures.push_back(m_positionsRT);
    m_albedoRT = GraphicsManager::instance().createTexture2D(renderTexDesc);
    m_gbufferRTTextures.push_back(m_albedoRT);
    m_normalsRT = GraphicsManager::instance().createTexture2D(renderTexDesc);
    m_gbufferRTTextures.push_back(m_normalsRT);
    m_emissiveRT = GraphicsManager::instance().createTexture2D(renderTexDesc);
    m_gbufferRTTextures.push_back(m_emissiveRT);
    m_pbrRT = GraphicsManager::instance().createTexture2D(renderTexDesc);
    m_backBufferRT = GraphicsManager::instance().getBackBufferTex();

    m_pbrVertexShader = GraphicsManager::instance().CreateVertexShader(
      L"Shaders\\PBR_vs.hlsl",
      "PBRvs_main",
      "vs_4_0");

    m_pbrLayout =
      GraphicsManager::instance().createInputLayout(m_pbrVertexShader);

    m_pbrPixelShader = GraphicsManager::instance().createPixelShader(
      L"Shaders\\PBRps.hlsl",
      "ps_main",
      "ps_4_0");

    m_toneMapPixelShader = GraphicsManager::instance().createPixelShader(
      L"Shaders\\ToneMap.hlsl",
      "ps_main",
      "ps_4_0");
    
    quad = new Model();
    quad->Load("Meshes\\QuadPerron.obj");

    m_lut = GraphicsManager::instance().LoadTextureFromFile("Textures\\ibl_brdf_lut.png");


  }

}
