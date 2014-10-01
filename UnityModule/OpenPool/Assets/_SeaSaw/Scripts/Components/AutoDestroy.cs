using UnityEngine;
using System.Collections;
using System;

namespace Tange {
public class AutoDestroy : MonoBehaviour {
	[SerializeField]
	float livingTime = 1.0f;
	
	public event Action onFinish;
	
	IEnumerator Start() {
		yield return new WaitForSeconds(livingTime);
		Destroy(this.gameObject);
		
		if(onFinish != null) {
			onFinish();
			onFinish = null;
		}
	}
	
	public float LivingTime {
		get {return livingTime;}
	}
}
}