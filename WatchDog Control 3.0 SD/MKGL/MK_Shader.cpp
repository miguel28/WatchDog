/*
 *  MK_Shader.cpp
 *  OpenGLEX
 *
 *  Created by mike on 1/16/13.
 *  Copyright 2013 MiGuEl Inc. All rights reserved.
 *
 */

#include "MK_Shader.h"

MK_Shader::MK_Shader()
{
}
MK_Shader::~MK_Shader()
{
	TrowShader();
	
}

void MK_Shader::UseShader()
{
	glUseProgram(progObj);
}

void MK_Shader::CreateShader()
{
	progObj = glCreateProgram();
}

void MK_Shader::LoadShader(const char *fileName, GLenum ShaderType)
{
    GLchar *vsString;
    const GLchar *vsStringPtr[1];
    GLint success;

    vsString = LoadText(fileName);
    if (!vsString)
    {
        fprintf(stderr, "Unable to load \"%s\"\n", fileName);
		cout << "Unable to load program shader!\n" << fileName << endl;
        Sleep(5000);
        exit(0);
    }
	
	vsStringPtr[0] = vsString;
	

	GLuint vShader= glCreateShader(ShaderType);
	glShaderSource(vShader, 1, vsStringPtr, NULL);
	glCompileShader(vShader);
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetShaderInfoLog(vShader, MAX_INFO_LOG_SIZE, NULL, infoLog);
		cout << "Error in vertex shader # compilation!\n" << "Info log: " << infoLog << endl;
		Sleep(5000);
		exit(0);
	}
		
	glAttachShader(progObj, vShader);
	free(vsString);
}

void MK_Shader::CompileShader()
{
	GLint success;
	glLinkProgram(progObj);
    glGetProgramiv(progObj, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[MAX_INFO_LOG_SIZE];
        glGetProgramInfoLog(progObj, MAX_INFO_LOG_SIZE, NULL, infoLog);
		cout << "Error in program linkage!\n" << "Info log: " << infoLog << endl;
        Sleep(5000);
        exit(0);
    }
	
    // Program object has changed, so we should revalidate
    needsValidation = GL_TRUE;
}

void MK_Shader::TrowShader()
{
	
	glUseProgram(0);
}

// Load shader from disk into a null-terminated string
GLchar* MK_Shader::LoadText(const char *fileName)
{
    GLchar *shaderText = NULL;
    GLint shaderLength = 0;
    FILE *fp;
	
    fp = fopen(fileName, "r");
    if (fp != NULL)
    {
        while (fgetc(fp) != EOF)
        {
            shaderLength++;
        }
        rewind(fp);
        shaderText = (GLchar *)malloc(shaderLength+1);
        if (shaderText != NULL)
        {
            fread(shaderText, 1, shaderLength, fp);
        }
        shaderText[shaderLength] = '\0';
        fclose(fp);
    }
	
    return shaderText;
}