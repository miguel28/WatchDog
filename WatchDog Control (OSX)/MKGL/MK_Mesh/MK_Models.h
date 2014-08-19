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

#include "../../glTools/gltools.h"
#include "../../glTools/math3d.h"

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

#include "../../glm/glm.h"
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

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> 

#endif

#include "../MK_Math.h"


#ifndef MIN  
#define MIN(a,b) ((a)<(b)?(a):(b))  
#define MAX(a,b) ((a)>(b)?(a):(b))  
#endif

using namespace std;

class MK_ModelOBJ
{
public:
	GLMmodel *ModelOBJ;
	Vector3f Position;
	Vector3f Rotation;
	GLfloat ScaleX, ScaleY, ScaleZ;
	GLfloat R,G,B,A;
	MK_ModelOBJ();
	~MK_ModelOBJ();
	int LoadFile(char* Filename);
	void Draw(GLint Mode);
	void Translate(GLfloat x, GLfloat y, GLfloat z);
	void Rotate(GLfloat axisx, GLfloat axisy, GLfloat axisz);
	void Scale(GLfloat x, GLfloat y, GLfloat z);
	void SetColor(GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha);
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

class Model3DS
{
public:
	
	Model3DS();
	~Model3DS();

	void LoadFile(const char *name);
	void CreateLightList();
	void renderNode(Lib3dsNode *node);
	void EnableLights();
	void DisableLights();
	void RenderModel();
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


typedef struct
{
	GLuint numVertices;
	GLfloat* Vertices;
	GLfloat* Normals;
	GLfloat* TexCoords;
}mMesh;

class mModel
{
public:
	unsigned int numMeshes, numMaterials;
	mMesh* mMeshes;
	GLuint* MaterialsIndex;
	mModel();
	//~mModel();
	void LoadFile(char* Filename);
	void InitMesh(int Index, const aiMesh* paiMesh);
	void Render();
};

#endif
