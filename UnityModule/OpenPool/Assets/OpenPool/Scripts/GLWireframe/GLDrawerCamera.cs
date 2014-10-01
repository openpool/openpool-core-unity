using UnityEngine;
using System.Collections.Generic;

namespace OpenPool {
[RequireComponent(typeof(Camera))]
[AddComponentMenu("OpenPool/Wireframe/GL Drawer Camera")]
public class GLDrawerCamera : MonoBehaviour {
	
	[SerializeField]
	Material mat;
	
	[SerializeField]
	List<GLDrawerBase> preDrawers;
	
	[SerializeField]
	List<GLDrawerBase> postDrawers;
	
	[SerializeField]
	int antiAliasing = 2;
	
	[SerializeField]
	bool isWireframe = true;
	
#region static (not singleton)
	public static GLDrawerCamera Camera {
		get;
		protected set;
	}
#endregion

#region
	Camera _camera;
#endregion
	
#region life cycle
	void Awake ()
	{
		GLDrawerCamera.Camera = this;
	}
	
	void Start ()
	{
		QualitySettings.antiAliasing = antiAliasing;
		_camera = this.camera;
	}

	void OnPreRender ()
	{
		if(isWireframe) {
			GL.wireframe = true;
		}
		PreDrawGL();
	}

	void OnPostRender ()
	{
		if(isWireframe) {
			GL.wireframe = false;
		}
		PostDrawGL();
	}
	
	void PreDrawGL() {
		
		GL.PushMatrix ();
		mat.SetPass (0);
		
		Matrix4x4 mtx = _camera.cameraToWorldMatrix;
		foreach (var drawer in preDrawers) {
			drawer.Draw (mtx);
		}
		
		GL.PopMatrix ();
	}
	
	void PostDrawGL() {
		
		GL.PushMatrix ();
		mat.SetPass (0);
		
		Matrix4x4 mtx = _camera.cameraToWorldMatrix;
		foreach (var drawer in postDrawers) {
			drawer.Draw (mtx);
		}
		
		GL.PopMatrix ();
	}
#endregion

#region public methods
	public void AddDrawer (GLDrawerBase drawer, bool post=true)
	{
		if(post) {
			postDrawers.Add (drawer);
		}
		else {
			preDrawers.Add(drawer);
		}
		
	}
	
	public void RemoveDrawer (GLDrawerBase drawer, bool post=true)
	{
		if(post) {
			postDrawers.Remove (drawer);
		}
		else {
			preDrawers.Remove(drawer);
		}
		
	}
#endregion
	
}
}