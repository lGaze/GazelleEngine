/**************************************************************************/
/* @filename gzModel.cpp
/* @author Victor Flores 
/* @date 2019/07/05
/* @brief 
/**************************************************************************/

#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

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

    const aiScene * pScene = importer.ReadFile(
      filename,
      aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_ConvertToLeftHanded);

    if (pScene == nullptr)
    {
      return false;
    }

    m_mesh.resize(pScene->mNumMeshes);
    m_modelName = filename;
      
    for (uint32 i = 0; i < pScene->mNumMeshes; ++i)
    {
      m_mesh[i].numVertex = pScene->mMeshes[i]->mNumVertices;
      m_mesh[i].meshName = pScene->mMeshes[i]->mName.C_Str();
      if (pScene->mMeshes[i]->HasFaces())
      {
        for (uint32 j = 0; j < pScene->mMeshes[i]->mNumFaces; ++j)
        {
          m_mesh[i].numIndex += pScene->mMeshes[i]->mFaces[j].mNumIndices;
        }
      }

      m_mesh[i].meshMaterial = new Material();
      if (pScene->mMeshes[i]->mMaterialIndex > 0)
      {
        aiMaterial * material =
          pScene->mMaterials[pScene->mMeshes[i]->mMaterialIndex];
        m_mesh[i].meshMaterial = createMaterial(material);
      }

    }


    for (uint32 i = 0; i < pScene->mNumMeshes; ++i)
    {
      auto& it = pScene->mMeshes[i];
      auto& currentMesh = m_mesh[i];
      m_vertices.resize(currentMesh.numVertex);
      m_indices.resize(currentMesh.numIndex);

      //Vertices
      for (uint32 j = 0; j < it->mNumVertices; ++j)
      {
        m_vertices[j].position.x = it->mVertices[j].x;
        m_vertices[j].position.y = it->mVertices[j].y;
        m_vertices[j].position.z = it->mVertices[j].z;

        if (it->mTextureCoords[0])
        {
          m_vertices[j].texcoord.x =
            static_cast<float>(it->mTextureCoords[0][j].x);
          m_vertices[j].texcoord.y =
            static_cast<float>(it->mTextureCoords[0][j].y);
        }
        if (it->HasNormals())
        {
          m_vertices[j].normal.x = it->mNormals[j].x;
          m_vertices[j].normal.y = it->mNormals[j].y;
          m_vertices[j].normal.z = it->mNormals[j].z;
        }
        if (it->HasTangentsAndBitangents())
        {
          m_vertices[j].binormal.x = it->mBitangents[j].x;
          m_vertices[j].binormal.y = it->mBitangents[j].y;
          m_vertices[j].binormal.z = it->mBitangents[j].z;

          m_vertices[j].tangent.x = it->mTangents[j].x;
          m_vertices[j].tangent.y = it->mTangents[j].y;
          m_vertices[j].tangent.z = it->mTangents[j].z;
        }
      }

      BUFFER_DESCRIPTOR tempDesc;
      memset(&tempDesc, 0, sizeof(tempDesc));
      tempDesc.BindFlags = BIND_FLAGS::E::BIND_VERTEX_BUFFER;
      tempDesc.Usage = USAGES::E::USAGE_DEFAULT;
      tempDesc.ByteWidth = currentMesh.numVertex * sizeof(VERTEX);
      
      SUBRESOUCE_DATA initData;
      memset(&initData, 0, sizeof(initData));
      initData.pSysMem = &m_vertices[0];
      initData.SysMemPitch = m_vertices.size();

      currentMesh.vertexBuffer = 
        g_GraphicsManager().createBuffer(tempDesc, &initData);

      int32 iterator = 0;
      //Indices
      for (uint32 j = 0; j < it->mNumFaces; ++j)
      {
        aiFace face = it->mFaces[j];
        for (uint32 k = 0; k < face.mNumIndices; ++k)
        {
          m_indices[iterator] = face.mIndices[k];
          iterator++;
        }
      }

      tempDesc.BindFlags = BIND_FLAGS::E::BIND_INDEX_BUFFER;
      tempDesc.Usage = USAGES::E::USAGE_DEFAULT;
      tempDesc.ByteWidth = currentMesh.numIndex * sizeof(uint32);

      memset(&initData, 0, sizeof(initData));
      initData.pSysMem = &m_indices[0];
      initData.SysMemPitch = m_indices.size();

      currentMesh.indexBuffer = 
        g_GraphicsManager().createBuffer(tempDesc, &initData);
    }
    return true;
  }

/*
  void 
  Model::Draw()
  {
    uint32 stride = sizeof(VERTEX);
    uint32 offset = 0;

    g_GraphicsManager().setVertexBuffers(0,
                                         1,
                                         m_vertexBuffer,
                                         &stride,
                                         &offset);

    g_GraphicsManager().setIndexBuffer(FORMATS::E::FORMAT_R32_UINT,
                                       m_indexBuffer,
                                       offset);

    for (uint32 i = 0; i < m_mesh.size(); i++)
    {
      if (nullptr != m_mesh[i].meshMaterial)
      {
        g_GraphicsManager().setShaderResources(&m_mesh[i].meshMaterial->getAlbedoTexture(),
                                                       0,
                                                       1);
        g_GraphicsManager().setShaderResources(&m_mesh[i].meshMaterial->getNormalTexture(),
                                                       1,
                                                       1);
        g_GraphicsManager().setShaderResources(&m_mesh[i].meshMaterial->getMetallicTexture(),
                                                       2,
                                                       1);
        g_GraphicsManager().setShaderResources(&m_mesh[i].meshMaterial->getRoughnessTexture(),
                                                       3,
                                                       1);
        g_GraphicsManager().setShaderResources(&m_mesh[i].meshMaterial->getEmissiveTexture(),
                                                       4,
                                                       1);
      }
      g_GraphicsManager().drawIndexed(m_mesh[i].numIndex, 
                                              m_mesh[i].indexBase, 
                                              0);
    }
  }*/

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
      tempTexture = g_GraphicsManager().LoadTextureFromFile(filename);
      tempMaterial->setAlbedoTexture(*tempTexture);
    }

    if (specular > 0)
    {
      material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
      String filename = str.C_Str();
      //TODO: just do that for spider, don´t use it for other shit
      //filename.erase(0, 2);
      filename = m_directoryPath + filename;
      tempTexture = g_GraphicsManager().LoadTextureFromFile(filename);
      tempMaterial->setSpecularTexture(*tempTexture);
    }

    if (normals > 0)
    {
      material->GetTexture(aiTextureType_NORMALS, 0, &str);
      String filename = str.C_Str();
      //TODO: just do that for spider, don´t use it for other shit
      //filename.erase(0, 2);
      filename = m_directoryPath + filename;
      tempTexture = g_GraphicsManager().LoadTextureFromFile(filename);
      tempMaterial->setSpecularTexture(*tempTexture);
    }

    if ( emissive > 0)
    {
      material->GetTexture(aiTextureType_EMISSIVE, 0, &str);
      String filename = str.C_Str();
      //TODO: just do that for spider, don´t use it for other shit
      //filename.erase(0, 2);
      filename = m_directoryPath + filename;
      tempTexture = g_GraphicsManager().LoadTextureFromFile(filename);
      tempMaterial->setSpecularTexture(*tempTexture);
    }

    return tempMaterial;
  }

  void 
  Model::changeMaterial(Material & newMat)
  {
    for (auto &it : m_mesh)
    {
      it.meshMaterial = &newMat;
    }
  }

}
