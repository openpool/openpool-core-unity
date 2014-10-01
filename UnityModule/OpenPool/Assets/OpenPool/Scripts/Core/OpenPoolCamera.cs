using UnityEngine;
using System.Collections;

namespace OpenPool {
	[RequireComponent(typeof(Camera))]
	[AddComponentMenu("OpenPool/Core/Open Pool Camera")]
	public class OpenPoolCamera : PoolBehaviour {
		
//		Camera _camera;
		
		protected override void Initialize ()
		{
//			_camera = camera;
			manager.calibrationTraker.OnChange += OnCalibrationChange;	
		}
		
		void OnDisable() {
			manager.calibrationTraker.OnChange -= OnCalibrationChange;
		}
		
		void OnCalibrationChange (Vector3 pos, Vector3 rot, Rect rect)
		{
			Transform t = transform;
			t.localPosition = pos;
			t.localEulerAngles = rot;
			
//			_camera.rect = rect;
		}
		
	}
}
