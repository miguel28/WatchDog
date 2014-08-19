/*
 *  WatchDogDef.cpp
 *  OpenGLEX
 *
 *  Created by mike on 3/1/13.
 *  Copyright 2013 MiGuEl Inc. All rights reserved.
 *
 */

#include "WatchDog.h"

#include "Controls.h"

Controls WControls;

WatchDogClass::WatchDogClass()
{
	USB = new USBInterface();
	USB->EnumerateHIDs();
    USB->HIDOpen(0x3995,0x0001);	
    USB->HIDDescription();	
	USB->SendOutputPort(0xFF);

#ifdef WIN32	
	Joy1 = new MK_Joystick(0,12);
	Joy2 = new MK_Joystick(1,12);
#else
	Joy = new MK_Joystick(0,24);
#endif
	
	Model = new MK_ModelOBJ();
	MdlGripper[0] = new MK_ModelOBJ();
	MdlGripper[1] = new MK_ModelOBJ();
	MdlGripper[2] = new MK_ModelOBJ();
	
	Transparent = false;
	Position.X = 0.0f;
	Position.Y = 0.0f;
	Position.Z = 0.0f;
	Angle = 0.0f;
	MainMotorsSpeed = 0;
	QuequeUpdate = 0.0f;
	
	tEncoder1 = Encoder1 = 32768;
	tEncoder2 = Encoder2 = 32768;
	
	FronCollision = false;
	BackCollision = false;
	
	CamButton=0;
	
	CollisionFront1 = Vector3f(-0.25,0.0f,0.8f);
	CollisionFront2 = Vector3f(0.25,0.0f,0.8f);
	CollisionBack1 = Vector3f(-0.25,0.0f,-0.8f);
	CollisionBack2 = Vector3f(0.25,0.0f,-0.8f);
	
	CurrentTime = glfwGetTime();
	LastTime = glfwGetTime();
	DiffTime = 0.0f;
	
	SolidSystem = false;
	CanTakeDistance = false;
	LaserON = false;
	IsOnline = false;
	
	ReadConfig();
}

WatchDogClass::~WatchDogClass()
{
	delete Model;
	delete MdlGripper[0];
	delete MdlGripper[1];
	delete MdlGripper[2];
	delete USB;
#ifdef WIN32	
	//delete Joy1;
	//delete Joy2;
#else
	//delete Joy;
#endif
}

void WatchDogClass::ReadConfig()
{
	FILE* ConfigFile = fopen ("Config.txt", "rb");
	int size;
	fseek(ConfigFile, 0, SEEK_END); // seek to end of file
	size = ftell(ConfigFile); // get current file pointer
	char* ConfigString = new char[size];
	rewind(ConfigFile);
	fread(ConfigString, 1, size, ConfigFile);
	fclose(ConfigFile);
	
	
	cout << ConfigString << endl;
	
	int tMoveStepFor, tMoveStepBack;
	int tAngleStepLeft, tAngleStepRight;
	int tSpeed1, tSpeed2;
	int tAngle1;
	int tPulseHigh, tPulseLow;
	sscanf(ConfigString, ">%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		   &tMoveStepFor,&tMoveStepBack,&tAngleStepLeft,&tAngleStepRight,
		   &tSpeed1,&tSpeed2,&tAngle1,&tPulseLow,&tPulseHigh,&UseShadder);
	
	MoveStepFor = tMoveStepFor/(1000.0f * 12.0f);
	MoveStepBack = tMoveStepBack/(1000.0f * 12.0f);
	AngleStepLeft = tAngleStepLeft/(1000.0f);
	AngleStepRight = tAngleStepRight/(1000.0f);
	Speed1 = tSpeed1/(1000.0f * 12.0f);
	Speed2 = tSpeed2/(1000.0f * 12.0f);
	Angle1 = tAngle1/1000.0f;
	
	
	WControls.PulseLimitLow = tPulseLow;
	WControls.PulseLimitHigh = tPulseHigh;
}

void WatchDogClass::LoadModels()
{
	Model->LoadFile((char*)"Models/Watchdog/watchdog2.obj");
	Model->Scale(W_LENGHT,W_HEIGHT,W_WIDTH);
	MdlGripper[0]->LoadFile((char*)"Models/Watchdog/basegripper.obj");
	MdlGripper[1]->LoadFile((char*)"Models/Watchdog/gripper1.obj");
	MdlGripper[2]->LoadFile((char*)"Models/Watchdog/gripper2.obj");
}

