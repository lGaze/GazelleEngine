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
    * @brief 
    */
   virtual void
   render() override;

 private:

   void
   createGBuffer();

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
   VertexShader * m_pbrVertexShader;

   //PixelShaders
   PixelShader * m_gbufferPixelShader;
   PixelShader * m_toneMapPixelShader;
   PixelShader * m_pbrPixelShader;

   //SamplerStates
   SamplerState * m_samplerState;

   //Textures/RenderTargets
   Texture * m_positionsRT;
   Texture * m_normalsRT;
   Texture * m_albedoRT;
   Texture * m_emissiveRT;
   Texture * m_pbrRT;
   Texture * m_lut;
   Texture * m_backBufferRT;
   Vector<Texture *> m_gbufferRTTextures;

   //Buffers
   Buffer * m_lightCBuffer;

   //QuadAligned
   Model * quad;

   //Viewports
   VIEWPORT_DESCRIPTOR m_viewport;

   float ClearColor1[4] = { 0,0,0,0 };

 };
}
