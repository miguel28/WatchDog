#include "MKGL/MK_GLFWApp.h"
#include "USBInterface/USBInterfaceClass.h"
#include "WatchDogDef.h"

MK_GLFWApp* MainApp = new MK_GLFWApp();
USBInterface* USB = new USBInterface();
MK_Joystick* Joy = new MK_Joystick(0,12);
PadType Key;

MK_Texture* Textures = new MK_Texture();
MK_Skybox Skybox;
MK_Text Text;
MK_ModelOBJ WatchDogModel,PlaneT,MdlBandera, MdlGripper[3],Rocks;
MK_Shader Shad;

MK_Camera MainCam(800,600,75.0f,0.01f,500.0f);
MK_TPlane Plane(-32,0,-32,64,64);
MK_Light Light0(GL_LIGHT0, MK_Spot_CutOff);
MK_Material Material0;
_WatchDog WatchDog;

void GLFWCALL Reshape(int width, int height)
{
	MainCam.Width=width;
	MainCam.Height=height;
	MainCam.aspect=width/(float)height;
}

void Keyboard()
{
	Key = GetPad();
	Joy->Update();
	
	//////Forward
	if(Key.Held.Up || Joy->GetAxis(3) < -15000)
	{
		/*if(Key.Held.Q)
		 {
		 USB->SendOutputPort((unsigned char) FORWARD_UP| Enconding);
		 }
		 else if(Key.Held.A)
		 {
		 USB->SendOutputPort((unsigned char) FORWARD_DOWN| Enconding);
		 }
		 else */USB->SendOutputPort((unsigned char) FORWARD | Enconding);
		
		WatchDog.X+=WatchDog.Speed_FootPerFrame*cos(WatchDog.Angle*M_PI/180);
		WatchDog.Y+=WatchDog.Speed_FootPerFrame*sin(WatchDog.Angle*M_PI/180);
		
	}
	//////// Backward
	else if(Key.Held.Down || Joy->GetAxis(3) > 15000)
	{
		/*if(Key.Held.Q)
		 {
		 USB->SendOutputPort((unsigned char) BACKWARD_UP| Enconding);
		 }
		 else if(Key.Held.A)
		 {
		 USB->SendOutputPort((unsigned char) BACKWARD_DOWN| Enconding);
		 }
		 else */USB->SendOutputPort((unsigned char) BACKWARD| Enconding);
		
		WatchDog.X-=WatchDog.Speed_FootPerFrame*cos(WatchDog.Angle*M_PI/180);
		WatchDog.Y-=WatchDog.Speed_FootPerFrame*sin(WatchDog.Angle*M_PI/180);
		
	}
	///////////Turn Left
	else if(Key.Held.Left || Joy->GetAxis(2) <  -15000)
	{
		if(WatchDog.Angle>360.0f)WatchDog.Angle-=360.0f;
		WatchDog.Angle+=WatchDog.SpeedAngle;
		USB->SendOutputPort((unsigned char) LEFT| Enconding);
	}
	///////////Turn Right
	else if(Key.Held.Right || Joy->GetAxis(2) > 15000)
	{
		if(WatchDog.Angle<0.0f)WatchDog.Angle+=360.0f;
		WatchDog.Angle-=WatchDog.SpeedAngle;
		
		USB->SendOutputPort((unsigned char) RIGHT| Enconding);
	}
	////// Up Motor
	else if(Key.Held.Q || Joy->ButtonHeld(1))
	{
		USB->SendOutputPort((unsigned char) UP| Enconding);
		if(WatchDog.GripperHeight<0.14f)WatchDog.GripperHeight+=WatchDog.GripperDeltaUp;
	}
	////// Down Motor
	else if(Key.Held.A || Joy->ButtonHeld(3))
	{
		USB->SendOutputPort((unsigned char) DOWN| Enconding);
		if(WatchDog.GripperHeight>-0.14f)WatchDog.GripperHeight-=WatchDog.GripperDeltaUp;
	}
    ///// Open an close Gripper
	else if(Key.Held.S || Joy->ButtonHeld(7))
	{
		USB->SendOutputPort(CLOSE_GRIPPER| Enconding);
		if(WatchDog.GripperOpening<0.07f)WatchDog.GripperOpening+=WatchDog.GripperDeltaOp;
	}
	else if(Key.Held.D || Joy->ButtonHeld(8))
	{
		USB->SendOutputPort(OPEN_GRIPPER| Enconding);
		if(WatchDog.GripperOpening>0.0f)WatchDog.GripperOpening -=WatchDog.GripperDeltaOp;
	}
	else 
	{
		USB->SendOutputPort((unsigned char) STOP| Enconding);
		
	}	

	if(Key.Newpress.Escape)MainApp->Exit();
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Keyboard();
	MainCam.ThirdPersonCamera(WatchDog.X,WatchDog.Y,0,WatchDog.Angle,1.5,atan(1.5/((Joy->GetAxis(0)-32000)/1500))*(180/M_PI)+30);
	
	//if(WatchDog.UseShadder)Shad.UseShader();
	
	Skybox.Translate(WatchDog.X,2,-WatchDog.Y);
	Skybox.Render(50.0f);
	
	Light0.SetPosition(-0.5f, 0.5f, 0.0f);
	Light0.SetAmbient(0.8f, 0.8f, 0.8f, 1.0f);
	Light0.SetEspecular(0.0f, 1.0f, 0.0f, 1.0f);
	Light0.SetDifuse(0.0f, 1.0f, 0.0f, 1.0f);
	Light0.Traslate(WatchDog.X,0, -WatchDog.Y);
	Light0.Rotate(0.0f,WatchDog.Angle,0.0f);
	Light0.Blind();
	
	Material0.SetAmbient(0.0f,0.0f,0.0f,1.0f);
	Material0.SetDifuse(0.0f,0.0f,0.0f,1.0f);
	Material0.SetEspecular(0.0f,1.0f,0.0f,1.0f);
	Material0.SetShininess(0);
	Material0.Blind();
	
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	Textures->Blind(2,GL_LINEAR);
	Plane.Draw(AxisX,64.0f);
	Rocks.Draw(GLM_TEXTURE|GLM_SMOOTH);
	//PlaneT.Draw(GLM_TEXTURE|GLM_SMOOTH);
	
	MdlBandera.rotY=180.0;
	MdlBandera.Draw(GLM_TEXTURE|GLM_SMOOTH);
	//Rocks.Draw(GLM_TEXTURE|GLM_SMOOTH);
	
	MdlGripper[0].A = 0.3f;
	short i;
	
	MdlGripper[0].Translate(WatchDog.X,WatchDog.GripperHeight, -WatchDog.Y );
	MdlGripper[1].Translate(WatchDog.X - (WatchDog.GripperOpening*sin(WatchDog.Angle*M_PI/180)),WatchDog.GripperHeight, -WatchDog.Y - (WatchDog.GripperOpening*cos(WatchDog.Angle*M_PI/180)));
	MdlGripper[2].Translate(WatchDog.X + (WatchDog.GripperOpening*sin(WatchDog.Angle*M_PI/180)),WatchDog.GripperHeight, -WatchDog.Y + (WatchDog.GripperOpening*cos(WatchDog.Angle*M_PI/180)));	
	for(i=2 ;i>=0; i--)MdlGripper[i].rotY = WatchDog.Angle;
	for(i=2 ;i>=0; i--)MdlGripper[i].Draw(GLM_TEXTURE|GLM_SMOOTH);
	
	if(Key.Held.D || Joy->ButtonHeld(8) || Key.Held.S || Joy->ButtonHeld(7) 
	   || Key.Held.Q || Joy->ButtonHeld(1) || Key.Held.A || Joy->ButtonHeld(3) || Key.Held.W || Joy->ButtonHeld(2))WatchDogModel.A = 0.35f;
	else WatchDogModel.A = 1.0f;
	WatchDogModel.Translate(WatchDog.X,0,-WatchDog.Y);	
	WatchDogModel.rotY = WatchDog.Angle;
	WatchDogModel.Draw(GLM_TEXTURE|GLM_SMOOTH);
	
	Shad.TrowShader();
		
	char Temp[255];
	Text.SetColor(0.0f,0.0f,0.0f,1.0f);
	sprintf(Temp, "Watchdog Version 1.0a -> X: %4.4f, Y: %4.4f Angle: %4.2f, Gripper: %4.2f", WatchDog.X,WatchDog.Y,WatchDog.Angle,WatchDog.GripperHeight);
	Text.Y = 0;
	Text.DrawText(Temp);
	
	sprintf(Temp, "Physical -> FPS: %4.2f, Time: %4.2f (sec)  Speed: %4.6f(ft/s), %4.6f(ft/frame)",calcFPS(1.0),glfwGetTime(),WatchDog.Speed_FootPS,WatchDog.Speed_FootPerFrame);
	Text.Y = 6;
	Text.DrawText(Temp);
	
	glFlush();
	glfwSwapBuffers();
}

