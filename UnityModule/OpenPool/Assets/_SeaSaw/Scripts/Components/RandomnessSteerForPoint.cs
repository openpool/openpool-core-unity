using UnityEngine;
using System.Collections;

namespace Tange {
[RequireComponent(typeof(SteerForPoint))]
public class RandomnessSteerForPoint : MonoBehaviour {
	[SerializeField]
	float updateRate = 1.0f;
	
	[SerializeField]
	Vector3 randomScale = Vector3.one;
	
	[SerializeField]
	Vector3 offset;
	
	[SerializeField]
	float randomSpeed = 0.1f;
	
	[SerializeField]
	bool update;
	
	SteerForPoint steer;
	
	void Start () {
		steer = GetComponent<SteerForPoint>();
		InvokeRepeating("Randomize", updateRate, updateRate);
	}
	
	void Randomize() {
		if(!update) {
			return;
		}
		Vector3 v = SmoothRandom.GetVector3(randomSpeed);
		v.Scale(randomScale);
		steer.TargetPoint = v + offset;
	}
	
	public bool isUpdate {
		set {this.update = value;}
		get {return this.update;}
	}
}
}