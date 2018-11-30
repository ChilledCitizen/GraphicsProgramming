Shader "Custom/Grass" {
    Properties {
        _Color ("Main Color", Color) = (0.5,0.5,0.5,1)
        _MainTex ("Base (RGB)", 2D) = "white" {}
        _SwaySpeed ("MoveSpeed", Range(20,50)) = 25
        _Rigidness("Rigidness", Range(1,50)) = 25 
        _SwayMax("Sway Max", Range(0, 0.1)) = .005 
        _YOffset("Y offset", float) = 0.0
        _MaxWidth("Max Displacement Width", Range(0, 2)) = 0.1 
		
    }

    SubShader {
        Tags { "RenderType"="Opaque" "DisableBatching" = "True" }
        LOD 200
        Blend SrcAlpha OneMinusSrcAlpha


CGPROGRAM
#pragma surface surf ToonRamp vertex:vert addshadow keepalpha // addshadow applies shadow after vertex animation
 
sampler2D _Ramp;
 

#pragma lighting ToonRamp exclude_path:prepass
inline half4 LightingToonRamp (SurfaceOutput s, half3 lightDir, half atten)
{
    #ifndef USING_DIRECTIONAL_LIGHT
    lightDir = normalize(lightDir);
    #endif
   
    half d = dot (s.Normal, lightDir)*0.5 + 0.5;
    half3 ramp = tex2D (_Ramp, float2(d,d)).rgb;
   
    half4 c;
    c.rgb = s.Albedo * _LightColor0.rgb * ramp * (atten * 2);
    c.a = s.Alpha;
    return c;
}

sampler2D _MainTex;
float4 _Color;


float _SwaySpeed;
float _SwayMax;
float _YOffset;
float _Rigidness;
float _MaxWidth;

uniform float3 _Positions[100];
uniform float _PositionArray;
uniform float _Radius;

struct Input {
    float2 uv_MainTex : TEXCOORD0;
};
void vert(inout appdata_full v)//
{
    // basic swaying movement
   float3 wpos = mul(unity_ObjectToWorld, v.vertex).xyz;
   float x = sin(wpos.x / _Rigidness + (_Time.x * _SwaySpeed)) *(v.vertex.y - _YOffset) * 5;
   float z = sin(wpos.z / _Rigidness + (_Time.x * _SwaySpeed)) *(v.vertex.y - _YOffset) * 5;
   v.vertex.x += (step(0,v.vertex.y - _YOffset) * x * _SwayMax);
   v.vertex.z += (step(0,v.vertex.y - _YOffset) * z * _SwayMax);

   // interaction radius movement for every position in array
   for  (int i = 0; i < _PositionArray; i++){
        float3 dis =  distance(_Positions[i], wpos); 
        float3 radius = 1-  saturate(dis /_Radius); 
        float3 sphereDisp = wpos - _Positions[i]; 
        sphereDisp *= radius; 
        v.vertex.xz += clamp(sphereDisp.xz * step(_YOffset, v.vertex.y), -_MaxWidth,_MaxWidth);
    }
}

void surf (Input IN, inout SurfaceOutput o) {
    half4 c = tex2D(_MainTex, IN.uv_MainTex) * _Color;
    o.Albedo = c.rgb;
    o.Alpha = c.a;
}
ENDCG

    }

    Fallback "Diffuse"
}