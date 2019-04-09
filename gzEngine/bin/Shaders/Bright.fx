//--------------------------------------------------------------------------------------
// File: Tutorial07.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
Texture2D m_pLuminance : register(t0); 
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
  int BrightLod = 0;
  float BloomThreshold = 0.05000f;

  //Bright calc
  return 0.5f * max( m_pLuminance.SampleLevel( samLinear, input.Tex.xy, BrightLod ) - BloomThreshold, 0.0f );
}
