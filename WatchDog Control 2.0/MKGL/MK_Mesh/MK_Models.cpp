/*
 *  MK_Models.cpp
 *  OpenGLEX
 *
 *  Created by mike on 12/14/12.
 *  Copyright 2012 MiGuEl Inc. All rights reserved.
 *
 */

#include "MK_Models.h"

MK_ModelOBJ::MK_ModelOBJ()
{	
	X = Y = Z = rotX = rotY = rotZ = 0.0f;
	R = G = B = A = ScaleX = ScaleY = ScaleZ = 1.0f;
}

MK_ModelOBJ::~MK_ModelOBJ()
{	
	//glmDelete(ModelOBJ);
}

int MK_ModelOBJ::LoadFile(char* Filename)
{
	ModelOBJ = new GLMmodel;
	ModelOBJ = glmReadOBJ(Filename);
	glmVertexNormals(ModelOBJ, 30, GL_TRUE);
	glmScale(ModelOBJ,0.5f);
	return 1;
}

void MK_ModelOBJ::Draw(GLint Mode)
{
	glPushMatrix();
	glTranslatef(X,Y,Z);
	glRotatef(rotX, 1, 0, 0);
	glRotatef(rotY, 0, 1, 0);
	glRotatef(rotZ, 0, 0, 1);
	glScalef(ScaleX, ScaleY, ScaleZ);
	glColor4f(R, G, B, A);
	glmDraw(ModelOBJ, Mode);
	glPopMatrix();
}

void MK_ModelOBJ::Translate(GLfloat x, GLfloat y, GLfloat z)
{
	X = x;
	Y = y;
	Z = z;
}
void MK_ModelOBJ::Rotate(GLfloat axisx, GLfloat axisy, GLfloat axisz)
{
	rotX = axisx;
	rotY = axisy;
	rotZ = axisz;
}

void MK_ModelOBJ::Scale(GLfloat x, GLfloat y, GLfloat z)
{
	if(x>0)ScaleX = x;
	if(y>0)ScaleY = y;
	if(z>0)ScaleZ = z;
}

void MK_ModelOBJ::SetColor(GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha)
{
	R=Red;
	G=Green;
	B=Blue;
	A=Alpha;
}



#ifndef WIN32
// Load 3DS model
CModel3DS::CModel3DS(std::string filename)
{
	m_TotalFaces = 0;
	
	m_model = lib3ds_file_load(filename.c_str());
	// If loading the model failed, we throw an exception
	if(!m_model)
	{
		throw strcat((char*)"Unable to load ", (char*)filename.c_str());
	}
	
}

// Destructor
CModel3DS::~CModel3DS()
{
	glDeleteBuffers(1, &m_VertexVBO);
	glDeleteBuffers(1, &m_NormalVBO);
	
	if(m_model != NULL)
	{
		lib3ds_file_free(m_model);
	}
}

// Copy vertices and normals to the memory of the GPU
void CModel3DS::CreateVBO()
{
	assert(m_model != NULL);
	
	// Calculate the number of faces we have in total
	GetFaces();
	
	// Allocate memory for our vertices and normals
	Lib3dsVector * vertices = new Lib3dsVector[m_TotalFaces * 3];
	Lib3dsVector * normals = new Lib3dsVector[m_TotalFaces * 3];
	
	Lib3dsMesh * mesh;
	unsigned int FinishedFaces = 0;
	// Loop through all the meshes
	for(mesh = m_model->meshes;mesh != NULL;mesh = mesh->next)
	{
		lib3ds_mesh_calculate_normals(mesh, &normals[FinishedFaces*3]);
		// Loop through every face
		for(unsigned int cur_face = 0; cur_face < mesh->faces;cur_face++)
		{
			Lib3dsFace * face = &mesh->faceL[cur_face];
			for(unsigned int i = 0;i < 3;i++)
			{
				memcpy(&vertices[FinishedFaces*3 + i], mesh->pointL[face->points[i]].pos, sizeof(Lib3dsVector));
			}
			FinishedFaces++;
		}
	}
	
	// Generate a Vertex Buffer Object and store it with our vertices
	glGenBuffers(1, &m_VertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Lib3dsVector) * 3 * m_TotalFaces, vertices, GL_STATIC_DRAW);
	
	// Generate another Vertex Buffer Object and store the normals in it
	glGenBuffers(1, &m_NormalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_NormalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Lib3dsVector) * 3 * m_TotalFaces, normals, GL_STATIC_DRAW);
	
	// Clean up our allocated memory
	delete vertices;
	delete normals;
	
	// We no longer need lib3ds
	lib3ds_file_free(m_model);
	m_model = NULL;
}

