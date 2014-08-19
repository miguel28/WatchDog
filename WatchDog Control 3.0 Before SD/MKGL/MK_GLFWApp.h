/*
 *  MK_GLFWApp.h
 *  MKGLibrary
 *
 *  Created by mike on 3/29/13.
 *  Copyright 2013 MiGuEl Inc. All rights reserved.
 *
 */

#ifndef MK_APP_H
#define MK_APP_H

#include "MK_Texture.h"
#include "MK_Primitives.h"
#include "MK_Mesh/MK_Models.h"
#include "MK_Camera.h"
#include "MK_Materials.h"
#include "MK_Shader.h"
#include "MK_Input.h"
#include "MK_Text.h"
#include <GL/glfw.h>
#include <iostream>

class MK_GLFWApp
{

private:	
	bool Running;
	void (*Renderfunc)(void);
public:	
	int Width, Height;
	MK_GLFWApp();
	~MK_GLFWApp();
	GLboolean Init();
	GLboolean OpenWindow(int winWidth, int winHeight, int Mode);
	void ReshapeFunc(void GLFWCALL(*func)(int width, int height));
	void SetWindowTitle(char* Caption);
	void KeyboardCallBack(void GLFWCALL (*func)(int key, int action));
	void SetDefaultInput();
	void Displayfunc(void (*func)(void));
	void Run();
	void Exit();
};

#endif

