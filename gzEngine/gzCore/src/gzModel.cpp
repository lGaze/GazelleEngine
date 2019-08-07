/**************************************************************************/
/* @filename gzModel.cpp
/* @author Victor Flores 
/* @date 2019/07/05
/* @brief 
/**************************************************************************/

#include "gzModel.h"
#include "gzGraphicsManager.h"
#include "gzMaterial.h"

namespace gzEngineSDK {
  
  Model::Model()
  {
    m_directoryPath = "Textures\\";
  }

  bool
  Model::Load(String filename)
  {
    Assimp::Importer importer;

    uint32 numOfVertices = 0;
    uint32 numOfIndices = 0;

    const aiScene * pScene = importer.ReadFile(
      filename,
      aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_ConvertToLeftHanded);

    if (pScene == nullptr)
    {
      return false;
    }

    m_mesh.resize(pScene->mNumMeshes);

    for (uint32 i = 0; i < pScene->mNumMeshes; ++i)
    {
      m_mesh[i].vertexBase = numOfVertices;
      numOfVertices += pScene->mMeshes[i]->mNumVertices;
      m_mesh[i].numVertex = pScene->mMeshes[i]->mNumVertices;

      m_mesh[i].indexBase = numOfIndices;

      if (pScene->mMeshes[i]->HasFaces())
      {
        for (uint32 j = 0; j < pScene->mMeshes[i]->mNumFaces; ++j)
        {
          numOfIndices += pScene->mMeshes[i]->mFaces[j].mNumIndices;
          m_mesh[i].numIndex += pScene->mMeshes[i]->mFaces[j].mNumIndices;
        }
      }

      if (pScene->mMeshes[i]->mMaterialIndex >= 0)
      {
        aiMaterial * material =
          pScene->mMaterials[pScene->mMeshes[i]->mMaterialIndex];
        m_mesh[i].material = createMaterial(material);
      }

    }

    m_vertices.resize(numOfVertices);
    m_indices.resize(numOfIndices);

    for (uint32 i = 0; i < pScene->mNumMeshes; ++i)
    {
      auto& it = pScene->mMeshes[i];
      auto& currentMesh = m_mesh[i];

      for (uint32 j = 0; j < it->mNumVertices; ++j)
      {
        uint32 index = currentMesh.vertexBase + j;
        m_vertices[index].position.x = it->mVertices[j].x;
        m_vertices[index].position.y = it->mVertices[j].y;
        m_vertices[index].position.z = it->mVertices[j].z;

        if (it->mTextureCoords[0])
        {
          m_vertices[index].texcoord.x =
            static_cast<float>(it->mTextureCoords[0][j].x);
          m_vertices[index].texcoord.y =
            static_cast<float>(it->mTextureCoords[0][j].y);
        }

        if (it->HasNormals())
        {
          m_vertices[index].normal.x = it->mNormals[j].x;
          m_vertices[index].normal.y = it->mNormals[j].y;
          m_vertices[index].normal.z = it->mNormals[j].z;
        }
      }
      for (uint32 j = 0; j < it->mNumFaces; ++j)
      {
        for (uint32 k = 0; k < it->mFaces[j].mNumIndices; ++k)
        {
          m_indices[m_mesh[i].indexBase + j * it->mFaces[j].mNumIndices + k] =
            it->mFaces[j].mIndices[k] + m_mesh[i].vertexBase;
        }
      }
    }

    BUFFER_DESCRIPTOR tempDesc;
    memset(&tempDesc, 0, sizeof(tempDesc));
    tempDesc.BindFlags = BIND_FLAGS::E::BIND_VERTEX_BUFFER;
    tempDesc.Usage = USAGES::E::USAGE_DEFAULT;
    tempDesc.ByteWidth = numOfVertices * sizeof(VERTEX);
    
    SUBRESOUCE_DATA initData;
    memset(&initData, 0, sizeof(initData));
    initData.pSysMem = &m_vertices[0];
    initData.SysMemPitch = m_vertices.size();

    m_vertexBuffer = 
      GraphicsManager::instance().createBuffer(tempDesc, &initData);
    
    tempDesc.BindFlags = BIND_FLAGS::E::BIND_INDEX_BUFFER;
    tempDesc.Usage = USAGES::E::USAGE_DEFAULT;
    tempDesc.ByteWidth = numOfIndices * sizeof(uint32);

    memset(&initData, 0, sizeof(initData));
    initData.pSysMem = &m_indices[0];
    initData.SysMemPitch = m_indices.size();

    m_indexBuffer = 
      GraphicsManager::instance().createBuffer(tempDesc, &initData);

    return true;
  }