// Count the total number of faces this model has
void CModel3DS::GetFaces()
{
	assert(m_model != NULL);
	
	m_TotalFaces = 0;
	Lib3dsMesh * mesh;
	// Loop through every mesh
	for(mesh = m_model->meshes;mesh != NULL;mesh = mesh->next)
	{
		// Add the number of faces this mesh has to the total faces
		m_TotalFaces += mesh->faces;
	}
}

// Render the model using Vertex Buffer Objects
void CModel3DS::Draw() const
{
	assert(m_TotalFaces != 0);
	
	// Enable vertex and normal arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	
	// Bind the vbo with the normals
	glBindBuffer(GL_ARRAY_BUFFER, m_NormalVBO);
	// The pointer for the normals is NULL which means that OpenGL will use the currently bound vbo
	glNormalPointer(GL_FLOAT, 0, NULL);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexVBO);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	
	// Render the triangles
	glDrawArrays(GL_TRIANGLES, 0, m_TotalFaces * 3);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

// constructor, enables and set properties of texture coordinate generation and set the current frame
Model3DS::Model3DS()
{
	curFrame = 0; // current frame of our model
	/*if(glIsEnabled(GL_LIGHTING))
		lightEnabled = true;
	else
		lightEnabled = false;*/
}

// destructor, free up memory and disable texture generation
Model3DS::~Model3DS()
{
	if(file) // if the file isn't freed yet
		lib3ds_file_free(file); //free up memory
	//disable texture generation
	unsigned int i;
	for(i = 0;i < textureIndices.size();i++)
		glDeleteTextures(1, &textureIndices.at(i));
}

