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

#define INTIAL_ANGLE 90
char FONT[]= "Gfx/arial.ttf";

#define ORIGINX -10
#define ORIGINY -10


#define VEL_IPS 50 /// Inches per second
#define W_GPS 50 /// Grades per second
#define FPS 30 /// Frames Per Second
#define FACTORCON_PIX2IN(x)  (x/5.33333333)
#define FACTORCON_PIX2FT(x)  (x/64)
#define FACTORCON_IN2PX(x)  (x*5.33333333)
#define LINEARSCALE ((VEL_IPS*5.33333333)/FPS) //// Pixel per Frame
#define RADIALSCALE (W_GPS/FPS)
#define STEPMOTOR_VEL 0.05 /// Adimencional

PadType Pad;
MouseType Mouse;
USBInterface USB;
SDL_Surface *screen;

MK_Sprite Sprite((char*)"Gfx/Tanque.bmp",0x00FF00FF,1,64,64,1,1);
MK_Sprite SprOrigin((char*)"Gfx/origin.bmp",0x00FF00FF,1,32,32,1,1);
MK_Sprite SprArm((char*)"Gfx/arm.bmp",0x00FF00FF,1,64,255,1,1);
MK_Sprite SprScale((char*)"Gfx/support.bmp",0x00FF00FF,1,128,255,1,1);
MK_Background Background((char*)"Gfx/grid.bmp",0x00FF00FF,0,2048, 2048);
MK_Sprite Notepad((char*)"Gfx/notes.bmp",0x00FF00FF,1,200,800,1,1);
MK_Sprite SprPiston((char*)"Gfx/piston.bmp",0x00FF00FF,1,144,32,1,2);

