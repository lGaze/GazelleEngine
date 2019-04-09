/**************************************************************************/
/* @filename BaseApp.h
/* @author Victor Flores 
/* @date 2019/03/02
/* @brief Base application
/*************************************************************************/

#pragma once

#include "gzPrerequisitesCore.h"
#include "gzWindow.h"
#include <gzModule.h>
#include <gzGraphicsManager.h>


namespace gzEngineSDK {
class GZ_CORE_EXPORT BaseApp : public Module<BaseApp>
{
 public:
   
  /**
   * @brief default constructor
   */
  BaseApp( uint32 windowWidth,
           uint32 windowHeight,
           String windowName,
           uint32 posX,
           uint32 posY );
	
  /**
   * @brief default destructor
   */
  ~BaseApp() = default;
	 
  /************************************************************************/
  /* BaseApp functions                                                    */
  /************************************************************************/
	
 public:

  /**
   * @brief Entry point of the base application
   */
  int32
  runMainLoop();

 private:

  /**
   * @brief Function which initializes all the Application needs 
   * @returns Bool value which indicates if the initialization succeed 
   */
  bool 
  initApp();

  /**
   * @brief 
   */
  bool
  postInit();

  /**
   * @brief Fuction for Render
   */
  void 
  render();

  /**
   * @brief Funtion for Update the logic 
   */
  void
  update();

  //TODO: Class for loadig libraries 
  /**
   * @brief Function for load plugins 
   * @returns Bool value wich indicates if the library could be loaded or not
   */
  bool
  loadLibrary(String libraryName, String funcName);
  

  using createGraphicsManager = void*(*)();

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
	
 private:
   
   /**
    * @brief Value wich indicates if the mainloop continues 
    */
   bool m_mainLoop;

   /**
    * @brief 
    */
   Window* m_pwindow;

   /**
    * @brief 
    */
   createGraphicsManager m_graphicsFunc;

   /**
    * @brief 
    */
   uint32 m_windowWidth;

   /**
    * @brief 
    */
   uint32 m_windowHeight;

   /**
    * @brief 
    */
   String m_windowName;

   /**
    * @brief 
    */
   uint32 m_windowPosX;

   /**
    * @brief 
    */
   uint32 m_windowPosY;

   /**
    * @brief BackBuffer RT
    */
   RenderTarget * m_pBackBuffer;  
   
   /**
    * @brief Albedo RT
    */
   RenderTarget * m_pAlbedoRT;

   /**
    * @brief Luminance RT
    */
   RenderTarget * m_pLuminanceRT;

   /**
    * @brief BlurH1 RT
    */
   RenderTarget * m_pBlurH1RT;

   /**
    * @brief BlurV1 RT
    */
   RenderTarget * m_pBlurV1RT;

   /**
    * @brief Bright RT
    */
   RenderTarget * m_pBrightRT;

   /**
    * @brief AddBright1 RT
    */
   RenderTarget * m_pAddBright1RT; 
   
   /**
    * @brief ToneMap RT
    */
   RenderTarget * m_pToneMapRT;

   /**
    * @brief 
    */
   Texture * renderTarget;

   /**
    * @brief 
    */
   Depth * m_pDepthStencilView;

   /**
    * @brief 
    */
   SamplerState * m_pSampler;

   /**
    * @brief 
    */
   VertexShader * m_pLightVertexShader;

   /**
    * @brief 
    */
   VertexShader * m_pLuminanceVertexShader;

   /**
    * @brief 
    */
   VertexShader * m_pBrightVertexShader;

   /**
    * @brief 
    */
   VertexShader * m_pBlurH1VertexShader; 
   
   /**
    * @brief 
    */
   VertexShader * m_pBlurV1VertexShader;

   /**
    * @brief 
    */
   VertexShader * m_pAddBright1VertexShader;

   /**
    * @brief 
    */
   VertexShader * m_pToneMapVertexShader;

   /**
    * @brief 
    */
   PixelShader * m_pLightPixelShader;

