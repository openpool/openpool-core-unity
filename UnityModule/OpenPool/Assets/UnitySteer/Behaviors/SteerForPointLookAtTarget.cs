using UnityEngine;
using System.Collections;
using UnitySteer;

[AddComponentMenu("UnitySteer/Steer/... for Point and Look-At Target")]
public class SteerForPointLookAtTarget : SteerForPoint {
	
	[SerializeField]
	Transform _lookTarget;
	
	[SerializeField]
	float _rotateTime = 0.2f;
	
	Transform _transform;
	
	public Transform LookTarget {
		get { return _lookTarget; }
		set { _lookTarget = value; }
	}
	
	public float RotateTime {
		get { return _rotateTime; }
		set { _rotateTime = value; }
	}
	
	void OnEnable() {
		_transform = transform;
	}
	
	void Update() {
		if(_lookTarget == null) {
			return;
		}
		
		var difference = this.TargetPoint - Vehicle.Position;
		
        float d = difference.sqrMagnitude;
        if (d <= Vehicle.SquaredArrivalRadius) {
        	Quaternion rot = Quaternion.LookRotation(_lookTarget.position - _transform.position);
			_transform.rotation = Quaternion.Slerp(transform.rotation, rot, Time.deltaTime * 1/_rotateTime);		
        }
	}
	
	protected override Vector3 CalculateForce()
	{
		return base.CalculateForce();
	}
}
