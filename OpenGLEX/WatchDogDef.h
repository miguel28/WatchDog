/*
 *  WatchDogDef.h
 *  OpenGLEX
 *
 *  Created by mike on 2/9/13.
 *  Copyright 2013 MiGuEl Inc. All rights reserved.
 *
 */

#ifdef WIN32
#include "gl\glut.h"			// Glut (Free-Glut on Windows)
#endif

// Mac OS X
#ifdef __APPLE__
#include <GLUT/glut.h>
// Just ignore sleep on Apple
#define Sleep(x)
#endif

#include <iostream>

#define Enconding 0xC0

#define SPEED_IPS 9.0 /// Inches per second
#define SPEED_FPS SPEED_IPS/12.0 /// Inches per second
#define W_GPS 50.0 /// Grades per second
#define FPS 152.0 /// Frames Per Second
#define SPEED_FOOTPERFRAME (SPEED_FPS/FPS) //// Foots per Frame
#define SPEED_RADIAL (W_GPS/FPS) /// Grades º per second

enum
{
	STOP,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	FORWARD_UP,
	FORWARD_DOWN,
	BACKWARD_UP,
	BACKWARD_DOWN,
	OPEN_GRIPPER,
	CLOSE_GRIPPER,
	PISTON
};

typedef struct
{
	float X,Y,Angle;
	bool Opened_Clamp;
	float GripperHeight,GripperOpening;
	float Speed_IPS, Speed_FootPS, Angle_GPS, FramesPS, Speed_FootPerFrame, SpeedAngle;
	float UpDownGripperLimit, OpenCloseGripperLimit, OpenCloseGripperAd, UpDownGripperAd;
	float GripperDeltaOp, GripperDeltaUp;
	int UseShadder;
	
}_WatchDog;

class PhysicalCalcs
{
public:
	PhysicalCalcs();
	void FrameTiming();
	float GetFPS();
	int GetTimeRuning();
private:
	int Frame,CurrentTime,Timebase;
	float CurrentFPS;
};