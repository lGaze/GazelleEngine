/**************************************************************************/
/* @filename gzPBRRenderer.h
/* @author Victor Flores 
/* @date 2019/08/10
/* @brief 
/**************************************************************************/
#pragma once

#include "gzPBRRendererPrerequisites.h"
#include <gzRenderer.h>
#include <gzSceneManager.h>
#include <gzGraphicsManager.h>

namespace gzEngineSDK {
class PBRRenderer : public Renderer
{
 public:

  /**
   * @brief default constructor
   */
   PBRRenderer();

  /**
   * @brief default destructor
   */
   virtual
  ~PBRRenderer() = default;

  /************************************************************************/
  /* PBRRenderer functions                                                */
  /************************************************************************/

   /**
    * @brief This function renders the the objects to screen 
    * @param int number that is going to indicate the render target
    */
   virtual void
   render(int32 renderTarget, float clearColor[4]) override;

 private:

   /**
    * @brief Gbuffer pass function
    */
   void
   gBufferPass();

   /**
    * @brief PBR pass function
    */
   void
   pbrPass();

   /**
    * @brief Tone map pass function 
    */
   void
   toneMapPass();

   /**
    * @brief Screen Space Ambient Oclusion Pass
    */
   void
   ssaoPass();

   /**
    * @brief Renders the given texture
    */
   void
   renderToScreen(int32 renderTarget);

   /**
    * @brief Blur h pass function
    */
   void
   blurH(Texture * textureToBlur);

   /**
    * @brief Blur v pass function
    */
   void
   blurV(Texture * textureToBlur);

   /**
    * @brief This function initializes all the objects that the renderer needs
    */
   void
   initRenderer();

   /**
    * @brief This function creates the render targets and the textures 
    * that are going to be used in the renderer.
    */
   void
   createRendererTextures();

   /**
    * @brief This function creates the shaders that are going to be used in the 
    * renderer.
    */
   void
   createRendererShaders();

  /************************************************************************/
  /* PBRRenderer declarations                                             */
  /************************************************************************/

 private:

  //RasterizerStates
   RasterizerState * m_rasterizerState;

   //InputLayouts
   InputLayout * m_gbufferLayout;
   InputLayout * m_pbrLayout;

   //VertexShaders
   VertexShader* m_gbufferVertexShader;
   VertexShader * m_quadAlignedVertexShader;

   //PixelShaders
   PixelShader * m_gbufferPixelShader;
   PixelShader * m_toneMapPixelShader;
   PixelShader * m_pbrPixelShader;
   PixelShader * m_backBufferPixelShader;
   PixelShader * m_ssaoPixelShader;
   PixelShader * m_blurh1PixelShader;
   PixelShader * m_blurv1PixelShader;

   //SamplerStates
   SamplerState * m_linearSampler;
   SamplerState * m_pointSampler;

   //Textures/RenderTargets
   Texture * m_positionsRT;
   Texture * m_normalsRT;
   Texture * m_albedoRT;
   Texture * m_emissiveRT;
   Texture * m_pbrRT;
   Texture * m_lut;
   Texture * m_toneMapRT;
   Texture * m_backBufferRT;
   Texture * m_irradiance;
   Texture * m_specularReflection;
   Texture * m_ssaoRT;
   Texture * m_blurH1RT;
   Texture * m_blurV1RT;
   Vector<Texture *> m_gbufferRTTextures;
   Vector<Texture *> m_pRTTextures;

   //Buffers
   Buffer * m_lightCBuffer;
   Buffer * m_ssaoCBuffer;

   //QuadAligned
   Model * quad;

   //Viewports
   VIEWPORT_DESCRIPTOR m_viewport;
   VIEWPORT_DESCRIPTOR m_halfViewport;

   uint32 stride;
   uint32 offset;
   float ClearColor1[4];

 };
}