  void 
  Model::Draw()
  {
    uint32 stride = sizeof(VERTEX);
    uint32 offset = 0;

    GraphicsManager::instance().setVertexBuffers(0, 
                                                 1, 
                                                 m_vertexBuffer,
                                                 &stride, 
                                                 &offset);

    GraphicsManager::instance().setIndexBuffer(FORMATS::E::FORMAT_R32_UINT,
                                               m_indexBuffer, 
                                               offset);

    for (uint32 i = 0; i < m_mesh.size(); i++)
    {
      if (nullptr != m_mesh[i].material)
      {
        GraphicsManager::instance().setShaderResources(&m_mesh[i].material->getAlbedoTexture(),
                                                       0,
                                                       1);
      }
      GraphicsManager::instance().drawIndexed(m_mesh[i].numIndex, 
                                              m_mesh[i].indexBase, 
                                              0);
    }
  }

  Material * 
  Model::createMaterial(aiMaterial * material)
  {
    aiString str;
    uint32 diff = 0;
    uint32 specular = 0;
    uint32 normals = 0;
    uint32 emissive = 0;
    Material * tempMaterial = new Material();
    Texture * tempTexture = new Texture();

    diff = material->GetTextureCount(aiTextureType_DIFFUSE);
    specular = material->GetTextureCount(aiTextureType_SPECULAR);
    normals = material->GetTextureCount(aiTextureType_NORMALS);
    emissive = material->GetTextureCount(aiTextureType_EMISSIVE);


    if (diff > 0)
    {
      material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
      String filename = str.C_Str();
      //TODO: just do that for spider, don´t use it for other shit
      //filename.erase(0, 2);
      filename = m_directoryPath + filename;
      tempTexture = GraphicsManager::instance().LoadTextureFromFile(filename);
      tempMaterial->setAlbedoTexture(*tempTexture);
    }

    if (specular > 0)
    {
      material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
      String filename = str.C_Str();
      //TODO: just do that for spider, don´t use it for other shit
      //filename.erase(0, 2);
      filename = m_directoryPath + filename;
      tempTexture = GraphicsManager::instance().LoadTextureFromFile(filename);
      tempMaterial->setSpecularTexture(*tempTexture);
    }

    if (normals > 0)
    {
      material->GetTexture(aiTextureType_NORMALS, 0, &str);
      String filename = str.C_Str();
      //TODO: just do that for spider, don´t use it for other shit
      //filename.erase(0, 2);
      filename = m_directoryPath + filename;
      tempTexture = GraphicsManager::instance().LoadTextureFromFile(filename);
      tempMaterial->setSpecularTexture(*tempTexture);
    }

    if ( emissive > 0)
    {
      material->GetTexture(aiTextureType_EMISSIVE, 0, &str);
      String filename = str.C_Str();
      //TODO: just do that for spider, don´t use it for other shit
      //filename.erase(0, 2);
      filename = m_directoryPath + filename;
      tempTexture = GraphicsManager::instance().LoadTextureFromFile(filename);
      tempMaterial->setSpecularTexture(*tempTexture);
    }

    return tempMaterial;
  }

}
