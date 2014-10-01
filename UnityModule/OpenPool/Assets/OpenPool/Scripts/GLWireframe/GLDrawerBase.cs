using UnityEngine;

namespace OpenPool {
[AddComponentMenu("OpenPool/Wireframe/GL Drawer Base")]
public abstract class GLDrawerBase : MonoBehaviour {
	[SerializeField]
	bool isPost = true;
	
	void OnEnable() {
		GLDrawerCamera.Camera.AddDrawer(this, isPost);
	}
	
	void OnDisable() {
		GLDrawerCamera.Camera.RemoveDrawer(this, isPost);
	}
	
	public void Draw (Matrix4x4 camMatrix)
	{
		if (!this.enabled) {
			return;
		}
		
		GL.PushMatrix ();
		GL.MultMatrix (camMatrix);
		GL.MultMatrix (transform.localToWorldMatrix);
		OnDraw ();
		GL.PopMatrix ();
	}
	
	/// <summary>
	/// override this method to Draw GL
	/// </summary>
	protected abstract void OnDraw ();
}
}