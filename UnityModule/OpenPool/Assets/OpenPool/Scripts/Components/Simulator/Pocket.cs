using UnityEngine;
using System.Collections;
using OSC;

namespace OpenPool.Simulator {
[AddComponentMenu("OpenPool/Simulator/Pocket")]
public class Pocket : PoolBehaviour {
	
	public enum ID {
		Num0,Num1,Num2,Num3,Num4,Num5
	}
	
	[SerializeField]
	Pocket.ID number;
	
	protected override void Initialize ()
		{
			
		}
	
	void OnTriggerEnter(Collider other) {
		
		Ball ball = other.GetComponent<Ball>();
		if(ball != null) {
			
			// (int)pocket1 (int)pocket2 (int)pocket3 (int)pocket4 (int)pocket5 (int)pocket6
			OSCMessage msg = new OSCMessage(Config.OSC_ADDRESS_POCKET);
			
			for(int i=0; i<6; ++i) {
				if((int)number == i) {
					msg.Append(1);
				}
				else {
					msg.Append(0);
				}
			}
			
			manager.SendOSCMessage(msg);
//			manager.SendOSCMessage(OSCMessage.Create(Config.OSC_ADDRESS_POCKET, (int) pocketNumber, (int) ball.ballNumber));
		}
	}
	
	public Pocket.ID pocketNumber {
		get {return number;}
	}
}
}