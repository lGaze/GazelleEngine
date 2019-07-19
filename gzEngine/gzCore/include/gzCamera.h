/**************************************************************************/
/* @filename gzCamera.h
/* @author Victor Flores 
/* @date 2019/07/15
/* @brief Camera class header file
/**************************************************************************/

#pragma once
#include "gzPrerequisitesCore.h"

namespace gzEngineSDK {
class GZ_CORE_EXPORT Camera
{
 public:

  /**
   * @brief default constructor
   */
  Camera(int width, int height);

  /**
   * @brief default destructor
   */
  ~Camera() = default;

  /************************************************************************/
  /* Camera functions                                                     */
  /************************************************************************/

  /**
   * @brief This function makes the camera moves
   */
  void
  Move(Vector3f direction, float cameraSpeed);

  /**
   * @brief This function makes the camera rotate
   */
  void
  Rotate(Vector3f axis, float degrees);

  /**
   * @brief This function sets camera position coordinates
   */
  void
  setPosition(Vector3f position);

  /**
   * @brief 
   */
  void
  setTarget(Vector3f target);


  /**
   * @brief Gets the transposed view matrix
   */
  FORCEINLINE const Matrix4
  getViewMatrix() {
    m_viewMatrix.transpose();
    return m_viewMatrix;
  }

  /**
   * @brief Gets the trasnposed projection matrix
   */
  FORCEINLINE const Matrix4
  getProjectionMatrix() {
    m_projectionMatrix.transpose();
    return m_projectionMatrix;
  }

 private:

  /**
   * @brief 
   */
  void
  UpdateViewMatrix();


  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:

  Vector3f m_eye; //Camera Postition
  Vector3f m_at; //Target Position
  Vector3f m_up; //Camera up vector

  float m_fovy;
  float m_aspect;
  float m_zNear;
  float m_zFar;

  Matrix4 m_viewMatrix; //View matrix
  Matrix4 m_projectionMatrix; //Projection matrix


 };
}
