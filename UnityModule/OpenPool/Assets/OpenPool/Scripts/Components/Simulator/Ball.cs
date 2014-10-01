using UnityEngine;
using System.Collections;
using OSC;

namespace OpenPool.Simulator {

[AddComponentMenu("OpenPool/Simulator/Ball")]
public class Ball : PoolBehaviour {
	
	public enum Number {
		White,Num1,Num2,Num3,Num4,Num5,Num6,Num7,Num8,Num9,Num10,Num11,Num12,Num13,Num14,Num15
	}
		
	[SerializeField]
	Ball.Number number;
	
	Transform _transform;
	
#region life cycle
	
	protected override void Initialize (){	
	}
	
	void OnEnable() {
		_transform = transform;
	}
	
	void Update() {
		if(manager==null) {
			return;
		}
		
		// send "/ball"
		int frame = Time.frameCount % 99;
		Vector2 screen = manager.WorldToScreen(_transform.position);
		manager.SendOSCMessage(OSCMessage.Create(Config.OSC_ADDRESS_BALL, frame, (double)screen.x, (double)screen.y));
	}
	
	void OnCollisionEnter(Collision collision) {
		if(collision.gameObject.name == "tableCollider") { // TODO ...
			return;
		}
		if (collision.relativeVelocity.sqrMagnitude > 2) {
			// send "/collision"
			manager.SendOSCMessage(OSCMessage.Create(Config.OSC_ADDRESS_COLLISION, collision.relativeVelocity.sqrMagnitude));
		}
	}
#endregion
	
	public Ball.Number ballNumber {
		get {return number;}
	}
}
}
