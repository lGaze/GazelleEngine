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
    m_target = Vector3f(0.0f, 0.0f, 1.0f);
    m_up = Vector3f(0.0, 1.0, 0.0);
    m_worldUp = Vector3f(0.0f, 1.0f, 0.0f);

    m_fovy = PIFOURTHS;
    m_aspect =
      g_GraphicsManager().getViewportDimensions().x / 
      g_GraphicsManager().getViewportDimensions().y;
    m_zNear = DEFAULT_NEAR;
    m_zFar = DEFAULT_FAR;

    m_dirty = true;
  }

  void 
  Camera::move(Vector3f direction, float cameraSpeed)
  {
    Vector3f tmp = direction * cameraSpeed;
    m_eye += tmp;
    m_target += tmp;
    m_dirty = true;
  }

  void 
  Camera::moveForward(float cameraSpeed)
  {
    move(m_forward, cameraSpeed);
  }

  void 
  Camera::moveRight(float cameraSpeed)
  {
    move(m_right, cameraSpeed);
  }

  void 
  Camera::rotateY(float angle)
  {
    m_target -= m_eye;

    m_target.rotateq(angle, m_worldUp);

    m_target += m_eye;

    m_dirty = true;
  }

  void
  Camera::rotateX(float angle)
  {
    m_target -= m_eye;

    m_target.rotateq(angle, m_right);

    m_target += m_eye;

    m_dirty = true;
  }


  void 
  Camera::setPosition(Vector3f position)
  {
    m_eye = position;
    m_target = m_eye + Vector3f(0.0f, 0.0f, 1.0f);
    m_dirty = true;
  }

  void 
  Camera::updateViewMatrix()
  {
    m_viewMatrix = m_viewMatrix.matrixLookAtLH(m_eye, m_target, m_up);
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
    if (!m_dirty) { return; }
    
    m_forward = (m_target - m_eye).getNormalized();
    m_right = m_up.crossProduct(m_forward).getNormalized();
    m_up = m_forward.crossProduct(m_right).getNormalized();


    updateViewMatrix();
    updateProjectionMatrix();
    m_dirty = false;
  }
}