// load the model, and if the texture has textures, then apply them on the geometric primitives
void Model3DS::LoadFile(const char *name)
{
	if(glIsEnabled(GL_LIGHTING))
	 lightEnabled = true;
	 else
	 lightEnabled = false;
	filename = name;
	// load file
	file = lib3ds_file_load(filename);
	if(!file) // if we were not able to load the file
	{
		// give some errors
		string event = "Error loading: ";
		event.append(filename);
		cout << event << endl;
		exit(1);
	}
	
//Node:
	/* No nodes?  Fabricate nodes to display all the meshes. */  
	if( !file->nodes )  
	{  
		cout << "No node found"<< endl;
		Lib3dsMesh *mesh;  
		Lib3dsNode *node;  
		
		for(mesh = file->meshes; mesh != NULL; mesh = mesh->next)  
		{  
			node = lib3ds_node_new_object();  
			strcpy(node->name, mesh->name);  
			node->parent_id = LIB3DS_NO_PARENT;  
			lib3ds_file_insert_node(file, node);  
		} 
		//goto Node;
	}  
	
	static Lib3dsVector bmin, bmax;  
	static float    sx, sy, sz, size;   /* bounding box dimensions */  
	static float    cx, cy, cz;     /* bounding box center */  
	
 
	lib3ds_file_bounding_box_of_nodes(file, LIB3DS_TRUE, LIB3DS_FALSE, LIB3DS_FALSE, bmin, bmax);  
	sx = bmax[0] - bmin[0];  
	sy = bmax[1] - bmin[1];  
	sz = bmax[2] - bmin[2];  
	size = MAX(sx, sy); size = MAX(size, sz);  
	cx = (bmin[0] + bmax[0])/2;  
	cy = (bmin[1] + bmax[1])/2;  
	cz = (bmin[2] + bmax[2])/2;  
	
	
	
	
	lib3ds_file_eval(file, 0); // set current frame to 0
	// apply texture to all meshes that have texels
	
	
	if (file->lights == NULL)  
	{  
		Lib3dsLight *light;  
		
		light = lib3ds_light_new("light0");  
		light->spot_light = 0;  
		light->see_cone = 0;  
		light->color[0] = light->color[1] = light->color[2] = .6;  
		light->position[0] = cx + size * .75;  
		light->position[1] = cy - size * 1.;  
		light->position[2] = cz + size * 1.5;  
		light->position[3] = 0.;  
		light->outer_range = 100;  
		light->inner_range = 10;  
		light->multiplier = 1;  
		lib3ds_file_insert_light(file, light);  
		
		light = lib3ds_light_new("light1");  
		light->spot_light = 0;  
		light->see_cone = 0;  
		light->color[0] = light->color[1] = light->color[2] = .3;  
		light->position[0] = cx - size;  
		light->position[1] = cy - size;  
		light->position[2] = cz + size * .75;  
		light->position[3] = 0.;  
		light->outer_range = 100;  
		light->inner_range = 10;  
		light->multiplier = 1;  
		lib3ds_file_insert_light(file, light);  
		
		light = lib3ds_light_new("light2");  
		light->spot_light = 0;  
		light->see_cone = 0;  
		light->color[0] = light->color[1] = light->color[2] = .3;  
		light->position[0] = cx;  
		light->position[1] = cy + size;  
		light->position[2] = cz + size;  
		light->position[3] = 0.;  
		light->outer_range = 100;  
		light->inner_range = 10;  
		light->multiplier = 1;  
		lib3ds_file_insert_light(file, light);  
		
	}  
	
	
	Lib3dsMesh *mesh;
	for(mesh = file->meshes;mesh != 0;mesh = mesh->next)
	{
		if(mesh->texels) //if there's texels for the mesh
			ApplyTexture(mesh); //then apply texture to it
	}
	if(file->lights) //if we have lights in our model
		CreateLightList();
}

void Model3DS::CreateLightList()
{
	lightListIndex = glGenLists(1);
	glNewList(lightListIndex, GL_COMPILE_AND_EXECUTE);
	Lib3dsLight *light; // temporary variable to store our lights
	GLint curlight = GL_LIGHT0;
	for(light = file->lights;light != 0;light = light->next)
	{
		if(light->off) //if our light is off
			continue; //Move to the next light
		
		GLfloat diff[4], amb[4], pos[4];
		
		for(int j = 0;j < 3;j++)
		{
			diff[j] = light->color[j];
			amb[j] = light->color[j] / 4.5; // We might wanna change this;
			pos[j] = light->position[j];
		}
		
		diff[3] = amb[3] = pos[3] = 1.0;
		
		curlight++;
		// Start setting light
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diff); //set the diffuse color
		glLightfv(GL_LIGHT0, GL_POSITION, pos); //set the position of the light
		glLightfv(GL_LIGHT0, GL_AMBIENT, amb); // set the ambient color of the light
		glLightfv(GL_LIGHT0, GL_SPECULAR, diff); // set the specular color of the light
		
		if(light->spot) // if it's a light spot
		{
			for(int i = 0;i < 3;i++) // get position of the light
				pos[i] = light->spot[i] - light->position[i];
			pos[3] = light->spot[3] - light->position[3];
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, pos); //specify that we have a spot at position 'pos'
		}
	}
	glEndList();
}

