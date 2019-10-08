/**************************************************************************/
/* @filename gzGraphicsTestApp.h
/* @author Victor Flores 
/* @date 2019/08/26
/* @brief Application for testing graphic things
/**************************************************************************/
#pragma once

#include <gzBaseApp.h>


namespace gzEngineSDK {
class GrapichsTestApp : public BaseApp
{
 public:
 
  /**
   * @brief default constructor
   */
  GrapichsTestApp(uint32 windowWidth,
                  uint32 windowHeight,
                  String windowName,
                  int32 posX,
                  int32 posY);

   /**
    * @brief default destructor
    */
  ~GrapichsTestApp() = default;

  /************************************************************************/
  /* GrapichsTestApp functions                                            */
  /************************************************************************/

 protected:

  /**
   * @brief Function that initializes the specific things of the application
   * @return Bool value which indicates if the initialization succeed or not
   */
  virtual bool
  postInit() override;

  /**
   * @brief Funtion for Update the logic of the app
   */
  virtual void 
  update() override;

  /**
   * @brief Function which initializes all the Application needs to run
   * @return Bool value which indicates if the initialization succeed or not
   */
  virtual bool
  initApp() override;

  /**
   * @brief Fuction which the app uses for render objects
   */
  virtual void
  render() override;

  /**
   * @brief Funtion that initializes ImGui
   */
  bool
  initImGui();

  /**
   * @brief function for render the imgui
   */
  void
  renderImGui();

  /**
   * @brief Opens a windows dialog and gets the path of the file
   */
  void
  openfile();



  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:
   
   Camera * m_camera;

   struct cbMatrix
   {
     Matrix4 view;
     Matrix4 projection;
     Matrix4 world;
   };

   struct cbLight
   {
     Vector4f viewPosition;
     Vector4f lightPosition;
     Vector4f clearColor;
   };

   cbLight cbLightBuffer;
   cbMatrix cbMatrixbuffer;

   Matrix4 g_World;

   Vector3f Eye;

   Buffer * constantMatrix;

   GameObject * m_gameObject;

   Material * tempMaterial;

   bool wasRotatingX = false;
   bool wasRotatingY = false;

   float time;
   float rotationValue = 0.0f;
   Vector4f m_ViewPos;
};
}
