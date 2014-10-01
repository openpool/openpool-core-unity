unity module for opennpool-core-unity
===================

# UnityModule/OpenPool

Project Structure

- Assets
	- _SeaSaw: The sample effect that you are using
	- Editor : Used only when you edit
	- OpenPool : OpenPool core
	- Plugins
	- UnitySteer : Libraries for _SeaSaw

### Getting started

Open the file:

	_SeaSaw/Scenes/SeaSaw.unity

and you will the sample effect. 

![image](./Docs/capture1.jpg)

### Creating your own effect

1. Put OpenPoolManager in the Scene

		Assets/OpenPool/Resources/Prefabs/OpenPoolManager.prefab
2. The status of PoolTable is notified as a c# event.
	- In /OpenPool/Scripts/Components/Effect/*, you can find some re-usable effecdts.
	- The simplest one is CollisoinEffect.cs:
				
			protected override void Initialize ()
			{	
				manager.collisionTracker.OnCollision += OnCollision;
			}
			
			void OnCollision (float level) {
				// play effects
			}
	- The position of balls:
		
			BallTracker = OpenPoolManager.instance.ballTracker;
			void Update() {				
				BallTracker.Ball[] balls = ballTracker.ballList;
				
				// play effects				
			}
	
	- Pocket:
	
			protected override void Initialize ()
			{
				manager.instance.pocketTracker.OnPocket += OnPocket;
			}
			
			void OnPocket (int pocketID, int ballID) {
				// play effects
			}
	
	- Collision:
			
			protected override void Initialize ()
			{
				manager.collisionTracker.OnCollision += OnCollision;
			}
			
			void OnCollision (float level) {
				// play effects
			}
	
	- Calibration:
			
			protected override void Initialize ()
			{
				manager.calibrationTraker.OnChange += OnCalibrationChange;
			}
			
			void OnCalibrationChange (Vector3 pos, Vector3 rot, Rect rect)
			{
				// calibration
			}

#### Environment

- Unity 4.5.0

#### Libraries
- [JsonSplitSprite](https://gist.github.com/tsubaki/7500360)   
- [MiniJSON](https://gist.github.com/darktable/1411710)
- [UnitySteer](https://github.com/ricardojmendez/UnitySteer)
- [OSC from reacTIVision](http://reactivision.sourceforge.net/)

#### License

Two different licenses applied as below; please carefully use the code.
- UnityModule/OpenPool/Assets/_SeaSaw : CreativeCommons CC-BY-NC-SA. 
- Everything else in UnityModule/OpenPool/ : GPL ver3. 

See [LICENSE.md](./OpenPool/LICENSE.md)

===================
# UnityModule/OscTest

The test codes for the OSC connection. You need Python.

![image](./Docs/capture2.jpg)

While Unity app is running, use the command:

	cd PathToOSCTest/  
	python OscTest.py
	# python OscTest.py 127.0.0.1 # change ip address

#### Libraries

- [SimpleOSC](http://www.ixi-audio.net/content/body_backyard_python.html)


#### License
GPL ver3. 
See [LICENSE.md](./OscTest/LICENSE.md)

===================
# UnityModule/Controller

The library for calibration. 

![image](./Docs/controller.jpg)

You can configure the parameters below:

- Position (X,Y,Z)
- Rotation (X,Y,Z)
- Rectangle (Trim) (X,Y,W,H)


#### Libraries

- [LitJson](https://github.com/lbv/litjson)


#### License
GPL ver3. 
See [LICENSE.md](./Controller/LICENSE.md)
