Shader "OpenPool/MaskedSprite" {
	Properties {
		_MainTex ("Base (RGB)", 2D) = "white" {}
	}
	SubShader {
		Tags {
		"Queue"="Transparent"
		"IgnoreProjector"="True"
		"RenderType"="Transparent"
		"PreviewType"="Plane"
		}
		LOD 100
		
		Alphatest Greater 0
		Cull Off
		Lighting Off	
		ZWrite Off
		Fog { Mode Off }
		Blend SrcAlpha OneMinusSrcAlpha 
		ColorMask RGB
	
		Pass {
			Blend SrcAlpha OneMinusSrcAlpha
			CGPROGRAM
			#pragma vertex vert
			#pragma fragment frag
			#pragma multi_compile DUMMY PIXELSNAP_ON
			#include "UnityCG.cginc"
			
			struct appdata_t
			{
				float4 vertex   : POSITION;
				float4 color    : COLOR;
				float2 texcoord : TEXCOORD0;
			};

			struct v2f
			{
				float4 vertex   : SV_POSITION;
				fixed4 color    : COLOR;
				half2 texcoord  : TEXCOORD0;
			};

			v2f vert(appdata_t IN)
			{
				v2f OUT;
				OUT.vertex = mul(UNITY_MATRIX_MVP, IN.vertex);
				OUT.texcoord = IN.texcoord;
				OUT.color = IN.color;
				
				#ifdef PIXELSNAP_ON
				OUT.vertex = UnityPixelSnap (OUT.vertex);
				#endif
				
				return OUT;
			}

			sampler2D _MainTex;
			
			half4 frag (v2f IN) : SV_Target
			{
				half2 mask_uv = IN.texcoord;
				mask_uv.y /= 2;
				
				half2 base_uv = mask_uv;
				base_uv.y += 0.5;
				
				fixed3 base = tex2D (_MainTex, base_uv);
				fixed3 mask = tex2D (_MainTex, mask_uv);
				
			    return fixed4(base, mask.r);
			}
			ENDCG
		}
	} 
	FallBack "Diffuse"
}
