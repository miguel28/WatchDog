/*
 *  MK_App.cpp
 *  OpenGLEX
 *
 *  Created by mike on 12/1/12.
 *  Copyright 2012 MiGuEl Inc. All rights reserved.
 *
 */

#include "MK_App.h"

MK_Application::MK_Application(int x,int y, int Width, int Height, char *Title)
{
	//glutInit(&argc, argv);
	//glutInit(NULL, NULL);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(x, y);
    glutInitWindowSize(Width, Height);
    glutCreateWindow(Title);
}

void MK_Application::Run()
{
	glutMainLoop();
}

void MK_Application::DisplayFunc(void (*func)(void))
{
	glutDisplayFunc(func);
}

void MK_Application::ReshapeFunc(void (*func)(int width, int height))
{
	glutReshapeFunc(func);
}

void MK_Application::KeyboardFunc(void (*func)(unsigned char key, int x, int y))
{
	glutKeyboardFunc(func);
}
void MK_Application::KeyboardUpFunc(void (*func)(unsigned char key, int x, int y))
{
	glutKeyboardUpFunc(func);
}
void MK_Application::SpecialFunc(void (*func)(int key, int x, int y))
{
	glutSpecialFunc(func);
}
void MK_Application::SpecialUpFunc(void (*func)(int key, int x, int y))
{
	glutSpecialUpFunc(func);
}

void JoystickFunc(void (*func)(unsigned int buttonMask, int x, int y, int z), int pollInterval)
{
	glutJoystickFunc(func, pollInterval);
}

void MK_Application::SetDefaultInput()
{
	glutKeyboardFunc(NormalKeys);
	glutKeyboardUpFunc(NormalUpKeys);
	glutSpecialFunc(SpecialKeys);
	glutSpecialUpFunc(SpecialUpKeys);
	//Keys = GetPad();
}
