using UnityEngine;
using System.Collections;

namespace Tange {

[AddComponentMenu("Tange/Components/UVAnimation")]
public class UVAnimation : MonoBehaviour {
	
	[RangeAttribute(1.0f, 60.0f)]
	public float fps = 30f;
	
	public int textureRow;
	public int textureColumn;
	
	[SerializeField]
	string textureName;
	
	[SerializeField]
	Renderer animationRenderer;
		
	Material mat;
	
	public int index = 0;
	int animationLength;
	
	void OnValidate() {
		if(string.IsNullOrEmpty(textureName)) {
			textureName = "_MainTex";
		}
		if(animationRenderer == null) {
			animationRenderer = renderer;
		}
		else if(animationRenderer == null) {
			animationRenderer = GetComponent<MeshRenderer>();
		}
		if(textureRow < 0) {
			textureRow = 1;
		}
		if(textureColumn < 0) {
			textureColumn = 1;
		}
	}
	
	void OnEnable() {
		animationLength = textureRow * textureColumn;
		mat = animationRenderer.material;
		StartCoroutine(Loop ());
	}
	
	void OnDisable() {
		StopAllCoroutines();
	}
	
	IEnumerator Loop() {
		while(this.enabled) {
			index++;
			if(index >= animationLength) {
				index = 0;
			}
			
			float u = (float)(index%textureColumn) / textureColumn;
			float v = -(float)(index/textureColumn) / textureRow;
			mat.SetTextureOffset(textureName, new Vector2(u,v));
			
			yield return new WaitForSeconds(1/fps);
		}
	}
}
}