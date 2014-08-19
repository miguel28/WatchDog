/*
 *  MK_Texture.cpp
 *  OpenGLEX
 *
 *  Created by mike on 12/14/12.
 *  Copyright 2012 MiGuEl Inc. All rights reserved.
 *
 */

#include "MK_Texture.h"
MK_Texture::MK_Texture()
{
	
}

MK_Texture::~MK_Texture()
{
	DeleteTextures();
}

void MK_Texture::CreateTextures(GLuint MaxTextures)
{
	Tex_Counter=0;
	max_textures = MaxTextures;
	textures_index = new GLuint[MaxTextures]; 
	/*glGenTextures(MaxTextures, textures_index);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATE);*/
}

int MK_Texture::AddTexture(char* Filename)
{
	GLuint tex;
	glGenTextures(1, &tex);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	// Load texture
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	textures_index[Tex_Counter]=tex;
	Tex_Counter++;
	
    //pBytes = gltLoadTGA(Filename, &iWidth, &iHeight, &iComponents, &eFormat);
	pBytes = (GLbyte*)ReadImage(Filename, GL_FALSE, &iWidth, &iHeight, &iComponents);
	
	//glmReadSDL(const char* filename, GLboolean alpha, int* width, int* height, int* type)
    //glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, iComponents, iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pBytes);
    gluBuild2DMipmaps(GL_TEXTURE_2D, iComponents, iWidth, iHeight, iComponents, GL_UNSIGNED_BYTE, pBytes);
	
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	free(pBytes);
	//std::cout << "Num texture: "<< tex << std::endl;
	//return tex;
	return Tex_Counter-1;
}

void MK_Texture::Blind(GLuint TextureId, GLint Mode)
{
	//glBindTexture(GL_TEXTURE_2D, TextureId);
	glBindTexture(GL_TEXTURE_2D, textures_index[TextureId]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Mode);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void MK_Texture::DeleteTextures()
{
	glDeleteTextures(max_textures, textures_index);
}

void MK_Texture::EnableEffect()
{
	glEnable (GL_TEXTURE_GEN_S);
	glEnable (GL_TEXTURE_GEN_T);
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}
void MK_Texture::DisableEffect()
{
	glDisable (GL_TEXTURE_GEN_S);
	glDisable (GL_TEXTURE_GEN_T);

}
void MK_Texture::ApplyEffect(GLint Mode,GLint Effect1,GLint Effect2)
{
	/* Effect
	GL_OBJECT_LINEAR
	GL_EYE_PLANE 
	GL_REFLECTION_MAP
	GL_SPHERE_MAP
	*/
	glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, Effect1);
	glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, Effect1);
	if(Mode == MK_TEXT_EFFECT2)
	{
		static float	plane_xy[3] = {1, 0, 0};
		static float	plane_yz[3] = {0, 0, 1};
	
		glTexGenfv (GL_S, Effect2, plane_xy);
		glTexGenfv (GL_T, Effect2, plane_yz);
	}
}

/////////////////////////////////////////////////
///////////////////SkyBox Render/////////////////
/////////////////////////////////////////////////

MK_Skybox::MK_Skybox() : MK_Texture()
{
	
}
MK_Skybox::~MK_Skybox()
{
	
}

void MK_Skybox::LoadTextures(char* Filename)
{
	
	cR=1.0f;
	cG=1.0f;
	cB=1.0f;
	cA=1.0f;
	X = Y = Z = 0.0f;
	CreateTextures(6);

	std::string file;
	
	file.append(Filename);
	file.append("_top.tga");
	Sky_Top=AddTexture((char*)file.c_str());
	file.clear();
	
	file.append(Filename);
	file.append("_bottom.tga");
	Sky_Bottom=AddTexture((char*)file.c_str());
	file.clear();
	
	file.append(Filename);
	file.append("_front.tga");
	Sky_Front=AddTexture((char*)file.c_str());
	file.clear();
	
	file.append(Filename);
	file.append("_back.tga");
	Sky_Back=AddTexture((char*)file.c_str());
	file.clear();
	
	file.append(Filename);
	file.append("_left.tga");
	Sky_Left=AddTexture((char*)file.c_str());
	file.clear();
	
	file.append(Filename);
	file.append("_right.tga");
	Sky_Right=AddTexture((char*)file.c_str());
	file.clear();
	
	Loaded = true;
}

void MK_Skybox::Render(GLfloat skySize)
{
	if(!Loaded) return;
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(X, Y, Z);

    // Enable/Disable features
    glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_TEXTURE_2D);
	glDisable(GL_FOG);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);
	
    // Just in case we set all vertices to white.
	glColor4f(cR,cG,cB,cA);

    // Render the front quad
    Blind(Sky_Front,GL_NEAREST);
    glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(  skySize, -skySize, -skySize );
	glTexCoord2f(1, 0); glVertex3f( -skySize, -skySize, -skySize );
	glTexCoord2f(1, 1); glVertex3f( -skySize,  skySize, -skySize );
	glTexCoord2f(0, 1); glVertex3f(  skySize,  skySize, -skySize );
    glEnd();
	
    // Render the left quad
	Blind(Sky_Left,GL_NEAREST);
    glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(  skySize, -skySize,  skySize );
	glTexCoord2f(1, 0); glVertex3f(  skySize, -skySize, -skySize );
	glTexCoord2f(1, 1); glVertex3f(  skySize,  skySize, -skySize );
	glTexCoord2f(0, 1); glVertex3f(  skySize,  skySize,  skySize );
    glEnd();
	
    // Render the back quad
	Blind(Sky_Back,GL_NEAREST);
    glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f( -skySize, -skySize,  skySize );
	glTexCoord2f(1, 0); glVertex3f(  skySize, -skySize,  skySize );
	glTexCoord2f(1, 1); glVertex3f(  skySize,  skySize,  skySize );
	glTexCoord2f(0, 1); glVertex3f( -skySize,  skySize,  skySize );
	
    glEnd();
	
    // Render the right quad
    Blind(Sky_Right,GL_NEAREST);
    glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f( -skySize, -skySize, -skySize );
	glTexCoord2f(1, 0); glVertex3f( -skySize, -skySize,  skySize );
	glTexCoord2f(1, 1); glVertex3f( -skySize,  skySize,  skySize );
	glTexCoord2f(0, 1); glVertex3f( -skySize,  skySize, -skySize );
    glEnd();
	
    // Render the top quad
    Blind(Sky_Top,GL_NEAREST);
    glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f( -skySize,  skySize, -skySize );
	glTexCoord2f(0, 0); glVertex3f( -skySize,  skySize,  skySize );
	glTexCoord2f(1, 0); glVertex3f(  skySize,  skySize,  skySize );
	glTexCoord2f(1, 1); glVertex3f(  skySize,  skySize, -skySize );
    glEnd();
	
    // Render the bottom quad
    Blind(Sky_Bottom,GL_NEAREST);
    glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f( -skySize, -skySize, -skySize );
	glTexCoord2f(0, 1); glVertex3f( -skySize, -skySize,  skySize );
	glTexCoord2f(1, 1); glVertex3f(  skySize, -skySize,  skySize );
	glTexCoord2f(1, 0); glVertex3f(  skySize, -skySize, -skySize );
    glEnd();
	
    // Restore enable bits and matrix
    glPopAttrib();
	glPopMatrix();
}

void MK_Skybox::SetColor(GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha)
{
	cR=Red;
	cG=Green;
	cB=Blue;
	cA=Alpha;
}

void MK_Skybox::Translate(GLfloat x, GLfloat y, GLfloat z)
{
	X = x;
	Y = y;
	Z = z;
}
