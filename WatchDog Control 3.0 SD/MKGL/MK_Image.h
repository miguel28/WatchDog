/*
 *  MK_Image.h
 *  OpenGLEX
 *
 *  Created by mike on 1/26/13.
 *  Copyright 2013 MiGuEl Inc. All rights reserved.
 *
 */

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

GLubyte* ReadImage(const char* filename, GLboolean alpha, int* width, int* height, int* type);
