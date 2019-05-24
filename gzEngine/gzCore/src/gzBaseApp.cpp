/**************************************************************************/
/* @filename gzBaseApp.cpp
/* @author Victor Flores 
/* @date 2019/03/02
/* @brief 
/**************************************************************************/

#include "gzBaseApp.h"
#include "gzMesh.h"


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

    if ( !initApp() )
    {
      std::cout << "Init App Failed" << std::endl;
    }

    while(m_mainLoop)
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
    if (!m_pwindow->initWindow( m_windowWidth, 
                                m_windowHeight, 
                                m_windowName,
                                m_windowPosX,
                                m_windowPosY ))
    {
      std::cout << "Init Window failed" << std::endl;
      return false;
    }

    if (!loadLibrary("gzGraphicsDX11d.dll", "CreateManagerObject"))
    {
      std::cout << "Failed to load the library " << std::endl;
      return false;
    }

    if (!postInit())
    {
      std::cout << "Failed to Initialize" << std::endl;
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
      static_cast< void* >( m_pwindow->getHWND() ), 
      m_windowWidth, 
      m_windowHeight );


    //Creates the Backbuffer texture
    m_pBackBufferTex =
      GraphicsManager::instance().createTextureFromBackBuffer();

    //Creates the render target 
    m_pBackBuffer = 
      GraphicsManager::instance().createRenderTarget(m_pBackBufferTex);


    //Albedo Texture
    TEXTURE2D_DESCRIPTOR renderTexDesc;
    memset( &renderTexDesc, 0, sizeof( renderTexDesc ) );
    renderTexDesc.Height = m_windowHeight;
    renderTexDesc.Width = m_windowWidth;
    renderTexDesc.MipLevels = 4;
    renderTexDesc.ArraySize = 1;
    renderTexDesc.Format = FORMAT_R16G16B16A16_FLOAT;
    renderTexDesc.Usage = USAGE_DEFAULT;
    renderTexDesc.BindFlags = BIND_RENDER_TARGET | BIND_SHADER_RESOURCE;
    renderTexDesc.CPUAccessFlags = 0;
    renderTexDesc.MiscFlags = 0;

    //Albedo Texture
    m_pAlbedoTexture =
      GraphicsManager::instance().createTexture2D( renderTexDesc );

    //AlbedoRT
    m_pAlbedoRT = GraphicsManager::instance().createRenderTarget( m_pAlbedoTexture );


    //Luminance Texture
    m_pLuminanceTexture =
      GraphicsManager::instance().createTexture2D( renderTexDesc );

    //LuminanceRT
    m_pLuminanceRT = 
      GraphicsManager::instance().createRenderTarget( m_pLuminanceTexture );
   

    //Bright Texture
    m_pBrightTexture = 
      GraphicsManager::instance().createTexture2D( renderTexDesc );

    //BrightRT
    m_pBrightRT = 
      GraphicsManager::instance().createRenderTarget( m_pBrightTexture );

    renderTexDesc.Height = m_windowHeight / 2;
    renderTexDesc.Width = m_windowWidth / 2;

    //BlurH1Texture
    m_pBlurH1Texture = 
      GraphicsManager::instance().createTexture2D( renderTexDesc );

    //BlurH1RT
    m_pBlurH1RT = 
      GraphicsManager::instance().createRenderTarget( m_pBlurH1Texture );

    //BlurV1Texture
    m_pBlurV1Texture = 
      GraphicsManager::instance().createTexture2D( renderTexDesc );

    //BlurV1RT
    m_pBlurV1RT = 
      GraphicsManager::instance().createRenderTarget( m_pBlurV1Texture );


    renderTexDesc.Height = m_windowHeight;
    renderTexDesc.Width = m_windowWidth;

    //AddBright1 texture
    m_pAddBright1Texture = 
      GraphicsManager::instance().createTexture2D( renderTexDesc );

    //AddBright1 RT
    m_pAddBright1RT = 
      GraphicsManager::instance().createRenderTarget( m_pAddBright1Texture );

    //ToneMap texture
    m_pToneMapTexture = 
      GraphicsManager::instance().createTexture2D( renderTexDesc );

    //ToneMap RT
    m_pToneMapRT = 
      GraphicsManager::instance().createRenderTarget( m_pToneMapTexture );

    //Creates the Depth descriptor
    TEXTURE2D_DESCRIPTOR depthTextureDesc;
    depthTextureDesc.Width = m_windowWidth;
    depthTextureDesc.Height = m_windowHeight;
    depthTextureDesc.MipLevels = 1;
    depthTextureDesc.ArraySize = 1;
    depthTextureDesc.Format = FORMAT_D24_UNORM_S8_UINT;
    depthTextureDesc.Usage = USAGE_DEFAULT;
    depthTextureDesc.BindFlags = BIND_DEPTH_STENCIL;
    depthTextureDesc.CPUAccessFlags = 0;
    depthTextureDesc.MiscFlags = 0;

    //Creates the Depth Stencil descriptor
    DEPTH_STENCIL_VIEW_DESCRIPTOR desc;
    desc.Format = FORMAT_D24_UNORM_S8_UINT;
    desc.ViewDimension = DSV_DIMENSION_TEXTURE2D;

    //Creates the DepthStencil View
    m_pDepthStencilView =
      GraphicsManager::instance().createDepthStencilView( desc, 
                                                          depthTextureDesc );


    //Creates the Viewport Descriptor
    vp.Width = static_cast< float >( m_windowWidth );
    vp.Height = static_cast< float >( m_windowHeight );
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0; 
    
    //Creates the Viewport2 Descriptor
    vp2.Width = static_cast< float >( m_windowWidth /2 );
    vp2.Height = static_cast< float >( m_windowHeight /2);
    vp2.MinDepth = 0.0f;
    vp2.MaxDepth = 1.0f;
    vp2.TopLeftX = 0;
    vp2.TopLeftY = 0;


    //Compile and create the vertex shader for light
    m_pLightVertexShader = GraphicsManager::instance().CreateVertexShader( 
      L"Shaders\\Phong.fx",
      "VS",
      "vs_4_0" );


    //Create the InputLayout with the blob
    inputLayout = GraphicsManager::instance().createInputLayout(
      m_pLightVertexShader);


    //Compile and Create the pixel shader for light
    m_pLightPixelShader = GraphicsManager::instance().createPixelShader(
      L"Shaders\\Phong.fx",
      "PS",
      "ps_4_0" );

    //------------------------------------------------------------------\\
  

    //Compile and create the vertex shader for luminance
    m_pLuminanceVertexShader = GraphicsManager::instance().CreateVertexShader(
      L"Shaders\\Luminance.fx",
      "VS",
      "vs_4_0" );


    //Create the InputLayout with the blob
    luminanceInputLayout = GraphicsManager::instance().createInputLayout(
      m_pLuminanceVertexShader );

    //Compile and Create the pixel shader for luminance
    m_pLuminancePixelShader = GraphicsManager::instance().createPixelShader(
      L"Shaders\\Luminance.fx",
      "PS",
      "ps_4_0" );

    //------------------------------------------------------------------\\

    //Compile and create the vertex shader for Bright
    m_pBrightVertexShader = GraphicsManager::instance().CreateVertexShader(
      L"Shaders\\Bright.fx",
      "VS",
      "vs_4_0" );


    //Create the InputLayout with the blob
    m_pBrightInputLayout = GraphicsManager::instance().createInputLayout(
      m_pBrightVertexShader );

    //Compile and Create the pixel shader for Bright
    m_pBrightPixelShader = GraphicsManager::instance().createPixelShader(
      L"Shaders\\Bright.fx",
      "PS",
      "ps_4_0" );

    //----------------------------------------------------------------------\\

    //Compile and create the vertex shader for BlurH1
    m_pBlurH1VertexShader = GraphicsManager::instance().CreateVertexShader(
      L"Shaders\\BlurH1.fx",
      "VS",
      "vs_4_0" );

    //Create the InputLayout with the blob
    m_pBlurH1InputLayout = GraphicsManager::instance().createInputLayout(
      m_pBlurH1VertexShader );

    //Compile and Create the pixel shader for luminance
    m_pBlurH1PixelShader = GraphicsManager::instance().createPixelShader(
      L"Shaders\\BlurH1.fx",
      "PS",
      "ps_4_0" );

    //----------------------------------------------------------------------\\

    //Compile and create the vertex shader for BlurV1
    m_pBlurV1VertexShader = GraphicsManager::instance().CreateVertexShader(
      L"Shaders\\BlurV1.fx",
      "VS",
      "vs_4_0" );

    //Create the InputLayout with the blob
    m_pBlurV1InputLayout = GraphicsManager::instance().createInputLayout(
      m_pBlurV1VertexShader );

    //Compile and Create the pixel shader for luminance
    m_pBlurV1PixelShader = GraphicsManager::instance().createPixelShader(
      L"Shaders\\BlurV1.fx",
      "PS",
      "ps_4_0" );

    //----------------------------------------------------------------------\\

    //Compile and create the vertex shader for BlurV1
    m_pAddBright1VertexShader = GraphicsManager::instance().CreateVertexShader(
      L"Shaders\\AddBright1.fx",
      "VS",
      "vs_4_0" );

    //Create the InputLayout with the blob
    m_pAddBright1InputLayout = GraphicsManager::instance().createInputLayout(
      m_pAddBright1VertexShader );

    //Compile and Create the pixel shader for luminance
    m_pAddBright1PixelShader = GraphicsManager::instance().createPixelShader(
      L"Shaders\\AddBright1.fx",
      "PS",
      "ps_4_0" );

    //----------------------------------------------------------------------\\

    //Compile and create the vertex shader for BlurV1
    m_pToneMapVertexShader = GraphicsManager::instance().CreateVertexShader(
      L"Shaders\\ToneMap.fx",
      "VS",
      "vs_4_0" );

    //Create the InputLayout with the blob
    m_pToneMapInputLayout = GraphicsManager::instance().createInputLayout(
      m_pToneMapVertexShader );

    //Compile and Create the pixel shader for luminance
    m_pToneMapPixelShader = GraphicsManager::instance().createPixelShader(
      L"Shaders\\ToneMap.fx",
      "PS",
      "ps_4_0" );


    //Quad Aligned
    quad = new Mesh();
    quad->loadModel( "Meshes\\QuadPerron.obj" );
    GraphicsManager::instance().createAndsetVertexAndIndexBufferFromMesh( 
      quad->getMeshData());



