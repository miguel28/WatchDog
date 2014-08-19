/*
 *  WatchDogDef.h
 *  OpenGLEX
 *
 *  Created by mike on 2/9/13.
 *  Copyright 2013 MiGuEl Inc. All rights reserved.
 *
 */
#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "MKGL/MK_GLFWApp.h"
#include "USBInterface/USBInterfaceClass.h"

#define SPEED_IPS 9.0 /// Inches per second
#define SPEED_FPS SPEED_IPS/12.0 /// Inches per second
#define W_GPS 50.0 /// Grades per second
#define FPS 152.0 /// Frames Per Second
#define SPEED_FOOTPERFRAME (SPEED_FPS/FPS) //// Foots per Frame
#define SPEED_RADIAL (W_GPS/FPS) /// Grades º per second

//#define UPDATE_EVERY 20
#define W_WIDTH 0.833f
#define W_HEIGHT 0.416f
#define W_LENGHT 1.166f
#define ENCODER_ERROR 50


enum Main_Intructions
{
	STOP,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
	
    UP_GRIPPER,
    DOWN_GRIPPER,
    OPEN_GRIPPER,
    CLOSE_GRIPPER,
	
	FORWARD_UP_GRIPPER,
    FORWARD_DOWN_GRIPPER,
    FORWARD_OPEN_GRIPPER,    
    FORWARD_CLOSE_GRIPPER,
	
	BACKWARD_UP_GRIPPER,
	BACKWARD_DOWN_GRIPPER,
    BACKWARD_OPEN_GRIPPER,
    BACKWARD_CLOSE_GRIPPER,
	
	LEFT_UP_GRIPPER,  
    LEFT_DOWN_GRIPPER,
    LEFT_OPEN_GRIPPER,
    LEFT_CLOSE_GRIPPER,
	
	RIGHT_UP_GRIPPER,
    RIGHT_DOWN_GRIPPER,
    RIGHT_OPEN_GRIPPER, 
    RIGHT_CLOSE_GRIPPER
};

enum SlaveMoves
{
    IDLE,
	CAM1_UP,     
    CAM1_DOWN,
    CAM1_LEFT,
    CAM1_RIGHT,
    CAM2_UP,
    CAM2_DOWN,
    CAM2_LEFT,
    CAM2_RIGHT,
	RESET_ENCODER1,
	RESET_ENCODER2,
	LASERS_OFF,
    LASERS_ON,
	UPDATE,
	UPDATE_CAM1_UP,     
    UPDATE_CAM1_DOWN,
    UPDATE_CAM1_LEFT,
    UPDATE_CAM1_RIGHT,
    UPDATE_CAM2_UP,
    UPDATE_CAM2_DOWN,
    UPDATE_CAM2_LEFT,
    UPDATE_CAM2_RIGHT,
	UPDATE_RESET_ENCODER1,
	UPDATE_RESET_ENCODER2,
	UPDATE_LASERS_OFF,
    UPDATE_LASERS_ON
};

class WatchDogClass
{
public:
	Vector3f Position;
	float Angle;
	int tDistance;
	float Distance;
	int Encoder1;
	int Encoder2;
	
	int tEncoder1,tEncoder2;
	
	float CurrentTime;
	float LastTime;
	float DiffTime;
	bool FronCollision, BackCollision;
	
	Vector3f CollisionFront1;
	Vector3f CollisionFront2;
	Vector3f CollisionBack1;
	Vector3f CollisionBack2;
	
	/////////////
	float MoveStepFor, MoveStepBack;
	float AngleStepLeft,AngleStepRight;
	float Speed1, Speed2;
	float Angle1;
	int UseShadder;
	/////////////
	
	bool SolidSystem, CanTakeDistance;
	bool LaserON;
	bool IsOnline;
	
	char MainMotorsMove;
	char MainMotorsSpeed;
	char CamButton;
	
	char OtherMove;
	char SlaveMove;
	
	float QuequeUpdate;	
	
	bool Transparent;
	MK_ModelOBJ *Model, *MdlGripper[3];
	
	USBInterface* USB;
	MK_Joystick *Joy,*Joy1,*Joy2;
	
	WatchDogClass();
	~WatchDogClass();
	void ReadConfig();
	void LoadModels();
	void SendInstruction();
	void CheckVel(int Axis);
	void CheckControls();
	void Draw();
	bool GetSystemMode();
};

double calcFPS(double theTimeInterval);

#endif
