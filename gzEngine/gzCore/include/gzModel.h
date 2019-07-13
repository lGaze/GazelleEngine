/**************************************************************************/
/* @filename gzModel.h
/* @author Victor Flores 
/* @date 2019/07/05
/* @brief 
/**************************************************************************/

#pragma once

#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include "gzPrerequisitesCore.h"
#include "gzTexture.h"

namespace gzEngineSDK {

struct Mesh {
    uint32 vertexBase;
    uint32 indexBase;
    uint32 numVertex;
    uint32 numIndex;
    Vector<Texture*> textures;
};

class GZ_CORE_EXPORT Model
{
 public:
   
  /**
   * @brief default constructor
   */
  Model();
 
  /**
   * @brief default destructor
   */
  ~Model() = default;

  /************************************************************************/
  /* Model functions                                                      */
  /************************************************************************/

 public:

   /**
    * @brief 
    */
   bool
   Load(String filename);

   /**
    * @brief 
    */
   void
   Draw();

 private:

   /**
    * @brief 
    */
   Texture *
   LoadTextures(aiMaterial* material);

  /************************************************************************/
  /* Member functions                                                     */
  /************************************************************************/

 private:

   Vector<VERTEX> m_vertices;

   Vector<uint32> m_indices;

   Vector<Mesh> m_mesh;

   String m_directoryPath;
 
 };
}
