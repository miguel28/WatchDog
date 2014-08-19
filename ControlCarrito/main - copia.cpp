#include "MkLib/MikeLibrary.h"
#include "USBInterfaceClass.h"
#include <iostream>

using namespace std;

enum
{
   STOP,
   FORWARD,
   BACKWARD,
   LEFT,
   RIGHT,
   FAST_FORWARD,
   FAST_BACKWARD,
   UP,
   DOWN,
   FORWARD_UP,
   FORWARD_DOWN,
   BACKWARD_UP,
   BACKWARD_DOWN,
   OPEN_CLAMP,
   CLOSE_CLAMP,
   PISTON
};

bool Opened_Clamp;


#define WIDTH 1000
#define HEIGHT 600
#define BPP 4
#define DEPTH 32


#define ORIGINX -10
#define ORIGINY -10

#define FACTORCON_PIX2IN(x)  (x/5.3333)
#define FACTORCON_PIX2FT(x)  (x/64)
#define LINEARSCALE 1
#define RADIALSCALE 1


PadType Pad;
MouseType Mouse;
USBInterface USB;

MK_Sprite Sprite((char*)"Gfx/Tanque.bmp",0x00FF00FF,1,64,64,1,1);
MK_Sprite SprOrigin((char*)"Gfx/origin.bmp",0x00FF00FF,1,32,32,1,1);
MK_Sprite SprArm((char*)"Gfx/arm.bmp",0x00FF00FF,1,64,255,1,1);
MK_Sprite SprScale((char*)"Gfx/support.bmp",0x00FF00FF,1,128,255,1,1);
MK_Background Background((char*)"Gfx/grid.bmp",0x00FF00FF,0,2048, 2048);
MK_Sprite Notepad((char*)"Gfx/notes.bmp",0x00FF00FF,1,200,800,1,1);

typedef struct
{
    double X,Y,H;
    double Angle;
    int ScrollX, ScrollY;
    int Time;
}_RealCar;
_RealCar Car;

void Controllers();
void Scroll();

int main(int argc, char* argv[])
{
    ////////////////////////////////Init System////////////////
	USB.EnumerateHIDs();
    USB.HIDOpen(0x3995,0x0001);	
    USB.HIDDescription();	
	USB.SendOutputPort((unsigned char) 0xFF);
    
    SDL_Surface *screen;
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) return 1;
    if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_SWSURFACE)))
    {
        SDL_Quit();
        return 1;
    }
    MK_FPSInit();
    TTF_Init();
    ////////////////////////////////Init System////////////////
    
    MK_Text TxtCoordinate((char*)"Gfx/arial.ttf",12,0,0,0);
    MK_Text TxtCoordinateFT((char*)"Gfx/arial.ttf",12,0,0,0);
    MK_Text TxtAngle((char*)"Gfx/arial.ttf",12,0,0,0);
    
	char Temp[255];
	Sprite.CreateGfxEffect(64,64);
	SprScale.x = 350;
	SprScale.y = 144;
	SprScale.Alpha = 200;
	SprArm.Alpha = 200;
	Car.Y=0;
	Car.X=0;
	Notepad.x=800;
	TxtCoordinate.x=845;
	TxtCoordinate.y=35;
	TxtCoordinateFT.x=845;
	TxtCoordinateFT.y=60;
	TxtAngle.x=845;
	TxtAngle.y=80;

    while(1) 
    {
		sprintf(Temp,"X: %0.3f in, Y: %0.3f in",FACTORCON_PIX2IN(Car.X),FACTORCON_PIX2IN(-Car.Y));
        TxtCoordinate.SetText(Temp);
        
        sprintf(Temp,"X: %0.3f ft, Y: %0.3f ft",FACTORCON_PIX2FT(Car.X),FACTORCON_PIX2FT(-Car.Y));
        TxtCoordinateFT.SetText(Temp);
        
        sprintf(Temp,"Angle %0.3f º",Car.Angle);
        TxtAngle.SetText(Temp);
        
        CheckKeyboardMouse();
		Controllers();
        Scroll();
		
		Background.x=Car.ScrollX+512;
		Background.y=Car.ScrollY+1536;
        Sprite.Rot((int)Car.Angle,32,32,1,0x00FF00FF);
        Sprite.y=(int)Car.Y - Car.ScrollY  + ORIGINY -32;
        Sprite.x=(int)Car.X - Car.ScrollX  + ORIGINX -32;
        SprArm.x=422;
        SprArm.y=240-((int)Car.H);
        
        SprOrigin.x=-16- Car.ScrollX ;
        SprOrigin.y=-16- Car.ScrollY ;
        
		
		Background.DrawBackground(screen);
		SprOrigin.DrawSprite(screen,0);
		Sprite.DrawEffect(screen);		
        SprArm.DrawSprite(screen,0);
        SprScale.DrawSprite(screen,0);
        Notepad.DrawSprite(screen,0);
		TxtCoordinate.DrawText(screen);
		TxtCoordinateFT.DrawText(screen);
		TxtAngle.DrawText(screen);
		
		MK_ShowFPSInWindow();
		SDL_Flip(screen); 
		
		TxtCoordinate.FreeGraphic();
		TxtCoordinateFT.FreeGraphic();
		TxtAngle.FreeGraphic();
		SDL_FreeSurface(Sprite.GfxEffect);
		
    }
	
    SDL_Quit();
	
    return 0;
}

