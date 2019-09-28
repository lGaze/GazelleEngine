/**************************************************************************/
/* @filename BaseApp.h
/* @author Victor Flores 
/* @date 2019/03/02
/* @brief In this file are the basic function for a application to work 
/* correctly.
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
   * @brief Default Constructor
   */
  BaseApp() = default;

  /**
   * @brief Default Destructor
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

 protected:

  /**
   * @brief Function which initializes all the Application needs to run 
   * @return Bool value which indicates if the initialization succeed or not
   */
  virtual bool 
  initApp();

  /**
   * @brief Function that initializes the specific things of the application 
   * @return Bool value which indicates if the initialization succeed or not
   */
  virtual bool
  postInit() = 0;

  /**
   * @brief Fuction which the app uses for render objects
   */
  virtual void 
  render();

  /**
   * @brief Funtion for Update the logic 
   */
  virtual void
  update() = 0;

  //TODO: Class for loadig libraries 
  /**
   * @brief Function for load plugins 
   * @returns Bool value wich indicates if the library could be loaded or not
   */
  bool
  loadLibrary(String libraryName, String funcName);  


  using createLibrary = void*(*)();

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 protected:
   
   /**
    * @brief Value wich indicates if the mainloop continues 
    */
   bool m_mainLoop;

   /**
    * @brief Pointer to the window  
    */
   Window* m_pwindow;

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
   createLibrary m_library;

   public:

   Buffer * constantLightBuffer;

};

BaseApp&
g_baseApp();
}