//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

cbuffer cbMatrix
{
  matrix View;
  matrix Projection;
  matrix World;
  float4 ViewPosition;
}; 


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
  float3 Light1 :TEXCOORD1;
};



//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
  PS_INPUT output = (PS_INPUT)0;

  float kDiffuse = float(.5f);
  float kSpecular = float(.8f);
  float SpecularPower = float(5.0f);
  float3 DiffuseColor = float3(0.0f, 0.0f, 1.0f);
  float4 SpecularColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
  float4 LightDir = float4(-1.0f, 1.0f, 1.0f, 1.0f);
  float3 AmbientColor = float3(1.0f, 0.5f, 1.0f);
  float kAmbient = float(0.2f);

  /************************************************************************/
  /* World Space
  /************************************************************************/
  float4 wsPos = mul( float4( input.Pos.xyz, 1.0f ), World);
  float3 wsNormal = mul(float4(normalize(input.Normal.xyz), 0.0), World).xyz;
  float3 wsViewDir = -normalize(wsPos.xyz - ViewPosition.xyz);
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
  //Lambert
  float wsLdN = dot(wsLightDir, wsNormal);
  float3 wsDiffuse = kDiffuse * DiffuseColor.xyz * wsLdN;

  //Phong
 //float3 wsReflection = normalize(reflect(wsLightDir.xyz, wsNormal));
 //float wsVdR = dot(wsViewDir.xyz, wsReflection.xyz);
 //float SpecularFactor = pow(max(0, wsVdR), SpecularPower);
 //float3 wsSpecular = kSpecular * SpecularColor * SpecularFactor;

 //Bling Phong
  float3 wsHalf = normalize(wsLightDir.xyz + wsViewDir.xyz);
  //Normal dot Half
  float wsNdH = dot(wsNormal.xyz, wsHalf.xyz);
  wsNdH = min(max(0, wsNdH), 1.0);
  float specularFactor = pow(wsNdH, SpecularPower);
  float3 wsSpecular = kSpecular * SpecularColor.xyz * specularFactor;

  //Ambient
  float3 wsAmbient = kAmbient + AmbientColor.xyz * -wsLdN;

  output.Light1 = wsDiffuse + wsSpecular + wsAmbient;
  output.Pos = psPos;
  output.Tex = input.Tex;
  return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
    float4 tex = txDiffuse.Sample(samLinear, input.Tex);
    return float4(tex.xyz * input.Light1,  1);
}