// what is basicly does is, set the properties of the texture for our mesh
void Model3DS::ApplyTexture(Lib3dsMesh *mesh)
{
	for(unsigned int i = 0;i < mesh->faces;i++)
	{
		Lib3dsFace *f = &mesh->faceL[i];
		if(! f->material[0])
			continue;
		
		GLbyte *pBytes;
		GLint iWidth, iHeight, iComponents;
		GLenum eFormat;
		Lib3dsMaterial *mat;
		bool found = false;
		mat = lib3ds_file_material_by_name(file, f->material);
		for(unsigned int i = 0;i < textureFilenames.size();i++)
		{
			if(strcmp(mat->texture1_map.name, textureFilenames.at(i).c_str()) == 0)
			{
				textureIndices.push_back(textureIndices.at(i));
				textureFilenames.push_back(mat->texture1_map.name);
				found = true;
				break;
			}
		}
		if(!found)
		{
			textureFilenames.push_back(mat->texture1_map.name);
			string tempfilename;
			tempfilename.append(mat->texture1_map.name);
			//tempfilename.append(".tga");
			pBytes = gltLoadTGA(tempfilename.c_str(), &iWidth, &iHeight, &iComponents, &eFormat);
			//glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes);
			//gluBuild2DMipmaps(GL_TEXTURE_2D, iComponents, iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pBytes);
			
			if(!pBytes)
			{
				cout << "3DS error" << endl;
				cout << "Error loading 3ds texture, perhaps file format not supported?  "<< tempfilename  << endl;
				exit(1);
			}
			//img = QGLWidget::convertToGLFormat(img);
			GLuint tmpIndex; // temporary index to old the place of our texture
			glGenTextures(1, &tmpIndex); // allocate memory for one texture
			textureIndices.push_back(tmpIndex); // add the index of our newly created texture to textureIndices
			glBindTexture(GL_TEXTURE_2D, tmpIndex); // use our newest texture
			//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, img.width() , img.height(), GL_RGBA, GL_UNSIGNED_BYTE, img.bits()); // genereate MipMap levels for our texture 
			//gluBuild2DMipmaps(GL_TEXTURE_2D, iComponents, iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pBytes);
			glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // give the best result for texture magnification
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //give the best result for texture minification
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // don't repeat texture 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); // don't repeat texture
		}
	}
}

