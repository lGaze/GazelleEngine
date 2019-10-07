/**************************************************************************/
/* @filename gzGraphicsTestApp.cpp
/* @author Victor Flores 
/* @date 2019/08/25
/**************************************************************************/

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_win32.h>
#include <ImGui/imgui_impl_dx11.h>
#include "gzGraphicsTestApp.h"
#include <gzSceneManager.h>
#include <gzCameraManager.h>
#include <gzResourceManager.h>
#include <gzMenuOptions.h>
#include <gzRenderer.h>
#include <gzMeshComponent.h>
#include <gzMaterial.h>
#include <gzTexture.h>
#include <gzGameObject.h>
#include <gzTime.h>
#include <gzCamera.h>
#include "gzWin32Window.h"



namespace gzEngineSDK {

  GrapichsTestApp::GrapichsTestApp(uint32 windowWidth, 
                                   uint32 windowHeight, 
                                   String windowName, 
                                   int32 posX, 
                                   int32 posY) 
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
      m_pwindow->getHandle(),
      m_pwindow->m_windowWidthRect,
      m_pwindow->m_windowHeightRect);

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
    cbLightBuffer.lightPosition = Vector4f(MenuOptions::s_lightPosition[0],
                                           MenuOptions::s_lightPosition[1],
                                           MenuOptions::s_lightPosition[2], 
                                           0.0);
    cbLightBuffer.lightPosition.w = cos(time);

    cbLightBuffer.clearColor = Vector4f(MenuOptions::s_color[0], 
                                        MenuOptions::s_color[1],
                                        MenuOptions::s_color[2],
                                        MenuOptions::s_color[3]);
    g_GraphicsManager().updateSubresource(constantLightBuffer,
                                          &cbLightBuffer);
    if (MenuOptions::s_rotationY)
    {
      g_World.matrixRotationY(time);
      g_World.transpose();
    }
    cbMatrixbuffer.world = g_World;
    CameraManager::instance().update();
    cbMatrixbuffer.view = CameraManager::instance().getActiveCameraViewMatrix();
    cbMatrixbuffer.view.transpose();
    g_GraphicsManager().updateSubresource(constantMatrix,
                                          &cbMatrixbuffer);
    g_GraphicsManager().setVSConstantBuffers(constantMatrix, 0, 1);
    
  }

  bool 
  GrapichsTestApp::initApp()
  {
    SceneManager::startUp();
    ResourceManager::startUp();
    CameraManager::startUp();
    g_Time().startUp();
    g_menuOptions().startUp();

    m_pwindow = new Win32Window();
    if (!m_pwindow->initWindow(m_windowWidth,
                               m_windowHeight,
                               m_windowName,
                               m_windowPosX,
                               m_windowPosY))
    {
      std::cout << "Init Window failed" << std::endl;
      return false;
    }

    if (!loadLibrary("gzGraphicsDX11d.dll", "CreateManagerObject"))
    {
      std::cout << "Failed to load the Graphics library " << std::endl;
      return false;
    }

    if (!postInit())
    {
      std::cout << "Failed to Initialize" << std::endl;
      return false;
    }

    if (!loadLibrary("gzPBRRendererd.dll", "CreateManagerObject"))
    {
      std::cout << "Failed to load the Renderer library " << std::endl;
      return false;
    }

    if (!initImGui())
    {
      std::cout << "Failed to initialize the UI" << std::endl;
      return false;
    }

    return true;
  }

  void 
  GrapichsTestApp::render()
  {
    Renderer::instance().render(MenuOptions::s_testCounter);
    renderImGui();
    g_GraphicsManager().present(0, 0);
  }

  bool 
  GrapichsTestApp::initImGui()
  {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    auto HWND = m_pwindow->getHandle();
    if (!ImGui_ImplWin32_Init(HWND)) {
      return false;
    }

    auto * device = 
      reinterpret_cast<ID3D11Device*>(g_GraphicsManager().getDevice());
    auto * context = 
      reinterpret_cast<ID3D11DeviceContext*>(g_GraphicsManager().getContext());
    if (!ImGui_ImplDX11_Init(device, context)) {
      return false;
    }
    ImGui::StyleColorsDark();

    return true;
  }

  void 
  GrapichsTestApp::renderImGui()
  {
    //start the ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    //Create ImGui Render Options Window
    ImGui::Begin("Renderer Options");
    if (ImGui::CollapsingHeader("Render To Screen")) {
      ImGui::RadioButton("PBR", &MenuOptions::s_testCounter, 0);
      ImGui::RadioButton("Tonemap", &MenuOptions::s_testCounter, 1);
      ImGui::RadioButton("Positions", &MenuOptions::s_testCounter, 2);
      ImGui::RadioButton("Albedo", &MenuOptions::s_testCounter, 3);
      ImGui::RadioButton("Normals", &MenuOptions::s_testCounter, 4);
      ImGui::RadioButton("Emissive", &MenuOptions::s_testCounter, 5);
    }
    ImGui::Checkbox("Activate Rotation Y", &MenuOptions::s_rotationY);
    ImGui::DragFloat3("Light Position",
                      MenuOptions::s_lightPosition,
                      0.01f,
                      -1.0f,
                      1.0f);
    ImGui::ColorEdit4("color", &MenuOptions::s_color[0]);
    ImGui::End();
    //Assemble Together Draw Data
    ImGui::Render();
    //Render Draw Data
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
  }

}

