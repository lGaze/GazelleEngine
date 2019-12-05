/**************************************************************************/
/* @filename gzSceneManager.cpp
/* @author Victor Flores 
/* @date 2019/08/03
/**************************************************************************/
#include "gzSceneManager.h"
#include "gzPrerequisitesCore.h"
#include "gzScene.h"
#include "gzGameObject.h"


namespace gzEngineSDK {

  SceneManager::SceneManager() : m_objectId(-1)
  {
    m_activeScene = nullptr;
  }

  void 
  SceneManager::setActiveScene()
  {
    m_activeScene = m_scenes[0];
  }

  Scene * 
  SceneManager::getActiveScene()
  {
    return m_activeScene;
  }

  void 
  SceneManager::createScene()
  {
    Scene * newScene = new Scene();
    m_scenes.push_back(newScene);
  }

  GameObjectHandle
  SceneManager::createEmptyGameObject()
  {
    GameObjectHandle handle;
    GameObject * emptyGameObject = new GameObject(m_objectId);
    m_objectId++;
    handle.setHandle(emptyGameObject);

    auto mapObjectName = m_gameObjectMap.find(handle->m_objectName);
    String gameObjectNum(" (");
    if (mapObjectName != m_gameObjectMap.end())
    {
      gameObjectNum.append(std::to_string(handle->m_uniqueID));
      handle->m_objectName.append(gameObjectNum += ")");
      return handle;
    }

    m_gameObjectMap.insert(std::pair<String, GameObjectHandle>(
      handle->m_objectName,
      handle));
    return handle;
  }

  GameObjectHandle 
  SceneManager::createEmptyGameObject(String gameObjectName)
  {
    GameObjectHandle handle;
    GameObject * emptyGameObject = new GameObject(m_objectId);
    m_objectId++;
    handle.setHandle(emptyGameObject);
    handle->m_objectName = gameObjectName;
    auto mapObjectName = m_gameObjectMap.find(handle->m_objectName);

    String gameObjectNum(" (");
    if (mapObjectName != m_gameObjectMap.end())
    {
      gameObjectNum.append(std::to_string(handle->m_uniqueID));
      handle->m_objectName.append(gameObjectNum += ")");
      return handle;
    }

    m_gameObjectMap.insert(std::pair<String, GameObjectHandle>(
      handle->m_objectName,
      handle));

    return handle;
  }

  void
  SceneManager::addGameObjectToScene(GameObjectHandle gameObject)
  {
    GameObject * tmpObject = reinterpret_cast<GameObject*>(gameObject.getHandle());
    m_activeScene->addGameObject(tmpObject);
  }

  void 
  SceneManager::update()
  {
    m_activeScene->update();
  }

  bool
  SceneManager::isActiveSceneEmpty()
  {
    return m_activeScene->isRootEmpty();
  }


  Vector<GameObjectHandle>
  SceneManager::getRendereableGameObjects()
  {
    Vector<GameObjectHandle> tmpGameObjectHandles;
    GameObjectHandle handle;
    tmpGameObjectHandles.reserve(m_activeScene->getRendereableGameObjects().size());
    for (auto it : m_activeScene->getRendereableGameObjects())
    {
      handle.setHandle(it);
      tmpGameObjectHandles.push_back(handle);
    }

    return tmpGameObjectHandles;
  }

  Vector<GameObject*> 
  SceneManager::getChildren()
  {
    return m_activeScene->getChildren();
  }

  String
  SceneManager::getActiveSceneName()
  {
    return m_activeScene->m_name.c_str();
  }

  GameObjectHandle
  SceneManager::findGameObjectByName(String gameObjectName)
  {
    auto filename = m_gameObjectMap.find(gameObjectName);
    if (filename != m_gameObjectMap.end())
    {
      return filename->second;
    }
    return GameObjectHandle();
  }

}