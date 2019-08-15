/**************************************************************************/
/* @filename gzModel.h
/* @author Victor Flores 
/* @date 2019/07/05
/* @brief 
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

   /**
    * @brief
    */
   void
   changeMaterial(Material & newMat);

   Buffer * m_vertexBuffer;

   Buffer * m_indexBuffer;

   Vector<Mesh> m_mesh;

 private:

   /**
    * @brief 
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
