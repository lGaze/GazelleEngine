//--------------------------------------------------------------------------------------
// File: Tutorial07.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
Texture2D m_pBright : register(t0); 
Texture2D m_pBlurH1Texture : register(t1);
Texture2D m_pBlurV2Texture : register(t2);

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

  int Blur1Mip = 4;                                // blur mip lod

  // Texture sampler
  float bright = pow( m_pBright.Sample( samLinear, input.Tex.xy ), 2.2f );
  float blurH = pow( m_pBlurH1Texture.SampleLevel( samLinear, input.Tex.xy, Blur1Mip - 1 ), 2.2f );
  float blurV = pow( m_pBlurV2Texture.SampleLevel( samLinear, input.Tex.xy, Blur1Mip - 1 ), 2.2f );
  
  // Combination
  float output = pow( ( 0.5f * ( blurH + blurV ) ) + bright, 1.0f / 2.2f );
  
  return output.xxxx;

}
