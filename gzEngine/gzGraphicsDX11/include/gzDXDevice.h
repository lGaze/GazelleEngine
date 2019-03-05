/**************************************************************************/
/* @filename gzDXDevice.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#pragma once

#include "gzDXPrerequisites.h"

namespace gzEngineSDK {
class Device
{
 public:
   
  /**
   * @brief default constructor
   */
  Device();
	
  /**
   * @brief default destructor
   */
  ~Device() = default;
	
  /************************************************************************/
  /* Device functions                                                     */
  /************************************************************************/
	
  /**
   * @brief Function for Device, Device Context and SwapChain creation
   * @returns Value wich indicates if the creation succeed
   */
  bool
  CreateDeviceAndSwapChain( DXGI_SWAP_CHAIN_DESC SwapChainDesc,
                            IDXGISwapChain ** SwapChainInterface,
                            ID3D11DeviceContext ** DeviceContextInterface );

  /**
   * @brief 
   */
  bool
  CreateRenderTargetView( ID3D11Resource *pResource,
                          const D3D11_RENDER_TARGET_VIEW_DESC *pDesc,
                          ID3D11RenderTargetView **ppRTView );

  /**
   * @brief 
   */
  bool
  CreateTexture2D( const D3D11_TEXTURE2D_DESC *pDesc,
                   const D3D11_SUBRESOURCE_DATA *pInitialData,
                   ID3D11Texture2D **ppTexture2D );

  /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/
	
 private:

   ID3D11Device* m_pDevice;

   uint32 m_deviceFlags;

   int32 m_sdk;

   D3D_DRIVER_TYPE m_driverType;

   D3D_FEATURE_LEVEL	m_featureLevel;

   uint32 m_numDriverTypes;

   uint32 m_numFeatureLevels;


   D3D_DRIVER_TYPE m_driverTypes[3] =
   {
     D3D_DRIVER_TYPE_HARDWARE,
     D3D_DRIVER_TYPE_WARP,
     D3D_DRIVER_TYPE_REFERENCE,
   };

   D3D_FEATURE_LEVEL m_featureLevels[3] =
   {
     D3D_FEATURE_LEVEL_11_0,
     D3D_FEATURE_LEVEL_10_1,
     D3D_FEATURE_LEVEL_10_0,
   };

 };
}
