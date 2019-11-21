/**************************************************************************/
/* @filename gzMeshComponent.h
/* @author Victor Flores 
/* @date 2019/07/14
/* @brief Class for the components of Mesh type
/**************************************************************************/
#pragma once
#include "gzPrerequisitesCore.h"
#include "gzComponent.h"

namespace gzEngineSDK {
class GZ_CORE_EXPORT MeshComponent : public Component
{
 public:
   
  /**
   * @brief default constructor
   */
  MeshComponent();

  /**
   * @brief default destructor
   */
  ~MeshComponent() = default;

  /************************************************************************/
  /* MeshComponent functions                                              */
  /************************************************************************/

  /**
   * @brief Functions that returns the type of this component
   * @return The type of this component
   */
  COMPONENT_TYPE::E
  getComponentType() override;

  /**
   * @brief Loads a mesh into the component
   * @param Path of the mesh 
   */
  void
  loadMesh(String path);

  /**
   * @brief This function updates the mesh component
   */
  void
  update() override;

  /**
   * @brief 
   * @param Reference to the new material 
   */
  void
  changeMaterial(Material &Material);

  /**
   * @brief This function gets the handle of the model
   */
  ResourceHandle<Model>
  getHandle() {
    return m_resource;
  }

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:

  ResourceHandle<Model> m_resource;
  COMPONENT_TYPE::E m_type;
   
 };
}
