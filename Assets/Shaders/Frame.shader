Shader "Custom/Frame" {
	Properties
	{

		_MainTex ("Frame",2D) = "white"{}
		_SecondTex ("Picture", 2D) = "black"{}
		
	}
	SubShader
	{

		Pass 
		{

		CGPROGRAM

		#pragma vertex vert
		#pragma fragment frag
		
		#include "UnityCG.cginc"

		struct appdata
		{
			float4 vertex : POSITION;
			float2 uv : TEXCOORD0;
		};

		struct v2f
		{
			float2 uv : TEXCOORD1;
			float4 vertex : SV_POSITION;
		};

		sampler2D _MainTex;
		sampler2D _SecondTex;
	

		v2f vert(appdata v)
		{
			v2f o;
			
			o.uv = v.uv;
			o.vertex = v.vertex;
			return o;
		}

		fixed4 frag(v2f i) : SV_Target
		{
			float4 n = tex2D(_MainTex, i.vertex.xy);
			float4 d = tex2D(_SecondTex, i.vertex.xy);
			return n+d;
		}



		ENDCG

		}



		
	}

}
