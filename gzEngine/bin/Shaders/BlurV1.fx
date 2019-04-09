//--------------------------------------------------------------------------------------
// File: Tutorial07.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
Texture2D m_pBright : register(t0); 
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

  /****************************************************/
  /* Constant defines                                 */
  /****************************************************/
  const float2 OFFSETS[] =                     // Pixel sampler(Near pixels)
  {
     float2( 0, -4 ),
     float2( 0, -3 ),
     float2( 0, -2 ),
     float2( 0, -1 ),
     float2( 0, 0 ),
     float2( 0, 1 ),
     float2( 0, 2 ),
     float2( 0, 3 ),
     float2( 0, 4 )
  };

  static const float g_BlurWeights[] =         // Gaus distribution
  {
     0.004815026f,
     0.028716039f,
     0.102818575f,
     0.221024189f,
     0.285252340f,
     0.221024189f,
     0.102818575f,
     0.028716039f,
     0.004815026f
  };


  float fViewportDimensionY = 240.0f;                  // Viewport dimensions(0.5,0.5)
  int Blur1Mip = 4;                                // blur mip lod

  // Pixel size calc
  float Texel = ( 1.0f / fViewportDimensionY ) * ( Blur1Mip + 1 );

  float4
   output = pow( m_pBright.SampleLevel( samLinear, input.Tex.xy + ( OFFSETS[0] * Texel ), Blur1Mip ), 2.2f ) * g_BlurWeights[0];
  output += pow( m_pBright.SampleLevel( samLinear, input.Tex.xy + ( OFFSETS[1] * Texel ), Blur1Mip ), 2.2f ) * g_BlurWeights[1];
  output += pow( m_pBright.SampleLevel( samLinear, input.Tex.xy + ( OFFSETS[2] * Texel ), Blur1Mip ), 2.2f ) * g_BlurWeights[2];
  output += pow( m_pBright.SampleLevel( samLinear, input.Tex.xy + ( OFFSETS[3] * Texel ), Blur1Mip ), 2.2f ) * g_BlurWeights[3];
  output += pow( m_pBright.SampleLevel( samLinear, input.Tex.xy + ( OFFSETS[4] * Texel ), Blur1Mip ), 2.2f ) * g_BlurWeights[4];
  output += pow( m_pBright.SampleLevel( samLinear, input.Tex.xy + ( OFFSETS[5] * Texel ), Blur1Mip ), 2.2f ) * g_BlurWeights[5];
  output += pow( m_pBright.SampleLevel( samLinear, input.Tex.xy + ( OFFSETS[6] * Texel ), Blur1Mip ), 2.2f ) * g_BlurWeights[6];
  output += pow( m_pBright.SampleLevel( samLinear, input.Tex.xy + ( OFFSETS[7] * Texel ), Blur1Mip ), 2.2f ) * g_BlurWeights[7];
  output += pow( m_pBright.SampleLevel( samLinear, input.Tex.xy + ( OFFSETS[8] * Texel ), Blur1Mip ), 2.2f ) * g_BlurWeights[8];


  return pow( output, 1.0f / 2.2 );

}
