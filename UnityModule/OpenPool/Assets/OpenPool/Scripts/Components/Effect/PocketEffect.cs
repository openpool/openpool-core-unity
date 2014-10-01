using UnityEngine;
using System.Collections;

namespace OpenPool.Effect {
[AddComponentMenu("OpenPool/Effect/Pocket Effect")]
public class PocketEffect : PoolBehaviour {
	
	public enum ID {
		Num0,Num1,Num2,Num3,Num4,Num5
	}
	
	[SerializeField]
	ID number;
	
	[SerializeField]
	GameObject effect;
	
	protected override void Initialize () {
		manager.pocketTracker.OnPocket += OnPocket;
	}
	
	void OnDisable() {
		manager.pocketTracker.OnPocket -= OnPocket;
	}
	
	void OnPocket (int pocketID, int ballID) {
		if(pocketID == (int)number) {
			StartCoroutine(ShowEffect());
		}
	}
	
	IEnumerator ShowEffect() {
		GameObject go = InstantiateChild(effect);
		yield return new WaitForSeconds(6f);
		Destroy(go);
	}

}
}