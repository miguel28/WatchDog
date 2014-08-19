/*
 *  Controls.cpp
 *  MKGLibrary
 *
 *  Created by Miguel Silva on 24/10/13.
 *  Copyright 2013 ITCJ. All rights reserved.
 *
 */

#include "Controls.h"

Controls::Controls()
{
	InitialTimePulse = 0.0f;
	IncrementTimePulse = 0.0f;
	CamMoving = false;
	SequenceInit = false;
#ifdef WIN32
	Joy1 = new MK_Joystick(0,12);
	Joy2 = new MK_Joystick(1,12);
	XAxis = 0;
	YAxis = 1;
	WAxis = 2;
	ZAxis = 3;
#else
	Joy = new MK_Joystick(0,24);
	XAxis = 2;
	YAxis = 3;
	WAxis = 0;
	ZAxis = 1;
	XAxis2 = 6;
	YAxis2 = 7;
	WAxis2 = 4;
	ZAxis2 = 5;
#endif
	SolidGrid = true;
	TakeDistance = false;
	Laser = false;
	PulseCounter = 60;
}

Controls::~Controls()
{
#ifdef WIN32
	delete Joy1;
	delete Joy2;
#else
	delete Joy;
#endif	
}

void Controls::CheckVel(int Axis)
{
#ifdef WIN32
	char TurboButton = Joy1->ButtonHeld(8);
#else
	char TurboButton = Joy->ButtonHeld(8);
#endif
	
	if(Axis<0)Axis *= -1;
	
	if(GetKeyHeld('X') || TurboButton )
		MainMotorsVelocity = SPEED2;
	else
	{
		if(MovingLeft || MovingRight) MainMotorsVelocity = SPEED2;
		else MainMotorsVelocity = SPEED1;
	}
}

void Controls::CheckPWM()
{
	if(!SequenceInit)
	{
		InitialTimePulse = glfwGetTime();
		IncrementTimePulse = InitialTimePulse + (0.2);
		CamMoving = true;
		SequenceInit = true;
	}
	
	if(SequenceInit && CamMoving && glfwGetTime()>IncrementTimePulse)
	{
		InitialTimePulse = glfwGetTime();
		IncrementTimePulse = InitialTimePulse + (0.05);
		CamMoving = false;
	}
	
	if(SequenceInit && !CamMoving && glfwGetTime()>IncrementTimePulse)
	{
		SequenceInit = false;
	}
}

void Controls::CheckPulse(char Move)
{
	if(Move != HAT_CENTERED)
	{
		PulseCounter = 0;
		PulseID = Move;
	}
	
	if(PulseCounter<PULSEWIDTH)
		PulseCounter++;
	else 
	{
		PulseID = HAT_CENTERED;
		PulseCounter = 60;
	}
	
}

