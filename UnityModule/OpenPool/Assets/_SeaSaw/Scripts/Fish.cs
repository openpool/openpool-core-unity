using UnityEngine;
using System.Collections;
using OpenPool;

namespace Tange {
	[AddComponentMenu("Tange/Fish")]
	public class Fish : PoolBehaviour {
		static readonly int _SPEED = Animator.StringToHash("speed");
		static readonly int _ACTION = Animator.StringToHash("action");
	
		Animator animator;
		
		int currentAction = 0;
		
		[SerializeField]
		int collisionAction = -1;
		
		[SerializeField]
		int pocketAction = -1;
		
		protected override void Initialize () {
			animator = GetComponentInChildren<Animator>();
			if(manager != null) {
				manager.collisionTracker.OnCollision += OnCollision;
				manager.pocketTracker.OnPocket += OnPocket;
			}
		}

		void OnDisable() {
			if(manager != null) {
				manager.collisionTracker.OnCollision -= OnCollision;
				manager.pocketTracker.OnPocket -= OnPocket;
			}
		}

		void OnCollision (float level) {
			if(currentAction == 0 && collisionAction > 0) {
				action = collisionAction;
			}
		}
		
		void OnPocket (int pocketID, int ballID) {
			if(currentAction == 0 && pocketAction > 0) {
				action = pocketAction;
			}
		}
		
		public float speed {
			set { 
//				StopAllCoroutines();
				animator.SetFloat(_SPEED, value); 
//				StartCoroutine(backAction(1f));
			}
			get { return animator.GetFloat(_SPEED);}
		}
		
		public int action {
			set {
				currentAction = value;
				StopAllCoroutines();
				animator.SetInteger(_ACTION, value);
				StartCoroutine(backAction(0.1f));
			}
			get { return animator.GetInteger(_ACTION);}
		}
		
		IEnumerator backAction(float time) {
			yield return new WaitForSeconds(time);
//			animator.SetFloat(_SPEED, 0);
			animator.SetInteger(_ACTION, 0);
			currentAction = 0;
		}		
	}
}
