using UnityEngine;
using System.Collections.Generic;

namespace OpenPool {
[AddComponentMenu("OpenPool/Wireframe/GL Grapher")]
public class GLGrapher : GLDrawerBase {
	[SerializeField]	
	public Color color = Color.gray;

	[SerializeField]
	public int maxCount = 1000;

	[SerializeField]
	public Vector2 scale = Vector2.one;

	[SerializeField]
	public Vector3 offset;

	//[SerializeField]
	List<float> values;


	void Awake() {
		values = new List<float>();
	}

	protected override void OnDraw ()
	{
		if(values.Count < 2) {
			return;
		}

		GL.Begin (GL.LINES);
		GL.Color (color);

		float v, x;
//		lock(values) {
		for (int i=1; i<values.Count; i++) {
			x = ((i-1f)/maxCount-0.5f) * scale.x;
			v = values[i-1] * scale.y;
			GL.Vertex (new Vector3(x,v,0)+offset);
			x = ((float)i/maxCount-0.5f) * scale.x;
			v = values[i] * scale.y;
			GL.Vertex (new Vector3(x,v,0)+offset);
		}
//		}
		GL.End ();

	}

	public void AddValue(float value) {
		values.Add(value);

		while(values.Count > maxCount) {
			values.RemoveAt(0);
		}
	}

	public void Clear() {
		values.Clear();
	}
}
}