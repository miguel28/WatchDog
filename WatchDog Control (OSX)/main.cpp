#include "WatchDog.h"
#include "Scene.h"
#include "GridHandler.h"

MK_GLFWApp *MainApp = new MK_GLFWApp();
WatchDogClass *WatchDog;
Scene *MyScene;
MK_Camera* MainCam = new MK_Camera(800,600,75.0f,0.01f,500.0f);
GridDrawer *Grid;

MK_ModelOBJ MdlBandera;
MK_TPlane Plane(-32,0,-32,64,64);

void DEBUG_Grid()
{
	float i;
	for(i=0.0f; i<=16.0f; i+=Grid->GridSize)
		Grid->SetPosition(1.0f,i,0x01);
	
	for(i=1.25; i<25.0f; i+=Grid->GridSize)
		Grid->SetPosition(-i,0.0f,0x01);
	
	for(i=0.0f; i<=16.0f; i+=Grid->GridSize)
		Grid->SetPosition(-24.0f,i,0x01);
	
	for(i=-1.0f; i<=25.0f; i+=Grid->GridSize)
		Grid->SetPosition(-i,16.0f,0x01);
}

void BatSystem()
{	
	WatchDog->BackCollision = false;
	WatchDog->FronCollision = false;
	
	Vector3f Vect1 = WatchDog->CollisionFront1.Rotate(WatchDog->Angle);
	
	if(Grid->GetThroughtVector(WatchDog->Position, Vect1))
		WatchDog->FronCollision = true;
	/*Vect1 += WatchDog->Position;
	Grid->Template->Position = Vect1;
	Grid->Template->Draw(GLM_TEXTURE|GLM_SMOOTH);*/
	
	
	Vect1 = WatchDog->CollisionFront2.Rotate(WatchDog->Angle);
	if(Grid->GetThroughtVector(WatchDog->Position, Vect1))
		WatchDog->FronCollision = true;
	/*Vect1 += WatchDog->Position;
	Grid->Template->Position = Vect1;
	Grid->Template->Draw(GLM_TEXTURE|GLM_SMOOTH);*/
	
	Vect1 = WatchDog->CollisionBack1.Rotate(WatchDog->Angle);
	if(Grid->GetThroughtVector(WatchDog->Position, Vect1))
		WatchDog->BackCollision = true;
	/*Vect1 += WatchDog->Position;
	Grid->Template->Position = Vect1;
	Grid->Template->Draw(GLM_TEXTURE|GLM_SMOOTH);*/
	
	Vect1 = WatchDog->CollisionBack2.Rotate(WatchDog->Angle);
	if(Grid->GetThroughtVector(WatchDog->Position, Vect1))
		WatchDog->BackCollision = true;
	/*Vect1 += WatchDog->Position;
	Grid->Template->Position = Vect1;
	Grid->Template->Draw(GLM_TEXTURE|GLM_SMOOTH);*/
}

void Reshape(int width, int height)
{
	MainCam->Width=width;
	MainCam->Height=height;
	MainCam->aspect=width/(float)height;
}

void DrawModels()
{
	
	MyScene->Reset();
	MyScene->Textures->Blind(2,GL_LINEAR);
	
	Plane.Draw(AxisX,64.0f);
	
	Grid->Update(WatchDog->Position, WatchDog->Distance, WatchDog->Angle);
	Grid->DrawGrid();
	MdlBandera.Rotation.Y=180.0;
	MdlBandera.Draw(GLM_TEXTURE|GLM_SMOOTH);
	WatchDog->Draw();
	
	BatSystem();
}

