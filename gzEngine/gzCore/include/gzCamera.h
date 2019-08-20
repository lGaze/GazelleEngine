/**************************************************************************/
/* @filename gzCamera.h
/* @author Victor Flores 
/* @date 2019/07/15
/* @brief Caemera header file
/**************************************************************************/

#pragma once
#include "gzPrerequisitesCore.h"

namespace gzEngineSDK {
class GZ_CORE_EXPORT Camera
{
 public:

  /**
   * @brief Default constructor.
   */
  Camera(int32 width, int32 height);

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
  Move(Vector3f direction, float cameraSpeed);

  /**
   * @brief This function makes the camera rotate.
   */
  void
  Rotate(Vector3f axis, float degrees);

  /**
   * @brief This function sets camera position coordinates.
   */
  void
  setPosition(Vector3f position);

  /**
   * @brief This function sets the target of the camera.
   */
  void
  setTarget(Vector3f target);

  Vector3f
  getEyePosition() {
    return m_eye;
  }

  /**
   * @brief Gets the transposed view matrix.
   * @return Transposed view matrix.
   */
  FORCEINLINE const Matrix4
  getViewMatrix() {
    m_viewMatrix.transpose();
    return m_viewMatrix;
  }

  /**
   * @brief Gets the trasnposed projection matrix.
   * @return Transposed projection matrix.
   */
  FORCEINLINE const Matrix4
  getProjectionMatrix() {
    m_projectionMatrix.transpose();
    return m_projectionMatrix;
  }

  /**
   * @brief This function updates the camera if it changed
   */
  void
  UpdateCamera();

 private:

  /**
   * @brief This function updates the view matrix if is needed
   */
  void
  UpdateViewMatrix();

  /**
   * @brief This function updates the projection matrix if is needed
   */
  void
  UpdateProjectionMatrix();

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:

  Vector3f m_eye; //Camera Postition
  Vector3f m_at; //Target Position
  Vector3f m_up; //Camera up vector

  float m_fovy; //field of view
  float m_aspect; //aspect of the window
  float m_zNear; //nearest point that the camera can see
  float m_zFar; //farest point that the camera can see

  Matrix4 m_viewMatrix; //View matrix
  Matrix4 m_projectionMatrix; //Projection matrix

  bool m_dirty;

 };
}
