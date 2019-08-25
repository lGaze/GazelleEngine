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

   RasterizerState * m_rasterizerState;
   InputLayout * m_gbufferLayout;
   InputLayout * m_pbrLayout;
   VertexShader* m_gbufferVertexShader;
   PixelShader * m_gbufferPixelShader;
   PixelShader * m_toneMapPixelShader;
   VertexShader * m_pbrVertexShader;
   PixelShader * m_pbrPixelShader;
   SamplerState * m_samplerState;
   Texture * m_positionsRT;
   Texture * m_normalsRT;
   Texture * m_albedoRT;
   Texture * m_emissiveRT;
   Texture * m_pbrRT;
   Texture * m_lut;
   Texture * m_backBuffer;
   Model * quad;
   Vector<Texture *> m_gbufferRTTextures;
   Buffer * m_lightCBuffer;
   float ClearColor1[4] = { 0,0,0,0 };

 };
}
