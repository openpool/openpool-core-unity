using UnityEngine;

namespace OpenPool {
	public class CaliblationTracker : AbstractTracker {
		
		Vector3 position;
		Vector3 rotation;
		Rect rect;
		
		public delegate void ChangeDelegate(Vector3 pos, Vector3 rot, Rect rect);
		
		public event ChangeDelegate OnChange;
		
		public override void Update (OSC.OSCMessage msg) {
			 position.x = (float) msg.Values[0];
			 position.y = (float) msg.Values[1];
			 position.z = (float) msg.Values[2];
			 
			 rotation.x = (float) msg.Values[3];
			 rotation.y = (float) msg.Values[4];
			 rotation.z = (float) msg.Values[5];
			 
			 rect = Rect.MinMaxRect(
			 	(float) msg.Values[6],
			 	(float) msg.Values[7],
			 	(float) msg.Values[8],
			 	(float) msg.Values[9]
			 );
			 
			 Notify();
		}
		
		public override void OnEnable ()
		{
			LoadData();
			Notify();
		}
		
		public override void OnDisable ()
		{
			SaveData();
		}
		
		void SaveData() {
			string data = string.Format("{0},{1},{2},{3},{4},{5},{6},{7},{8},{9}", 
				position.x, position.y, position.z, 
				rotation.x, rotation.y, rotation.z,
				rect.xMin, rect.yMin, rect.xMax, rect.yMax);
//			Debug.Log("saved:"+data);
			PlayerPrefs.SetString(typeof(CaliblationTracker).ToString(), data);
		}
		
		void LoadData() {
			string data = PlayerPrefs.GetString(typeof(CaliblationTracker).ToString(), "0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,1.0");
//			Debug.Log("loaded:"+data);
			string[] splits = data.Split(',');
			
			position.x = float.Parse(splits[0]);
			position.y = float.Parse(splits[1]);
			position.z = float.Parse(splits[2]);
			rotation.x = float.Parse(splits[3]);
			rotation.y = float.Parse(splits[4]);
			rotation.z = float.Parse(splits[5]);
			
			
			 rect = Rect.MinMaxRect(
			 	float.Parse(splits[6]),
			 	float.Parse(splits[7]),
			 	float.Parse(splits[8]),
			 	float.Parse(splits[9])
			 );
			
			Notify();
		}
		
		public void Notify() {
			if(OnChange != null) {
				OnChange(position, rotation, rect);
			}
		}
	}
}