using UnityEngine;
using System.Collections;

namespace Tange {

public class BallFx : MonoBehaviour {
	
	bool show = false;
	
	Transform _transform;
	SpriteRenderer _spriteRenderer;
	
	void OnEnable() {
		_transform = transform;
		_spriteRenderer = GetComponentInChildren<SpriteRenderer>();
		SetShow(true);
	}
	
	void OnDisable() {
		SetShow(false);
	}
	
	void Update() {
		Color color = _spriteRenderer.color;
		float a = color.a - 0.05f;
		color.a = (a>0) ? a : 0;;
		_spriteRenderer.color = color;
	}
	
	public void SetShow(bool isShow) {
		if(isShow) {
			Color color = _spriteRenderer.color;
			color.a = 1;
			_spriteRenderer.color = color;
			show = true;
		}
		else {
			if(!show) return;
			show = false;
		}
	}
	
	public void SetShow(bool isShow, Vector3 position) {
		_transform.position = position;
		SetShow(isShow);
	}
	
}
}