/*
 *  MK_Video.h
 *  SDLExample
 *
 *  Created by mike on 4/19/12.
 *  Copyright 2012 MiGuEl Inc. All rights reserved.
 *
 */
#include <SDL/SDL.h>
#include <stdio.h>

// How many frames time values to keep
// The higher the value the smoother the result is...
// Don't make it 0 or less :)
#define FRAME_VALUES 10

void MK_FPSInit();
void MK_ShowFPSInWindow();
