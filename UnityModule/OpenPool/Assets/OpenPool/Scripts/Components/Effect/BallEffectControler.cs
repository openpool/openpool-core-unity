using UnityEngine;
using System.Collections;

namespace OpenPool.Effect {
[AddComponentMenu("OpenPool/Effect/Ball Effect Controller")]
public class BallEffectControler : PoolBehaviour {
	
	[SerializeField]
	BallEffect effectPrefab;
	
	BallTracker tracker;
	
	BallEffect[] ballEffects;
	
	
	
	// cache
	protected override void Initialize ()
	{
		tracker = manager.ballTracker;
		ballEffects = new BallEffect[Config.BALL_MAX_COUNT];
		
		BallTracker.Ball[] ballList = tracker.ballList;
		for(int i=0; i<Config.BALL_MAX_COUNT; i++) {
			ballEffects[i] = this.InstantiateChild<BallEffect>(effectPrefab);
			ballEffects[i].gameObject.SetActive(false);
			ballEffects[i].Ball = ballList[i];
		}
	}
	
	void Update() {
//		foreach(BallTracker.Ball ball in ballList) {
//			
//		}
	}
	
	void OnDrawGizmos() {
		
	}
}
}