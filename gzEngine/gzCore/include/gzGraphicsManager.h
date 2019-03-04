/**************************************************************************/
/* @filename gzGraphicsManager.h
/* @author Victor Flores 
/* @date 2019/03/03
/* @brief 
/**************************************************************************/
#pragma once

#include "gzPrerequisitesCore.h"
#include "gzModule.h"

namespace gzEngineSDK {
class GZ_UTILITY_EXPORT GraphicsManager : public Module<GraphicsManager>
{
 public:
   
  /**
   * @brief default constructor
   */
  GraphicsManager() = default;
	
  /**
   * @brief default destructor
   */
  ~GraphicsManager() = default;
	
  /************************************************************************/
  /* GraphicsManager functions                                            */
  /************************************************************************/
  
  /**
   * @brief 
   */
  virtual bool
  InitGraphicsManager(void* hWnd, int32 width, int32 height ) = 0;

  /**
   * @brief 
   */
  virtual bool
  CreateRenderTargetView() = 0;

  /**
   * @brief 
   */
  virtual bool
  CreateDepthStencilView() = 0;

  /**
   * @brief 
   */
  virtual bool
  CreateVertexShader() = 0;

  /**
   * @brief 
   */
  virtual bool
  CreateInputLayout() = 0;

  /**
   * @brief 
   */
  virtual bool
  CreatePixelShader() = 0;

  /**
   * @brief 
   */
  virtual bool
  CreateBuffer() = 0;

  /**
   * @brief 
   */
  virtual bool
  CreateTexture2D() = 0;

  /**
   * @brief 
   */
  virtual bool
  CreateVertexAndIndexBufferFromFile( std::string file ) = 0;

  /**
   * @brief 
   */
  virtual bool
  CreateSamplerState() = 0;


  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
	
 public:
   
 };
}