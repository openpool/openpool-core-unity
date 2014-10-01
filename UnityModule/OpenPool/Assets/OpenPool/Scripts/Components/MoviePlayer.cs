using UnityEngine;
using System.Collections;

namespace OpenPool {
[AddComponentMenu("OpenPool/Components/Movie Player")]
public class MoviePlayer : MonoBehaviour {
	
	[SerializeField]
	Material mat;
	
	MovieTexture movieTexture;
	
	// Use this for initialization
	void Start () {
		movieTexture = mat.mainTexture as MovieTexture;
		movieTexture.loop = true;
		movieTexture.Play();
	}
}
}