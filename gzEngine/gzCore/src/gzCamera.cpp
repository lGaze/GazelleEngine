/**************************************************************************/
/* @filename gzCamera.cpp
/* @author Victor Flores 
/* @date 2019/07/19
/* @brief 
/**************************************************************************/

#include "gzCamera.h"
#include <gzGraphicsManager.h>

namespace gzEngineSDK {

  Camera::Camera()
  {

    m_eye = Vector3f(0.0f, 0.0f, 0.0f);
    m_front = Vector3f(0.0f, 0.0f, -1.0f);
    m_up = Vector3f(0.0, 1.0, 0.0);

    m_fovy = PIFOURTHS;
    m_aspect =
      GraphicsManager::instance().getViewportDimensions().x / 
      GraphicsManager::instance().getViewportDimensions().y;
    m_zNear = DEFAULT_NEAR;
    m_zFar = DEFAULT_FAR;

    m_dirty = true;
  }

  void 
  Camera::move(Vector3f direction, float cameraSpeed)
  {
    m_eye += direction * cameraSpeed;
    m_front = m_eye + Vector3f(0.0f, 0.0f, -1.0f);
    m_dirty = true;
  }

  void 
  Camera::rotate(Vector3f axis, float degrees)
  {
  }

  void 
  Camera::setPosition(Vector3f position)
  {
    m_eye = position;
    m_front += m_eye;
    m_dirty = true;
  }

  void 
  Camera::updateViewMatrix()
  {
    m_viewMatrix = m_viewMatrix.matrixLookAtLH(m_eye, m_front, m_up);
  }

  void 
  Camera::updateProjectionMatrix()
  {
    m_projectionMatrix =
      m_projectionMatrix.matrixPerspectiveFovLH(m_fovy,
                                                m_aspect,
                                                m_zNear,
                                                m_zFar);
  }

  void 
  Camera::updateCamera()
  {
    if (!m_dirty) {
      return;
    }
    updateViewMatrix();
    updateProjectionMatrix();
    m_dirty = false;
  }
}
