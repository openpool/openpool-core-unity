using UnityEngine;
using System.Collections;

namespace OpenPool {
public class CollisionTracker : AbstractTracker {
	
	public delegate void CollisonDelegate(float level);
	
	public event CollisonDelegate OnCollision;
	
	bool ticked = true;
	
	public override void Update (OSC.OSCMessage msg)
	{
		if(!ticked) {
			return;
		}
		ticked = false;
		
		float level = (float) msg.Values[0];
		if(OnCollision != null) {
			OnCollision(level);
		}
	}
	
	public override void OnTick ()
	{
		ticked = true;
	}
}
}