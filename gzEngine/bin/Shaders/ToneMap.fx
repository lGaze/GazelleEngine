//--------------------------------------------------------------------------------------
// File: Tutorial07.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
Texture2D m_pAlbedoTexture : register(t0); 
Texture2D m_pAddBright1 : register(t1); 

SamplerState samLinear : register(s0);


//--------------------------------------------------------------------------------------
struct VS_INPUT
{
  float3 Pos : POSITION;
  float3 Normal : NORMAL;
  float2 Tex : TEXCOORD0;
};

struct PS_INPUT
{
  float4 Pos : SV_POSITION;
  float2 Tex : TEXCOORD0;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
  PS_INPUT output = (PS_INPUT)0;

  output.Pos = float4(input.Pos.xyz, 1);
  output.Tex = float2(input.Tex.x, -input.Tex.y);
  return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
  float BloomMuiltiplier = 34.0f;                      // HDR mult

  // Texture sampling
  float Bloom = pow( BloomMuiltiplier * m_pAddBright1.Sample( samLinear, input.Tex.xy ), 2.2 );
  
  float4 Color = pow( m_pAlbedoTexture.Sample( samLinear, input.Tex.xy ), 2.2 );
  
  Color.xyz += Color.xyz * Bloom;
  
  return pow( Color, 1.0 / 2.2 );
}
