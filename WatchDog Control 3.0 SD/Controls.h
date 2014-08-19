/*
 *  Controls.h
 *  MKGLibrary
 *
 *  Created by Miguel Silva on 24/10/13.
 *  Copyright 2013 ITCJ. All rights reserved.
 *
 */

#ifndef CONTROLS_A_H
#define CONTROLS_A_H

#include "MKGL/MK_GLFWApp.h"

#define PULSEWIDTH 4

enum SpeedList
{
	SPEED1,
	SPEED2,
	SPEED3,
	SPEED4
};

class Controls
{
private:
//#ifdef WIN32 
	MK_Joystick *Joy1;
	MK_Joystick *Joy2;
//#else
    MK_Joystick *Joy;
//#endif
	char Mode;
	char PulseCounter;
	char PulseID;
	short XAxis,YAxis,WAxis,ZAxis;
	short XAxis2,YAxis2,WAxis2,ZAxis2;
	float InitialTimePulse;
	float IncrementTimePulse;
	bool CamMoving;
	bool SequenceInit;
	
	
	int GripPulse;
	bool GripMinipulse;
	
	void CheckVel(int Axis);
	void CheckCamVel(int Axis);
	void CheckPWM();
	void UpdateMainMotorsControls();
	void UpdateGripperControls();
	void UpdateCamControls();
	void UpdateSystemControls();
	void Clear();
	void CheckPulse(char Move);
public:
	Controls();
	~Controls();
	
	int PulseLimitLow, PulseLimitHigh;
	
	char MainMotorsVelocity;
	char CamMotorsVelocity;
	char CamButton;
	
	bool MovingForward;
	bool MovingBackward;
	bool MovingLeft;
	bool MovingRight;
	
	bool MovingGripperUp;
	bool MovingGripperDown;
	bool MovingGripperOpen;
	bool MovingGripperClose;
	
	bool MovingCamUp;
	bool MovingCamDown;
	bool MovingCamLeft;
	bool MovingCamRight;
	
	bool SolidGrid;
	bool TakeDistance;
	bool Laser;
	bool CloseLoopControlSystem;
	
	void SetMode(char mode);
	void Update();
};


#endif
