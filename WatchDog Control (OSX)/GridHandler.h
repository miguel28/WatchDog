/*
 *  GridHandler.h
 *  MKGLibrary
 *
 *  Created by Miguel Silva on 16/10/13.
 *  Copyright 2013 ITCJ. All rights reserved.
 *
 */

#ifndef GRIDHANDLER_H
#define GRIDHANDLER_H

#include <iostream>
#include "MKGL/MK_GLFWApp.h"

//#include "MK_Math.h"

//#define GRIDSIZE 0.02f;

class GridHandler
{
private:
	char* buffer;
	int Width;
	int Height;
	
	void _SetPosition(int x, int y, char occuped);
	char _GetPosition(int x, int y);
	bool OutofRange(int x, int y);
public:
	int HWidth;
	int HHeight;
	float GridSize;
	bool Solid;
	
	GridHandler(int width, int height, float gridSize);
	GridHandler(float width, float height, float gridSize);
	~GridHandler();
	void SetPosition(int x, int y, char occuped);
	char GetPosition(int x, int y);
	void SetPosition(float x, float y, char occuped);
	char GetPosition(float x, float y);
	void Clear();
	void Fill();
	void SetThroughtVector(Vector3f Pos, float distance, float angle);
	char GetThroughtVector(Vector3f Pos, float distance, float angle);
	char GetThroughtVector(Vector3f Pos, Vector3f Distance);
};

class GridDrawer : public GridHandler
{	
public:
	MK_ModelOBJ *Template;
	bool ActiveSystem;
	
	GridDrawer(int width, int height, float gridSize);
	GridDrawer(float width, float height, float gridSize);
	void LoadModel(char* file);
	void UnloadModel();
	void DrawGrid();
	void SetSolid(bool on);
	void Update(Vector3f Pos, float distance, float angle);
};


#endif
