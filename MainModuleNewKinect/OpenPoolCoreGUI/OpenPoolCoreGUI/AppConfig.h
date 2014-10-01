#pragma once
#include <cliext/vector>
#include "cvRectManagedWrapper.h"

public ref class AppConfig
{
public:

	AppConfig(){;}

	int ThreshNearValue;
	int ThreshFarValue;
	int BlobMinValue; 
	int BlobMaxValue; 
	int AntiNoiseValue;
	int BallSmoothingValue;
	int PreviousBallDistanceThresholdValue;

	int rect0x;
	int rect0y;
	int rect0width;
	int rect0height;
};

