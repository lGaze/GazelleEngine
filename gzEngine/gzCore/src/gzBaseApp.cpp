
/**************************************************************************/
/* @filename gzBaseApp.cpp
/* @author Victor Flores 
/* @date 2019/03/02
/* @brief 
/**************************************************************************/

#include "gzBaseApp.h"
#include "gzModel.h"
#include "gzTexture.h"
#include "gzGameObject.h"
#include "gzMeshComponent.h"
#include "gzCamera.h"
#include "gzSceneManager.h"
#include "gzResourceManager.h"
#include "gzRenderer.h"
#include "gzMaterial.h"

namespace gzEngineSDK {

  BaseApp::BaseApp(uint32 windowWidth,
                   uint32 windowHeight,
                   String windowName,
                   uint32 posX,
                   uint32 posY) :
    m_windowWidth(windowWidth),
    m_windowHeight(windowHeight),
    m_windowName(windowName),
    m_windowPosX(posX),
    m_windowPosY(posY) { }

  int32
    BaseApp::runMainLoop()
  {
    m_mainLoop = true;

    if (!initApp())
    {
      std::cout << "Init App Failed" << std::endl;
    }

    while (m_mainLoop)
    {

      m_pwindow->messageHandler();

      //Update
      update();

      //Render
      render();
    }

    return 0;
  }

  bool
  BaseApp::initApp()
  {
    m_pwindow = new Window();
    if (!m_pwindow->initWindow(m_windowWidth,
                               m_windowHeight,
                               m_windowName,
                               m_windowPosX,
                               m_windowPosY))
    {
      std::cout << "Init Window failed" << std::endl;
      return false;
    }

    if (!loadGraphicsLibrary("gzGraphicsDX11d.dll", "CreateManagerObject"))
    {
      std::cout << "Failed to load the library " << std::endl;
      return false;
    }

    SceneManager::startUp();
    ResourceManager::startUp();

    if (!postInit())
    {
      std::cout << "Failed to Initialize" << std::endl;
      return false;
    }

    if (!loadRendererLibrary("gzPBRRendererd.dll", "CreateManagerObject"))
    {
      std::cout << "Failed to load the library " << std::endl;
      return false;
    }

    return true;
  }