void DrawTexts()
{
	char Temp[255];
	MyScene->Text->SetColor(0.0f,0.0f,0.0f,1.0f);
	sprintf(Temp, "Watchdog Version 3.0b2 -> X: %4.4f, Z: %4.4f Angle: %4.2f", WatchDog->Position.X,WatchDog->Position.Z,WatchDog->Angle);
	MyScene->Text->Y = 0;
	MyScene->Text->DrawText(Temp);
	
	sprintf(Temp, "Physical -> FPS: %4.2f, Time: %4.2f (sec)",calcFPS(1.0),glfwGetTime());
	MyScene->Text->Y = 6;
	MyScene->Text->DrawText(Temp);
	
	MyScene->Text->Y = 12;
	if(WatchDog->USB->HIDisOpen)
	{
		if(WatchDog->USB->Error)
		{
			MyScene->Text->SetColor(1.0f,0.0f,0.0f,1.0f);
			sprintf(Temp, "Error: Hid was Disconnected!");
		}
		else
		{
			MyScene->Text->SetColor(0.0f,0.5f,0.0f,1.0f);
			sprintf(Temp, "Hid Opened Successfully!");
		}
	}
	else 
	{
		MyScene->Text->SetColor(1.0f,0.0f,0.0f,1.0f);
		sprintf(Temp, "Error: Hid not connected!");
	}
	MyScene->Text->DrawText(Temp);
	
	MyScene->Text->SetColor(0.0f,0.0f,0.0f,1.0f);
	sprintf(Temp, "Distance: %4.2f  %d , Encoder1: %d, Encoder2: %d",WatchDog->Distance,WatchDog->tDistance,
			WatchDog->Encoder1,WatchDog->Encoder2);
	MyScene->Text->Y = 18;
	MyScene->Text->DrawText(Temp);
	
	if(WatchDog->GetSystemMode())
	{
		MyScene->Text->SetColor(0.0f,0.0f,1.0f,1.0f);
		sprintf(Temp, "Close Loop System");
	}
	else
	{
		MyScene->Text->SetColor(0.0f,1.0f,1.0f,1.0f);
		sprintf(Temp, "Open Loop System");
	}

	MyScene->Text->Y = 24;
	MyScene->Text->DrawText(Temp);
	
}

void Display()
{
	if(GetKeyHeld(KEY_ESC))MainApp->Exit();
	
	WatchDog->CheckControls();
	Grid->ActiveSystem = WatchDog->CanTakeDistance;
	Grid->SetSolid(WatchDog->SolidSystem);
	
	MyScene->ClearScreen();
	MainCam->ThirdPersonCamera(WatchDog->Position,WatchDog->Angle,2.5f);
	MyScene->PaintSkybox(WatchDog->Position.X,2,WatchDog->Position.Z);
	
	if(WatchDog->UseShadder)MyScene->Shad->UseShader();
	MyScene->SetLights(WatchDog->Position.X, WatchDog->Position.Z, WatchDog->Angle);
	MyScene->SetMaterials();
	
	DrawModels();
	
	MyScene->Shad->TrowShader();
	DrawTexts();
	MyScene->Flush();
}

void ReadModels()
{
	WatchDog->LoadModels();
	Grid->LoadModel((char*) "Models/Others/Bricks.obj");
	MdlBandera.LoadFile((char*)"Models/Objs/Bandera.obj");
	Grid->Clear();
	Grid->ActiveSystem = false;
	DEBUG_Grid();
}

int main(int argc, char* argv[])
{	
	WatchDog = new WatchDogClass();
	MainApp = new MK_GLFWApp();
	MainApp->Init();
	
	//MainApp->OpenWindow(1200,800,GLFW_WINDOW);
	MainApp->OpenWindow(600,400,GLFW_WINDOW);
	MainApp->SetWindowTitle((char*)"WatchDog PC Control 3.0 beta 2");
	MainApp->ReshapeFunc(Reshape);
	MainApp->SetDefaultInput();
	
	MyScene = new Scene();
	Grid = new GridDrawer(64.0f,64.0f,0.25f);
	ReadModels();
	
	MainApp->Displayfunc(Display);
	MainApp->Run();
	
	delete MainApp;
	delete WatchDog; 
	
	return 0;
}

