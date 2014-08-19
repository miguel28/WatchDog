/*
 *  GridHandler.cpp
 *  MKGLibrary
 *
 *  Created by Miguel Silva on 16/10/13.
 *  Copyright 2013 ITCJ. All rights reserved.
 *
 */

#include "GridHandler.h"


GridHandler::GridHandler(int width, int height, float gridSize)
{
	Width = width;
	Height = height;
	HWidth = Width / 2;
	HHeight = Height / 2;
	
	GridSize = gridSize;
	buffer = new char[width*height];
}

GridHandler::GridHandler(float width, float height, float gridSize)
{
	Width = (int)(width/gridSize);
	Height = (int)(height/gridSize);
	HWidth = Width / 2;
	HHeight = Height / 2;
	
	GridSize = gridSize;
	buffer = new char[Width*Height];
}

GridHandler::~GridHandler()
{
	delete buffer;
}

void GridHandler::_SetPosition(int x, int y, char occuped)
{
	buffer[(Height * y) + x] = occuped;
}

char GridHandler::_GetPosition(int x, int y)
{
	return buffer[(Height * y) + x];
}

bool GridHandler::OutofRange(int x, int y)
{
	return (x < -HWidth || x > HWidth || y < -HHeight || y > HHeight);
}

void GridHandler::SetPosition(int x, int y, char occuped)
{
	if (OutofRange(x,y)) 
	{
		std::cout << "Out of range" << std::endl;
		return;
	}
	_SetPosition(x + HWidth, y + HHeight, occuped);
}

char GridHandler::GetPosition(int x, int y)
{
	if (OutofRange(x,y)) 
	{
		std::cout << "Out of range" << std::endl;
		return 0x00;
	}
	else return _GetPosition(x + HWidth, y + HHeight);
}

void GridHandler::SetPosition(float x, float y, char occuped)
{
	SetPosition((int)(x/GridSize), (int)(y/GridSize), occuped);
}
	
char GridHandler::GetPosition(float x, float y)
{
	return GetPosition((int)(x/GridSize), (int)(y/GridSize));
}
	
void GridHandler::Clear()
{
	int i,j;
	for(i=0; i<Width; i++)
		for(j=0; j<Height; j++)
			_SetPosition(i, j, 0x00);
	
	
}
void GridHandler::Fill()
{
	int i,j;
	for(i=0; i<Width; i++)
		for(j=0; j<Height; j++)
			_SetPosition(i, j, 0x01);
}
	
void GridHandler::SetThroughtVector(Vector3f Pos, float distance, float angle)
{
	float i = 0.0f;
	float rad = ToRadians(angle);
	
	for(i = 0.0f; i<distance; i+=GridSize)
	{
		SetPosition(Pos.X + (i * sinf(rad)), Pos.Z + (i * cosf(rad)), 0x00);
	}
	SetPosition(Pos.X + (distance * sinf(rad)), Pos.Z  + (distance * cosf(rad)), 0x01);	
}

char GridHandler::GetThroughtVector(Vector3f Pos, float distance, float angle)
{
	if(!Solid) return 0x00;
	float i = 0.0f;
	float rad = ToRadians(angle);
	
	for(i = 0.0f; i<distance; i+=GridSize)
	{
		float x = i * sinf(rad);
		float y = i * cosf(rad);
		if( GetPosition(Pos.X + x, Pos.Z + y) )
			return 0x01;
	}
	return GetPosition(Pos.X + (distance * sinf(rad)), Pos.Z  + (distance * cosf(rad)));	
}

char GridHandler::GetThroughtVector(Vector3f Pos, Vector3f Distance)
{
	if(!Solid) return 0x00;
	float i = 0.0f;
	float distance = Distance.Length();
	Vector3f vNormal = Distance.Normalize();
	
	for(i = 0.0f; i<distance; i+=GridSize)
	{
		Vector3f Segment = vNormal;
		Segment *=i;
		Vector3f Absolute = Pos; 
		Absolute += Segment;
		if( GetPosition(Absolute.X, Absolute.Z) )
			return 0x01;
	}
	return GetPosition(Pos.X + Distance.X, Pos.Z  + Distance.Z);
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
GridDrawer::GridDrawer(int width, int height, float gridSize) : GridHandler(width, height, gridSize)
{
	Solid = true;
	ActiveSystem = true;
}

GridDrawer::GridDrawer(float width, float height, float gridSize) : GridHandler(width, height, gridSize)
{
	Solid = true;
	ActiveSystem = true;
}

void GridDrawer::LoadModel(char* file)
{
	Template = new MK_ModelOBJ();
	Template->LoadFile(file);
	Template->Scale(GridSize*2, 0.8f, GridSize*2);
}

void GridDrawer::UnloadModel()
{
	delete Template;
}

void GridDrawer::DrawGrid()
{
	int i,j;
	Template->Rotation.Y = 0.0f;
	for(i=-HWidth; i<HWidth; i++)
	{
		for(j=-HHeight; j<HHeight; j++)
		{
			if(GetPosition(i,j))
			{
				Template->Position.X = (i*GridSize);
				Template->Position.Z = (j*GridSize);
				Template->Draw(GLM_TEXTURE|GLM_SMOOTH);
			}
		}
	}
}

void GridDrawer::SetSolid(bool on)
{
	Solid = on;
	if(Solid) Template->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	else Template->SetColor(1.0f, 1.0f, 1.0f, 0.5f);
}

void GridDrawer::Update(Vector3f Pos, float distance, float angle)
{
	if(!ActiveSystem || distance < 0.05f)return;
	
	distance += 0.3f;
	SetThroughtVector(Pos, distance, angle);
	
	Template->Position.X = Pos.X + (distance*sinf(ToRadians(angle)));
	Template->Position.Z = Pos.Z + (distance*cosf(ToRadians(angle)));
	Template->Rotation.Y = angle;					   
	Template->Draw(GLM_TEXTURE|GLM_SMOOTH);
}

