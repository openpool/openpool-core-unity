using UnityEngine;
using System.Collections;
using UnitySteer;

[AddComponentMenu("UnitySteer/Steer/... for Path Point (Custom)")]
public class SteerForPathPoint : SteerForPoint {
	[SerializeField]
	IPathway _pathway;
	
	[SerializeField]
	float rate;
	
	[SerializeField]
	float speed;
	
	public IPathway Path {
		get { return _pathway;}
		set { _pathway = value; }
	}
	
	public float Rate {
		get { return rate;}
		set {rate = value; }
	}
	
	public float Speed {
		get { return speed; }
		set { speed = value; }
	}
		
	protected override Vector3 CalculateForce () {
		if(_pathway == null) {
			return Vector3.zero;
		}
		
		Vector3 pos = _pathway.MapPathDistanceToPoint(rate * _pathway.TotalPathLength);
		rate += Time.deltaTime * speed;
		
		if(rate > 1) {
			rate = 0;
		}
		
		this.TargetPoint = pos;	
		this.ConsiderVelocity = false;
		return base.CalculateForce();
		
	}
}
