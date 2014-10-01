using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using OpenPool;

namespace Tange {

public class BallFxController : PoolBehaviour {
	[SerializeField]
	BallFx ballPrefab;
	
	[SerializeField]
	int ballMax = 21;
	
	BallTracker ballTracker;
	List<BallFx> ballFx;
	
	bool initialized = false;
	
	protected override void Initialize () {
		ballTracker = manager.ballTracker;
		
		ballFx = new List<BallFx>();
		StartCoroutine(_initialize());
	}
	
	IEnumerator _initialize() {
		for(int i=0; i<ballMax; ++i) {
			BallFx fx = this.InstantiateChild<BallFx>(ballPrefab);
			ballFx.Add(fx);
			fx.SetShow(false);
			yield return null;
			yield return null;
		}
		initialized = true;
	}
	
	
	void Update() {
		if(!initialized) {
			return;
		}
		
		BallTracker.Ball[] balls = ballTracker.ballList;
		int num = balls.Length;
		
		if(num <= ballMax) {
			for(int i=0; i<num; ++i) {
				BallTracker.Ball ball = balls[i];
				if(ball.isTracked) {
					Vector3 target_point = manager.ScreenToWorld(ball.position);
					Debug.Log("blll:"+target_point);
					target_point.y = 0;
					ballFx[i].SetShow(true, target_point);
				}
				else {
//					ballFx[i].SetShow(false);
				}
				
			}
		}
		
	}
}
}