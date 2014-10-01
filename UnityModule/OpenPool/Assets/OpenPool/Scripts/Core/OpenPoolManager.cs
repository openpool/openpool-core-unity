using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Linq;
using OSC;


namespace OpenPool {
[AddComponentMenu("")] // hidden
public class OpenPoolManager : MonoBehaviour {
#region singleton
	static OpenPoolManager _instance;
	public static OpenPoolManager instance {
		get {return _instance;}	
	}
#endregion

#region properties	
	
	[SerializeField]
	Transform marker00;
	
	[SerializeField]
	Transform marker11;
	
	OSCManager oscManager;
	Dictionary<string,AbstractTracker> trackers;
	IPEndPoint sendEndPort = new IPEndPoint(IPAddress.Parse("127.0.0.1"), Config.OSC_PORT); // "localhost" does not recognize OSX native
#endregion

#region life cycle
	void Awake () {
		_instance = this;
		
		// assign tracker
		trackers = new Dictionary<string, AbstractTracker>();
		trackers.Add(Config.OSC_ADDRESS_BALL, new BallTracker(Config.BALL_MAX_COUNT));
		trackers.Add(Config.OSC_ADDRESS_POCKET, new PocketTracker());
		trackers.Add(Config.OSC_ADDRESS_COLLISION, new CollisionTracker());
		trackers.Add(Config.OSC_ADDRESS_CUE, new CueTracker());
		trackers.Add(Config.OSC_ADDRESS_CALIBRATION, new CaliblationTracker());
		
		oscManager = OSCManager.instance;
		oscManager.LocalPort = Config.OSC_PORT;
	}
	
	IEnumerator Start() {
		// add debug draw
		OpenPoolDebugDrawer debugDrawer = PoolBehaviour.GetOrAddComponent<OpenPoolDebugDrawer>(gameObject);
		foreach(var tracker in trackers.Values) {
			debugDrawer.AddTracker(tracker);
		}
		yield return new WaitForSeconds(1.0f);
		calibrationTraker.Notify();
	}
	
	void OnEnable() {
		oscManager.OnMessage += OnOscMessage;
		trackers.Values.ToList().ForEach(i => i.OnEnable());
	}
	
	void OnDisable() {
		oscManager.OnMessage -= OnOscMessage;
		trackers.Values.ToList().ForEach(i => i.OnDisable());
	}
	
	public Vector3 ScreenToWorld(Vector2 screen) {
		Vector3 p = new Vector3();
		p.x = Mathf.Lerp(marker00.position.x, marker11.position.x, screen.x);
		p.z = Mathf.Lerp(marker00.position.z, marker11.position.z, screen.y);
		return p;
	}
	
	public Vector2 WorldToScreen(Vector3 world) {
		Vector2 s = new Vector2();
		s.x = Mathf.InverseLerp(marker00.position.x, marker11.position.x, world.x);
		s.y = Mathf.InverseLerp(marker00.position.z, marker11.position.z, world.z);
		return s;
	}
	
#endregion	

#region private methods
	
	void OnOscMessage (OSCMessage msg) {
		if(msg.Address == Config.OSC_ADDRESS_TICK) {
			foreach(var tracker in trackers.Values) {
				tracker.OnTick();
			}
		}
		else {
			trackers[msg.Address].Update(msg);
		}
	}
	
	 
#endregion

#region public
	public void SendOSCMessage(OSCPacket packet) {
		oscManager.SendPacket(packet, sendEndPort);
	}
	
	public BallTracker ballTracker {
		get {return (BallTracker) trackers[Config.OSC_ADDRESS_BALL];}
	}
	
	public PocketTracker pocketTracker {
		get {return (PocketTracker) trackers[Config.OSC_ADDRESS_POCKET];}
	}
	
	public CollisionTracker collisionTracker {
		get {return (CollisionTracker) trackers[Config.OSC_ADDRESS_COLLISION];}
	}
	
	public CaliblationTracker calibrationTraker {
		get {return (CaliblationTracker) trackers[Config.OSC_ADDRESS_CALIBRATION];}
	}
	
	
	
#endregion

}
}