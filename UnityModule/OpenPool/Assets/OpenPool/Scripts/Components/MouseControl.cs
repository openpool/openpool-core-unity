using UnityEngine;
using System.Collections;

namespace OpenPool {
[AddComponentMenu("OpenPool/Components/MouseControl")]
public class MouseControl : MonoBehaviour {
	Transform _transform;
	
	Vector2 mousePosition;

	void Start () {
		_transform = transform;
	}
	
	void Update () {
		Vector2 current = Input.mousePosition;
		if(Input.GetMouseButton(0)) {
			Vector2 diff = current - mousePosition;
			_transform.Rotate(diff.y, diff.x, 0, Space.World);
		}
		mousePosition = Input.mousePosition;
	}
}
}