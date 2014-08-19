#include "MKGL/MK_App.h"
#include "USBInterface/USBInterfaceClass.h"

USBInterface USB;

GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat mat1_ambiente[] = { 0.0, 0.0, 0.4, 1.0 };
GLfloat mat1_difusa[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat mat1_especular[] = { 1.0, 0.0, 0.0, 1.0 };

MK_Texture Textures;
MK_Skybox sky;
MK_Camera MainCam(800,600,75.0f,0.01f,500.0f);
MK_ModelOBJ model,p,Rocks;
MK_Cube cube(-3,0,-0.5,1,1,1);
MK_TPlane plane(-16,0,-16,32,32);
MK_Text Text;
MK_Light Light0(GL_LIGHT0, MK_Spot_CutOff);
MK_Light Light1(GL_LIGHT1,MK_Spot);

MK_Shader Shad;


typedef struct
{
	GLfloat X,Y,Angle;
	
}_CarType;
_CarType Car;

void Reshape(int width, int height)
{
	MainCam.Width=width;
	MainCam.Height=height;
	MainCam.aspect=width/(float)height;
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	MainCam.ThirdPersonCamera(Car.X,Car.Y,0,Car.Angle,1.5,30);
	
	Shad.UseShader();
	
	
	glPushMatrix();
	{
		glLoadIdentity();
		glTranslatef(Car.X,2,-Car.Y);
		//glRotatef(Car.Angle, 0, 1, 0);
		glScalef(0.5f,0.5f,0.5f);
		glColor3f(1.0f, 1.0f, 1.0f);
		
		sky.Render(10.0f);
	}
	glPopMatrix();
	
	// Definimos el material del objeto modificando la forma en 
	// como refleja cada componente de la luz que le llega.
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat1_ambiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat1_difusa);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat1_especular);
	// El brillo especular pequeno (de 0 a 255).
	glMaterialf(GL_FRONT, GL_SHININESS, 20);
		
	Light0.SetPosition(-0.5f, 0.5f, 0.0f);
	Light0.SetAmbient(0.2, 0.2, 0.2, 1.0);
	Light0.SetEspecular(0.0, 0.0, 0.99, 1.0);
	Light0.SetDifuse(0.1, 0.0, 0.0, 1.0);
	Light0.Traslate(Car.X,0, -Car.Y);
	Light0.Rotate(0.0f,Car.Angle,0.0f);
	Light0.Blind();
	
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	
	
	//Textures.Blind(1,GL_LINEAR);
	//plane.Draw(AxisX,32.0f);
	p.Draw(GLM_TEXTURE|GLM_SMOOTH);
	Rocks.Draw(GLM_TEXTURE|GLM_SMOOTH);
	cube.Draw();

	glPushMatrix();
	{
		glTranslatef(Car.X,0,-Car.Y);
		glRotatef(Car.Angle, 0, 1, 0);
		glScalef(0.5f,0.5f,0.5f);
		glColor3f(1.0f, 1.0f, 1.0f);
		
		model.Draw(GLM_TEXTURE|GLM_SMOOTH);
	}
	glPopMatrix();

	char Temp[255];
	sprintf(Temp, "Watchdog Demo v1.1 X: %4.4f, Y: %4.4f Angle: %4.2f", Car.X,Car.Y,Car.Angle);
	Text.DrawText(Temp);
	
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void Keyboard(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_RIGHT:
			if(Car.Angle>0)Car.Angle=Car.Angle-0.5f;
			else Car.Angle=359;
			USB.SendOutputPort((unsigned char) 0x01);
			break;
		case GLUT_KEY_LEFT:
			if(Car.Angle<360)Car.Angle=Car.Angle+0.5f;
			else Car.Angle=0;
			USB.SendOutputPort((unsigned char) 0x02);
			break;
		case GLUT_KEY_UP:
			Car.X+=0.15f*cos(Car.Angle*M_PI/180);
			Car.Y+=0.15f*sin(Car.Angle*M_PI/180);
			USB.SendOutputPort((unsigned char) 0x03);
			break;
		case GLUT_KEY_DOWN:
			Car.X-=0.15f*cos(Car.Angle*M_PI/180);
			Car.Y-=0.15f*sin(Car.Angle*M_PI/180);
			USB.SendOutputPort((unsigned char) 0x04);
			break;
		default:
			break;
	}
	
}

void Init()
{
    glClearColor(0,0,0,0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//glEnable(GL_CULL_FACE);

	
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
    glMateriali(GL_FRONT, GL_SHININESS,50);
	
	/*GLfloat fLowLight[] ={0,0,0,0};
	glEnable(GL_FOG); glFogfv(GL_FOG_COLOR, fLowLight); 
	glFogf(GL_FOG_START, 5.0f); 
	glFogf(GL_FOG_END, 50.0f); 
	glFogi(GL_FOG_MODE, GL_LINEAR);*/
	
	
	sky.SkyboxTextures((char*)"Textures/Skybox/sp3");
	sky.SetColor(0.8f, 0.8f, 0.8f, 1.0);
	
	Textures.CreateTextures(4);
	Textures.AddTexture((char*)"Textures/Stone.tga");
	Textures.AddTexture((char*)"Textures/Brick.tga");
	Textures.AddTexture((char*)"Textures/chrome.tga");
	Textures.AddTexture((char*)"Textures/gold.tga");
	
	model.LoadFile((char*)"Models/Watchdog/watchdog2.obj");
	p.LoadFile((char*)"Models/plane.obj");
	Rocks.LoadFile((char*)"Models/Objs/rocks.obj");
	Shad.CreateShader();
	Shad.LoadShader((char*)"Shaders/Texture2.vs",GL_VERTEX_SHADER);
	Shad.LoadShader((char*)"Shaders/Texture2.fs",GL_FRAGMENT_SHADER);
	Shad.CompileShader();
}

int main(int argc, char **argv)
{
    
	USB.EnumerateHIDs();
    USB.HIDOpen(0x3995,0x0001);	
    USB.SetMode(SIMPLE_ASME_DRIVER);
    USB.HIDDescription();	
	USB.SendOutputPort((unsigned char) 0xFF);
	
	glutInit(&argc, argv);
	MK_Application MainApp(20,20,1330,900,(char*)"Watchdog Demo v1.1");
    
	Init();
	
	MainApp.DisplayFunc(Display);
	MainApp.ReshapeFunc(Reshape);
	MainApp.SpecialFunc(Keyboard);
	USB.SendOutputPort((unsigned char) 0x00);
	MainApp.Run();
	
	Textures.DeleteTextures();
	sky.DeleteTextures();
	
    return 0;
}
