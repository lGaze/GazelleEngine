#include "..\include\gzMesh.h"
#include "gzPrerequisitesCore.h"

namespace gzEngineSDK {

Mesh::Mesh() : 
  m_pModelScene(nullptr),
  m_pModelNode(nullptr),
  m_pModelMesh(nullptr),
  m_pModelFace(nullptr),
  m_IndexIterator(0),
  m_iNumVertices(0)
{}

bool
Mesh::loadModel( String fileName )
{
  int32 flags = aiProcess_Triangulate | aiProcessPreset_TargetRealtime_MaxQuality;
  m_pModelScene = importer.ReadFile( fileName, flags );

  if ( !m_pModelScene )
  {
    return false;
  }
  else
  {
    processData();
  }

  readTextures();

  return true;
}

bool Mesh::readTextures()
{
  for ( uint32 i = 0; i < m_pModelScene->mNumMeshes; i++ )
  {
    aiString Path;

    const aiMaterial* Material =
      m_pModelScene->mMaterials[m_pModelScene->mMeshes[i]->mMaterialIndex];

    if ( Material->GetTexture(
      aiTextureType_DIFFUSE,
      0,
      &Path,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr ) == AI_SUCCESS )
    {
      TexturePaths.push_back( static_cast< std::string >( Path.data ) );
    }
  }
  return true;
}

bool Mesh::processData()
{
  bool repeat = true;
  m_pVecNodeBuff.push_back( m_pModelScene->mRootNode );


  while ( repeat )
  {
    for ( uint32 i = 0; i < m_pVecNodeBuff.size(); i++ )
    {
      m_pModelNode = m_pVecNodeBuff.at( i );
      if ( m_pModelNode->mNumChildren > 0 )
      {
        for ( unsigned int j = 0; j < m_pModelNode->mNumChildren; j++ )
        {
          m_pVecNodeBuff.push_back( m_pModelNode->mChildren[j] );
        }
      }
      else
      {
        repeat = false;
      }
    }
  }

  for ( uint32 i = 0; i < m_pVecNodeBuff.size(); i++ )
  {
    m_pModelNode = m_pVecNodeBuff.at( i );


    if ( m_pModelNode->mNumMeshes > 0 )
    {
      for ( uint32 j = 0; j < m_pModelNode->mNumMeshes; j++ )
      {
        assimpGetMeshData( m_pModelScene->mMeshes[j] );
      }
    }
  }
  return true;
}

bool Mesh::assimpGetMeshData( const aiMesh * mesh )
{
  aiFace *face;
  m_iNumVertices = mesh->mNumVertices;
  VERTICES temp;

  for ( uint32 i = 0; i < mesh->mNumVertices; i++ )
  {

    temp.position = DirectX::XMFLOAT3(
      mesh->mVertices[i].x,
      mesh->mVertices[i].y,
      mesh->mVertices[i].z );


    if ( mesh->HasNormals() )
    {
      temp.normals = DirectX::XMFLOAT3(
        mesh->mNormals[i].x,
        mesh->mNormals[i].y,
        mesh->mNormals[i].z );
    }
    else
    {
      temp.normals = DirectX::XMFLOAT3( 0, 0, 0 );
    }

    if ( mesh->HasTextureCoords( 0 ) )
    {
      temp.uv = { mesh->mTextureCoords[0][i].x,
                     mesh->mTextureCoords[0][i].y };
    }
    else
    {
      temp.uv = { 0,0 };
    }

    m_vecVert.push_back( temp );
  }


  // Get index and fills buffer
  m_iNumIndices = 0;
  for ( uint32 f = 0; f < mesh->mNumFaces; f++ )
  {
    face = &mesh->mFaces[f];
    
    for ( uint32 g = 0; g < face->mNumIndices; g++ )
    {
      indexBuff.push_back( static_cast<uint16>(face->mIndices[g]));
    }

  }
  m_IndexIterator = indexBuff.size();

  return true;
}

}
