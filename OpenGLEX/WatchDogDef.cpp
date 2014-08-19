/*
 *  WatchDogDef.cpp
 *  OpenGLEX
 *
 *  Created by mike on 3/1/13.
 *  Copyright 2013 MiGuEl Inc. All rights reserved.
 *
 */

#include "WatchDogDef.h"


PhysicalCalcs::PhysicalCalcs()
{
	Frame = CurrentTime = Timebase = 0;
}

void PhysicalCalcs::FrameTiming()
{
	Frame++;
	CurrentTime=glutGet(GLUT_ELAPSED_TIME);
	if (CurrentTime - Timebase > 1000) {
		//sprintf(s,"FPS:%4.2f",Frame*1000.0/(CurrentTime-Timebase));
		CurrentFPS = Frame*1000.0/(CurrentTime-Timebase);
		Timebase = CurrentTime;
		CurrentTime = 0;
		Frame = 0;
	}
}

float PhysicalCalcs::GetFPS()
{
	return CurrentFPS;
}

int PhysicalCalcs::GetTimeRuning()
{
	return (glutGet(GLUT_ELAPSED_TIME)/1000);	
}
