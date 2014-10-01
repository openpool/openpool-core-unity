using UnityEngine;
using System.Collections;
using OpenPool;

namespace Tange {
public class TangeEffectController : PoolBehaviour {
	
	[SerializeField]
	Transform fishContainer;
	
	[SerializeField]
	float timeScale;
	
	[SerializeField]
	[RangeAttribute(0f,1f)]
	float yScale;
	
	BallTracker ballTrakcer;
	SteerForPoint[] fishes;
	
	void OnEnable() {
		fishes = fishContainer.GetComponentsInChildren<SteerForPoint>();
	}
	
	protected override void Initialize () {
		ballTrakcer = manager.ballTracker;
	}
	
	void Update () {
		foreach(var fish in fishes) {
			BallTracker.Ball ball = ballTrakcer.GetNearestBall(fish.transform.position);
			if(ball == null) {
				break;
			}
			Vector3 target_point = manager.ScreenToWorld(ball.position);
			target_point.y = 0;
			
			fish.TargetPoint = target_point;
		}
	}
}

}
