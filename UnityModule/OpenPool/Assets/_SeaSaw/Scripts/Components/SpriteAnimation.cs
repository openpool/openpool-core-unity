using UnityEngine;
using System.Collections;
using System.Linq;


namespace Tange {
	[RequireComponent(typeof(SpriteRenderer))]
	public class SpriteAnimation : MonoBehaviour {
	
		public Sprite[] sprites;
		public float fps;
		public bool loop;
		public bool autoSortByName;	
		
		int currentFrame;
		SpriteRenderer spriteRenderer;
		
		void Start() {
			spriteRenderer = this.GetComponent<SpriteRenderer>();
		}
			
		void Update () {
			NextFrame();
		}
		
		void OnValidate() {
			if(autoSortByName) {
				sprites = sprites.OrderBy(sprite => sprite.name).ToArray();
			}
		}
		
		public void NextFrame() {
			currentFrame++;
			if(currentFrame >= sprites.Length) {
				if(loop) {
					currentFrame = 0;
				}
				else {
					currentFrame = sprites.Length-1;
				}
			}
			spriteRenderer.sprite = sprites[currentFrame];
		}
		
	}
}