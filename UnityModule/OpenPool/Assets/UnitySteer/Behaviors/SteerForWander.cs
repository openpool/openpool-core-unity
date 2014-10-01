using UnityEngine;
using UnitySteer;
using UnitySteer.Helpers;

/// <summary>
/// Steers a vehicle to wander around
/// </summary>
[AddComponentMenu("UnitySteer/Steer/... for Wander")]
public class SteerForWander : Steering
{
	#region Private fields
	float _wanderSide = 0;
	float _wanderUp = 0;
	
	[SerializeField]
	float _maxLatitudeSide = 2;
	[SerializeField]
	float _maxLatitudeUp = 2;
    
    /// <summary>
    /// The smooth rate on which the random walk values are blended. Set to 1 for no smoothing.
    /// </summary>
    [RangeAttribute(0.0f, 1.0f)]
    [SerializeField]
    float _smoothRate = 0.05f;
    
    [SerializeField]
	bool _considerVelocity = true;
	
	#endregion
	
	#region Public properties
	/// <summary>
	/// Maximum latitude to use for the random scalar walk on the side
	/// </summary>
	public float MaxLatitudeSide {
		get {
			return this._maxLatitudeSide;
		}
		set {
			_maxLatitudeSide = value;
		}
	}

	/// <summary>
	/// Maximum latitude to use for the random scalar walk on the up vector
	/// </summary>
	public float MaxLatitudeUp {
		get {
			return this._maxLatitudeUp;
		}
		set {
			_maxLatitudeUp = value;
		}
	}
	
	/// <summary>
	/// Should the vehicle's velocity be considered in the seek calculations?
	/// </summary>
	/// <remarks>
	/// If true, the vehicle will slow down as it approaches its target
	/// </remarks>
 		public bool ConsiderVelocity
	{
		get { return _considerVelocity; }
		set { _considerVelocity = value; }
	}
	#endregion

	
	protected override Vector3 CalculateForce ()
	{
		float speed = Vehicle.MaxSpeed;

		// random walk WanderSide and WanderUp between -1 and +1        
        var randomSide = OpenSteerUtility.scalarRandomWalk(_wanderSide, speed, -_maxLatitudeSide, _maxLatitudeSide);
        var randomUp = OpenSteerUtility.scalarRandomWalk(_wanderUp, speed, -_maxLatitudeUp, _maxLatitudeUp);
		_wanderSide = OpenSteerUtility.blendIntoAccumulator(_smoothRate, randomSide, _wanderSide);
        _wanderUp = OpenSteerUtility.blendIntoAccumulator(_smoothRate, randomUp, _wanderUp);
        
        
		Vector3	 result = (Vehicle.Transform.right * _wanderSide) + (Vehicle.Transform.up * _wanderUp) + Vehicle.Transform.forward;
		if(ConsiderVelocity) {
			result -= Vehicle.Velocity;
		}
		return result;
	}
	
}