   /**
    * @brief 
    */
   PixelShader * m_pLuminancePixelShader;

   /**
    * @brief 
    */
   PixelShader * m_pBrightPixelShader;

   /**
    * @brief 
    */
   PixelShader * m_pBlurH1PixelShader;

   /**
    * @brief 
    */
   PixelShader * m_pBlurV1PixelShader;

   /**
    * @brief 
    */
   PixelShader * m_pAddBright1PixelShader;

   /**
    * @brief 
    */
   PixelShader * m_pToneMapPixelShader;

   /**
    * @brief 
    */
   Texture * textGorda;

   /**
    * @brief BackBuffer texture 
    */
   Texture * m_pBackBufferTex;

   /**
    * @brief Texture for Albedo RT
    */
   Texture * m_pAlbedoTexture;

   /**
    * @brief Texture for Luminance RT
    */
   Texture * m_pLuminanceTexture;

   /**
    * @brief Texture for Bright RT
    */
   Texture * m_pBrightTexture;

   /**
    * @brief Texture for Blurh1
    */
   Texture * m_pBlurH1Texture;

   /**
    * @brief Texture for BlurV1
    */
   Texture * m_pBlurV1Texture;

   /**
    * @brief Texture for AddBright1
    */
   Texture * m_pAddBright1Texture;
   
   /**
    * @brief Texture for AddBright1
    */
   Texture * m_pToneMapTexture;

   /**
    * @brief 
    */
   Mesh * quad;

   /**
    * @brief 
    */
   Mesh * cube;

   /**
    * @brief Input layout for luminance
    */
   InputLayout * luminanceInputLayout;

   /**
    * @brief Input layout for bright shader
    */
   InputLayout * m_pBrightInputLayout;

   /**
    * @brief InputL layout for light
    */
   InputLayout * inputLayout;

   /**
    * @brief Input Layout for BlurH1
    */
   InputLayout * m_pBlurH1InputLayout;

   /**
    * @brief Input Layout for BlurV1
    */
   InputLayout * m_pBlurV1InputLayout;

   /**
    * @brief Input Layout for AddBright1
    */
   InputLayout * m_pAddBright1InputLayout; 
   
   /**
    * @brief Input Layout for AddBright1
    */
   InputLayout * m_pToneMapInputLayout;

   /**
    * @brief 
    */
   Buffer * vCubeBuffer;

   /**
    * @brief 
    */
   Buffer * iCubeBuffer;

   /**
    * @brief 
    */
   Buffer * vQuadBuffer;

   /**
    * @brief 
    */
   Buffer * iQuadBuffer;

   /**
    * @brief 
    */
   RasterizerState * m_RasterizerState;


   /**
    * @brief normal viewport
    */
   VIEWPORT_DESCRIPTOR vp;

   /**
    * @brief normal viewport / 2
    */
   VIEWPORT_DESCRIPTOR vp2;


 /************************************************************************/
 /*       Test                                                           */
 /************************************************************************/


   struct SimpleVertex
   {
     DirectX::XMFLOAT3 Pos;
     DirectX::XMFLOAT3 Normal;
     DirectX::XMFLOAT2 Tex;
   };


   struct CBNeverChanges
   {
     DirectX::XMMATRIX mView;
   };

   struct CBChangeOnResize
   {
     DirectX::XMMATRIX mProjection;
   };

   struct CBChangesEveryFrame
   {
     DirectX::XMMATRIX mWorld;
     DirectX::XMFLOAT4 vMeshColor;
     DirectX::XMFLOAT4 ViewPosition;
   };

 

   DirectX::XMMATRIX g_World;
   DirectX::XMMATRIX g_World2;
   DirectX::XMMATRIX g_World3;

   DirectX::XMMATRIX g_View;
   DirectX::XMMATRIX g_Projection;

   DirectX::XMVECTOR Eye;

   Buffer * constantNeverChanges;
   Buffer * constantChangesonResize;
   Buffer * constantChangesEveryFrame;

};

BaseApp&
g_baseApp();

}