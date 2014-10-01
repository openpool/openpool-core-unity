using UnityEngine;
using System.Collections;

namespace OpenPool {
[AddComponentMenu("")] // hidden
public abstract class PoolBehaviour : MonoBehaviour {
	
	protected OpenPoolManager manager;
	
	void Start () {
		manager = OpenPoolManager.instance;
		Initialize();
	}
	
	abstract protected void Initialize();
	
	
	
#region utilities methods
	
	protected T GetOrAddComponent<T>() where T : Component {
		T comp = GetComponent<T>();
		if(comp == null) {
			comp = gameObject.AddComponent<T>();
		}
		return comp;
	}
	
	public static T GetOrAddComponent<T>(GameObject go) where T : Component {
		T comp = go.GetComponent<T>();
		if(comp == null) {
			comp = go.AddComponent<T>();
		}
		return comp;
	}
	
	/// <summary>
	/// Instantiate prefab at child.
	/// </summary>
	/// <returns>The child.</returns>
	/// <param name="prefab">Prefab.</param>
	protected GameObject InstantiateChild(GameObject prefab) {
		Transform parent = this.transform;
		GameObject go = Instantiate(prefab) as GameObject;
		go.layer = gameObject.layer;
		
		Transform t = go.transform;
		t.parent = parent;
		t.localPosition = Vector3.zero;
		t.localRotation = Quaternion.identity;
		t.localScale = Vector3.one;
		return go;
	}
	
	protected T InstantiateChild<T>(T prefab) where T : Component {
		GameObject go = InstantiateChild(prefab.gameObject);
		return go.GetComponent<T>();
	}
	
#endregion
}
}