// this code is rewritten from player.c example that came with lib3ds
// what it does is render a node from our model
void Model3DS::renderNode(Lib3dsNode *node)
{
	ASSERT(file); //this is for debugging
	{
		Lib3dsNode *tmp;
		for(tmp = node->childs;tmp != 0;tmp = tmp->next)
			renderNode(tmp); //render all child nodes of this note
	}
	if(node->type == LIB3DS_OBJECT_NODE) //check wheter the node is a 3ds node
	{
		
		if(! node->user.d) //Wheter we have a list or not, if not we're gonna create one
		{
			
			Lib3dsMesh *mesh = lib3ds_file_mesh_by_name(file, node->name); //get all the meshes of the current node
			ASSERT(mesh); //for debugging in case we don't have a mesh
			if(! mesh)
				return;
			node->user.d = glGenLists(1); //alocate memory for one list
			/////////////////////////////////////////////////////////////	
			if(glGetError() != GL_NO_ERROR)
			{
				cout << "ERROR!\n";
				exit(0);
			}
			/////////////////////////////////////////////////////////////	
			glNewList(node->user.d, GL_COMPILE); //here we create our list
			{
				unsigned p;
				Lib3dsVector *normals;
				normals = static_cast<float(*)[3]> (std::malloc (3*sizeof(Lib3dsVector)*mesh->faces)); //alocate memory for our normals
				{
					Lib3dsMatrix m;
					lib3ds_matrix_copy(m, mesh->matrix); //copy the matrix of the mesh in our temporary matrix
					lib3ds_matrix_inv(m);
					glMultMatrixf(&m[0][0]); //adjust our current matrix to the matrix of the mesh
				}
				lib3ds_mesh_calculate_normals(mesh, normals); //calculate the normals of the mesh
				int j = 0;
				for(p = 0;p < mesh->faces;p++)
				{
					Lib3dsFace *f = &mesh->faceL[p];
					Lib3dsMaterial *mat=0;
					if(f->material[0]) //if the face of the mesh has material properties
						mat = lib3ds_file_material_by_name(file, f->material); //read material properties from file
					if(mat) //if we have material
					{
						static GLfloat ambient[4] = { 0.0, 0.0, 0.0, 1.0 };
						glMaterialfv(GL_FRONT, GL_AMBIENT, ambient); // Ambient color
						glMaterialfv(GL_FRONT, GL_DIFFUSE, mat->diffuse); //diffuse color
						glMaterialfv(GL_FRONT, GL_SPECULAR, mat->specular); //specular color
						float shine;
						shine = pow(2, 10.0 * mat->shininess);
						if(shine > 128.0)
							shine = 128.0;
						glMaterialf(GL_FRONT, GL_SHININESS, shine);
					}
					else // if we do not have material properties, we have to set them manually
					{
						GLfloat diff[4] = { 0.75, 0.75, 0.75, 1.0 }; // color: white/grey
						GLfloat amb[4] = { 0.25, 0.25, 0.25, 1.0 }; //color: black/dark gray
						GLfloat spec[4] = { 0.0, 0.0, 0.0, 1.0 }; //color: completly black
						glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
						glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
						glMaterialfv(GL_FRONT, GL_AMBIENT, spec);
					}
					{
						if(mesh->texels)
						{
							glBindTexture(GL_TEXTURE_2D, textureIndices.at(j));
							j++;
						}
						glBegin(GL_TRIANGLES);
						for(int i = 0;i < 3;i++)
						{
							glNormal3fv(normals[3*p+i]); //set normal vector of that point
							if(mesh->texels)
								glTexCoord2f(mesh->texelL[f->points[i]][0], mesh->texelL[f->points[i]][1]);
							glVertex3fv(mesh->pointL[f->points[i]].pos); //Draw the damn triangle
						}
						glEnd();
					}
				}
				free(normals); //free up memory
			}
			glEndList(); // end of list
		}
		if(node->user.d) // if we have created a link list(with glNewList)
		{
			Lib3dsObjectData *tmpdat;
			glPushMatrix(); //save transformation values
			tmpdat = &node->data.object; // get the position data
			glMultMatrixf(&node->matrix[0][0]); //adjust matrix according to the node
			glTranslatef(-tmpdat->pivot[0], -tmpdat->pivot[1], -tmpdat->pivot[2]); //move to the right place;
			glCallList(node->user.d); //render node
			glPopMatrix(); //return transformation original values
		}
	}	 
}

// this function actually renders the model at place (x, y, z) and then rotated around the y axis by 'angle' degrees
void Model3DS::RenderModel()
{
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glShadeModel(GL_SMOOTH);
	
	if(file->lights) //if we have lights in the model
	{
		EnableLights(); //enable all lights
		glCallList(lightListIndex); //set lights.
	}
	///cout << "B";
	Lib3dsNode *nodes;
	for(nodes = file->nodes;nodes != 0;nodes = nodes->next)// Render all nodes
	{	
		renderNode(nodes);
		//cout << "R";
	}
	
	
	if(file->lights)
		DisableLights(); // disable lighting, we don't want it have it enabled longer than necessary
	
	curFrame++;
	if(curFrame > file->frames) //if the next frame doesn't exist, go to frame 0
		curFrame = 0;
	lib3ds_file_eval(file, curFrame); // set current frame
	
	//glDisable(GL_CULL_FACE);
	glShadeModel(GL_FLAT);
}

void Model3DS::EnableLights()
{
	glEnable(GL_LIGHTING);
	GLuint lightNum = GL_LIGHT0;
	Lib3dsLight *light;
	for(light = file->lights;light != 0;light = light->next)
	{
		if(!glIsEnabled(lightNum))
			glEnable(lightNum);
		lightNum++;
	}
}

