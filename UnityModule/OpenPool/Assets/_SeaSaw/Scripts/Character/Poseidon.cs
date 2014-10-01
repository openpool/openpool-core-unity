using UnityEngine;
using System.Collections;
using OpenPool;

namespace Tange {

[RequireComponent(typeof(RandomnessSteerForPoint))]
public class Poseidon : PoolBehaviour {
	readonly int _KEY_SPEED = Animator.StringToHash("speed");
	
	[SerializeField]
	Transform musclePosition;
	
	[SerializeField]
	AutoDestroy musclePrefab;
	
	[SerializeField]
	float speedScale = 100f;
	
	RandomnessSteerForPoint randomSteer;
	SteerForPoint steerForPoint;
	AutonomousVehicle vehicle;
	Animator animator;
	
	bool isAnimating;
	
	override protected void Initialize() {
		randomSteer = GetComponent<RandomnessSteerForPoint>();
		steerForPoint = GetComponent<SteerForPoint>();
		vehicle = GetComponent<AutonomousVehicle>();
		animator = GetComponentInChildren<Animator>();
		
		if(manager != null) {
			manager.pocketTracker.OnPocket += OnPocket;
		}
	}
	
	void Update() {
		float speed = vehicle.Speed * speedScale;
		animator.SetFloat(_KEY_SPEED, speed);
	}
	
	void OnDisable() {
		if(manager != null) {
			manager.pocketTracker.OnPocket -= OnPocket;
		}
	}

	void OnPocket (int pocketID, int ballID) {
		if(!isAnimating) {
			StartCoroutine(_OnPocket());
		}
	}
	
	IEnumerator _OnPocket() {
		this.isAnimating = true;
		
		randomSteer.isUpdate = false;
		steerForPoint.TargetPoint = new Vector3(0, -3, 10);
		yield return new WaitForSeconds(4.0f);
		
		AutoDestroy ad = Instantiate(musclePrefab) as AutoDestroy;
		
		Transform t = ad.transform;
		t.parent = musclePosition;
		t.localPosition = Vector3.zero;
		t.localRotation = Quaternion.identity;
		t.localScale = Vector3.one;
		
		bool onfinish = false;
		
		ad.onFinish += delegate() {
			onfinish = true;
		};
		
		if(!onfinish) {
			yield return null;
		}
		
		randomSteer.isUpdate = true;
		yield return new WaitForSeconds(15.0f);
		this.isAnimating = false;
	}
	
	
}
}