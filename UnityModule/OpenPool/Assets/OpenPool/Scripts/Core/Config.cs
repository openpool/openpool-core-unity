namespace OpenPool {
public class Config {
	
	public const int OSC_PORT = 7000;
	
	/// <summary>
	/// ball postions <br>
	/// (int)framenumber (float)x (float)y
	/// </summary>
	public const string OSC_ADDRESS_BALL = "/ball";
	
	/// <summary>
	/// tick every farme
	/// </summary>
	public const string OSC_ADDRESS_TICK = "/tick";
	
	/// <summary>
	/// callisions <br>
	/// (float) level
	/// </summary>
	public const string OSC_ADDRESS_COLLISION = "/collision";
	
	/// <summary>
	/// pocket detecter <br>
	/// (int)pocket1 (int)pocket2 (int)pocket3 (int)pocket4 (int)pocket5 (int)pocket6
	/// </summary>
	public const string OSC_ADDRESS_POCKET = "/pocket";
	
	// (not using) cue
	public const string OSC_ADDRESS_CUE = "/cue";
	
	/// <summary>
	/// calibration<br>
	/// (float)positionX, (float)positionY, (float)positionZ, (float)rotationX, (float)rotationY, (float)rotationZ
	/// </summary>
	public const string OSC_ADDRESS_CALIBRATION = "/calibration";
	
	public const float BALL_RADIUS = 0.03f; // meter
	public const int BALL_MAX_COUNT = 20;
}
}
