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

  PBRRenderer::PBRRenderer() : stride(sizeof(VERTEX)), offset(0)
  {
    initRenderer();
  }

  void 
  PBRRenderer::render(int32 renderTarget, float clearColor[4])
  {
    memcpy(ClearColor1,clearColor,sizeof(ClearColor1));
    g_GraphicsManager().clearDepthStencilView(CLEAR_DSV_FLAGS::E::CLEAR_DEPTH,
                                              1.0f,
                                              0);
    if (!SceneManager::instance().activeSceneEmpty())
    {
      gBufferPass();
      ssaoPass();
      blurH(m_ssaoRT);
      blurV(m_blurH1RT);
    }
    pbrPass();
    toneMapPass();
    renderToScreen(renderTarget);
  }

  void 
  PBRRenderer::gBufferPass()
  {

    g_GraphicsManager().clearRenderTargetView(ClearColor1, m_positionsRT);
    g_GraphicsManager().clearRenderTargetView(ClearColor1, m_albedoRT);
    g_GraphicsManager().clearRenderTargetView(ClearColor1, m_normalsRT);
    g_GraphicsManager().clearRenderTargetView(ClearColor1, m_emissiveRT);
    g_GraphicsManager().setRenderTargets(m_gbufferRTTextures);

    g_GraphicsManager().setInputLayout(m_gbufferLayout);
    g_GraphicsManager().setVertexShader(m_gbufferVertexShader);
    g_GraphicsManager().setPixelShader(m_gbufferPixelShader);
    g_GraphicsManager().setSamplerState(0, m_samplerState, 1);

    SceneManager::instance().update();

  }

  void 
  PBRRenderer::ssaoPass()
  {
    m_ssaoCBuffer = BaseApp::instance().constantSSAOBuffer;

    g_GraphicsManager().setRenderTarget(m_ssaoRT);
    g_GraphicsManager().clearRenderTargetView(ClearColor1, m_ssaoRT);
    g_GraphicsManager().setInputLayout(m_pbrLayout);
    g_GraphicsManager().setVertexShader(m_quadAlignedVertexShader);
    g_GraphicsManager().setPixelShader(m_ssaoPixelShader);
    g_GraphicsManager().setPSConstantBuffers(m_ssaoCBuffer, 0, 1);
    g_GraphicsManager().setVertexBuffers(0,
                                         1,
                                         quad->m_vertexBuffer,
                                         &stride,
                                         &offset);

    g_GraphicsManager().setIndexBuffer(FORMATS::E::FORMAT_R32_UINT,
                                       quad->m_indexBuffer,
                                       offset);

    g_GraphicsManager().setShaderResources(m_positionsRT, 0, 1);
    g_GraphicsManager().setShaderResources(m_normalsRT, 1, 1);

    g_GraphicsManager().drawIndexed(quad->m_mesh[0].numIndex,
                                    quad->m_mesh[0].indexBase,
                                    0);
  }

  void 
  PBRRenderer::pbrPass()
  {
    m_lightCBuffer = BaseApp::instance().constantLightBuffer;
    g_GraphicsManager().setRenderTarget(m_pbrRT);
    g_GraphicsManager().setViewports(1, m_viewport);
    g_GraphicsManager().clearDepthStencilView(CLEAR_DSV_FLAGS::E::CLEAR_DEPTH,
                                              1.0f,
                                              0);
    g_GraphicsManager().clearRenderTargetView(ClearColor1, m_pbrRT);
    g_GraphicsManager().setRasterizerState(m_rasterizerState);
    g_GraphicsManager().setInputLayout(m_pbrLayout);
    g_GraphicsManager().setVertexShader(m_quadAlignedVertexShader);
    g_GraphicsManager().setPSConstantBuffers(m_lightCBuffer, 0, 1);
    g_GraphicsManager().setPixelShader(m_pbrPixelShader);
    g_GraphicsManager().setVertexBuffers(0,
                                         1,
                                         quad->m_vertexBuffer,
                                         &stride,
                                         &offset);

    g_GraphicsManager().setIndexBuffer(FORMATS::E::FORMAT_R32_UINT,
                                       quad->m_indexBuffer,
                                       offset);

    for (uint32 i = 0; i < m_gbufferRTTextures.size(); ++i)
    {
      g_GraphicsManager().setShaderResources(m_gbufferRTTextures[i],
                                             i,
                                             1);
    }

    g_GraphicsManager().setShaderResources(m_irradiance, 4, 1);
    g_GraphicsManager().setShaderResources(m_specularReflection, 5, 1);
    g_GraphicsManager().setShaderResources(m_lut, 6, 1);
    g_GraphicsManager().setShaderResources(m_ssaoRT, 7, 1);

    g_GraphicsManager().drawIndexed(quad->m_mesh[0].numIndex,
                                    quad->m_mesh[0].indexBase,
                                    0);
  }


  void 
  PBRRenderer::toneMapPass()
  {
    g_GraphicsManager().clearRenderTargetView(ClearColor1, m_toneMapRT);
    g_GraphicsManager().clearDepthStencilView(CLEAR_DSV_FLAGS::E::CLEAR_DEPTH,
                                              1.0f,
                                              0);
    g_GraphicsManager().setRenderTarget(m_toneMapRT);
    g_GraphicsManager().setRasterizerState(m_rasterizerState);
    g_GraphicsManager().setInputLayout(m_pbrLayout);
    g_GraphicsManager().setVertexShader(m_quadAlignedVertexShader);
    g_GraphicsManager().setPixelShader(m_toneMapPixelShader);
    g_GraphicsManager().setShaderResources(m_pbrRT, 0, 1);
    g_GraphicsManager().setVertexBuffers(0,
                                         1,
                                         quad->m_vertexBuffer,
                                         &stride,
                                         &offset);

    g_GraphicsManager().setIndexBuffer(FORMATS::E::FORMAT_R32_UINT,
                                       quad->m_indexBuffer,
                                       offset);

    g_GraphicsManager().drawIndexed(quad->m_mesh[0].numIndex,
                                    quad->m_mesh[0].indexBase,
                                    0);
  }


  void 
  PBRRenderer::renderToScreen(int32 renderTarget)
  {
    g_GraphicsManager().clearRenderTargetView(ClearColor1, m_backBufferRT);
    g_GraphicsManager().clearDepthStencilView(CLEAR_DSV_FLAGS::E::CLEAR_DEPTH,
                                              1.0f,
                                              0);
    g_GraphicsManager().setRenderTarget(m_backBufferRT);
    g_GraphicsManager().setRasterizerState(m_rasterizerState);
    g_GraphicsManager().setInputLayout(m_pbrLayout);
    g_GraphicsManager().setVertexShader(m_quadAlignedVertexShader);
    g_GraphicsManager().setPixelShader(m_backBufferPixelShader);

    g_GraphicsManager().setShaderResources(m_pRTTextures[renderTarget], 0, 1);
    g_GraphicsManager().setVertexBuffers(0,
                                         1,
                                         quad->m_vertexBuffer,
                                         &stride,
                                         &offset);

    g_GraphicsManager().setIndexBuffer(FORMATS::E::FORMAT_R32_UINT,
                                       quad->m_indexBuffer,
                                       offset);

    g_GraphicsManager().drawIndexed(quad->m_mesh[0].numIndex,
                                    quad->m_mesh[0].indexBase,
                                    0);
    
  }

  void
  PBRRenderer::blurH(Texture * textureToBlur)
  {
    g_GraphicsManager().clearRenderTargetView(ClearColor1, m_blurH1RT);
    g_GraphicsManager().clearDepthStencilView(CLEAR_DSV_FLAGS::E::CLEAR_DEPTH,
                                              1.0f,
                                              0);
    g_GraphicsManager().setViewports(1, m_halfViewport);
    g_GraphicsManager().setRenderTarget(m_blurH1RT);
    g_GraphicsManager().setInputLayout(m_pbrLayout);
    g_GraphicsManager().setVertexShader(m_quadAlignedVertexShader);
    g_GraphicsManager().setPixelShader(m_blurh1PixelShader);
    g_GraphicsManager().setShaderResources(textureToBlur, 0, 1);
    g_GraphicsManager().setVertexBuffers(0,
                                         1,
                                         quad->m_vertexBuffer,
                                         &stride,
                                         &offset);

    g_GraphicsManager().setIndexBuffer(FORMATS::E::FORMAT_R32_UINT,
                                       quad->m_indexBuffer,
                                       offset);

    g_GraphicsManager().drawIndexed(quad->m_mesh[0].numIndex,
                                    quad->m_mesh[0].indexBase,
                                    0);

  }

  void 
  PBRRenderer::blurV(Texture * textureToBlur)
  {
    g_GraphicsManager().clearRenderTargetView(ClearColor1, m_blurV1RT);
    g_GraphicsManager().clearDepthStencilView(CLEAR_DSV_FLAGS::E::CLEAR_DEPTH,
                                              1.0f,
                                              0);
    g_GraphicsManager().setRenderTarget(m_blurV1RT);
    g_GraphicsManager().setInputLayout(m_pbrLayout);
    g_GraphicsManager().setVertexShader(m_quadAlignedVertexShader);
    g_GraphicsManager().setPixelShader(m_blurv1PixelShader);
    g_GraphicsManager().setShaderResources(textureToBlur, 0, 1);
    g_GraphicsManager().setVertexBuffers(0,
                                         1,
                                         quad->m_vertexBuffer,
                                         &stride,
                                         &offset);

    g_GraphicsManager().setIndexBuffer(FORMATS::E::FORMAT_R32_UINT,
                                       quad->m_indexBuffer,
                                       offset);

    g_GraphicsManager().drawIndexed(quad->m_mesh[0].numIndex,
                                    quad->m_mesh[0].indexBase,
                                    0);
  }

  void
  PBRRenderer::initRenderer()
  {
    RASTERIZER_DESCRIPTOR rasterizerDes;
    memset(&rasterizerDes, 0, sizeof(rasterizerDes));
    rasterizerDes.CullMode = CULL_MODE::E::CULL_NONE;
    rasterizerDes.FillMode = FILL_MODE::E::FILL_SOLID;

    m_rasterizerState = g_GraphicsManager().createRasterizerState(rasterizerDes);

    SAMPLER_DESCRIPTOR samplerDesc;
    memset(&samplerDesc, 0, sizeof(samplerDesc));
    samplerDesc.Filter = FILTER::E::FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = ADDRESS_MODE::E::TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressY = ADDRESS_MODE::E::TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = ADDRESS_MODE::E::TEXTURE_ADDRESS_WRAP;
    samplerDesc.ComparisonFunc = COMPARISON_FUNC::E::COMPARISON_NEVER;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = 3.402823466e+38f;

    m_samplerState = g_GraphicsManager().createSamplerState(samplerDesc);

    Vector2f vpDimensions = g_GraphicsManager().getViewportDimensions();

    m_viewport = g_GraphicsManager().getViewport();
    g_GraphicsManager().setViewports(1, m_viewport);

    m_halfViewport = m_viewport;
    m_halfViewport.Width = vpDimensions.x * 0.5;
    m_halfViewport.Height = vpDimensions.y * 0.5;


    //Texture desc
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

    m_positionsRT = g_GraphicsManager().createTexture2D(renderTexDesc);
    m_gbufferRTTextures.push_back(m_positionsRT);
    m_albedoRT = g_GraphicsManager().createTexture2D(renderTexDesc);
    m_gbufferRTTextures.push_back(m_albedoRT);
    m_normalsRT = g_GraphicsManager().createTexture2D(renderTexDesc);
    m_gbufferRTTextures.push_back(m_normalsRT);
    m_emissiveRT = g_GraphicsManager().createTexture2D(renderTexDesc);
    m_gbufferRTTextures.push_back(m_emissiveRT);
    m_pbrRT = g_GraphicsManager().createTexture2D(renderTexDesc);
    m_toneMapRT = g_GraphicsManager().createTexture2D(renderTexDesc);
    m_backBufferRT = g_GraphicsManager().getBackBufferTex();
    renderTexDesc.Height = vpDimensions.y * 0.5;
    renderTexDesc.Width = vpDimensions.x * 0.5;
    m_blurH1RT = g_GraphicsManager().createTexture2D(renderTexDesc);
    m_blurV1RT = g_GraphicsManager().createTexture2D(renderTexDesc);
    renderTexDesc.Height = vpDimensions.y;
    renderTexDesc.Width = vpDimensions.x;
    renderTexDesc.MipLevels = 4;
    m_ssaoRT = g_GraphicsManager().createTexture2D(renderTexDesc);

    m_pRTTextures.push_back(m_toneMapRT);
    m_pRTTextures.push_back(m_pbrRT);
    m_pRTTextures.insert(std::end(m_pRTTextures),
                         std::begin(m_gbufferRTTextures),
                         std::end(m_gbufferRTTextures));
    m_pRTTextures.push_back(m_ssaoRT);

    m_gbufferVertexShader = g_GraphicsManager().CreateVertexShader(
      L"Shaders\\common.hlsl",
      "vs_main",
      "vs_4_0");

    m_gbufferLayout =
      g_GraphicsManager().createInputLayout(m_gbufferVertexShader);

    m_gbufferPixelShader = g_GraphicsManager().createPixelShader(
      L"Shaders\\GBuffer.hlsl",
      "ps_main",
      "ps_4_0");

    m_quadAlignedVertexShader = g_GraphicsManager().CreateVertexShader(
      L"Shaders\\commonQuadAligned.hlsl",
      "commonQuadAligned_main",
      "vs_4_0");

    m_pbrLayout =
      g_GraphicsManager().createInputLayout(m_quadAlignedVertexShader);

    m_pbrPixelShader = g_GraphicsManager().createPixelShader(
      L"Shaders\\PBR.hlsl",
      "ps_main",
      "ps_4_0");

    m_toneMapPixelShader = g_GraphicsManager().createPixelShader(
      L"Shaders\\ToneMap.hlsl",
      "ps_main",
      "ps_4_0");

    m_backBufferPixelShader = g_GraphicsManager().createPixelShader(
      L"Shaders\\backBufferPS.hlsl",
      "ps_main",
      "ps_4_0");

    m_ssaoPixelShader = g_GraphicsManager().createPixelShader(
      L"Shaders\\SSAO.hlsl",
      "ps_main",
      "ps_4_0");

    m_blurh1PixelShader = g_GraphicsManager().createPixelShader(
      L"Shaders\\BlurH1PS.hlsl",
      "ps_main",
      "ps_4_0");

    m_blurv1PixelShader = g_GraphicsManager().createPixelShader(
      L"Shaders\\BlurV1PS.hlsl",
      "ps_main",
      "ps_4_0");

    m_irradiance = 
      g_GraphicsManager().loadDDSTextureFromFile(L"Textures\\Vela\\CubeMap.dds");
    
    m_specularReflection =
      g_GraphicsManager().loadDDSTextureFromFile(L"Textures\\galileo_cross.dds");

    quad = new Model();
    quad->Load("Meshes\\QuadPerron.obj");

    m_lut = g_GraphicsManager().LoadTextureFromFile("Textures\\ibl_brdf_lut.png");

  }
}
