/**************************************************************************/
/* @filename gzGraphicsTestApp.cpp
/* @author Victor Flores 
/* @date 2019/08/25
/**************************************************************************/

#include "gzGraphicsTestApp.h"
#include <gzSceneManager.h>
#include <gzMeshComponent.h>
#include <gzMaterial.h>
#include <gzTexture.h>
#include <gzGameObject.h>
#include <gzCameraManager.h>
#include <gzTime.h>
#include <gzCamera.h>

namespace gzEngineSDK {

  GrapichsTestApp::GrapichsTestApp(uint32 windowWidth, 
                                   uint32 windowHeight, 
                                   String windowName, 
                                   uint32 posX, 
                                   uint32 posY) 
  {
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
    m_windowName = windowName;
    m_windowPosX = posX;
    m_windowPosY = posY;
  }

  bool 
  GrapichsTestApp::postInit()
  {
    bool result = true;

    //Creates the Device, Context and SwapChain
    result = g_GraphicsManager().initGraphicsManager(
      static_cast<void*>(m_pwindow->getHWND()),
      m_windowWidth,
      m_windowHeight);

    //Create the constant buffers desc
    BUFFER_DESCRIPTOR bufferDesc;
    memset(&bufferDesc, 0, sizeof(bufferDesc));
    bufferDesc.Usage = USAGES::E::USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof(cbMatrix);
    bufferDesc.BindFlags = BIND_FLAGS::E::BIND_CONSTANT_BUFFER;
    bufferDesc.CPUAccessFlags = 0;

    //Create Constant buffer
    constantMatrix =
      g_GraphicsManager().createBuffer(bufferDesc, nullptr);

    bufferDesc.ByteWidth = sizeof(cbLight);
    constantLightBuffer =
      g_GraphicsManager().createBuffer(bufferDesc, nullptr);

    SceneManager::instance().createScene();
    SceneManager::instance().setActiveScene();

    m_gameObject = SceneManager::instance().createEmptyGameObject();

    MeshComponent * testModel = new MeshComponent();

    //testModel->loadMesh("Meshes\\BattleDroid.fbx");
    testModel->loadMesh("Meshes\\model.dae");


    Material * tempMaterial = new Material();

    Texture * tempTex = new Texture;

    /*
         //Droide Material
        //-------------------------------------------------------------------------------------//
        tempTex =
          g_GraphicsManager().LoadTextureFromFile("Textures\\Droid\\17_-_Default_albedo.jpg");
        tempMaterial->setAlbedoTexture(*tempTex);

        tempTex =
          g_GraphicsManager().LoadTextureFromFile("Textures\\Droid\\17_-_Default_metallic.jpg");
        tempMaterial->setMetallicTexture(*tempTex);

        tempTex =
          g_GraphicsManager().LoadTextureFromFile("Textures\\Droid\\17_-_Default_normal.jpg");
        tempMaterial->setNormalTexture(*tempTex);

        tempTex =
          g_GraphicsManager().LoadTextureFromFile("Textures\\Droid\\17_-_Default_roughness.jpg");
        tempMaterial->setRoughnessTexture(*tempTex);

        tempTex =
          g_GraphicsManager().LoadTextureFromFile("Textures\\Droid\\17_-_Default_emissive.jpg");
        tempMaterial->setEmissiveTexture(*tempTex);*/

        //Robot Material
       //-------------------------------------------------------------------------------------//
    tempTex =
      g_GraphicsManager().LoadTextureFromFile("Textures\\Robot\\default_albedo.jpg");
    tempMaterial->setAlbedoTexture(*tempTex);

    tempTex =
      g_GraphicsManager().LoadTextureFromFile("Textures\\Robot\\default_metallic.jpg");
    tempMaterial->setMetallicTexture(*tempTex);

    tempTex =
      g_GraphicsManager().LoadTextureFromFile("Textures\\Robot\\default_normal.jpg");
    tempMaterial->setNormalTexture(*tempTex);

    tempTex =
      g_GraphicsManager().LoadTextureFromFile("Textures\\Robot\\default_roughness.jpg");
    tempMaterial->setRoughnessTexture(*tempTex);

    tempTex =
      g_GraphicsManager().LoadTextureFromFile("Textures\\Robot\\default_emissive.jpg");
    tempMaterial->setEmissiveTexture(*tempTex);


    testModel->changeMaterial(*tempMaterial);

    m_gameObject->addComponent(testModel);

    SceneManager::instance().addGameObjectToScene(*m_gameObject);

    //Sets primitive topology
    g_GraphicsManager().setPrimitiveTopology(4);

    //Initialize the matrices
    g_World.identity();

    //Initialize the camera
    m_camera = CameraManager::instance().createCamera();

    CameraManager::instance().setActiveCameraPosition(Vector3f(0.0f, 0.0f, -4.0f));
    cbMatrixbuffer.view = CameraManager::instance().getActiveCameraViewMatrix();
    cbMatrixbuffer.view.transpose();
    cbMatrixbuffer.projection = 
      CameraManager::instance().getActiveCameraProjectionMatrix();
    cbMatrixbuffer.projection.transpose();

    return result;

  }

  void 
  GrapichsTestApp::update()
  {
    time = g_Time().getTime();
    Vector3f viewPos = CameraManager::instance().getActiveCameraEyePosition();
    cbLightBuffer.viewPosition = Vector4f(viewPos.x, viewPos.y, viewPos.z, 1.0f);
    cbLightBuffer.lightPosition = Vector4f(-100.0, -100.0, -100.0, 0.0);
    cbLightBuffer.lightPosition.w = cos(time);
    g_GraphicsManager().updateSubresource(constantLightBuffer,
                                          &cbLightBuffer);
    g_World.matrixRotationY(time);
    g_World.transpose();
    cbMatrixbuffer.world = g_World;
    CameraManager::instance().update();
    cbMatrixbuffer.view = CameraManager::instance().getActiveCameraViewMatrix();
    cbMatrixbuffer.view.transpose();
    g_GraphicsManager().updateSubresource(constantMatrix,
                                          &cbMatrixbuffer);
    g_GraphicsManager().setVSConstantBuffers(constantMatrix, 0, 1);
    
  }

}

