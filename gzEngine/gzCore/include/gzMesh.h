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
  readTextures();

  /**
   * @brief
   */
  bool
  processData();

 /* / **
   * @brief
   * /
  FORCEINLINE VERTICES *
    getVertexData()
  {
    return &m_vecVert[0];
  }

  / **
   * @brief
   * /
  FORCEINLINE uint16 *
    getIndexData()
  {
    return &indexBuff[0];
  }

  / **
   * @brief
   * /
  FORCEINLINE uint32
    getNumVertices()
  {
    return m_vecVert.size();
  }

  / **
   * @brief
   * /
  FORCEINLINE uint32
    getNumIndices()
  {
    return indexBuff.size();
  }*/

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
   * @brief Vector that stores all the texture paths of the Mesh
   */
  Vector<String>TexturePaths;


  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:


  Vector<MESH_DATA> m_meshData;
  //Vector<VERTICES> m_vecVert;
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

 // Vector<uint16> indexBuff;
  Vector<float> vertexBuff;

  int32 m_iNumVertices;
  uint32 m_iNumIndices;

 };
}