typedef struct
{
    double X,Y,H;
    double Angle;
	double LinearDistance;
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
    USB.SetMode(SIMPLE_ASME_DRIVER);
    USB.HIDDescription();	
	USB.SendOutputPort((unsigned char) 0xFF);
  
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) return 1;
    if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_SWSURFACE)))
    {
        SDL_Quit();
        return 1;
    }
    //MK_FPSInit();
    TTF_Init();
    ////////////////////////////////Init System////////////////
    
    MK_Text TxtCoordinate(FONT,12,0,0,0);
    MK_Text TxtCoordinateFT(FONT,12,0,0,0);
    MK_Text TxtAngle(FONT,12,0,0,0);
	MK_Text TxtMsg(FONT,10,128,0,0);
	MK_Text TxtTime(FONT,12,0,0,0);
	MK_Text TxtDistance(FONT,12,0,0,0);
	MK_Text TxtDistanceFT(FONT,12,0,0,0);
	
	if(!USB.HIDisOpen)
	{
		TxtMsg.SetText((char*)"Error: Cannot Open Hid!");
	}
	else
	{
		TxtMsg.SetColor(0,128,0);		
		TxtMsg.SetText((char*)"Hid Opened Susessfull!");
	}    
	TxtMsg.x=840;
	TxtMsg.y=400;

	char Temp[255];
	Sprite.CreateGfxEffect(64,64);
	SprScale.x = 500;
	SprScale.y = 144;
	SprScale.Alpha = 200;
	SprArm.Alpha = 200;
	SprArm.x=572;
	SprPiston.x = 618;
	SprPiston.y = 385;
	Car.Y=0;
	Car.X=0;
	Car.LinearDistance=0;
	Car.Angle = INTIAL_ANGLE;
	Notepad.x=800;
	TxtCoordinate.x=845;
	TxtCoordinate.y=35;
	TxtCoordinateFT.x=845;
	TxtCoordinateFT.y=60;
	TxtAngle.x=845;
	TxtAngle.y=80;

	TxtTime.x=845;
	TxtTime.y=100;

	TxtDistance.x=845;
	TxtDistance.y=120;
	TxtDistanceFT.x=845;
	TxtDistanceFT.y=140;


    while(1) 
    {
		sprintf(Temp,"X: %0.3f in, Y: %0.3f in",FACTORCON_PIX2IN(Car.X),FACTORCON_PIX2IN(-Car.Y));
        TxtCoordinate.SetText(Temp);
        
        sprintf(Temp,"X: %0.3f ft, Y: %0.3f ft",FACTORCON_PIX2FT(Car.X),FACTORCON_PIX2FT(-Car.Y));
		//sprintf(Temp,"X: %d Y: %d",Car.ScrollX,Car.ScrollY);
        TxtCoordinateFT.SetText(Temp);
        
        sprintf(Temp,"Angle %0.3f ",Car.Angle);
        TxtAngle.SetText(Temp);

		sprintf(Temp,"Time %d seg",Car.Time/FPS);
        TxtTime.SetText(Temp);

		sprintf(Temp,"Distance: %0.3f in",FACTORCON_PIX2IN(Car.LinearDistance));
        TxtDistance.SetText(Temp);

		sprintf(Temp,"Distance: %0.3f ft ",FACTORCON_PIX2FT(Car.LinearDistance));
        TxtDistanceFT.SetText(Temp);
        
        CheckKeyboardMouse();
		Controllers();
        Scroll();
		
		if(Car.ScrollY>0) Background.y=Car.ScrollY;
		else if(Car.ScrollY<-1024) Background.y=Car.ScrollY+1536+512;
		else Background.y=Car.ScrollY+1536;

		if(Car.ScrollX>=-128 && Car.ScrollX<512) Background.x=Car.ScrollX+256;
		else if(Car.ScrollX>=512) Background.x=Car.ScrollX-512;
		else if(Car.ScrollX<-1024) Background.x=Car.ScrollX+2048;
		else Background.x=Car.ScrollX+1536;


		//Background.x=Car.ScrollX;
		//Background.y=Car.ScrollY;

		//Background.x=Car.ScrollX+512;
		//Background.y=Car.ScrollY+1536;



        Sprite.Rot((int)Car.Angle,32,32,1,0x00FF00FF);
        Sprite.y=(int)Car.Y - Car.ScrollY  + ORIGINY -32;
        Sprite.x=(int)Car.X - Car.ScrollX  + ORIGINX -32;
        SprArm.y=240-((int)Car.H);
        SprOrigin.x=-16- Car.ScrollX ;
        SprOrigin.y=-16- Car.ScrollY ;
        
		Car.Time++;
		///////////////// ReDraw All Gfx ////////////////////////
		Background.DrawBackground(screen);
		SprOrigin.DrawSprite(screen,0);
		Sprite.DrawEffect(screen);		
        SprArm.DrawSprite(screen,0);
        SprScale.DrawSprite(screen,0);
		SprPiston.DrawSprite(screen,0);
        Notepad.DrawSprite(screen,0);
		TxtCoordinate.DrawText(screen);
		TxtCoordinateFT.DrawText(screen);
		TxtAngle.DrawText(screen);
		TxtMsg.DrawText(screen);
		TxtTime.DrawText(screen);
		TxtDistance.DrawText(screen);
		TxtDistanceFT.DrawText(screen);

		//MK_ShowFPSInWindow();
		SDL_Flip(screen); 
		///////////////// ReDraw All Gfx ////////////////////////

		TxtCoordinate.FreeGraphic();
		TxtCoordinateFT.FreeGraphic();
		TxtAngle.FreeGraphic();
		TxtTime.FreeGraphic();
		TxtDistance.FreeGraphic();
		TxtDistanceFT.FreeGraphic();
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
            if(Car.H<110)
			{
				Car.H+=STEPMOTOR_VEL;
				USB.SendOutputPort(FORWARD_UP|0xC0);
			}
			else
			{
				USB.SendOutputPort(FORWARD|0xC0);
			}
        }
        else if(Pad.Held.A)
        {
            
            if(Car.H>0)
			{
				Car.H-=STEPMOTOR_VEL;
				USB.SendOutputPort(FORWARD_DOWN|0xC0);
			}
			else
			{
				USB.SendOutputPort(FORWARD|0xC0);
			}
        }
        else USB.SendOutputPort(FORWARD|0xC0);
        
        Car.Y-=(LINEARSCALE*MK_Sin((int)Car.Angle));
        Car.X+=(LINEARSCALE*MK_Cos((int)Car.Angle));
		Car.LinearDistance+=LINEARSCALE;
	}
    //////// Backward
	else if(Pad.Held.Down) 
    {
        if(Pad.Held.Q)
        { 
            if(Car.H<110)
			{
				Car.H+=STEPMOTOR_VEL;
				USB.SendOutputPort(BACKWARD_UP|0xC0);
			}
			else
			{
				USB.SendOutputPort(BACKWARD|0xC0);
			}
        }
        else if(Pad.Held.A)
        {
            
            if(Car.H>0)
			{
				Car.H-=STEPMOTOR_VEL;
				USB.SendOutputPort(BACKWARD_DOWN|0xC0);
			}
			else
			{
				USB.SendOutputPort(BACKWARD|0xC0);
			}
        }
        else USB.SendOutputPort(BACKWARD|0xC0);
        
        Car.Y+=(LINEARSCALE*MK_Sin((int)Car.Angle));
        Car.X-=(LINEARSCALE*MK_Cos((int)Car.Angle));
		Car.LinearDistance+=LINEARSCALE;
    }
    ///////////Turn Left
	else if(Pad.Held.Left)
    { 
        USB.SendOutputPort(LEFT|0xC0);
        Car.Angle+=(double)RADIALSCALE;
        if(Car.Angle>=360)
		{
			Car.Angle-=360;
		}
    }
    ///////////Turn Right
	else if(Pad.Held.Right)
    { 
        USB.SendOutputPort(RIGHT|0xC0);
        Car.Angle-=(double)RADIALSCALE;
        if(Car.Angle<0)
		{
			Car.Angle+=360;
		}
    }
    ////// Up Motor
    else if(Pad.Held.Q)
    { 
        if(Car.H<110)
		{
			Car.H+=STEPMOTOR_VEL;
			USB.SendOutputPort(UP|0xC0);
		}
		else
		{
			USB.SendOutputPort(STOP|0xC0);
		}
    }
    ////// Down Motor
    else if(Pad.Held.A)
    { 
        if(Car.H>0)
		{
			Car.H-=STEPMOTOR_VEL;
			USB.SendOutputPort(DOWN|0xC0);
		}
		else
		{
			USB.SendOutputPort(STOP|0xC0);
		}
    }
    ////// Activate Piston
	else if(Pad.Held.W)
    { 
        USB.SendOutputPort(PISTON);
		Sprite.Rot((int)Car.Angle,32,32,1,0x00FF00FF);
		Background.DrawBackground(screen);
		SprOrigin.DrawSprite(screen,0);
		Sprite.DrawEffect(screen);		
        SprArm.DrawSprite(screen,0);
        SprScale.DrawSprite(screen,0);
		SprPiston.DrawSprite(screen,1);
        Notepad.DrawSprite(screen,0);
		SDL_Flip(screen); 
        SDL_Delay(1000);
		Car.Time+=FPS;
    }
    ///// Open an close Clamp
	else if(Pad.Newpress.S)
    { 
        if(Opened_Clamp)
		{
			USB.SendOutputPort(CLOSE_CLAMP|0xC0);
			SDL_Delay(1000);
			Car.Time+=FPS;
			Opened_Clamp=false;
		}
		else
		{
			USB.SendOutputPort(OPEN_CLAMP|0xC0);
			SDL_Delay(1000);
			Car.Time+=FPS;
			Opened_Clamp=true;
		}
    }
    ////// else send stop
	else USB.SendOutputPort(STOP|0xC0);
    //else USB.SendOutputPort(0xFF);
}

void Scroll()
{
    ////////////// Scroll for Y
    if ((Car.Y - Car.ScrollY) > (600-256) && Car.Y < 2048-256)
    {
		Car.ScrollY = Car.Y - (600-256);
	}
	if ((Car.Y - Car.ScrollY) < 128  && Car.Y > -2048+256)
    {
		Car.ScrollY = Car.Y - 128;	
	}
	
    /////////////// Scroll for X
	if ((Car.X - Car.ScrollX) > 800-256  && Car.X < 2048-256)
    {
		Car.ScrollX = Car.X - (800-256);
	}
	if ((Car.X - Car.ScrollX) < 128  && Car.X > -2048+256)
    {
		Car.ScrollX = Car.X - 128;	
	}    
}
