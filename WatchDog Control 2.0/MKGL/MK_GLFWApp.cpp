/*
 *  MK_GLFWApp.cpp
 *  MKGLibrary
 *
 *  Created by mike on 3/29/13.
 *  Copyright 2013 MiGuEl Inc. All rights reserved.
 *
 */

#include "MK_GLFWApp.h"

using namespace std;

MK_GLFWApp::MK_GLFWApp()
{

}

MK_GLFWApp::~MK_GLFWApp()
{
	glfwTerminate();
}

GLboolean MK_GLFWApp::Init()
{
	GLboolean Initialized = glfwInit();
	if(Initialized) cout << "App: Sucessful Library Initialization" << endl; 
	else 
	{
		cout << "App: Error Library Initialization" << endl; 
		glfwTerminate();
		exit(-1);
	}
	return Initialized;
}

GLboolean MK_GLFWApp::OpenWindow(int winWidth, int winHeight, int Mode)
{
	GLboolean Initialized = glfwOpenWindow(winWidth,winHeight,0,0,0,0,16,0,Mode);
	if(Initialized) cout << "App: Sucessful Opening Window" << endl; 
	else
	{
		cout << "App: Error Opening Window" << endl; 
		glfwTerminate();
		exit(-1);
	}
	Running = true;
	glfwSwapInterval(1);
	return Initialized;
}

void MK_GLFWApp::ReshapeFunc(void GLFWCALL (*func)(int width, int height))
{
	glfwSetWindowSizeCallback(func);
}

void MK_GLFWApp::SetWindowTitle(char* Caption)
{
	glfwSetWindowTitle(Caption);
}

void MK_GLFWApp::KeyboardCallBack(void GLFWCALL (*func)(int key, int action))
{
	glfwSetKeyCallback(func);
	glfwEnable( GLFW_KEY_REPEAT );
}

void MK_GLFWApp::SetDefaultInput()
{
	KeyboardCallBack(KeysHandle);
}

void MK_GLFWApp::Displayfunc(void (*func)(void))
{
	Renderfunc = func;
}

void MK_GLFWApp::Run()
{
	while(Running)
	{
		Renderfunc();
		Running = Running && glfwGetWindowParam( GLFW_OPENED );
	}
}

void MK_GLFWApp::Exit()
{
	Running=false;
}

