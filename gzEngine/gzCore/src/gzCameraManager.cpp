/**************************************************************************/
/* @filename gzCameraManager.cpp
/* @author Victor Flores 
/* @date 2019/08/24
/**************************************************************************/

#include "gzCameraManager.h"
#include "gzCamera.h"
#include <gzTime.h>

namespace gzEngineSDK {

  CameraManager::CameraManager() : m_activeCamera(nullptr) {}

  Camera * 
  CameraManager::createCamera()
  {
    Camera * tmpCamera = new Camera();
    if (m_activeCamera == nullptr)
    {
      m_activeCamera = tmpCamera;
    }
    
    m_cameras.push_back(tmpCamera);
    return tmpCamera;
  }

  void 
  CameraManager::setActiveCamera(Camera & camera)
  {
    m_activeCamera = &camera;
  }

  void 
  CameraManager::setActiveCameraPosition(Vector3f newPosition)
  {
    m_activeCamera->setPosition(newPosition);
    m_activeCamera->updateCamera();
  }

  void 
  CameraManager::moveActiveCamera(CAMERA_MOVEMENT::E direction)
  {
    if (direction == CAMERA_MOVEMENT::E::LEFT)
    {
      m_activeCamera->moveRight(-100.0f * g_Time().getDelta());
      m_activeCamera->updateCamera();
    }

    if (direction == CAMERA_MOVEMENT::E::RIGHT)
    {
      m_activeCamera->moveRight(100.0f * g_Time().getDelta());
      m_activeCamera->updateCamera();
    }

    if (direction == CAMERA_MOVEMENT::E::FORWARD)
    {
      m_activeCamera->moveForward(100.0f * g_Time().getDelta());
      m_activeCamera->updateCamera();
    }

    if (direction == CAMERA_MOVEMENT::E::BACKWARD)
    {
      m_activeCamera->moveForward(-100.0f * g_Time().getDelta());
      m_activeCamera->updateCamera();
    }

  }

  void
  CameraManager::rotateActiveCameraX(float angle)
  {
    m_activeCamera->rotateX(angle);
    m_activeCamera->updateCamera();
  }

  void
  CameraManager::rotateActiveCameraY(float angle)
  {
    m_activeCamera->rotateY(angle);
    m_activeCamera->updateCamera();
  }

  Vector3f 
  CameraManager::getActiveCameraEyePosition()
  {
    return m_activeCamera->getEyePosition();
  }

  Matrix4 
  CameraManager::getActiveCameraViewMatrix()
  {
    return m_activeCamera->getViewMatrix();
  }

  Matrix4 
  CameraManager::getActiveCameraProjectionMatrix()
  {
    return m_activeCamera->getProjectionMatrix();
  }

  void 
  CameraManager::update()
  {
    m_activeCamera->updateCamera();
  }
}