void Controllers()
{
    if(Pad.Held.Up) //Forward
    {
        if(Pad.Held.Q)
        {
            USB.SendOutputPort(FORWARD_UP);
            if(Car.H<110)Car.H+=0.5;
        }
        else if(Pad.Held.A)
        {
            USB.SendOutputPort(FORWARD_DOWN);
            if(Car.H>0)Car.H-=0.5;
        }
        else USB.SendOutputPort(FORWARD);
        
        Car.Y-=(5*MK_Sin((int)Car.Angle));
        Car.X+=(5*MK_Cos((int)Car.Angle)); 
    }
    //////// Backward
	else if(Pad.Held.Down) 
    {
        if(Pad.Held.Q)
        {
            USB.SendOutputPort(BACKWARD_UP);
            if(Car.H<110)Car.H+=0.5;
        }
        else if(Pad.Held.A)
        {
            USB.SendOutputPort(BACKWARD_DOWN);
            if(Car.H>0)Car.H-=0.5;
        }
        else USB.SendOutputPort(BACKWARD);
        
        Car.Y+=(5*LINEARSCALE*MK_Sin((int)Car.Angle));
        Car.X-=(5*LINEARSCALE*MK_Cos((int)Car.Angle));
    }
    ///////////Turn Left
	else if(Pad.Held.Left)
    { 
        USB.SendOutputPort(LEFT);
        Car.Angle+=RADIALSCALE;
        if(Car.Angle>360)Car.Angle=0;
    }
    ///////////Turn Right
	else if(Pad.Held.Right)
    { 
        USB.SendOutputPort(RIGHT);
        Car.Angle-=RADIALSCALE;
        if(Car.Angle<0)Car.Angle=360;
    }
    ////// Up Motor
    else if(Pad.Held.Q)
    { 
        USB.SendOutputPort(UP);
        if(Car.H<110)Car.H+=0.5;
    }
    ////// Down Motor
    else if(Pad.Held.A)
    { 
        USB.SendOutputPort(DOWN);
        if(Car.H>0)Car.H-=0.5;
    }
    ////// Activate Piston
	else if(Pad.Held.W)
    { 
        USB.SendOutputPort(PISTON);
        SDL_Delay(1000);
    }
    ///// Open an close Clamp
	else if(Pad.Newpress.S)
    { 
        if(Opened_Clamp)
		{
			USB.SendOutputPort(CLOSE_CLAMP);
			SDL_Delay(1000);
			Opened_Clamp=false;
		}
		else
		{
			USB.SendOutputPort(OPEN_CLAMP);
			SDL_Delay(1000);
			Opened_Clamp=true;
		}
    }
    ////// else send stop
	else USB.SendOutputPort(STOP);
    
}

void Scroll()
{
    ////////////// Scroll for Y
    if ((Car.Y - Car.ScrollY) > (600-256) && Car.Y < 512-256)
    {
		Car.ScrollY = Car.Y - (600-256);
	}
	if ((Car.Y - Car.ScrollY) < 128  && Car.Y > -1536+256)
    {
		Car.ScrollY = Car.Y - 128;	
	}
	
    /////////////// Scroll for X
	if ((Car.X - Car.ScrollX) > 800-256  && Car.X < 1536-256)
    {
		Car.ScrollX = Car.X - (800-256);
	}
	if ((Car.X - Car.ScrollX) < 128  && Car.X > -512+256)
    {
		Car.ScrollX = Car.X - 128;	
	}    
}
