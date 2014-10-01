using UnityEngine;
using System.Collections;

namespace OpenPool {

[AddComponentMenu("OpenPool/Components/Mouse Draggable")]
[RequireComponent(typeof(Rigidbody))]
public class MouseDraggable : MonoBehaviour {

	[SerializeField]
	[RangeAttribute(0f,1f)]
	float gain = 1.0f;

	Vector3 startPosition;
	Vector3 hitPoint;
	
	void OnMouseDown() {
		startPosition = Input.mousePosition;
		
		RaycastHit hit;
		Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
		if (Physics.Raycast(ray, out hit)) {
			if (hit.rigidbody != null) {
				hitPoint = transform.position - hit.point;
			}
		}
	}
	
	void OnMouseUp() {
		Vector3 endPosition = Input.mousePosition;
		Vector3 diff = endPosition - startPosition;
		diff.z = diff.y;
		diff.y = 0;
		
		Vector3 point = transform.position + hitPoint;
		rigidbody.AddForceAtPosition(diff * gain, point, ForceMode.Force);
	}
}
}