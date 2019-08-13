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
   VertexShader* m_gbufferVertexShader;
   PixelShader * m_gbufferPixelShader;
   SamplerState * m_samplerState;
   Texture * m_positionsRT;
   Texture * m_normalsRT;
   Texture * m_albedoRT;
   Texture * m_emissiveRT;
   //Model * quad;
   Vector<Texture *> m_gbufferRTTextures;
 };
}
