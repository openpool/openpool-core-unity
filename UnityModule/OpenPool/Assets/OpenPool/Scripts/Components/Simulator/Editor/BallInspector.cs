using UnityEngine;
using UnityEditor;
using System.Collections;

namespace OpenPool.Simulator {

[CustomEditor(typeof(Ball))]
[CanEditMultipleObjects]
public class BallInspector : Editor {

	Ball _target;

	void OnEnable() {
		_target = target as Ball;
	}

	new void OnInspectorGUI() {
		DrawDefaultInspector ();
	}

	protected virtual void OnSceneGUI() {
		Vector3 pos = _target.transform.position;
		Handles.Label(pos, "[Ball] " + _target.ballNumber);
	}
	
}
}