  bool
    BaseApp::postInit()
  {
    bool result = true;

    //Creates the Device, Context and SwapChain
    result = GraphicsManager::instance().initGraphicsManager(
      static_cast<void*>(m_pwindow->getHWND()),
      m_windowWidth,
      m_windowHeight);

    m_pBackBufferTex = GraphicsManager::instance().getBackBufferTex();

    vp = GraphicsManager::instance().getViewport();

    //Create the constant buffers desc
    BUFFER_DESCRIPTOR bufferDesc;
    memset(&bufferDesc, 0, sizeof(bufferDesc));
    bufferDesc.Usage = USAGES::E::USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof(cbMatrix);
    bufferDesc.BindFlags = BIND_FLAGS::E::BIND_CONSTANT_BUFFER;
    bufferDesc.CPUAccessFlags = 0;

    //Create Constant buffer
    constantMatrix =
      GraphicsManager::instance().createBuffer(bufferDesc, nullptr);

    SceneManager::instance().createScene();
    SceneManager::instance().setActiveScene();
   
    a = SceneManager::instance().createEmptyGameObject();

    MeshComponent * testModel = new MeshComponent();
    MeshComponent * testModel1 = new MeshComponent();
    MeshComponent * testModel2 = new MeshComponent();
    MeshComponent * testModel3 = new MeshComponent();
    MeshComponent * testModel4 = new MeshComponent();
    MeshComponent * testModel5 = new MeshComponent();

    testModel->loadMesh("Meshes\\Vela\\Vela_Mat_1.x");
    //testModel1->loadMesh("Meshes\\Vela\\Vela_Mat_2.x");
    //testModel2->loadMesh("Meshes\\Vela\\Vela_Mat_3.x");
    //testModel3->loadMesh("Meshes\\Vela\\Vela_Mat_4.x");
    //testModel4->loadMesh("Meshes\\Vela\\Vela_Mat_5.x");
    //testModel5->loadMesh("Meshes\\Vela\\Vela_Mat_6.x");

    Material * tempMaterial = new Material();
    Material * tempMaterial1 = new Material();
    Material * tempMaterial2= new Material();
    Material * tempMaterial3 = new Material();
    Material * tempMaterial4 = new Material();
    Material * tempMaterial5 = new Material();

    Texture * tempTex = new Texture;

     //Guns Material
    //-------------------------------------------------------------------------------------//
    tempTex = 
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Gun_BaseColor.tga");
    tempMaterial->setAlbedoTexture(*tempTex);
    
    tempTex = 
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Gun_Metallic.tga");
    tempMaterial->setMetallicTexture(*tempTex);

    tempTex =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Gun_Normal.tga");
    tempMaterial->setNormalTexture(*tempTex);

    tempTex =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Gun_Roughness.tga");
    tempMaterial->setRoughnessTexture(*tempTex);

    testModel->changeMaterial(*tempMaterial);

/*
     //Legs Material
    //-------------------------------------------------------------------------------------//
    tempTex = 
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Legs_BaseColor.tga");
    tempMaterial1->setAlbedoTexture(*tempTex);
    
    tempTex = 
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Legs_Metallic.tga");
    tempMaterial1->setMetallicTexture(*tempTex);

    tempTex =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Legs_Normal.tga");
    tempMaterial1->setNormalTexture(*tempTex);

    tempTex =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Legs_Roughness.tga");
    tempMaterial1->setRoughnessTexture(*tempTex);

    testModel1->changeMaterial(*tempMaterial1);*/

   /*  //Mechanic Material
    //-------------------------------------------------------------------------------------//
    tempTex = 
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Mechanical_BaseColor.tga");
    tempMaterial2->setAlbedoTexture(*tempTex);
    
    tempTex = 
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Mechanical_Metallic.tga");
    tempMaterial2->setMetallicTexture(*tempTex);

    tempTex =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Mechanical_Normal.tga");
    tempMaterial2->setNormalTexture(*tempTex);

    tempTex =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Mechanical_Roughness.tga");
    tempMaterial2->setRoughnessTexture(*tempTex);

    tempTex =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Mechanical_Emissive.tga");
    tempMaterial2->setEmissiveTexture(*tempTex);

    testModel2->changeMaterial(*tempMaterial2);

     //Char Material
    //-------------------------------------------------------------------------------------//
    tempTex = 
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Char_BaseColor.tga");
    tempMaterial3->setAlbedoTexture(*tempTex);
    
    tempTex = 
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Char_Metallic.tga");
    tempMaterial3->setMetallicTexture(*tempTex);

    tempTex =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Char_Normal.tga");
    tempMaterial3->setNormalTexture(*tempTex);

    tempTex =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Char_Roughness.tga");
    tempMaterial3->setRoughnessTexture(*tempTex);

    tempTex =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Char_Emissive.tga");
    tempMaterial3->setEmissiveTexture(*tempTex);

    testModel3->changeMaterial(*tempMaterial3);

     //Plate Material
    //-------------------------------------------------------------------------------------//
    tempTex = 
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Plate_BaseColor.tga");
    tempMaterial4->setAlbedoTexture(*tempTex);
    
    tempTex = 
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Plate_Metallic.tga");
    tempMaterial4->setMetallicTexture(*tempTex);

    tempTex =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Plate_Normal.tga");
    tempMaterial4->setNormalTexture(*tempTex);

    tempTex =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Plate_Roughness.tga");
    tempMaterial4->setRoughnessTexture(*tempTex);

    tempTex =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_Plate_Emissive.tga");
    tempMaterial4->setEmissiveTexture(*tempTex);

    testModel4->changeMaterial(*tempMaterial4);

     //Eyes Material
    //-------------------------------------------------------------------------------------//
    tempTex = 
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_EyeCornea_BaseColor.tga");
    tempMaterial5->setAlbedoTexture(*tempTex);

    tempTex =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_EyeCornea_Normal.tga");
    tempMaterial5->setNormalTexture(*tempTex);

    tempTex =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Vela\\Vela_EyeCornea_Roughness.tga");
    tempMaterial5->setRoughnessTexture(*tempTex);

    testModel5->changeMaterial(*tempMaterial5);*/



    a->addComponent(testModel);
    //a->addComponent(testModel1);
    //a->addComponent(testModel2);
    //a->addComponent(testModel3);
    //a->addComponent(testModel4);
    //a->addComponent(testModel5);

    SceneManager::instance().addGameObjectToScene(*a);

    //Sets primitive topology
    GraphicsManager::instance().setPrimitiveTopology(4);

    //Initialize the matrices
    g_World.identity();

    //Initialize the camera
    m_camera = new Camera(m_windowWidth, m_windowHeight);

    m_camera->setPosition(Vector3f(0.0, 0.0, -50.0));
    m_camera->UpdateCamera();
    cbMatrixbuffer.view = m_camera->getViewMatrix();
    cbMatrixbuffer.projection = m_camera->getProjectionMatrix();
    GraphicsManager::instance().updateSubresource(constantMatrix,
                                                  &cbMatrixbuffer);

    return result;

  }