/*
    //Dwarf
    dwarf = new Mesh();
    dwarf->loadModel( "Meshes\\Dwarf\\dwarf.x" );
    GraphicsManager::instance().createAndsetVertexAndIndexBufferFromMesh(
      dwarf->getNumVertices(),
      dwarf->getVertexData(),
      dwarf->getNumIndices(),
      dwarf->getIndexData(),
      &vDwarfBuffer,
      &iDwarfBuffer);*/

    //Cube
    cube = new Mesh();
    cube->loadModel( "Meshes\\ninjaHead.obj" );
    GraphicsManager::instance().createAndsetVertexAndIndexBufferFromMesh( 
      cube->getMeshData());


    //Create RasterizerState desc
    RASTERIZER_DESCRIPTOR rasterizerDesc;
    memset( &rasterizerDesc, 0, sizeof( rasterizerDesc ) );
    rasterizerDesc.CullMode = CULL_NONE;
    rasterizerDesc.FillMode = FILL_SOLID;

    //Create RasterizerState
    m_RasterizerState = 
      GraphicsManager::instance().createRasterizerState(rasterizerDesc);

    //Sets primitive topology
    GraphicsManager::instance().setPrimitiveTopology( 4 );
   
    //Create the constant buffers desc
    BUFFER_DESCRIPTOR bufferDesc;
    memset( &bufferDesc, 0, sizeof( bufferDesc ) );
    bufferDesc.Usage = USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof( CBNeverChanges );
    bufferDesc.BindFlags = BIND_CONSTANT_BUFFER;
    bufferDesc.CPUAccessFlags = 0;

    //Create Constant buffer
    constantNeverChanges = 
      GraphicsManager::instance().createBuffer( bufferDesc, nullptr );

    bufferDesc.ByteWidth = sizeof( CBChangeOnResize );
    constantChangesonResize =
     GraphicsManager::instance().createBuffer( bufferDesc, nullptr );

    bufferDesc.ByteWidth = sizeof( CBChangesEveryFrame );
    constantChangesEveryFrame =
      GraphicsManager::instance().createBuffer( bufferDesc, nullptr );


    //Load and create shader resource view
    textGorda = GraphicsManager::instance().CreateShaderResourceViewFromFile(
      "Textures\\normal.jpg" );

    //Shader resource view for albedoTex
    m_pAlbedoTexture =
      GraphicsManager::instance().CreateShaderResourceView( m_pAlbedoTexture );

    //Shader resource view for luminance
    m_pLuminanceTexture = 
      GraphicsManager::instance().CreateShaderResourceView( 
        m_pLuminanceTexture );

    //Shader resource view for Bright
    m_pBrightTexture = 
      GraphicsManager::instance().CreateShaderResourceView( 
        m_pBrightTexture );

    //Shader resource view for Blurh1
    m_pBlurH1Texture = 
      GraphicsManager::instance().CreateShaderResourceView(
      m_pBlurH1Texture );

    //Shader resource view for BlurV1
    m_pBlurV1Texture =
     GraphicsManager::instance().CreateShaderResourceView(
     m_pBlurV1Texture );

    //Shader resource view for AddBright1
    m_pAddBright1Texture = 
      GraphicsManager::instance().CreateShaderResourceView(
      m_pAddBright1Texture );  
    
    //Shader resource view for AddBright1
    m_pToneMapTexture = 
      GraphicsManager::instance().CreateShaderResourceView(
      m_pToneMapTexture );


    SAMPLER_DESCRIPTOR sampDesc;
    memset( &sampDesc, 0 ,sizeof( sampDesc ) );
    sampDesc.Filter = FILTER_MIN_MAG_MIP_POINT;
    sampDesc.AddressU = TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressY = TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = 3.402823466e+38f;
    
    m_pSampler = GraphicsManager::instance().createSamplerState( sampDesc );

   //Initialize the matrices
    g_World.identity();

    //initialize the view matrix
    Eye = Vector3f( 0.0f, 3.0f, -175.0f);
    Vector3f At = Vector3f( 0.0f, 1.0f, 0.0f);
    Vector3f Up = Vector3f( 0.0f, 1.0f, 0.0f );
    g_View = g_View.matrixLookAtLH( Eye, At, Up );
    g_View.transpose();

    CBNeverChanges cbNeverChanges;
    cbNeverChanges.mView = g_View;
    GraphicsManager::instance().updateSubresource( constantNeverChanges, 
                                                   &cbNeverChanges );

    //initialize the prijection matrix
    g_Projection = g_Projection.matrixPerspectiveFovLH( 
      0.785398163f,
      static_cast< float >(m_windowWidth) / static_cast<float>(m_windowHeight),
      0.001f,
      500.0f );
    g_Projection.transpose();

    CBChangeOnResize cbChangesonResize;
   
    cbChangesonResize.mProjection = g_Projection;
    GraphicsManager::instance().updateSubresource( constantChangesonResize,
                                                   &cbChangesonResize );

    return result;

  }

  void 
  BaseApp::render()
  {


    //Update our time
    float t = 0.0f;
    static DWORD dwTimeStart = 0;
    DWORD dwTimerCur = GetTickCount();
    if ( dwTimeStart == 0 )
    {
      dwTimeStart = dwTimerCur;
    }
    t = ( dwTimerCur - dwTimeStart ) / 1000.0f;

    //rotate mesh 
    //g_World = DirectX::XMMatrixRotationY( t );




    //Clear back buffer
    float ClearColor2[4] = { 0.0f, 1.0f, 0.0f, 0.0f }; //Azul
    float ClearColor[4] = { 1.0f, 0.0f, 1.0f, 1.0f }; //Rosa
    float ClearColor3[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; //Rojo
    GraphicsManager::instance().clearRenderTargetView( ClearColor, 
                                                       m_pBackBuffer);

    GraphicsManager::instance().clearRenderTargetView( ClearColor2, 
                                                       m_pAlbedoRT );    

   /* GraphicsManager::instance().clearRenderTargetView( ClearColor3, 
                                                       m_pLuminanceRT );*/

    

    //Clear depth Stencil
    GraphicsManager::instance().clearDepthStencilView( CLEAR_DEPTH, 
                                                       1.0f, 
                                                       0, 
                                                       m_pDepthStencilView );

    g_World.transpose();
    CBChangesEveryFrame cb;
    cb.mWorld = g_World;
    cb.vMeshColor = Vector4f( 0.7f, 0.7f, 0.7f, 1.0f );
    cb.ViewPosition = Vector4f(Eye.x, Eye.y, Eye.z, 0.0f);
    GraphicsManager::instance().updateSubresource( constantChangesEveryFrame,
                                                   &cb );

    


    /************************************************************************/
    /* Light                                                                */
    /************************************************************************/

  
    GraphicsManager::instance().setRenderTargets( 1, m_pAlbedoRT,
                                                  m_pDepthStencilView );
    //Sets the Viewport
    GraphicsManager::instance().setViewports( 1, vp );

    uint32 Stride = sizeof( VERTICES );
    uint32 offset = 0;
    GraphicsManager::instance().setVertexBuffers(
      0,
      1,
      reinterpret_cast< Buffer* >( cube->getMeshData()->VertexBuffer ),
      &Stride,
      &offset );

    GraphicsManager::instance().setIndexBuffer( 
      FORMAT_R16_UINT,
      reinterpret_cast<Buffer*>(cube->getMeshData()->IndexBuffer),
      0 );

    GraphicsManager::instance().setInputLayout( inputLayout );
    GraphicsManager::instance().setVertexShader( m_pLightVertexShader );
    GraphicsManager::instance().setVSConstantBuffers( constantNeverChanges, 0, 1 );
    GraphicsManager::instance().setVSConstantBuffers( constantChangesonResize, 1, 1 );
    GraphicsManager::instance().setVSConstantBuffers( constantChangesEveryFrame, 2, 1 );
    GraphicsManager::instance().setPixelShader( m_pLightPixelShader );
    GraphicsManager::instance().setPSConstantBuffers( constantChangesEveryFrame, 2, 1 );
    GraphicsManager::instance().setShaderResources( textGorda, 0, 1 );
    GraphicsManager::instance().setSamplerState( 0, m_pSampler, 1 );


    GraphicsManager::instance().drawIndexed( cube->getMeshData()->IndexData.size(),
                                             0,
                                             0 );
    

    /************************************************************************/
    /* Luminance                                                            */
    /************************************************************************/
  


    GraphicsManager::instance().setRenderTargets( 1,
                                                  m_pLuminanceRT,
                                                  nullptr );
    //Sets the Viewport
    GraphicsManager::instance().setViewports( 1, vp );
    GraphicsManager::instance().setRasterizerState( m_RasterizerState );
    GraphicsManager::instance().setVertexBuffers(
      0,
      1,
      reinterpret_cast< Buffer* >( quad->getMeshData()->VertexBuffer ),
      &Stride,
      &offset );

    GraphicsManager::instance().setIndexBuffer(
      FORMAT_R16_UINT,
      reinterpret_cast< Buffer* >( quad->getMeshData()->IndexBuffer ),
      0 );
    GraphicsManager::instance().setInputLayout( luminanceInputLayout );
    GraphicsManager::instance().setVertexShader( m_pLuminanceVertexShader );
    GraphicsManager::instance().setPixelShader( m_pLuminancePixelShader );
    GraphicsManager::instance().setShaderResources( m_pAlbedoTexture, 0, 1 );
    GraphicsManager::instance().setSamplerState( 0, m_pSampler, 1 );


    GraphicsManager::instance().drawIndexed( quad->getMeshData()->IndexData.size(),
                                             0,
                                             0 );


    /************************************************************************/
    /* Bright                                                               */
    /************************************************************************/

    GraphicsManager::instance().setRenderTargets( 1,
                                                  m_pBrightRT,
                                                  nullptr );
    //Sets the Viewport
    GraphicsManager::instance().setViewports( 1, vp );
    GraphicsManager::instance().setRasterizerState( m_RasterizerState );

    GraphicsManager::instance().setVertexBuffers(
      0,
      1,
      reinterpret_cast< Buffer* >( quad->getMeshData()->VertexBuffer ),
      &Stride,
      &offset );

    GraphicsManager::instance().setIndexBuffer(
      FORMAT_R16_UINT,
      reinterpret_cast< Buffer* >( quad->getMeshData()->IndexBuffer ),
      0 );
    GraphicsManager::instance().setInputLayout( m_pBrightInputLayout );
    GraphicsManager::instance().setVertexShader( m_pBrightVertexShader );
    GraphicsManager::instance().setPixelShader( m_pBrightPixelShader );
    GraphicsManager::instance().setShaderResources( m_pAlbedoTexture, 0, 1 );
    GraphicsManager::instance().setSamplerState( 0, m_pSampler, 1 );

    GraphicsManager::instance().drawIndexed( quad->getMeshData()->IndexData.size(),
                                             0,
                                             0 );


    /************************************************************************/
    /* BlurH1                                                               */
    /************************************************************************/

    GraphicsManager::instance().setRenderTargets( 1,
                                                  m_pBlurH1RT,
                                                  nullptr );
    //Sets the Viewport
    GraphicsManager::instance().setViewports( 1, vp2 );
    GraphicsManager::instance().setRasterizerState( m_RasterizerState );
    GraphicsManager::instance().setVertexBuffers(
      0,
      1,
      reinterpret_cast< Buffer* >( quad->getMeshData()->VertexBuffer ),
      &Stride,
      &offset );

    GraphicsManager::instance().setIndexBuffer(
      FORMAT_R16_UINT,
      reinterpret_cast< Buffer* >( quad->getMeshData()->IndexBuffer ),
      0 );
    GraphicsManager::instance().setInputLayout( m_pBlurH1InputLayout );
    GraphicsManager::instance().setVertexShader( m_pBlurH1VertexShader );
    GraphicsManager::instance().setPixelShader( m_pBlurH1PixelShader );
    GraphicsManager::instance().setShaderResources( m_pBrightTexture, 0, 1 );
    GraphicsManager::instance().setSamplerState( 0, m_pSampler, 1 );

    GraphicsManager::instance().drawIndexed( quad->getMeshData()->IndexData.size(),
                                             0,
                                             0 );

    /************************************************************************/
    /* BlurV1                                                               */
    /************************************************************************/

    GraphicsManager::instance().setRenderTargets( 1,
                                                  m_pBlurV1RT,
                                                  nullptr );
    //Sets the Viewport
    GraphicsManager::instance().setViewports( 1, vp2 );
    GraphicsManager::instance().setRasterizerState( m_RasterizerState );
    GraphicsManager::instance().setVertexBuffers(
      0,
      1,
      reinterpret_cast< Buffer* >( quad->getMeshData()->VertexBuffer ),
      &Stride,
      &offset );

    GraphicsManager::instance().setIndexBuffer(
      FORMAT_R16_UINT,
      reinterpret_cast< Buffer* >( quad->getMeshData()->IndexBuffer ),
      0 );
    GraphicsManager::instance().setInputLayout( m_pBlurV1InputLayout );
    GraphicsManager::instance().setVertexShader( m_pBlurV1VertexShader );
    GraphicsManager::instance().setPixelShader( m_pBlurV1PixelShader );
    GraphicsManager::instance().setShaderResources( m_pBlurH1Texture, 0, 1 );
    GraphicsManager::instance().setSamplerState( 0, m_pSampler, 1 );

    GraphicsManager::instance().drawIndexed( quad->getMeshData()->IndexData.size(),
                                             0,
                                             0 );

    /************************************************************************/
    /* AddBright1                                                           */
    /************************************************************************/

    GraphicsManager::instance().setRenderTargets( 1,
                                                  m_pAddBright1RT,
                                                  nullptr );
    //Sets the Viewport
    GraphicsManager::instance().setViewports( 1, vp );
    GraphicsManager::instance().setRasterizerState( m_RasterizerState );
    GraphicsManager::instance().setVertexBuffers(
      0,
      1,
      reinterpret_cast< Buffer* >( quad->getMeshData()->VertexBuffer ),
      &Stride,
      &offset );

    GraphicsManager::instance().setIndexBuffer(
      FORMAT_R16_UINT,
      reinterpret_cast< Buffer* >( quad->getMeshData()->IndexBuffer ),
      0 );
    GraphicsManager::instance().setInputLayout( m_pAddBright1InputLayout );
    GraphicsManager::instance().setVertexShader( m_pAddBright1VertexShader );
    GraphicsManager::instance().setPixelShader( m_pAddBright1PixelShader );
    GraphicsManager::instance().setShaderResources( m_pBrightTexture, 0, 1 );
    GraphicsManager::instance().setShaderResources( m_pBlurH1Texture, 1, 1 );
    GraphicsManager::instance().setShaderResources( m_pBlurV1Texture, 2, 1 );
    GraphicsManager::instance().setSamplerState( 0, m_pSampler, 1 );

    GraphicsManager::instance().drawIndexed( quad->getMeshData()->IndexData.size(),
                                             0,
                                             0 );

    /************************************************************************/
    /* ToneMap                                                          */
    /************************************************************************/

    GraphicsManager::instance().setRenderTargets( 1,
                                                  m_pBackBuffer,
                                                  nullptr );
    //Sets the Viewport
    GraphicsManager::instance().setViewports( 1, vp );
    GraphicsManager::instance().setRasterizerState( m_RasterizerState );
    GraphicsManager::instance().setVertexBuffers(
      0,
      1,
      reinterpret_cast< Buffer* >( quad->getMeshData()->VertexBuffer),
                                   &Stride,
                                   &offset );

    GraphicsManager::instance().setIndexBuffer(
      FORMAT_R16_UINT,
      reinterpret_cast< Buffer* >( quad->getMeshData()->IndexBuffer ),
      0 );
    GraphicsManager::instance().setInputLayout( m_pToneMapInputLayout );
    GraphicsManager::instance().setVertexShader( m_pToneMapVertexShader );
    GraphicsManager::instance().setPixelShader( m_pToneMapPixelShader );
    GraphicsManager::instance().setShaderResources( m_pAlbedoTexture, 0, 1 );
    GraphicsManager::instance().setShaderResources( m_pAddBright1Texture, 1, 1 );
    GraphicsManager::instance().setSamplerState( 0, m_pSampler, 1 );

    GraphicsManager::instance().drawIndexed( quad->getMeshData()->IndexData.size(),
                                             0,
                                             0 );
   
    GraphicsManager::instance().present( 0, 0 );
  }

  void 
  BaseApp::update()
  {
    //Update
  }

  bool 
  BaseApp::loadLibrary( String libraryName, String funcName )
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

  BaseApp&
  g_baseApp()
  {
    return BaseApp::instance();
  }
}

