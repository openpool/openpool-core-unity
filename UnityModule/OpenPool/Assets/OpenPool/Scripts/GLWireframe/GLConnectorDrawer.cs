using UnityEngine;
using System.Collections;
using System.Collections.Generic;

namespace OpenPool {
[AddComponentMenu("OpenPool/Wireframe/GL Connector")]
public class GLConnectorDrawer : GLDrawerBase {
	
	[SerializeField]
	public Transform start;
	
	[SerializeField]
	public Transform end;
	
	
	[SerializeField]
	Color color;
	
	Transform _transform;
	Vector3[] points;
	
	void OnEnable() {
		
	}
	
	IEnumerator Start() {
	
		while(GLDrawerCamera.Camera == null) {
			yield return null;
		}
		
		GLDrawerCamera.Camera.AddDrawer(this);
		_transform = transform;
		points = new Vector3[3];
	}
	
	
	
	void OnDisable() {
		GLDrawerCamera.Camera.RemoveDrawer(this);
	}

	protected override void OnDraw() {
		GL.Begin (GL.LINES);
		GL.Color (color);
		
		points[0] = _transform.InverseTransformPoint(start.position);
		points[1] = points[0];
		points[2] = _transform.InverseTransformPoint(end.position);
		
		points[1].y = (points[0].y + points[2].y) * 0.5f;
		
		for (int i=1; i<points.Length; ++i) {
			GL.Vertex (points [i-1]);
			GL.Vertex (points [i]);
		}
		
		GL.End ();
	}
}
}