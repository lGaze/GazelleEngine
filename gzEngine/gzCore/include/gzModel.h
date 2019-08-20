/**************************************************************************/
/* @filename gzModel.h
/* @author Victor Flores 
/* @date 2019/07/05
/* @brief This file can be used for create models 
/**************************************************************************/

#pragma once

#include "gzPrerequisitesCore.h"
#include "gzTexture.h"
#include "gzResource.h"

struct aiMaterial;

namespace gzEngineSDK {

struct Mesh {
    uint32 vertexBase;
    uint32 indexBase;
    uint32 numVertex;
    uint32 numIndex;
    Material * material;
};

class GZ_CORE_EXPORT Model : public Resource
{
 public:
   
  /**
   * @brief Default Constructor
   */
  Model();
 
  /**
   * @brief Default Destructor
   */
  ~Model() = default;

  /************************************************************************/
  /* Model functions                                                      */
  /************************************************************************/

 public:

   /**
    * @brief This function loads a model from a given path 
    * @param The path of the model
    * @return Bool value wich indicates if the load succed or not
    */
   bool
   Load(String filename);

   /**
    * @brief This function draws all the meshes 
    */
   void
   Draw();

   /**
    * @brief This function changes the material for a new one
    * @param Reference to the new material 
    */
   void
   changeMaterial(Material & newMat);

   //TODO: Fix this public variables, make them private and make getters

   Buffer * m_vertexBuffer;

   Buffer * m_indexBuffer;

   Vector<Mesh> m_mesh;

 private:

   /**
    * @brief This function creates a material
    * @param Material from assimp 
    * @return A new material of the mesh
    */
   Material *
   createMaterial(aiMaterial* material);

   

  /************************************************************************/
  /* Member functions                                                     */
  /************************************************************************/

 private:

   Vector<VERTEX> m_vertices;

   Vector<uint32> m_indices;


   String m_directoryPath;

 };
}
