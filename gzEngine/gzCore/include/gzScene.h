/**************************************************************************/
/* @filename gzScene.h
/* @author Victor Flores 
/* @date 2019/08/03
/* @brief 
/**************************************************************************/
#pragma once
#include "gzPrerequisitesCore.h"

namespace gzEngineSDK {
class GZ_CORE_EXPORT Scene
{
 public:
   
  /**
   * @brief default constructor
   */
  Scene();

  /**
   * @brief default destructor
   */
  ~Scene() = default;

  /************************************************************************/
  /* Scene functions                                                      */
  /************************************************************************/
  
  /**
   * @brief Adds a GameObject into the Scene
   */
  void
  addGameObject(GameObject & gameObject);

  /**
   * @brief Removes a GameObject from the scene
   */
  void
  removeGameObject();

  /**
   * @brief Gets the Scene Name
   */
  String
  getSceneName();

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 public:

  String m_name;

 private:

  GameObject * m_root;

 };
}

