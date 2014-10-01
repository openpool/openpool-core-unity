Shader "OpenPool/Toon" {
	Properties {
		_MainTex ("Base (RGB)", 2D) = "white" {}
		_Ramp ("Shadow (RGB)", 2D) = "gray" {}
	}
	SubShader {
		Tags {
			"RenderType"="Opaque"
		}
		LOD 200
		
		CGPROGRAM
		
		#pragma surface surf Toon
		#include "UnityCG.cginc"

		// Lighting
		sampler2D _Ramp;

		inline half4 LightingToon (SurfaceOutput s, half3 lightDir, half atten)
		{
			#ifndef USING_DIRECTIONAL_LIGHT
			lightDir = normalize(lightDir);
			#endif
			
			half d = dot (s.Normal, lightDir) * 0.5 + 0.5;
			half3 ramp = tex2D (_Ramp, float2(d,d)).rgb;
			
			half4 c;
			c.rgb = s.Albedo * ramp * _LightColor0.rgb * (atten * 2); // Dont use light color
//			c.rgb = s.Albedo * ramp * (atten * 2);
			c.a = 0;
			return c;
		}

		// Surface
		sampler2D _MainTex;		

		struct Input {
			float2 uv_MainTex;
			float2 uv_ShadowTex;
		};
		
		void surf (Input IN, inout SurfaceOutput o) {
			half4 c = tex2D (_MainTex, IN.uv_MainTex);
			o.Albedo = c.rgb;
		}
		
		ENDCG
		
	} 
	FallBack "Diffuse"
}
