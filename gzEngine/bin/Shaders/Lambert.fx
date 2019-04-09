//--------------------------------------------------------------------------------------
// File: Tutorial07.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
Texture2D txDiffuse : register( t0 );
SamplerState samLinear : register( s0 );

cbuffer cbNeverChanges : register( b0 )
{
    matrix View;
};

cbuffer cbChangeOnResize : register( b1 )
{
    matrix Projection;
};

cbuffer cbChangesEveryFrame : register( b2 )
{
    matrix World;
    float4 vMeshColor;
    float4 ViewPosition;
};


//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;
    float3 Normal : NORMAL;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Light1 :TEXCOORD0;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
    PS_INPUT output = (PS_INPUT)0;

    float kDiffuse = float(1.0f);
    float4 DiffuseColor = float4(0.5f, 0.01f, 1.0f, 1.0f);
    float4 LightDir = float4(0.0f, 0.0f, 1.0f, 1.0f);
   /************************************************************************/
   /* World Space
   /************************************************************************/
    float4 wsPos = mul(input.Pos , World);
    float3 wsNormal = mul(input.Normal, World);
    float3 wsLightDir = -normalize(LightDir); //LightDir

   /************************************************************************/
   /* View Space
   /************************************************************************/
    float4 vsPos = mul(wsPos, View);

   /************************************************************************/
   /* Projection Space
   /************************************************************************/
    float4 psPos = mul(vsPos, Projection);

   /************************************************************************/
   /* World Space Light Calc
   /************************************************************************/
    float wsLdN = dot(wsLightDir, wsNormal);
    float4 wsDiffuse = kDiffuse * DiffuseColor * wsLdN;

    output.Light1 = wsDiffuse;
    output.Pos = psPos;
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( PS_INPUT input) : SV_Target
{
    return float4(input.Light1.xyz, 1);
}
