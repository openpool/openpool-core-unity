using UnityEngine;
using UnitySteer;

[AddComponentMenu("UnitySteer/Steer/... to Follow Ranged (Custom)")]
public class SteerToFollowRanged : SteerToFollow {
	
	[SerializeField]
	Vector3 _randomRange;
	
	Vector3 _offset;
	
	public Vector3 RandomRange {
		get {
			return _randomRange;	
		}
		set {
			_randomRange = value;
			_offset = Vector3.Scale(value,Random.insideUnitSphere);
			if(Vehicle.IsPlanar) {
				_offset.y = 0;
			}
		}
	}
	
	public Vector3 Offset {
		get {
			return _offset;
		}
	}
	

	public new void Start()
	{
		base.Start();
		this.RandomRange = _randomRange;
		
	}

	/// <summary>
	/// Calculates the force to apply to the vehicle to reach a point
	/// </summary>
	/// <returns>
	/// A <see cref="Vector3"/>
	/// </returns>
	protected override Vector3 CalculateForce()
	{
		Vector3 force = Vehicle.GetSeekVector(Target.position + _offset, ConsiderVelocity);
		
		
		var difference = Target.position - Vehicle.Position;
        float d = difference.sqrMagnitude;
        
        if(d < Vehicle.Radar.DetectionRadius) { // use rader radius
        	force *= d / Vehicle.Radar.DetectionRadius;
        }
		
		return force;
	}
}
