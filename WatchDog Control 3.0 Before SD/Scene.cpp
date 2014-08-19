/*
 *  Scene.cpp
 *  MKGLibrary
 *
 *  Created by Miguel Silva on 03/10/13.
 *  Copyright 2013 ITCJ. All rights reserved.
 *
 */

#include "Scene.h"
#include <iostream>
using namespace std;

Scene::Scene()
{
	
	glClearColor(0,0,0,0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//glEnable(GL_CULL_FACE);
	
	/*GLfloat fLowLight[] ={0,0,0,0};
	glEnable(GL_FOG); glFogfv(GL_FOG_COLOR, fLowLight); 
	glFogf(GL_FOG_START, 5.0f); 
	glFogf(GL_FOG_END, 50.0f); 
	glFogi(GL_FOG_MODE, GL_LINEAR);*/
	
	Textures = new MK_Texture();
	Skybox = new MK_Skybox();
	Text = new MK_Text();
	Shad = new MK_Shader;
	
	Light0 = new MK_Light(GL_LIGHT0, MK_Spot_CutOff);
	Material0 = new MK_Material();
	
	Textures->CreateTextures(3);
	Textures->AddTexture((char*)"Textures/Stone.tga");
	Textures->AddTexture((char*)"Textures/Brick.tga");
	Textures->AddTexture((char*)"Textures/Crackless.tga");
	
	Skybox->LoadTextures((char*)"Textures/Skybox/Sunset");
	//Skybox->SetColor(0.0f, 0.1f, 0.5f, 1.0);
	
	Shad->CreateShader();
	Shad->LoadShader((char*)"Shaders/Texture2.vs",GL_VERTEX_SHADER);
	Shad->LoadShader((char*)"Shaders/Texture2.fs",GL_FRAGMENT_SHADER);
	Shad->CompileShader();	
}

Scene::~Scene()
{
	delete Textures;
	delete Skybox;
	delete Text;
	delete Shad;

	delete Plane;
	delete Light0;
	delete Material0;
}

void Scene::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Scene::PaintSkybox(float x, float y, float z)
{
	Skybox->Translate(x,y,z);
	Skybox->Render(50.0f);
}

void Scene::SetLights(float x, float y, float angle)
{
	//Light0->SetPosition(-0.5f, 0.5f, 0.0f);
	//Light0->SetPosition(x, 1.0f, y);
	Light0->SetAmbient(0.8f, 0.8f, 0.8f, 1.0f);
	Light0->SetEspecular(1.0f, 0.5f, 0.5f, 1.0f);
	Light0->SetDifuse(1.0f, 0.5f, 0.5f, 1.0f);
	Light0->Traslate(x,1.0f,y);
	//Light0->SetDirection(0,0,0);
	Light0->Rotate(0.0f,angle - 90.0f,0.0f);
	Light0->Blind();
}

void Scene::SetMaterials()
{
	Material0->SetAmbient(0.0f,0.0f,0.0f,1.0f);
	Material0->SetDifuse(0.0f,0.0f,0.0f,1.0f);
	Material0->SetEspecular(0.0f,1.0f,0.0f,1.0f);
	//Material0->SetShininess(0);
	Material0->Blind();
}

void Scene::Reset()
{
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
}

void Scene::Flush()
{
	glFlush();
	glfwSwapBuffers();
}

