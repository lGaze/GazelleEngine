/**************************************************************************/
/* @filename gzDXTexture.h
/* @author Victor Flores 
/* @date 2019/03/04
/* @brief 
/**************************************************************************/

#pragma once

#include "gzDXPrerequisites.h"
#include  <gzTexture.h>

namespace gzEngineSDK {
class DXTexture : public Texture
{
 public:
   
  /**
   * @brief default constructor
   */
  DXTexture();
	
  /**
   * @brief default destructor
   */
  ~DXTexture() = default;
	
  /************************************************************************/
  /* Texture functions                                                    */
  /************************************************************************/
   
   /**
    * @brief 
    */
   void
   CreateTextureDesc( uint32 width,
                      uint32 height,
                      uint32 format,
                      uint32 usage );



   /**
    * @brief 
    */
   FORCEINLINE ID3D11Texture2D **
   GetTextureInterface() {
     return &m_ptex;
   }

   /**
    * @brief 
    */
   FORCEINLINE D3D11_TEXTURE2D_DESC
   GetTextureDesc() {
     return m_desc;
   }

   /**
    * @brief This function creates a 2D Texture
    */
   virtual bool
   createTexture2D() override;

     /************************************************************************/
  /* Member declarations                                                  */
  /************************************************************************/

 private:

   /**
    * @brief
    */
   ID3D11Texture2D* m_ptex;

   /**
    * @brief 
    */
   D3D11_TEXTURE2D_DESC m_desc;

   /**
    * @brief 
    */
   DXGI_FORMAT m_format;

   /**
    * @brief
    */
   D3D11_USAGE m_usage;
   
 };
}