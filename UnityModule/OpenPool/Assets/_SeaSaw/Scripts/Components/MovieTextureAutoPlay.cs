using UnityEngine;
using System.Collections;

public class MovieTextureAutoPlay : MonoBehaviour {
		
	void Start() {
		Material mat = renderer.material;
		Texture texture = mat.mainTexture;
		MovieTexture movie = texture as MovieTexture;
		
		movie.Stop();
		movie.loop = true;
		movie.Play();
	}
}