void WatchDogClass::SendInstruction()
{
	char MainInstruction;
	char SlaveInstruction;
	
	switch(MainMotorsMove)
	{
		case FORWARD:
			switch(OtherMove)
			{
				case UP_GRIPPER:
					MainInstruction = FORWARD_UP_GRIPPER;
					break;
				case DOWN_GRIPPER:
					MainInstruction = FORWARD_DOWN_GRIPPER;
					break;
				case OPEN_GRIPPER:
					MainInstruction = FORWARD_OPEN_GRIPPER;
					break;
				case CLOSE_GRIPPER:
					MainInstruction = FORWARD_CLOSE_GRIPPER;
					break;
				default:
					MainInstruction = FORWARD;
					break;
			}
			break;
			
		case BACKWARD:
			switch(OtherMove)
			{
				case UP_GRIPPER:
					MainInstruction = BACKWARD_UP_GRIPPER;
					break;
				case DOWN_GRIPPER:
					MainInstruction = BACKWARD_DOWN_GRIPPER;
					break;
				case OPEN_GRIPPER:
					MainInstruction = BACKWARD_OPEN_GRIPPER;
					break;
				case CLOSE_GRIPPER:
					MainInstruction = BACKWARD_CLOSE_GRIPPER;
					break;
				default:
					MainInstruction = BACKWARD;
					break;
			}
			break;
		
		case LEFT:
			switch(OtherMove)
			{
				case UP_GRIPPER:
					MainInstruction = LEFT_UP_GRIPPER;
					break;
				case DOWN_GRIPPER:
					MainInstruction = LEFT_DOWN_GRIPPER;
					break;
				case OPEN_GRIPPER:
					MainInstruction = LEFT_OPEN_GRIPPER;
					break;
				case CLOSE_GRIPPER:
					MainInstruction = LEFT_CLOSE_GRIPPER;
					break;
				default:
					MainInstruction = LEFT;
					break;
			
			}
			break;
		
		case RIGHT:
			switch(OtherMove)
			{
				case UP_GRIPPER:
					MainInstruction = RIGHT_UP_GRIPPER;
					break;
				case DOWN_GRIPPER:
					MainInstruction = RIGHT_DOWN_GRIPPER;
					break;
				case OPEN_GRIPPER:
					MainInstruction = RIGHT_OPEN_GRIPPER;
					break;
				case CLOSE_GRIPPER:
					MainInstruction = RIGHT_CLOSE_GRIPPER;
					break;
				default:
					MainInstruction = RIGHT;
					break;
			}
			break;
		
		case STOP:
			MainInstruction = OtherMove;
			
			break;
	}
	MainInstruction |=(MainMotorsSpeed<<5);
	MainInstruction &=0x7F;
	
	SlaveInstruction = SlaveMove;
	
	if(QuequeUpdate == 0.0f || QuequeUpdate<glfwGetTime())
	{
		QuequeUpdate = glfwGetTime() + 0.3333f;
		SlaveInstruction += UPDATE;
	}
	
	SlaveInstruction |= 0x80; 
	
	USB->SetByte(0, MainInstruction);
	USB->SetByte(1, SlaveInstruction);
	USB->SetByte(2,  WControls.CamButton);
	USB->SendBuffer();
	
	USB->ReciveBuffer();
	
	Encoder1 = ((USB->GetByte(0)<<8) | USB->GetByte(1)) & 0xffff;
	Encoder2 = ((USB->GetByte(2)<<8) | USB->GetByte(3)) & 0xffff;
	tDistance = ((USB->GetByte(5)<<8) | USB->GetByte(4)) & 0xffff;
	Distance = (float)((tDistance-35)/(10.0f*2.54f*12.0f));
	if(Distance<0.0f)Distance = 0.0f;
	
	//USB->PrintBufferIN();
	//USB->PrintBufferIN(4);
}

