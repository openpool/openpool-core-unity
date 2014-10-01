using UnityEngine;

namespace OpenPool {
public sealed class GLUtils {
	public static void DrawCube(Vector3 center, float size) {
		
		/*=======
		
		  a-----b
		 /|    /|
		c-+---d |
		| e---|-f
		|/    |/
		g-----h
		
		y z
		|/
		/-x
		
		=======*/
		
		Vector3 a = center + new Vector3(-size, size, size);
		Vector3 b = center + new Vector3( size, size, size);
		Vector3 c = center + new Vector3(-size, size,-size);
		Vector3 d = center + new Vector3( size, size,-size);
		Vector3 e = center + new Vector3(-size,-size, size);
		Vector3 f = center + new Vector3( size,-size, size);
		Vector3 g = center + new Vector3(-size,-size,-size);
		Vector3 h = center + new Vector3( size,-size,-size);
		
		DrawVertexes(
			a,b,
			b,d,
			d,c,
			c,b,
			
			a,e,
			b,f,
			c,g,
			d,h,
			
			e,f,
			f,h,
			h,g,
			g,e
		);
	}
	
	public static void DrawVertexes(params Vector3[] points) {
		foreach(Vector3 p in points) {
			GL.Vertex(p);
		}
	}
	
}
}