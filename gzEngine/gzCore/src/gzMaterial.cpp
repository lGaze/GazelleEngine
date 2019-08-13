/**************************************************************************/
/* @filename gzMaterial.cpp
/* @author Victor Flores 
/* @date 2019/08/13
/* @brief 
/*************************************************************************/

#include "gzMaterial.h"
#include "gzPrerequisitesCore.h"
#include "gzTexture.h"
#include "gzGraphicsManager.h"

namespace gzEngineSDK {

  Material::Material()
  {
    m_albedoTexture = new Texture();
    m_metallicTexture = new Texture();
    m_roughnessTexture = new Texture();
    m_normalTexture = new Texture();
    m_emissiveTexture = new Texture();
    m_specularTexture = new Texture();
    createAsDefault();
  }

  Material::~Material()
  {
    delete m_albedoTexture;
    delete m_metallicTexture;
    delete m_roughnessTexture;
    delete m_normalTexture;
    delete m_emissiveTexture;
    delete m_specularTexture;
  }

  void 
  Material::createAsDefault()
  {
    m_albedoTexture = 
      GraphicsManager::instance().LoadTextureFromFile("Textures\\default_albedo.png");
    m_metallicTexture =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\default_EMR.png");
    m_roughnessTexture = 
      GraphicsManager::instance().LoadTextureFromFile("Textures\\default_EMR.png");
    m_normalTexture = 
      GraphicsManager::instance().LoadTextureFromFile("Textures\\default_normal.png");
    m_emissiveTexture =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\default_EMR.png");
    m_specularTexture =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\default_albedo.png");
    
  }

}
