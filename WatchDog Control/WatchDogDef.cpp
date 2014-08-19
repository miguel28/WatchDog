/*
 *  WatchDogDef.cpp
 *  OpenGLEX
 *
 *  Created by mike on 3/1/13.
 *  Copyright 2013 MiGuEl Inc. All rights reserved.
 *
 */

#include "WatchDogDef.h"

double calcFPS(double theTimeInterval)
{
	static double t0Value       = glfwGetTime(); // Set the initial time to now
	static int    fpsFrameCount = 0;             // Set the initial FPS frame count to 0
	static double fps           = 0.0;           // Set the initial FPS value to 0.0
	double currentTime = glfwGetTime();
	
	if (theTimeInterval < 0.1)
	{
		theTimeInterval = 0.1;
	}
	if (theTimeInterval > 10.0)
	{
		theTimeInterval = 10.0;
	}

	if ((currentTime - t0Value) > theTimeInterval)
	{
		fps = (double)fpsFrameCount / (currentTime - t0Value);

		fpsFrameCount = 0;
		t0Value = glfwGetTime();
	}
	else
	{
		fpsFrameCount++;
	}
	
	return fps;
}