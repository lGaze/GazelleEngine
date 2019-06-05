/**************************************************************************/
/* @filename gzMesh.h
/* @author Victor Flores 
/* @date 2019/04/06
/* @brief 
/**************************************************************************/

#pragma once
#include "gzPrerequisitesCore.h"

#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <gzGraphicsManager.h>

namespace gzEngineSDK {
class GZ_CORE_EXPORT Mesh
{
 public:

 /**
  * @brief default constructor
  */
  Mesh();

  /**
   * @brief default destructor
   */
  ~Mesh() = default;

  /************************************************************************/
  /* DXMesh functions                                                     */
  /************************************************************************/

 public:

  /**
   * @brief
   */
  bool
  loadModel( String fileName );


  /**
   * @brief
   */
  bool
  processData();

  /**
   * @brief 
   */
  FORCEINLINE MESH_DATA *
  getMeshData() { 
    return &m_meshData[0];
  }

  /**
   * @brief 
   */
  FORCEINLINE int32
  getNumMeshes() {
    return m_meshData.size();
  }

 private:

  /**
   * @brief
   */
  bool
  assimpGetMeshData( const aiMesh * mesh );

  /**
   * @brief This function loads and stores the textures of the mesh
   */
  bool
  loadTextures();

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 public:

  /**
   * @brief Vector that stores all the texture paths of the Mesh
   */
  Vector<Texture*>MeshTextures;

 private:


  Vector<MESH_DATA> m_meshData;

  VERTICES * m_pVertices;

  int32 m_IndexIterator;
  Assimp::Importer importer;
  const aiScene *m_pModelScene;
  const aiNode *m_pModelNode;
  const aiMesh *m_pModelMesh;
  const aiFace *m_pModelFace;

  Vector<const aiNode*> m_pVecNodeBuff;
  uint32 m_iNumNodeBuff;
  Vector<Buffer*> Meshes;

  Vector<float> vertexBuff;

  String filePath;

 };
}