/*
 *  MK_Models.h
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
#include <time.h>
#include <iostream>
#include <cassert>
#include <vector>

#include "../glTools/gltools.h"
#include "../glTools/math3d.h"

#ifdef WIN32
#include <windows.h>		// Must have for Windows platform builds
#include <gl\gl.h>			// Microsoft OpenGL headers (version 1.1 by themselves)
#include <gl\glu.h>			// OpenGL Utilities
#include "gl\glut.h"			// Glut (Free-Glut on Windows)
#endif

// Mac OS X
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
// Just ignore sleep on Apple
#define Sleep(x)
#endif

#include "../glm/glm.h"
#ifndef WIN32
//#include <lib3ds.h>       
#include <lib3ds/file.h>                        
#include <lib3ds/camera.h>
#include <lib3ds/mesh.h>
#include <lib3ds/node.h>
#include <lib3ds/material.h>
#include <lib3ds/matrix.h>
#include <lib3ds/vector.h>
#include <lib3ds/light.h>
#endif

#ifndef MIN  
#define MIN(a,b) ((a)<(b)?(a):(b))  
#define MAX(a,b) ((a)>(b)?(a):(b))  
#endif

using namespace std;

class MK_ModelOBJ
{
public:
	GLMmodel *ModelOBJ;
	int LoadFile(char* Filename);
	void Draw(GLint Mode);
	
};

#ifndef WIN32
class CModel3DS
{
public:
	CModel3DS(std:: string filename);
	virtual void Draw() const;
	virtual void CreateVBO();
	virtual ~CModel3DS();
protected:
	void GetFaces();
	unsigned int m_TotalFaces;
	Lib3dsFile * m_model;
	GLuint m_VertexVBO, m_NormalVBO;
};

class Model
{
public:
	/**
	 \brief Constructor of this class
	 
	 Model() is the constructor of this class, and enables texture generation and sets how that should be done, and sets the current frame variable to 0
	 */
	Model();
	/**
	 \brief Destructor of this class
	 
	 The destructor disables texture generation mode and free's the memory of the model, if it's not already freed.
	 */
	~Model();
	/**
	 \brief Loads the file
	 
	 It loads the file 'name', sets the current frame to 0 and if the model has textures, it will be applied to the model
	 
	 \param name Contains the name of the to be loaded file
	 */
	void LoadFile(const char *name);
	/**
	 \brief create lighting list
	 
	 Creates a display list that sets all the information for the lights.
	 */
	void CreateLightList();
	/**
	 \brief renders nodes
	 
	 It renders the node specified by the argument and sets material properties to the node if nescesary
	 
	 \param node Contains the node to be renderd
	 */
	void renderNode(Lib3dsNode *node);
	/**
	 \brief Enable lights
	 
	 Enables all lights in the model if not already enabled
	 */
	void EnableLights();
	/**
	 \brief Enable lights
	 
	 Disables all lights in the model if not already disabled
	 */
	void DisableLights();
	/**
	 \brief Actually renders the model
	 
	 It renders the model, by rendering node by node using the renderNode function.But before it's renderd it's translated to (x,y,z) and then rotates it angle degrees
	 
	 \sa renderNode()
	 */
	void RenderModel();
	/**
	 \brief Apply the texture
	 
	 It applies a texture to mesh ,according to the data that mesh contains
	 
	 \param mesh That's the mesh on which the texture should be applied
	 */
	void ApplyTexture(Lib3dsMesh *mesh);
	Lib3dsFile * get3DSPointer();
	string getFilename();
private:
	Lib3dsFile *file; /**< file holds the data of the model */
	const char *filename; /**< It's the filename of the model */
	int curFrame; /**< curFrame keeps track of the current frame that shuold be renderd */
	vector<GLuint> textureIndices; /**< this variable holds the texture indicies */
	vector<string> textureFilenames; /**< Holds the filenames of the textures, so I can see wheter a texture is used multiple times or not */
	bool lightEnabled; /**< wheter light was enabled before this class. */
	GLuint lightListIndex;
};
#endif

