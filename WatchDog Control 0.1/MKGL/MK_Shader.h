/*
 *  MK_Shader.h
 *  OpenGLEX
 *
 *  Created by mike on 1/16/13.
 *  Copyright 2013 MiGuEl Inc. All rights reserved.
 *
 */

#include "../glTools/gltools.h"   // OpenGL toolkit
#include "../glTools/glFrame.h"   // OpenGL toolkit

#include <stdio.h>
#include <iostream>

#define MAX_INFO_LOG_SIZE 2048

using namespace std;

class MK_Shader
{
public:
	GLuint progObj;
	GLboolean needsValidation;
	
	void LoadShader(const char *fileName, GLenum ShaderType);
	void UseShader();
	void CreateShader();
	void CompileShader();
	
protected:
	GLchar *LoadText(const char *fileName);
};

