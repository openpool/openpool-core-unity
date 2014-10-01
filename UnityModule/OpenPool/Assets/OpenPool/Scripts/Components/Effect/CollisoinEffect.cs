using UnityEngine;
using System.Collections;

namespace OpenPool.Effect{
[AddComponentMenu("OpenPool/Effect/Collision Effect")]
public class CollisoinEffect : PoolBehaviour {
	
	[SerializeField]
	float time = 1f;
	
	protected override void Initialize ()
	{
		manager.collisionTracker.OnCollision += OnCollision;
		gameObject.SetActive(false);
	}
	
	void OnDestroy() {
		manager.collisionTracker.OnCollision -= OnCollision;
	}
//	
//	void OnEnable() {	
////		OnCollision(1.0f);
//	}
//	
//	void OnDisable() {
//		
//	}
	
	void OnCollision (float level) {
		gameObject.SetActive(false);
		gameObject.SetActive(true);
		StartCoroutine(play());
	}
	
	IEnumerator play() {
		yield return new WaitForSeconds(time);
		gameObject.SetActive(false);
	}
}
}