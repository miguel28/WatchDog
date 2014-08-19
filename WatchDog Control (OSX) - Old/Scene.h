/*
 *  Scene.h
 *  MKGLibrary
 *
 *  Created by Miguel Silva on 03/10/13.
 *  Copyright 2013 ITCJ. All rights reserved.
 *
 */

#ifndef SCENE_H
#define SCENE_H
#include "MKGL/MK_GLFWApp.h"

class Scene
{
public:
	MK_Texture* Textures;
	MK_Skybox* Skybox;
	MK_Text* Text;
	MK_Shader* Shad;
	
	MK_TPlane* Plane;
	MK_Light* Light0;
	MK_Material* Material0;
	
	Scene();
	~Scene();
	
	void ClearScreen();
	void PaintSkybox(float x, float y, float z);
	void SetLights(float x, float y, float angle);
	void SetMaterials();
	void Reset();
	void Flush();
};

#endif
