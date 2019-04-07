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
    * @brief 
    */
   RenderTarget * m_pBackBuffer;  
   
   /**
    * @brief 
    */
   RenderTarget * m_pAlbedoRT;

   /**
    * @brief 
    */
   RenderTarget * m_pLuminanceRT;

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
   PixelShader * m_pLightPixelShader;

   /**
    * @brief 
    */
   Texture * textGorda;

   /**
    * @brief 
    */
   Texture * m_pBackBufferTex;

   /**
    * @brief 
    */
   Texture * m_pAlbedoTexture;

   /**
    * @brief 
    */
   Texture * m_pLuminanceTexture;

   /**
    * @brief 
    */
   Mesh * quad;

   /**
    * @brief 
    */
   Mesh * cube;



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