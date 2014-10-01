using UnityEngine;
using System.Collections;

[AddComponentMenu("UnitySteer/Vehicle/Vehicle Look-At Direction (Custom)")]
public class VehicleLookAtDirection : MonoBehaviour {
	
	[SerializeField]
	Vector3 _targetAngle;
	
	[SerializeField]
	bool _isLocal;
	
	[SerializeField]
	float _smoothSpeed = 1f;
	
	Transform _t; // transform cache
	
#region life cycle
	void Start() {
		_t = this.transform;
	}
	
	void Update() {
		
		Quaternion euler = Quaternion.Euler(_targetAngle);
		if(_isLocal) {
			_t.localRotation = Quaternion.Slerp(_t.localRotation, euler, Time.deltaTime * _smoothSpeed);
		}
		else {
			_t.rotation = Quaternion.Slerp(_t.rotation, euler, Time.deltaTime * _smoothSpeed);
		}
		
	}
#endregion	

#region properties
	public Vector3 targetAngle {
		get {return _targetAngle;}
		set {_targetAngle = value;}
	}
	
	public bool isLocal {
		get {return _isLocal;}
		set {_isLocal = value;} 
	}
	
	public float smoothSpeed  {
		get {return this._smoothSpeed;}
		set {_smoothSpeed = value;}
	}
#endregion
	
}
