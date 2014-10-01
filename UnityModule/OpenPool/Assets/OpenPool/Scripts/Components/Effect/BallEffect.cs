using UnityEngine;
using System.Collections;

namespace OpenPool.Effect {

[AddComponentMenu("OpenPool/Effect/Ball Effect")]
public class BallEffect : MonoBehaviour {
	[SerializeField]
	BallTracker.Ball ball;
	
	public BallTracker.Ball Ball {
		get {return ball;}
		set {ball = value;}
	}
}
}