  void
  BaseApp::render()
  {

    /*  MESH_DATA * dwarf = Model->getMeshData();*/
   //Update our time
    float t = 0.0f;
    static DWORD dwTimeStart = 0;
    DWORD dwTimerCur = GetTickCount();
    if (dwTimeStart == 0)
    {
      dwTimeStart = dwTimerCur;
    }
    t = (dwTimerCur - dwTimeStart) / 1000.0f;

    //rotate mesh 
   //g_World.matrixRotationY(t);

    //Clear back buffer
    float ClearColor[4] = { .5f, 0.5f, 0.5f, 1.0f }; //Gris
    GraphicsManager::instance().clearRenderTargetView(ClearColor,
                                                      m_pBackBufferTex);


    //Clear depth Stencil
    GraphicsManager::instance().clearDepthStencilView(
      CLEAR_DSV_FLAGS::E::CLEAR_DEPTH,
      1.0f,
      0);

    g_World.transpose();
    cbMatrixbuffer.world = g_World;
    cbMatrixbuffer.ViewPosition = Vector4f(Eye.x, Eye.y, Eye.z, 1.0f);

    GraphicsManager::instance().updateSubresource(constantMatrix,
                                                  &cbMatrixbuffer);


    /************************************************************************/
    /* Light                                                                */
    /************************************************************************/

    //Sets the Viewport
    GraphicsManager::instance().setViewports(1, vp);
    GraphicsManager::instance().setRenderTarget(m_pBackBufferTex);
    Renderer::instance().render();

  }

  void 
  BaseApp::update()
  {
  
/*
    m_camera->Move(Vector3f(0.0, 0.0, -1.0), 0.5);
    m_camera->UpdateCamera();
    cbMatrixbuffer.view = m_camera->getViewMatrix();
    GraphicsManager::instance().updateSubresource(constantMatrix,
                                                  &cbMatrixbuffer);*/
    GraphicsManager::instance().setVSConstantBuffers(constantMatrix, 0, 1);
  }

  bool 
  BaseApp::loadGraphicsLibrary( String libraryName, String funcName )
  {
    HINSTANCE hCGDll = LoadLibraryEx( libraryName.c_str(),
                                      nullptr,
                                      LOAD_WITH_ALTERED_SEARCH_PATH );

    if (!hCGDll)
    {
      std::cout << "Could not load the dynamic" << "" << std::endl;
      return false;
    }

    m_graphicsFunc = (createGraphicsManager)GetProcAddress(hCGDll,
                                                           funcName.c_str());

    if (!m_graphicsFunc)
    {
      std::cout << "Could not locate the function" << std::endl;
      return false;
    }

    hCGDll = LoadLibraryEx( libraryName.c_str(),
                            nullptr,
                            0 );

    m_graphicsFunc = (createGraphicsManager)GetProcAddress(hCGDll,
                                                           funcName.c_str());
    m_graphicsFunc();
    return true;
  }

  bool 
  BaseApp::loadRendererLibrary(String libraryName, String funcName)
  {
    HINSTANCE hCGDll = LoadLibraryEx(libraryName.c_str(),
                                     nullptr,
                                     LOAD_WITH_ALTERED_SEARCH_PATH);

    if (!hCGDll)
    {
      std::cout << "Could not load the dynamic" << "" << std::endl;
      return false;
    }

    m_rendererFunc = (createRenderer)GetProcAddress(hCGDll,
                                                           funcName.c_str());

    if (!m_graphicsFunc)
    {
      std::cout << "Could not locate the function" << std::endl;
      return false;
    }

    hCGDll = LoadLibraryEx(libraryName.c_str(),
                           nullptr,
                           0);

    m_rendererFunc = (createRenderer)GetProcAddress(hCGDll,
                                                    funcName.c_str());
    m_rendererFunc();
    return true;
  }

  BaseApp&
  g_baseApp()
  {
    return BaseApp::instance();
  }
}

