/**************************************************************************/
/* @filename gzCamera.cpp
/* @author Victor Flores 
/* @date 2019/07/19
/* @brief 
/**************************************************************************/

#include "gzCamera.h"

namespace gzEngineSDK {

  Camera::Camera(int width, int height)
  {
    m_eye = Vector3f(0.0f, 0.0f, -1.0);
    m_at = Vector3f(0.0f, 0.0f, 0.0f);
    m_up = m_eye + Vector3f(0.0, 1.0, 0.0);
    UpdateViewMatrix();

    m_fovy = 0.785398163f;
    m_aspect =
      static_cast<float>(width) / static_cast<float>(height);
    m_zNear = 3.0f;
    m_zFar = 1000.0f;
    m_projectionMatrix = m_projectionMatrix.matrixPerspectiveFovLH(m_fovy,
                                                                   m_aspect,
                                                                   m_zNear,
                                                                   m_zFar);
  }

  void 
  Camera::Move(Vector3f direction, float cameraSpeed)
  {
    m_eye += direction * cameraSpeed;
    m_at = m_eye + Vector3f(0.0, 0.0, 1.0);
    UpdateViewMatrix();
  }

  void 
  Camera::Rotate(Vector3f axis, float degrees)
  {
  }

  void 
  Camera::setPosition(Vector3f position)
  {
    m_eye = position;
    UpdateViewMatrix();
  }

  void 
  Camera::setTarget(Vector3f target)
  {
  }

  void 
  Camera::UpdateViewMatrix()
  {
    m_viewMatrix = m_viewMatrix.matrixLookAtLH(m_eye, m_at, m_up);
  }
}
