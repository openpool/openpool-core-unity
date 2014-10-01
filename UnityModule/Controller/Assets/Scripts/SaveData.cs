using UnityEngine;
using LitJson;

[System.Serializable]
public class SaveData {
	
	public string address;
	
	public double pos_x;
	public double pos_y;
	public double pos_z;
	
	public double rot_x;
	public double rot_y;
	public double rot_z;

	public double trim_x;
	public double trim_y;
	public double trim_w;
	public double trim_h;
	
	
	static public SaveData Load() {
		string json = PlayerPrefs.GetString(typeof(SaveData).ToString(), "");
		Debug.Log("load:"+json);
		SaveData data;
		if(string.IsNullOrEmpty(json)) {
			data = new SaveData();
			data.trim_w = 1;
			data.trim_h = 1;
		}
		else {
			data = JsonMapper.ToObject<SaveData>(json);
		}
		
		if(string.IsNullOrEmpty(data.address)) {
			data.address = "127.0.0.1";
		}
		return data;
	}
	
	static public void Save(SaveData data) {
		string json = JsonMapper.ToJson(data);
		Debug.Log("save:"+json);
		PlayerPrefs.SetString(typeof(SaveData).ToString(), json);
		PlayerPrefs.Save();
	}
	
	
	public void SetData(string ipaddress, Vector3 position, Vector3 rotation, Rect rect) {
		address = ipaddress;
		pos_x = position.x;
		pos_y = position.y;
		pos_z = position.z;
		
		rot_x = rotation.x;
		rot_y = rotation.y;
		rot_z = rotation.z;
		
		trim_x = rect.x;
		trim_y = rect.y;
		trim_w = rect.width;
		trim_h = rect.height;
	}
	
	public void GetData(ref string ipaddress, ref Vector3 position, ref Vector3 rotation, ref Rect rect) {
		ipaddress = address;
		
		position.x = (float) pos_x;
		position.y = (float) pos_y;
		position.z = (float) pos_z;
		
		rotation.x = (float) rot_x;
		rotation.y = (float) rot_y;
		rotation.z = (float) rot_z;
		
		rect.x = (float) trim_x;
		rect.y = (float) trim_y;
		rect.width = (float) trim_w;
		rect.height = (float) trim_h;
	}
}
