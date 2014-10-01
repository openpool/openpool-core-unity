using UnityEngine;
using System.Collections;

namespace OpenPool {
public class CalibrationCorner : PoolBehaviour {
	
	public enum Corner {
		TopLeft,
		BottomRight
	}
	
	[SerializeField]
	Corner corner;
	
	protected override void Initialize ()
	{
		manager.calibrationTraker.OnChange += OnCalibrationChange;
	}
	
	void OnDisable() {
		manager.calibrationTraker.OnChange -= OnCalibrationChange;
	}
	
	void OnCalibrationChange (Vector3 pos, Vector3 rot, Rect rect)
	{
		Transform t = transform;
		Camera c = Camera.main;
		
		Vector3 v;
		if(corner == Corner.TopLeft) {
			v = new Vector3(rect.xMin, 1.0f-rect.yMin, c.transform.position.y-t.position.y);
		}
		else {
			v = new Vector3(rect.xMax, 1.0f-rect.yMax, c.transform.position.y-t.position.y);
		}
		
		t.position = c.ViewportToWorldPoint(v);
	}
	
	
}
}