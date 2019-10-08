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
    * @brief Renders the given texture
    */
   void
   renderToScreen(int32 renderTarget);

   void
   initRenderer();

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

   //SamplerStates
   SamplerState * m_samplerState;

   //Textures/RenderTargets
   Texture * m_positionsRT;
   Texture * m_normalsRT;
   Texture * m_albedoRT;
   Texture * m_emissiveRT;
   Texture * m_pbrRT;
   Texture * m_lut;
   Texture * m_toneMapRT;
   Texture * m_backBufferRT;
   Vector<Texture *> m_gbufferRTTextures;
   Vector<Texture *> m_pRTTextures;

   //Buffers
   Buffer * m_lightCBuffer;

   //QuadAligned
   Model * quad;

   //Viewports
   VIEWPORT_DESCRIPTOR m_viewport;

   uint32 stride;
   uint32 offset;
   float ClearColor1[4];

 };
}