void Model3DS::DisableLights()
{
	glDisable(GL_LIGHTING);
	GLuint lightNum = GL_LIGHT0;
	Lib3dsLight *light;
	for(light = file->lights;light != 0;light = light->next)
	{
		if(glIsEnabled(lightNum))
			glDisable(lightNum);
		lightNum++;
	}
}

Lib3dsFile * Model3DS::get3DSPointer()
{
	return file;
}

string Model3DS::getFilename()
{
	string returnvalue = filename;
	return returnvalue;
}



mModel::mModel()
{	
}

void mModel::LoadFile(char* Filename)
{
    Assimp::Importer Importer;
    const aiScene* pScene = Importer.ReadFile(Filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
    
    if (!pScene) 
	{
        cout << "mModel: Error, Can't Read The file" << endl;
    }
    
	numMeshes = pScene->mNumMeshes;
	numMaterials = pScene->mNumMaterials;
	MaterialsIndex = new GLuint(numMaterials);
	//mMeshes = new mMesh(pScene->mNumMeshes);
	mMeshes = (mMesh*)calloc(numMeshes, sizeof(mMesh));
	if(!mMeshes) cout << "Error Assing Memory Meshes" <<endl;
	cout << "numMeshes: " << numMeshes << " numMaterials: " << numMaterials << endl;
	
	int i;
    for (i = 0 ; i < numMeshes ; i++) {
        aiMesh* paiMesh = pScene->mMeshes[i];
        InitMesh(i, paiMesh);
    }
	//const aiMesh* paiMesh = pScene->mMeshes[0];
	//InitMesh(0, paiMesh);
	
	
    //return InitMaterials(pScene, Filename);

}

void mModel::InitMesh(int Index, const aiMesh* paiMesh)
{
	cout <<"Init Mesh " <<endl;
	MaterialsIndex[Index] = paiMesh->mMaterialIndex;
	mMeshes[Index].numVertices = paiMesh->mNumVertices;
	mMeshes[Index].Vertices = new GLfloat( (paiMesh->mNumVertices) * 3 *2);
	mMeshes[Index].Normals = new GLfloat( (paiMesh->mNumVertices) * 3 *2);
	mMeshes[Index].TexCoords = new GLfloat( (paiMesh->mNumVertices) * 2 *2);
	
	if(!mMeshes[Index].Vertices || !mMeshes[Index].Normals || !mMeshes[Index].TexCoords)cout << "Error assing Vertices "<< endl;
	else cout << "Momory Success numVertices " << mMeshes[Index].numVertices << " agsa " << paiMesh->mNumVertices<<endl;
	
	
    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
	int i;
    for (i = 0 ; i < paiMesh->mNumVertices ; i++) {
        const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal   = &(paiMesh->mNormals[i]);
        const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
		cout << "Address : " << (i*3)+0 << "X: "<<pPos->x << endl; 
        mMeshes[Index].Vertices[(i*3)+0] = pPos->x;
		mMeshes[Index].Vertices[(i*3)+1] = pPos->y;
		mMeshes[Index].Vertices[(i*3)+2] = pPos->z;
		
		mMeshes[Index].Normals[(i*3)+0] = pNormal->x;
		mMeshes[Index].Normals[(i*3)+1] = pNormal->y;
		mMeshes[Index].Normals[(i*3)+2] = pNormal->z;
		
		mMeshes[Index].TexCoords[(i*2)+0] = pTexCoord->x;
		mMeshes[Index].TexCoords[(i*2)+1] = pTexCoord->y;
    }
	cout << "Finish Mesh" << endl;
}

void mModel::Render()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, mMeshes[0].Vertices);
	
	/* Send data : 24 vertices */
	glDrawArrays(GL_TRIANGLES, 0, mMeshes[0].numVertices);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	
}
#endif