void Controls::UpdateMainMotorsControls()
{
#ifdef WIN32 
	if(GetKeyHeld(KEY_UP) || Joy1->GetAxis(YAxis)<-20000 || Joy1->GetHatNewPress(0) == HAT_UP || PulseID==HAT_UP)
	{
		CheckPulse(Joy1->GetHatNewPress(0));
		
		MovingForward=true;
		if(PulseCounter<PULSEWIDTH)
			CheckVel(30000);
		else
			CheckVel(Joy1->GetAxis(YAxis));
	}
	else if(GetKeyHeld(KEY_DOWN) || Joy1->GetAxis(YAxis) > 20000 || Joy1->GetHatNewPress(0) == HAT_DOWN || PulseID==HAT_DOWN)
	{
		CheckPulse(Joy1->GetHatNewPress(0));
		
		MovingBackward=true;
		if(PulseCounter<PULSEWIDTH)
			CheckVel(30000);
		else
			CheckVel(Joy1->GetAxis(YAxis));
	}
	else if(GetKeyHeld(KEY_LEFT) || Joy1->GetAxis(XAxis) <  -20000 || Joy1->GetHatNewPress(0) == HAT_LEFT || PulseID==HAT_LEFT)
	{
		CheckPulse(Joy1->GetHatNewPress(0));
		
		MovingLeft=true;
		if(PulseCounter<PULSEWIDTH)
			CheckVel(30000);
		else
			CheckVel(Joy1->GetAxis(XAxis));
	}
	else if(GetKeyHeld(KEY_RIGHT) || Joy1->GetAxis(XAxis) >  20000 || Joy1->GetHatNewPress(0) == HAT_RIGHT || PulseID==HAT_RIGHT)
	{
		CheckPulse(Joy1->GetHatNewPress(0));
		
		MovingRight=true;
		if(PulseCounter<PULSEWIDTH)
			CheckVel(30000);
		else
			CheckVel(Joy1->GetAxis(XAxis));
	}
	
#else
	if(GetKeyHeld(KEY_UP) || Joy->GetAxis(YAxis)<-20000 || Joy->GetHatNewPress(0) == HAT_UP || PulseID==HAT_UP)
	{
		CheckPulse(Joy->GetHatNewPress(0));

		MovingForward=true;
		if(PulseCounter<PULSEWIDTH)
			CheckVel(30000);
		else
			CheckVel(Joy->GetAxis(YAxis));
	}
	else if(GetKeyHeld(KEY_DOWN) || Joy->GetAxis(YAxis) > 20000 || Joy->GetHatNewPress(0) == HAT_DOWN || PulseID==HAT_DOWN)
	{
		CheckPulse(Joy->GetHatNewPress(0));
		
		MovingBackward=true;
		if(PulseCounter<PULSEWIDTH)
			CheckVel(30000);
		else
			CheckVel(Joy->GetAxis(YAxis));
	}
	else if(GetKeyHeld(KEY_LEFT) || Joy->GetAxis(XAxis) <  -20000 || Joy->GetHatNewPress(0) == HAT_LEFT || PulseID==HAT_LEFT)
	{
		CheckPulse(Joy->GetHatNewPress(0));
		
		MovingLeft=true;
		if(PulseCounter<PULSEWIDTH)
			CheckVel(30000);
		else
			CheckVel(Joy->GetAxis(XAxis));
	}
	else if(GetKeyHeld(KEY_RIGHT) || Joy->GetAxis(XAxis) >  20000 || Joy->GetHatNewPress(0) == HAT_RIGHT || PulseID==HAT_RIGHT)
	{
		CheckPulse(Joy->GetHatNewPress(0));
		
		MovingRight=true;
		if(PulseCounter<PULSEWIDTH)
			CheckVel(30000);
		else
			CheckVel(Joy->GetAxis(XAxis));
	}	
#endif
}

void Controls::UpdateGripperControls()
{
#ifdef WIN32
	MovingGripperUp = GetKeyHeld('Q')  || Joy1->ButtonHeld(1) || Joy2->ButtonHeld(1);
	MovingGripperDown = GetKeyHeld('A')  || Joy1->ButtonHeld(3) || Joy2->ButtonHeld(3);
	MovingGripperOpen = GetKeyHeld('S')  || Joy1->ButtonHeld(2) || Joy2->ButtonHeld(2);
	MovingGripperClose = GetKeyHeld('D')  || Joy1->ButtonHeld(4) || Joy2->ButtonHeld(4);
#else
	MovingGripperUp = GetKeyHeld('Q')  || Joy->ButtonHeld(1) || Joy->ButtonHeld(13);
	MovingGripperDown = GetKeyHeld('A')  || Joy->ButtonHeld(3) || Joy->ButtonHeld(15);
	MovingGripperOpen = GetKeyHeld('S')  || Joy->ButtonHeld(2) || Joy->ButtonHeld(14);
	MovingGripperClose = GetKeyHeld('D')  || Joy->ButtonHeld(4) || Joy->ButtonHeld(16);
#endif
}

