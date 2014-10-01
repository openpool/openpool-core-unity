using UnityEngine;
using UnityEditor;
using System.Collections;

namespace OpenPool.Simulator {

[CustomEditor(typeof(Pocket))]
[CanEditMultipleObjects]
public class PocketInspector : Editor {

	Pocket _target;

	void OnEnable() {
		_target = target as Pocket;
	}

	new void OnInspectorGUI() {
		DrawDefaultInspector ();
	}

	protected virtual void OnSceneGUI() {
		Vector3 pos = _target.transform.position;
		Handles.Label(pos, "[POCKET] " + _target.pocketNumber);
	}
}
}
