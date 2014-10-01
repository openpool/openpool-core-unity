using UnityEngine;

namespace OpenPool {
public abstract class AbstractTracker {
	
	public abstract void Update(OSC.OSCMessage msg);
	
	public virtual void OnTick() {
		// overide this
	}
	
	public virtual void DrawDebug() {
		// override this
	}
	
	public virtual void OnEnable() {
		// override this
	}
	
	public virtual void OnDisable() {
		// override this
	}
}
}
