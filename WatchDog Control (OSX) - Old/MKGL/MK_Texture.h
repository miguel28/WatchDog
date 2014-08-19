/*
 *  MK_Texture.h
 *  OpenGLEX
 *
 *  Created by mike on 12/14/12.
 *  Copyright 2012 MiGuEl Inc. All rights reserved.
 *
 */

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

#include "../glTools/gltools.h"
#include "../glTools/math3d.h"
#include "MK_Image.h"

#ifdef WIN32
#include <windows.h>		// Must have for Windows platform builds
#include <gl\gl.h>			// Microsoft OpenGL headers (version 1.1 by themselves)
#include <gl\glu.h>			// OpenGL Utilities
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
// Just ignore sleep on Apple
#define Sleep(x)
#endif

/*Textures.Blind(2);
 Textures.EnableEffect();
 Textures.ApplyEffect(MK_TEXT_EFFECT2,GL_SPHERE_MAP,GL_EYE_PLANE);
 //glutSolidTeapot (0.4);
 //glutWireTeapot(0.3);
 //glutSolidSphere(3,150,100);
 Textures.DisableEffect();*/

enum {
	MK_TEXT_EFFECT1,
	MK_TEXT_EFFECT2
};

class MK_Texture
{

private:	
	GLbyte *pBytes;
    GLint iWidth, iHeight, iComponents;
    GLenum eFormat;
	GLuint max_textures;
	GLuint *textures_index;
	GLuint Tex_Counter;
	
public:
	MK_Texture();
	~MK_Texture();
	void CreateTextures(GLuint MaxTextures);
	int AddTexture(char* Filename);
	void Blind(GLuint TextureId,GLint Mode);
	void DeleteTextures();
	void EnableEffect();
	void DisableEffect();
	void ApplyEffect(GLint Mode,GLint Effect1,GLint Effect2);
};

class MK_Skybox : public MK_Texture
{
public:
	GLint Sky_Back,
	Sky_Bottom,
	Sky_Front,
	Sky_Left,
	Sky_Right,
	Sky_Top;
	
	GLfloat cR,cG,cB,cA;
	GLfloat X,Y,Z;
	
	GLboolean Loaded;
	MK_Skybox();
	~MK_Skybox();
	void LoadTextures(char* Filename);
	void Render(GLfloat skySize);
	void SetColor(GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha);
	void Translate(GLfloat x, GLfloat y, GLfloat z);
};

