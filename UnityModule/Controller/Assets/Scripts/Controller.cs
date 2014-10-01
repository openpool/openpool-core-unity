using UnityEngine;
using System.Collections;
using OSC;

public class Controller : MonoBehaviour {
	
	Vector3 position;
	Vector3 _position;
	
	Vector3 rotation;
	Vector3 _rotation;
	
	Rect trimarea = new Rect(0,0,1,1);
	Rect _trimarea;
	
	string ipAddress = "127.0.0.1";
	
	OSCManager manager;
	
	void Start() {
		manager = OSCManager.instance;
		manager.LocalPort = 9000;
	}
	
	void OnEnable() {
		SaveData data = SaveData.Load();
		data.GetData(ref ipAddress, ref position, ref rotation, ref trimarea);
	}
	
	void OnDisable() {
		SaveData data = new SaveData();
		data.SetData(ipAddress, position, rotation, trimarea);
		SaveData.Save(data);
	}
	
	void Update () {
		bool changed = false;
		
		if(_position != position) {
			_position = position;
			changed = true;
		}
		if(_rotation != rotation) {
			_rotation = rotation;
			changed = true;
		}
		if(_trimarea != trimarea) {
			_trimarea = trimarea;
			changed = true;
		}
		if(changed) {
			SendOSC(position, rotation, trimarea);
		}
	}
	
	void OnGUI() {
		GUILayout.BeginArea(new Rect(20, 20, Screen.width-40, Screen.height-40));
		ipAddress = GUILayout.TextField(ipAddress, GUILayout.MinHeight(30f));
		DrawVecotor3Slider("position", ref position, -0.8f, 0.8f);
		DrawVecotor3Slider("rotation", ref rotation, -2f, 2f);
		DrawRectSlider("rect", ref trimarea);
		GUILayout.EndArea();
	}
	
	void DrawVecotor3Slider(string title, ref Vector3 v, float min, float max) {
		GUILayout.Label(title);
		
		GUILayout.BeginHorizontal();
		GUILayout.Label(string.Format("X {0:F3}", v.x), GUILayout.MaxWidth(50));
		v.x = GUILayout.HorizontalSlider (v.x, min, max, GUILayout.MinHeight(50f));
		GUILayout.EndHorizontal();
		
		GUILayout.BeginHorizontal();
		GUILayout.Label(string.Format("Y {0:F3}", v.y), GUILayout.MaxWidth(50));
		v.y = GUILayout.HorizontalSlider (v.y, min, max, GUILayout.MinHeight(50f));
		GUILayout.EndHorizontal();
		
		GUILayout.BeginHorizontal();
		GUILayout.Label(string.Format("Z {0:F3}", v.z), GUILayout.MaxWidth(50));
		v.z = GUILayout.HorizontalSlider (v.z, min, max, GUILayout.MinHeight(50f));
		GUILayout.EndHorizontal();
	}
	
	void DrawRectSlider(string title, ref Rect r) {
		float min, max;
		min = 0f;
		max = 0.5f;
		GUILayout.Label(title);
		
		GUILayout.BeginHorizontal();
		GUILayout.Label(string.Format("X {0:F3}", r.x), GUILayout.MaxWidth(50));
		r.x = GUILayout.HorizontalSlider (r.x, min, max, GUILayout.MinHeight(50f));
		GUILayout.EndHorizontal();
		
		GUILayout.BeginHorizontal();
		GUILayout.Label(string.Format("Y {0:F3}", r.y), GUILayout.MaxWidth(50));
		r.y = GUILayout.HorizontalSlider (r.y, min, max, GUILayout.MinHeight(50f));
		GUILayout.EndHorizontal();
		
		min = 0.5f;
		max = 1f;
		GUILayout.BeginHorizontal();
		GUILayout.Label(string.Format("W {0:F3}", r.width), GUILayout.MaxWidth(50));
		r.width = GUILayout.HorizontalSlider (r.width, min, max, GUILayout.MinHeight(50f));
		GUILayout.EndHorizontal();
		
		GUILayout.BeginHorizontal();
		GUILayout.Label(string.Format("H {0:F3}", r.height), GUILayout.MaxWidth(50));
		r.height = GUILayout.HorizontalSlider (r.height, min, max, GUILayout.MinHeight(50f));
		GUILayout.EndHorizontal();
	}
	
	void SendOSC(Vector3 pos, Vector3 rot, Rect rect) {
		OSCManager manager = OSCManager.instance;
		OSCMessage msg = OSCMessage.Create("/calibration", pos.x, pos.y, pos.z, rot.x, rot.y, rot.z, rect.x, rect.y, rect.width, rect.height);
		
		manager.SendPacket(msg, ipAddress, 7000);
	}
}
