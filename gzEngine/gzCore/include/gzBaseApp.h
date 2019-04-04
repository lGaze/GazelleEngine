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
#include "IDVMath.h"


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
   Depth * m_pDepthStencilView;

   /**
    * @brief 
    */
   SamplerState * m_pSampler;

   /**
    * @brief 
    */
   VertexShader * m_pVertexShader;

   /**
    * @brief 
    */
   PixelShader * m_pPixelShader;


 /************************************************************************/
 /*       Test                                                           */
 /************************************************************************/

   struct SimpleVertex
   {
     XVECTOR3 Pos;
     XVECTOR3 Tex;
   };

   struct CBNeverChanges
   {
     XMATRIX44 mView;
   };

   struct CBChangeOnResize
   {
     XMATRIX44 mProjection;
   };

   struct CBChangesEveryFrame
   {
     XMATRIX44 mWorld;
     XVECTOR3 vMeshColor;
     XVECTOR3 ViewPosition;
   };

};

BaseApp&
g_baseApp();

}