void InitOpenGL()
{
    glClearColor(0,0,0,0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//glEnable(GL_CULL_FACE);
	
	/*GLfloat fLowLight[] ={0,0,0,0};
	 glEnable(GL_FOG); glFogfv(GL_FOG_COLOR, fLowLight); 
	 glFogf(GL_FOG_START, 5.0f); 
	 glFogf(GL_FOG_END, 50.0f); 
	 glFogi(GL_FOG_MODE, GL_LINEAR);*/
		
	Textures->CreateTextures(3);
	Textures->AddTexture((char*)"Textures/Stone.tga");
	Textures->AddTexture((char*)"Textures/Brick.tga");
	Textures->AddTexture((char*)"Textures/Crackless.tga");
	
	Skybox.SkyboxTextures((char*)"Textures/Skybox/Sunset");
	//Skybox.SetColor(0.9f, 0.4f, 0.1f, 1.0);
	
	PlaneT.LoadFile((char*)"Models/Others/plane.obj");
	WatchDogModel.LoadFile((char*)"Models/Watchdog/watchdog2.obj");
	MdlBandera.LoadFile((char*)"Models/Objs/Bandera.obj");
	MdlGripper[0].LoadFile((char*)"Models/Watchdog/basegripper.obj");
	MdlGripper[1].LoadFile((char*)"Models/Watchdog/gripper1.obj");
	MdlGripper[2].LoadFile((char*)"Models/Watchdog/gripper2.obj");
	Rocks.LoadFile((char*)"Models/Objs/rocks.obj");
	if(WatchDog.UseShadder)
	{
		Shad.CreateShader();
		Shad.LoadShader((char*)"Shaders/Texture2.vs",GL_VERTEX_SHADER);
		Shad.LoadShader((char*)"Shaders/Texture2.fs",GL_FRAGMENT_SHADER);
		Shad.CompileShader();	
	}
}

void ReadConfig()
{
	FILE* ConfigFile = fopen ("Config.txt", "rb");
	int size;
	fseek(ConfigFile, 0, SEEK_END); // seek to end of file
	size = ftell(ConfigFile); // get current file pointer
	char* ConfigString = new char[size];
	rewind(ConfigFile);
	fread(ConfigString, 1, size, ConfigFile);
	fclose(ConfigFile);
	cout << ConfigString << endl;
	
	int Speed_IPS, Angle_GPS, FramesPS;
	int OpenCloseGripperAd, UpDownGripperAd;
	int UseShadder;
	sscanf(ConfigString, "-%d,%d,%d,%d,%d,%d",&Speed_IPS,&Angle_GPS,&FramesPS,&OpenCloseGripperAd,&UpDownGripperAd,&UseShadder);
	
	
	WatchDog.Speed_IPS= Speed_IPS/100.0;
	WatchDog.Angle_GPS = Angle_GPS/100.0;
	WatchDog.FramesPS = FramesPS/100.0;
	WatchDog.OpenCloseGripperAd = OpenCloseGripperAd/100.0;
	WatchDog.UpDownGripperAd = UpDownGripperAd/100.0;
	WatchDog.UseShadder = UseShadder;
	
	WatchDog.Speed_FootPS = WatchDog.Speed_IPS/12.0;
	WatchDog.Speed_FootPerFrame = WatchDog.Speed_FootPS /WatchDog.FramesPS;
	WatchDog.SpeedAngle = WatchDog.Angle_GPS / WatchDog.FramesPS;
	WatchDog.UpDownGripperLimit = 1.0f;
	WatchDog.OpenCloseGripperLimit = 1.0f;
	WatchDog.GripperDeltaOp = WatchDog.OpenCloseGripperAd / WatchDog.FramesPS;
	WatchDog.GripperDeltaUp = WatchDog.UpDownGripperAd/WatchDog.FramesPS;
	WatchDog.GripperOpening = 0.07f;
}

int main(int argc, char* argv[])
{
	USB->EnumerateHIDs();
    USB->HIDOpen(0x3995,0x0001);	
    USB->SetMode(SIMPLE_ASME_DRIVER);
    USB->HIDDescription();	
	USB->SendOutputPort((unsigned char) 0xFF);
	ReadConfig();
	
	MainApp->Init();
	MainApp->OpenWindow(1200,800,GLFW_WINDOW);
	MainApp->SetWindowTitle((char*)"WhatDog Control");
	MainApp->ReshapeFunc(Reshape);
	MainApp->SetDefaultInput();
	InitOpenGL();
	
	MainApp->Displayfunc(Display);
	USB->SendOutputPort((unsigned char) 0x00);
	MainApp->Run();

	delete MainApp;
	delete Joy;
	delete Textures;
	delete USB;
	
	return 0;
}