void WatchDogClass::CheckControls()
{
	WControls.Update();
	
	SolidSystem = WControls.SolidGrid;
	CanTakeDistance = WControls.TakeDistance;
	
	LastTime = CurrentTime;
	CurrentTime = glfwGetTime();
	DiffTime = CurrentTime - LastTime;
	
	MainMotorsSpeed = WControls.MainMotorsVelocity;
	float speed, aspeed;
	switch (MainMotorsSpeed) 
	{
		case SPEED1:
			speed = Speed1;
			aspeed = Angle1;
			break;
		case SPEED2:
			speed = Speed2;
			aspeed = Angle1;
			break;
	}
	
	if(WControls.CloseLoopControlSystem)
	{
		int Encoder1Diff = Encoder1 - tEncoder1;
		int Encoder2Diff = Encoder2 - tEncoder2; 
		bool ValidLectureE1 = true;
		bool ValidLectureE2 = true;
		
		if(Encoder1Diff>ENCODER_ERROR || Encoder1Diff<-ENCODER_ERROR)
			ValidLectureE1 = false;
		if(Encoder1==0 || Encoder1==32768)
			ValidLectureE1 = false;
		
		
		if(Encoder2Diff>ENCODER_ERROR || Encoder2Diff<-ENCODER_ERROR)
			ValidLectureE2 = false;
		if(Encoder2 ==0 || Encoder2 ==32768 )
			ValidLectureE2 = false;
		
		if(ValidLectureE1)
		{
			
			tEncoder1 = Encoder1;
			
			if(Encoder1Diff > 0)
				Position += Vector3f(MoveStepFor * Encoder1Diff, Angle);
			if(Encoder1Diff < 0)
				Position += Vector3f(MoveStepBack * Encoder1Diff, Angle);
		}
		if(ValidLectureE2)
		{
			tEncoder2 = Encoder2;
			
			if(Encoder2Diff > 0)
				Angle += AngleStepLeft * Encoder2Diff;
			if(Encoder2Diff < 0)
				Angle += AngleStepRight * Encoder2Diff;
			
			if(Angle>360.0f)Angle-=360.0f;
			if(Angle<0.0f)Angle+=360.0f;
		}
	}
	
	if(WControls.MovingForward && !FronCollision)
	{
		MainMotorsMove = FORWARD;
		if(!WControls.CloseLoopControlSystem)
			Position += Vector3f(speed * DiffTime, Angle);
	}
	else if(WControls.MovingBackward && !BackCollision)
	{
		MainMotorsMove = BACKWARD;
		if(!WControls.CloseLoopControlSystem)
			Position -= Vector3f(speed * DiffTime, Angle);
	}
	else if(WControls.MovingLeft)
	{
		MainMotorsMove = RIGHT;
		
		if(!WControls.CloseLoopControlSystem)
		{
			if(Angle>360.0f)Angle-=360.0f;
			Angle+=aspeed * DiffTime;
		}
	}
	else if(WControls.MovingRight)
	{
		MainMotorsMove = LEFT;
		
		if(!WControls.CloseLoopControlSystem)
		{
			if(Angle<0.0f)Angle+=360.0f;
			Angle-=aspeed * DiffTime;
		}
	}
	else
		MainMotorsMove = STOP;
	
	
	if(WControls.MovingGripperUp)
		OtherMove = UP_GRIPPER;
	else if(WControls.MovingGripperDown)
		OtherMove = DOWN_GRIPPER;
	else if(WControls.MovingGripperClose)
		OtherMove = CLOSE_GRIPPER;
	else if(WControls.MovingGripperOpen)
		OtherMove = OPEN_GRIPPER;
	else 
		OtherMove = STOP;
	
	
	
	if(WControls.MovingCamUp)
		SlaveMove = CAM2_UP;
	else if(WControls.MovingCamDown)
		SlaveMove= CAM2_DOWN;
	else if(WControls.MovingCamLeft)
		SlaveMove = CAM2_LEFT;
	else if(WControls.MovingCamRight)
		 SlaveMove = CAM2_RIGHT;
	else if(WControls.Laser)
	{
		if(LaserON)
		{
			SlaveMove = LASERS_OFF;
			LaserON = false;
		}
		else 
		{
			SlaveMove = LASERS_ON;
			LaserON = false;
		}
	}
	else 
		SlaveMove = IDLE;

	if(GetKeyNewpress('P') && (USB->Error || !USB->HIDisOpen))
		USB->HIDReOpen();
	
	SendInstruction();
}

void WatchDogClass::Draw()
{
	short i;
	
	MdlGripper[0]->A = 0.3f;
	Model->A = Transparent ? 0.35f : 1.0f;
	
	Model->Translate(Position.X,0,Position.Z);	
	Model->Rotation.Y = Angle-90.0f;
	Model->Draw(GLM_TEXTURE|GLM_SMOOTH);	
	 
	MdlGripper[0]->Position = this->Position;
	MdlGripper[1]->Position = this->Position;
	MdlGripper[2]->Position = this->Position;
	
	for(i=2 ;i>=0; i--)MdlGripper[i]->Rotation.Y = Angle-90.0f;
	for(i=2 ;i>=0; i--)MdlGripper[i]->Draw(GLM_TEXTURE|GLM_SMOOTH);
	 
}

bool WatchDogClass::GetSystemMode()
{
	return WControls.CloseLoopControlSystem;
}

double calcFPS(double theTimeInterval)
{
	static double t0Value       = glfwGetTime(); // Set the initial time to now
	static int    fpsFrameCount = 0;             // Set the initial FPS frame count to 0
	static double fps           = 0.0;           // Set the initial FPS value to 0.0
	double currentTime = glfwGetTime();
	
	if (theTimeInterval < 0.1)
		theTimeInterval = 0.1;
	
	if (theTimeInterval > 10.0)
		theTimeInterval = 10.0;

	if ((currentTime - t0Value) > theTimeInterval)
	{
		fps = (double)fpsFrameCount / (currentTime - t0Value);

		fpsFrameCount = 0;
		t0Value = glfwGetTime();
	}
	else
		fpsFrameCount++;
	
	return fps;
}

