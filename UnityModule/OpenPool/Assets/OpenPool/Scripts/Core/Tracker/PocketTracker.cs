using UnityEngine;
using System.Collections;
using OSC;

namespace OpenPool {

public class PocketTracker : AbstractTracker {
	public delegate void PocketDelegate(int pocketID, int ballID);
	
	public event PocketDelegate OnPocket; 

	public PocketTracker() {
		
	}
	
	public override void Update(OSCMessage msg) {
		
		int pocket;
		int ball;
		
		if(msg.Values.Count >= 6) {
			// new api
			ball = 0; // not tracked
			pocket = 0;
			
			for(int i=0; i<6; i++) {
				if((int)msg.Values[i] >= 1)	{
					pocket = i;
					break;
				}
			}
		}
		else {
			// legacy api
			pocket = (int) msg.Values[0];
			ball = (int) msg.Values[1];
		}
		
		if(OnPocket != null) {
			OnPocket(pocket, ball);
		}
	}
	
}
}
