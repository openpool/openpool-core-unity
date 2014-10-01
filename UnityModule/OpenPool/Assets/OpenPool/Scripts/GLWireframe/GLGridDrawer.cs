using UnityEngine;

namespace OpenPool {
[AddComponentMenu("OpenPool/Wireframe/GL Grid")]
public class GLGridDrawer : GLDrawerBase {
	
	[SerializeField]
	int count = 8;
	
	[SerializeField]
	float scale = 0.5f;
	
	[SerializeField]
	float distance = 50f;
	
	[SerializeField]
	Color color = Color.green;
	
	void Start ()
	{
		
	}
	
	protected override void OnDraw ()
	{
		GL.Begin (GL.LINES);
		GL.Color (color);
		
		Vector3 pos;
		for (int x=0; x<count; ++x) {
			for (int y=0; y<count; ++y) {
				for (int z=0; z<count; ++z) {
					
					pos = new Vector3 (
						((float)x / count - .5f) * distance,
						((float)y / count - .5f) * distance,
						((float)z / count - .5f) * distance
						);
					
					drawGrid (ref pos);
				}
			}
		}
		GL.End ();	
		
		
	}
		
	void drawGrid (ref Vector3 pos)
	{
		GL.Vertex3 (pos.x - scale, pos.y, pos.z);
		GL.Vertex3 (pos.x + scale, pos.y, pos.z);
		
		GL.Vertex3 (pos.x, pos.y - scale, pos.z);
		GL.Vertex3 (pos.x, pos.y + scale, pos.z);
		
		GL.Vertex3 (pos.x, pos.y, pos.z - scale);
		GL.Vertex3 (pos.x, pos.y, pos.z + scale);
	}
}
}