void Controls::UpdateCamControls()
{
	CheckPWM();
	
#ifdef WIN32
	if(GetKeyHeld('M') || Joy1->ButtonHeld(12) || Joy2->ButtonHeld(12))
		CamButton = 1;
	else CamButton = 0;
	
	if(GetKeyHeld('T') || Joy1->GetAxis(WAxis) <  -20000 || Joy2->GetAxis(WAxis) <  -20000)
	{
		MovingCamUp = CamMoving;
	}
	else if(GetKeyHeld('G') || Joy1->GetAxis(WAxis) >  20000 || Joy2->GetAxis(WAxis) >  20000)
	{
		MovingCamDown = CamMoving;
	} 
	else if(GetKeyHeld('F') || Joy1->GetAxis(ZAxis) <  -20000 || Joy2->GetAxis(ZAxis) <  -20000)
	{
		MovingCamLeft = CamMoving;
	}
	else if(GetKeyHeld('H') || Joy1->GetAxis(ZAxis) >  20000 || Joy2->GetAxis(ZAxis) >  20000)
	{
		MovingCamRight = CamMoving;
	}
#else
	if(GetKeyHeld('M') || Joy->ButtonHeld(12) || Joy->ButtonHeld(24))
		CamButton = 1;
	else CamButton = 0;
	
	if(GetKeyHeld('T') || Joy->GetAxis(WAxis) <  -20000 || Joy->GetAxis(WAxis2) <  -20000)
	{
		MovingCamUp = CamMoving;
	}
	else if(GetKeyHeld('G') || Joy->GetAxis(WAxis) >  20000 || Joy->GetAxis(WAxis2) >  20000)
	{
		MovingCamDown = CamMoving;
	} 
	else if(GetKeyHeld('F') || Joy->GetAxis(ZAxis) <  -20000 || Joy->GetAxis(ZAxis2) <  -20000)
	{
		MovingCamLeft = CamMoving;
	}
	else if(GetKeyHeld('H') || Joy->GetAxis(ZAxis) >  20000 || Joy->GetAxis(ZAxis2) >  20000)
	{
		MovingCamRight = CamMoving;
	}
#endif
}

void Controls::UpdateSystemControls()
{
#ifdef WIN32
	Laser = GetKeyNewpress('L')==1 || Joy2-> ButtonHeld(10)==0x01; 
	
	TakeDistance = GetKeyHeld(KEY_SPACE)==1 || Joy2-> ButtonHeld(8)==0x01;
	if(GetKeyNewpress('B') || Joy2->ButtonNewpress(7))
	{
		if(SolidGrid)
			SolidGrid = false;
		else 
			SolidGrid = true;
	}
	
#else
	Laser = GetKeyNewpress('L')==1 || Joy-> ButtonHeld(22)==0x01; 
	
	TakeDistance = GetKeyHeld(KEY_SPACE)==1 || Joy-> ButtonHeld(20)==0x01;
	if(GetKeyNewpress('B') || Joy->ButtonNewpress(19))
	{
		if(SolidGrid)
			SolidGrid = false;
		else 
			SolidGrid = true;
	}
#endif
}

void Controls::Clear()
{
	MovingForward=false;
	MovingBackward=false;
	MovingLeft=false;
	MovingRight=false;
	
	MovingGripperUp=false;
	MovingGripperDown=false;
	MovingGripperOpen=false;
	MovingGripperClose=false;
	
	MovingCamUp=false;
	MovingCamDown=false;
	MovingCamLeft=false;
	MovingCamRight=false;
}

void Controls::SetMode(char mode)
{
	
}

void Controls::Update()
{
#ifdef WIN32
	Joy1->Update();
	Joy1->Update();
#else
	Joy->Update();
#endif
	Clear();
	UpdateMainMotorsControls();
	UpdateGripperControls();
	UpdateCamControls();
	UpdateSystemControls();
}
 
 
