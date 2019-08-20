
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

    bufferDesc.ByteWidth = sizeof(cbLight);
    constantLightBuffer =
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

   //testModel->loadMesh("Meshes\\BattleDroid.fbx");
   testModel->loadMesh("Meshes\\model.dae");
   

    Material * tempMaterial = new Material();

    Texture * tempTex = new Texture;

/*
     //Droide Material
    //-------------------------------------------------------------------------------------//
    tempTex = 
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Droid\\17_-_Default_albedo.jpg");
    tempMaterial->setAlbedoTexture(*tempTex);
    
    tempTex = 
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Droid\\17_-_Default_metallic.jpg");
    tempMaterial->setMetallicTexture(*tempTex);

    tempTex =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Droid\\17_-_Default_normal.jpg");
    tempMaterial->setNormalTexture(*tempTex);

    tempTex =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Droid\\17_-_Default_roughness.jpg");
    tempMaterial->setRoughnessTexture(*tempTex);

    tempTex =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Droid\\17_-_Default_emissive.jpg");
    tempMaterial->setEmissiveTexture(*tempTex);*/

     //Robot Material
    //-------------------------------------------------------------------------------------//
    tempTex = 
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Robot\\default_albedo.jpg");
    tempMaterial->setAlbedoTexture(*tempTex);
    
    tempTex = 
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Robot\\default_metallic.jpg");
    tempMaterial->setMetallicTexture(*tempTex);

    tempTex =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Robot\\default_normal.jpg");
    tempMaterial->setNormalTexture(*tempTex);

    tempTex =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Robot\\default_roughness.jpg");
    tempMaterial->setRoughnessTexture(*tempTex);

    tempTex =
      GraphicsManager::instance().LoadTextureFromFile("Textures\\Robot\\default_emissive.jpg");
    tempMaterial->setEmissiveTexture(*tempTex);


    testModel->changeMaterial(*tempMaterial);

    a->addComponent(testModel);

    SceneManager::instance().addGameObjectToScene(*a);

    //Sets primitive topology
    GraphicsManager::instance().setPrimitiveTopology(4);

    //Initialize the matrices
    g_World.identity();

    //Initialize the camera
    m_camera = new Camera(m_windowWidth, m_windowHeight);

    m_camera->setPosition(Vector3f(0.0, 0.0, -5.0));
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
   //Update our time
    time = 0.0f;
    static DWORD dwTimeStart = 0;
    DWORD dwTimerCur = GetTickCount();
    if (dwTimeStart == 0)
    {
      dwTimeStart = dwTimerCur;
    }
    time = (dwTimerCur - dwTimeStart) / 1000.0f;

    //rotate mesh 
    //g_World.matrixRotationX(time);

    //Clear back buffer
    float ClearColor[4] = { .5f, 0.5f, 0.5f, 1.0f }; //Gris
    //GraphicsManager::instance().clearRenderTargetView(ClearColor,
     //                                                 m_pBackBufferTex);

    Vector3f a = m_camera->getEyePosition();
    cbLight.viewPosition = Vector4f(a.x, a.y, a.z, 1.0f);
    cbLight.lightPosition = Vector4f(-100.0, -100.0, -100.0, 0.0);
    cbLight.lightPosition.w = cos(time);
    GraphicsManager::instance().updateSubresource(constantLightBuffer,
                                                  &cbLight);

    //Clear depth Stencil
    GraphicsManager::instance().clearDepthStencilView(
      CLEAR_DSV_FLAGS::E::CLEAR_DEPTH,
      1.0f,
      0);

    g_World.transpose();
    cbMatrixbuffer.world = g_World;
    GraphicsManager::instance().updateSubresource(constantMatrix,
                                                  &cbMatrixbuffer);


    /************************************************************************/
    /* Light                                                                */
    /************************************************************************/

    //Sets the Viewport
    GraphicsManager::instance().setViewports(1, vp);
    //GraphicsManager::instance().setRenderTarget(m_pBackBufferTex);
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

