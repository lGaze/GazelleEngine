/**************************************************************************/
/* @filename gzCameraManager.h
/* @author Victor Flores 
/* @date 2019/07/24
/* @brief This file can be used for create and manipulate cameras
/*************************************************************************/

#pragma once

#include "gzPrerequisitesCore.h"

#include <gzModule.h>

namespace gzEngineSDK {

  namespace CAMERA_MOVEMENT {
    enum E
    {
      FORWARD,
      BACKWARD,
      LEFT,
      RIGHT
    };
  }

class GZ_CORE_EXPORT CameraManager : public Module<CameraManager>
{
 public:

  /**
   * @brief Default Constructor
   */
  CameraManager();

  /**
   * @brief Default Destructor
   */
  ~CameraManager() = default;

  /************************************************************************/
  /* CameraManager functions                                              */
  /************************************************************************/

  /**
   * @brief This function creates a Camera
   * @return The created Camera
   */
  Camera *
  createCamera();

  /**
   * @brief Sets the given camera to be the active camera
   * @param The camera that is going to be the active camera
   */
  void
  setActiveCamera(Camera & camera);

  /**
   * @brief Sets the position of the active camera
   * @param Vector3f wich indicates the given position 
   */
  void
  setActiveCameraPosition(Vector3f newPosition);

  /**
   * @brief Moves the active camera
   * @param The direction of the movement
   */
  void
  moveActiveCamera(CAMERA_MOVEMENT::E direction);

  /**
   * @brief Updates the camera manager
   */
  void
  update();


  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 public:

   Camera * m_activeCamera;
   Vector<Camera *> m_cameras;
   
 };
}

