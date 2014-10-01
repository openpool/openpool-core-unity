using UnityEngine;
using System.Collections;

namespace OSC {
public class OSCManager : MonoBehaviour {

#region delegate
	public delegate void OscMessageDelegate(OSCMessage message);
#endregion
	
#region singleton
	static OSCManager _instance;
	public static OSCManager instance {
		get {
			if(_instance == null) {
				GameObject go = new GameObject(typeof(OSCManager).ToString());
				_instance = go.AddComponent<OSCManager>();
				DontDestroyOnLoad(go);
			}
			return _instance;
		}
	}
#endregion

#region member

	[SerializeField]
	int localPort = 7000;
	
	OSCServer server;
	
	public event OscMessageDelegate OnMessage;
#endregion
	
#region life cycle
	
	void Awake() {
		if(_instance == null) {
			_instance = this;
		}
		DontDestroyOnLoad(_instance.gameObject);
	}
	
	void OnEnable() {
		server = new OSCServer();
		server.Start(localPort);
	}
	
	void OnDisable() {
		server.Stop();
	}
	
	void Update() {
		// get osc
		OSCMessage[] msgs = server.Update();
		foreach(OSCMessage msg in msgs) {
			if(OnMessage != null) {
				OnMessage(msg);
			}
		}
	}
#endregion

#region public
	public int LocalPort {
		get {return localPort;}
		set {localPort = value;}
	}
	
	public void SendPacket(OSCPacket packet, System.Net.IPEndPoint endPoint) {
		server.Send(packet, endPoint);
	}
	
	public void SendPacket(OSCPacket packet, string hostname, int port) {
		server.Send(packet, hostname, port);
	}
#endregion

}
}