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
    g_GraphicsManager().clearRenderTargetView(LinearColor::Transparent.rgba, m_positionsRT);
    g_GraphicsManager().clearRenderTargetView(LinearColor::Transparent.rgba, m_albedoRT);
    g_GraphicsManager().clearRenderTargetView(LinearColor::Transparent.rgba, m_normalsRT);
    g_GraphicsManager().clearRenderTargetView(LinearColor::Transparent.rgba, m_emissiveRT);
    g_GraphicsManager().clearDepthStencilView(CLEAR_DSV_FLAGS::E::CLEAR_DEPTH);
    g_GraphicsManager().setRenderTargets(m_gbufferRTTextures);
    g_GraphicsManager().setRasterizerState(m_rasterizerState);
    g_GraphicsManager().setInputLayout(m_gbufferLayout);
    g_GraphicsManager().setVertexShader(m_gbufferVertexShader);
    g_GraphicsManager().setPixelShader(m_gbufferPixelShader);
    g_GraphicsManager().setSamplerState(0, m_linearSampler, 1);

    SceneManager::instance().update();

  }

  void 
  PBRRenderer::ssaoPass()
  {
    m_ssaoCBuffer = BaseApp::instance().constantSSAOBuffer;
 
    g_GraphicsManager().clearRenderTargetView(LinearColor::White.rgba, m_ssaoRT);
    g_GraphicsManager().setRenderTarget(m_ssaoRT);
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
    g_GraphicsManager().clearDepthStencilView(CLEAR_DSV_FLAGS::E::CLEAR_DEPTH);
    g_GraphicsManager().setViewports(1, m_viewport);
    g_GraphicsManager().setSamplerState(0, m_pointSampler, 1);
    g_GraphicsManager().clearRenderTargetView(ClearColor1, m_pbrRT);
    g_GraphicsManager().setInputLayout(m_pbrLayout);
    g_GraphicsManager().setVertexShader(m_quadAlignedVertexShader);
    g_GraphicsManager().setPSConstantBuffers(m_lightCBuffer, 0, 1);
    g_GraphicsManager().setPixelShader(m_pbrPixelShader);

    for (uint32 i = 0; i < m_gbufferRTTextures.size(); ++i)
    {
      g_GraphicsManager().setShaderResources(m_gbufferRTTextures[i],
                                             i,
                                             1);
    }

    g_GraphicsManager().setShaderResources(m_irradiance, 4, 1);
    g_GraphicsManager().setShaderResources(m_lut, 5, 1);
    g_GraphicsManager().setShaderResources(m_blurV1RT, 6, 1);

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
  PBRRenderer::toneMapPass()
  {
    g_GraphicsManager().clearRenderTargetView(ClearColor1, m_toneMapRT);
    g_GraphicsManager().setRenderTarget(m_toneMapRT);
    g_GraphicsManager().clearDepthStencilView(CLEAR_DSV_FLAGS::E::CLEAR_DEPTH);
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
    g_GraphicsManager().setRenderTarget(m_backBufferRT);
    g_GraphicsManager().clearDepthStencilView(CLEAR_DSV_FLAGS::E::CLEAR_DEPTH);
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
    g_GraphicsManager().clearRenderTargetView(LinearColor::White.rgba, m_blurH1RT);
    g_GraphicsManager().clearDepthStencilView(CLEAR_DSV_FLAGS::E::CLEAR_DEPTH);
    g_GraphicsManager().setRenderTarget(m_blurH1RT);
    g_GraphicsManager().setInputLayout(m_pbrLayout);
    g_GraphicsManager().setSamplerState(0, m_linearSampler, 1);
    g_GraphicsManager().setSamplerState(1, m_pointSampler, 1);
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
    g_GraphicsManager().clearRenderTargetView(LinearColor::White.rgba, m_blurV1RT);
    g_GraphicsManager().clearDepthStencilView(CLEAR_DSV_FLAGS::E::CLEAR_DEPTH);
    g_GraphicsManager().setRenderTarget(m_blurV1RT);
    g_GraphicsManager().setInputLayout(m_pbrLayout);
    g_GraphicsManager().setSamplerState(0, m_linearSampler, 1);
    g_GraphicsManager().setSamplerState(1, m_pointSampler, 1);
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
    //Rasterizer
    RASTERIZER_DESCRIPTOR rasterizerDes;
    memset(&rasterizerDes, 0, sizeof(rasterizerDes));
    rasterizerDes.CullMode = CULL_MODE::E::CULL_NONE;
    rasterizerDes.FillMode = FILL_MODE::E::FILL_SOLID;

    m_rasterizerState = g_GraphicsManager().createRasterizerState(rasterizerDes);

    //Sampler Descriptor
    SAMPLER_DESCRIPTOR samplerDesc;
    memset(&samplerDesc, 0, sizeof(samplerDesc));
    samplerDesc.Filter = FILTER::E::FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = ADDRESS_MODE::E::TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressY = ADDRESS_MODE::E::TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = ADDRESS_MODE::E::TEXTURE_ADDRESS_WRAP;
    samplerDesc.ComparisonFunc = COMPARISON_FUNC::E::COMPARISON_NEVER;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = 3.402823466e+38f;

    //Linear Sampler
    m_linearSampler = g_GraphicsManager().createSamplerState(samplerDesc);

    //Point Sampler
    samplerDesc.Filter = FILTER::E::FILTER_MIN_MAG_MIP_POINT;
    m_pointSampler = g_GraphicsManager().createSamplerState(samplerDesc);

    //Viewport
    m_viewport = g_GraphicsManager().getViewport();
    g_GraphicsManager().setViewports(1, m_viewport);

    createRendererTextures();
    createRendererShaders();

    quad = new Model();
    quad->Load("Meshes\\QuadPerron.obj");

  }

  void
  PBRRenderer::createRendererTextures()
  {
    //Gets the default Viewport Dimentions 
    Vector2i vpDimensions = g_GraphicsManager().getViewportDimensions();

    //Texture desc
    TEXTURE2D_DESCRIPTOR renderTexDesc;
    memset(&renderTexDesc, 0, sizeof(renderTexDesc));
    renderTexDesc.Height = vpDimensions.y;
    renderTexDesc.Width = vpDimensions.x;
    renderTexDesc.MipLevels = 1;
    renderTexDesc.ArraySize = 1;
    renderTexDesc.Format = FORMATS::E::FORMAT_R32G32B32A32_FLOAT;
    renderTexDesc.Usage = USAGES::E::USAGE_DEFAULT;
    renderTexDesc.BindFlags = BIND_FLAGS::E::BIND_SHADER_RESOURCE | 
                              BIND_FLAGS::E::BIND_RENDER_TARGET;
    renderTexDesc.CPUAccessFlags = 0;
    renderTexDesc.MiscFlags = 0;

    //Shader Resources/Render Targets
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

    m_blurH1RT = g_GraphicsManager().createTexture2D(renderTexDesc);

    m_blurV1RT = g_GraphicsManager().createTexture2D(renderTexDesc);

    renderTexDesc.MipLevels = 4;
    m_ssaoRT = g_GraphicsManager().createTexture2D(renderTexDesc);

    m_pRTTextures.push_back(m_toneMapRT);
    m_pRTTextures.push_back(m_pbrRT);
    m_pRTTextures.insert(std::end(m_pRTTextures),
                         std::begin(m_gbufferRTTextures),
                         std::end(m_gbufferRTTextures));
    m_pRTTextures.push_back(m_ssaoRT);
    m_pRTTextures.push_back(m_blurV1RT);

    //Shader Resources
    m_irradiance =
      g_GraphicsManager().loadDDSTextureFromFile(L"Textures\\DDS\\Garage.dds");

    m_specularReflection =
      g_GraphicsManager().loadDDSTextureFromFile(L"Textures\\Vela\\Irradiance.dds");

    m_lut =
      g_GraphicsManager().LoadTextureFromFile("Textures\\ibl_brdf_lut.png");

  }

  void 
  PBRRenderer::createRendererShaders()
  {
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
      L"Shaders\\BlurHPS.hlsl",
      "ps_main",
      "ps_4_0");

    m_blurv1PixelShader = g_GraphicsManager().createPixelShader(
      L"Shaders\\BlurVPS.hlsl",
      "ps_main",
      "ps_4_0");
  }
}
