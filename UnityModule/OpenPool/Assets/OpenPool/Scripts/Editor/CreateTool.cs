using UnityEngine;
using UnityEditor;
using System.Collections;

/// <summary>
/// Editor Utility tool.
/// author koki ibukuro
/// </summary>
public class CreateTool : ScriptableObject {
	
	static GameObject _CreateChild (string name)
	{
		GameObject go = new GameObject (name);
		Transform t = go.transform;
		t.parent = Selection.activeTransform;
		t.localScale = Vector3.one;
		t.localPosition = Vector3.zero;
		t.localRotation = Quaternion.identity;
		
		Transform parent = Selection.activeTransform;
		if (parent != null) {
			go.layer = parent.gameObject.layer;
		}
		Selection.activeGameObject = go;
		
		EditorUtility.SetDirty(go);
		return go;
	}
	
	/// <summary>
	/// Create selected object's child. 
	/// SHORTCUT KEY [cmd shift N]
	/// </summary>
	/// <returns>
	/// created gameobject
	/// </returns>
	[MenuItem("OpenPool/Tools/Create/Blank Child %#n")]
	public static GameObject CreateChild ()
	{
		return _CreateChild ("GameObject");
	}
	
	[MenuItem("OpenPool/Tools/Create/Wrap Selected %&n")]
	public static GameObject CreateParent ()
	{
		Transform selected = Selection.activeTransform;
		if(selected == null) {
			return null;
		}
		GameObject parent = _CreateChild (selected.name+"Wrapper");
		Transform t = parent.transform;
		t.parent = selected.parent;
		t.localScale = Vector3.one;
		selected.parent = t;
		return parent;
	}
		
	/// <summary>
	/// Delete all player preferences.
	/// </summary>
	[MenuItem ("OpenPool/Tools/Delete/Delete PlayerPref")]
	public static void DeletePlayerPref ()
	{
		PlayerPrefs.DeleteAll ();
		Debug.LogWarning ("deleted");
	}
	
	
}