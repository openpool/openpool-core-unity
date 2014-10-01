using UnityEngine;
using System.Collections;
using System.Linq;

namespace OpenPool {
public class BallTracker : AbstractTracker {
#region strust
	public class Ball {
		static int TOTAL_ID = 0;
		static int FAZZY_FRAMES = 5;
		
		public int fuzzy;
		public int id;
		public Vector2 position;
		public Vector2 velocity;
		
		public Ball(bool tracked) {
			id = TOTAL_ID++;
			fuzzy = FAZZY_FRAMES-1;
			position = new Vector2(Random.value, Random.value);
			velocity = Vector2.zero;
		}
		
		public void Update(Vector2 new_pos) {
			fuzzy = FAZZY_FRAMES;
			velocity = new_pos - position;
			position = new_pos;
		}
		
		public void NextFrame() {
			fuzzy--;
			if (fuzzy == 0) {
				id = TOTAL_ID++;
				velocity = Vector2.zero;
			}
		}
		
		public bool isTracked {
			get {return fuzzy > 0;}
		}
		
		public bool isUpdatedInThisFrame {
			get {return fuzzy >= FAZZY_FRAMES;}
		}
		
		public override string ToString () {
			return string.Format ("[Ball] ID:{0} fuzzy:{1} pos:{2} vel:{3}", id, fuzzy, position, velocity);
		}
	}
#endregion
	
	int currentFrame;
	Ball[] balls;
	
	/// <summary>
	/// Initializes a new instance of the <see cref="OpenPool.BallTracker"/> class.
	/// </summary>
	/// <param name="maxcount">Maxcount.</param>
	public BallTracker(int maxcount) {
		balls = new Ball[maxcount];
		for(int i=0; i<balls.Length; ++i) {
			balls[i] = new Ball(false);
		}
	}
	
	public override void OnTick ()
	{
		for(int i=0; i<balls.Length; ++i) {
			balls[i].NextFrame();
		}
	}
	
	public override void Update(OSC.OSCMessage msg) {
//		Debug.Log(msg.ToString());
		int frame = (int)msg.Values[0];
		if(msg.Values[1] is System.Double) {
			System.Double x = (System.Double) msg.Values[1];
			System.Double y = (System.Double) msg.Values[2];
			Update(frame, new Vector2((float)x, (float)y));
		}
		else {
			Update(frame, new Vector2((float)msg.Values[1], (float)msg.Values[2]));
		}
		
	}
	
	void Update(int frame, Vector2 position) {
		// find nearest ball
		MatchNearestBall(ref position);
		
		if(currentFrame != frame) {
			// next frame
			currentFrame = frame;
			
		}
	}
	
	public override void DrawDebug ()
	{	
		GL.Begin (GL.LINES);
		GL.Color (Color.green);
		
		OpenPoolManager manager = OpenPoolManager.instance;
		
		foreach(Ball ball in balls) {
			if(ball.isTracked) {
				Vector3 from = manager.ScreenToWorld(ball.position);
				Vector3 direction = new Vector3(ball.velocity.x, 0, -ball.velocity.y) * 50f;
				
				// cube
				GLUtils.DrawCube(from, Config.BALL_RADIUS);
				// velocity
				GL.Vertex(from);
				GL.Vertex(from+direction);
			}
		}
		GL.End ();	
	}
	
	void MatchNearestBall(ref Vector2 position) {
		int i=0, len=balls.Length;
		int nearest = -1;
		float distance = float.MaxValue;
		float sqrmag;
		
		for(i=0; i<len; ++i) {
			if(balls[i].isUpdatedInThisFrame) {
				continue;
			}
			sqrmag = (balls[i].position - position).sqrMagnitude;
			if(sqrmag < distance) {
				distance = sqrmag;
				nearest = i;
			}
		}
		
		if(nearest < 0) {
			return;
		}
		
		Ball ball = balls[nearest];
		ball.Update(position);
		balls[nearest] = ball;
	}
	
	public Ball[] ballList {
		get {
			return balls;
		}
	}
	
	public Ball GetNearestBall(Vector3 position) {
		
		OpenPoolManager manager = OpenPoolManager.instance;
		
		Ball nearest_ball = balls[0];
		float nearest_distance = float.MaxValue;
		
		
		for(int i=1; i<balls.Length; ++i) {
			Ball ball = balls[i];
			if(ball.isTracked) {
				Vector3 pos = manager.ScreenToWorld(ball.position);
				float d = Vector3.Distance(position, pos);
				if(nearest_distance > d) {
					nearest_distance = d;
					nearest_ball = ball;
				}
			}
		}
		
		if(nearest_ball.isTracked) {
			return nearest_ball;
		}
		else {
			return null;
		}
	}
	
	public Ball GetMostMovingBall(float limit=0.3f) {
		Ball fastest_ball = balls[0];
		float max_magnitude = 0f;
		
		
		for(int i=1; i<balls.Length; ++i) {
			Ball ball = balls[i];
			if(ball.isTracked) {
				float mag = ball.velocity.sqrMagnitude;
				if(max_magnitude < mag && mag < limit) {
					max_magnitude = mag;
					fastest_ball = ball;
				}
			}
		}
		
		if(max_magnitude > 0) {
			return fastest_ball;
		}
		else {
			return null;
		}
	}
	
	
}
}
