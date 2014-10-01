using UnityEngine;
using System.Collections.Generic;

namespace OpenPool {

[AddComponentMenu("OpenPool/Core/Debug Drawer")]
public class OpenPoolDebugDrawer : GLDrawerBase {

	protected OpenPoolManager manager;
	protected List<AbstractTracker> trackers;
	
	void Awake() {
		trackers = new List<AbstractTracker>();
	}
	
	void Start() {
		manager = OpenPoolManager.instance;
	}
	
	public void AddTracker(AbstractTracker tracker) {
		trackers.Add(tracker);
	}
	
	public void RemoveTracker(AbstractTracker tracker) {
		trackers.Remove(tracker);
	}
	
	protected override void OnDraw () {
		foreach(AbstractTracker tracker in trackers) {
			tracker.DrawDebug();
		}
	}
	
	
}
}