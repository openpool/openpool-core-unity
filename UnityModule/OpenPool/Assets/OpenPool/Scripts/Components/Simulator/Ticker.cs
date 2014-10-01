using UnityEngine;
using System.Collections;
using OSC;

namespace OpenPool.Simulator {
[AddComponentMenu("OpenPool/Simulator/Ticker")]
public class Ticker : PoolBehaviour {
	
	protected override void Initialize () {
	}
	
	void Update() {
		if(Time.frameCount % 2 == 0) { // TODO fixed fps tick
			manager.SendOSCMessage(OSCMessage.Create(Config.OSC_ADDRESS_TICK, Time.time));
		}
	}
}
}