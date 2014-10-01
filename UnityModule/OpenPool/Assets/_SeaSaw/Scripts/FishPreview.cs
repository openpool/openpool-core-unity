using UnityEngine;
using System.Collections;
using System.Linq;

namespace Tange {
[AddComponentMenu("")] // hide
public class FishPreview : MonoBehaviour {
	
	[SerializeField]
	Fish[] fishes;
	
	void OnGUI() {
		if(DrawButton("speed 1.0")) {
			fishes.ToList().ForEach(i => i.speed = 1f);
		}
		if(DrawButton("speed 2.0")) {
			fishes.ToList().ForEach(i => i.speed = 2f);
		}
		
		if(DrawButton("action 1")) {
			fishes.ToList().ForEach(i => i.action = 1);
			BackAction();
		}
		if(DrawButton("action 2")) {
			fishes.ToList().ForEach(i => i.action = 2);
			BackAction();
		}
		if(DrawButton("action 3")) {
			fishes.ToList().ForEach(i => i.action = 3);
			BackAction();
		}
	}
	
	bool DrawButton(string label) {
		return GUILayout.Button(label, GUILayout.MinWidth(100), GUILayout.MinHeight(50));
	}
	
	void BackAction() {
		StartCoroutine(_BackAction(0.1f));
	}
	
	IEnumerator _BackAction(float time) {
		yield return new WaitForSeconds(time);
		fishes.ToList().ForEach(i => i.action = 0);
	}
	
}
}