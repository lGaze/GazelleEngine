/**************************************************************************/
/* @filename gzCamera.h
/* @author Victor Flores 
/* @date 2019/07/15
/* @brief Caemera header file
/**************************************************************************/

#pragma once
#include "gzPrerequisitesCore.h"

constexpr auto DEFAULT_NEAR = 3.0f;
constexpr auto DEFAULT_FAR = 1000.0f;

namespace gzEngineSDK {
class GZ_CORE_EXPORT Camera
{
 public:

  /**
   * @brief Default constructor.
   */
  Camera();

  /**
   * @brief Default destructor.
   */
  ~Camera() = default;

  /************************************************************************/
  /* Camera functions                                                     */
  /************************************************************************/

  /**
   * @brief This function makes the camera move.
   */
  void
  move(Vector3f direction, float cameraSpeed);

  /**
   * @brief This function moves the camera in the forward direction of the camera
   */
  void
  moveForward(float cameraSpeed);

  /**
   * @brief This function moves the camera in the right direction of the camera
   */
  void
  moveRight(float cameraSpeed);

  /**
   * @brief This function makes the camera rotate in X axis.
   */
  void
  rotateX(float angle);

  /**
   * @brief This function makes the camera rotate in Y axis.
   */
  void
  rotateY(float angle);

  /**
   * @brief This function sets camera position coordinates.
   */
  void
  setPosition(Vector3f position);

  Vector3f
  getEyePosition() {
    return m_eye;
  }

  /**
   * @brief Gets the transposed view matrix.
   * @return Transposed view matrix.
   */
  FORCEINLINE Matrix4
  getViewMatrix() {
    return m_viewMatrix;
  }

  /**
   * @brief Gets the trasnposed projection matrix.
   * @return Transposed projection matrix.
   */
  FORCEINLINE Matrix4
  getProjectionMatrix() {
    return m_projectionMatrix;
  }

  /**
   * @brief This function updates the camera if it changed
   */
  void
  updateCamera();

 private:

  /**
   * @brief This function updates the view matrix if is needed
   */
  void
  updateViewMatrix();

  /**
   * @brief This function updates the projection matrix if is needed
   */
  void
  updateProjectionMatrix();

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:

  Vector3f m_eye; //Camera Postition
  Vector3f m_target; //Front Position
  Vector3f m_up; //Camera up vector
  Vector3f m_worldUp; //world up vector
  Vector3f m_forward;
  Vector3f m_right;

  float m_fovy; //field of view
  float m_aspect; //aspect of the window
  float m_zNear; //nearest point that the camera can see
  float m_zFar; //farest point that the camera can see

  Matrix4 m_viewMatrix; //View matrix
  Matrix4 m_projectionMatrix; //Projection matrix

  bool m_dirty;

 };
}
