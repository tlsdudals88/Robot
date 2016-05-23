#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>

typedef float vec3_t[3]; 
vec3_t cube[] = { 
 {-1,-1,-1}, 
 {-1,1,-1},
 {1,1,-1}, 
 {1,-1,-1},
 {1,1,1},
 {1,1,-1},
 {-1,1,-1},
 {-1,1,1}, 
 {1,-1,1},
 {-1,-1,1}, 
 {-1,-1,-1},
 {1,-1,-1}, 
 {-1,1,1},
 {-1,1,-1},
 {-1,-1,-1}, 
 {-1,-1,1},
  {1,1,1},
 {1,-1,1},
 {1,-1,-1},
 {1,1,-1}, 
 {-1,-1,1},
 {1,-1,1},
 {1,1,1},
 {-1,1,1}    
};
vec3_t color[] = {
 {1.0f, 0.0f, 0.0f},  //red
 {0.0f, 1.0f, 0.0f},  //green
 {0.0f, 0.0f, 1.0f},  //blue
 {1.0f, 1.0f, 0.0f},  //yellow
 {1.0f, 0.0f, 1.0f},  //magenta
 {0.0f, 1.0f, 1.0f},  //cyan
 {1.0f, 1.0f, 1.0f},  //white
 {.25f, .25f, .25f},  //dark gray
 {.60f, .40f, .70f},  //barney purple
 {.98f, .625f, .12f},  //pumpkin orange
 {.98f, .04f, .70f},  //pastel pink
 {.75f, .75f, .75f},  //light gray
 {.60f, .40f, .12f}  //brown
};


vec3_t rot = {0.,0.,0.};
vec3_t eye = {0.,0.,-5.};
vec3_t center = {0.,0.,0.};


float size=3.;
float theta=.0;
float thetaDelta=.125;
float eyeDelta=.125;
float scale=1.0;
float scaleDelta=1.01;
int  mouseX = 0;
int  mouseY = 0;
int  mouseState = 0;
int  mouseButton = 0;
int  projection = 0; 
int  aniOn = 0;
int  depthOn = 1;
int  openOn = 0;
int  fillOn = 0;
int  windowWidth, windowHeight;
float anitheta=.0;
float anithetaDelta=.125;
GLUquadricObj *c;

GLUquadricObj *OBJ;


int increase_flag = 0;
int decrease_flag = 0;


void head();
void Draw_Body();
void Draw_R_shoulder();
void Draw_L_shoulder();
void Draw_R_arm_up();
void Draw_R_arm_down();
void Draw_L_arm_up();
void Draw_L_arm_down();
void Draw_R_pelvis();
void Draw_L_pelvis();
void Draw_R_leg();
void Draw_R_leg2();
void Draw_R_knee();
void Draw_R_elbow();
void Draw_L_leg();
void Draw_L_leg2();
void Draw_L_knee();
void Draw_L_elbow();


void Draw_L_arm_up()
{  
 glScalef(.3, .3, 1.3); 

 gluCylinder(OBJ, 0.6, 0.6, 0.5, 30,1); 


 //glutWireCube(1.0);
}

void Draw_L_arm_down()
{  
 glScalef(.3, .3, 1.3); 

 gluCylinder(OBJ, 0.6, 0.6, 0.7, 30,1); 


 //glutWireCube(1.0);
}

void Draw_L_shoulder()
{
	glutWireSphere(.2, 10, 10);
}

void Draw_L_elbow()
{
	glutWireSphere(0.15, 10, 10);
}

void Draw_R_arm_up()
{
 glScalef(.3, .3, 1.3);

 gluCylinder(OBJ, 0.6, 0.6, 0.5, 30,1); 
 //glutWireCube(1.0);
}

void Draw_R_arm_down()
{  
 glScalef(.3, .3, 1.3); 

 gluCylinder(OBJ, 0.6, 0.6, 0.7, 30,1); 


 //glutWireCube(1.0);
}

void Draw_R_shoulder()
{
	glutWireSphere(.2, 10, 10);
}

void Draw_R_elbow()
{
	glutWireSphere(0.15, 10, 10);
}

void Draw_Body()
{
	glScalef(1, 1, 2);
	gluCylinder(OBJ, 0.5, 0.5, 1, 20, 20);
}


void Draw_L_leg()
{
	glScalef(.3, .3, 0.8);
	gluCylinder(OBJ, .7, .7, 1, 10, 10);
}

void Draw_L_leg2()
{
	glScalef(.3, .3, 0.7);
	gluCylinder(OBJ, .7, .7, 1, 10, 10);
}

void Draw_L_knee()
{
	glutWireSphere(.15, 10, 10);
}

void Draw_L_pelvis() 
{
	glutWireSphere(.2, 10, 10);
}
void Draw_R_leg()
{
	glScalef(.3, .3, .8);
	gluCylinder(OBJ, .7, .7, 1, 10, 10);
}
void Draw_R_knee()
{
	glutWireSphere(.15, 10, 10);
}

void Draw_R_leg2()
{
	glScalef(0.3, 0.3, 0.7);
	gluCylinder(OBJ, 0.7, 0.7, 1, 10, 10);
}

void Draw_R_pelvis() 
{
	glutWireSphere(.2, 10, 10);
}
void Draw_Head()
{
	if(fillOn) glutSolidSphere(.43, 10, 10);
	else glutWireSphere(.43, 10, 10);
}


void myDisplay (void)
{
	OBJ = gluNewQuadric();
	gluQuadricDrawStyle(OBJ,GLU_LINE);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
 
	if(!projection)
		gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);

	glRotatef(rot[0], 1.0f, 0.0f, 0.0f);
	glRotatef(rot[1], 0.0f, 1.0f, 0.0f);
	glRotatef(rot[2], 0.0f, 0.0f, 1.0f);
	glScalef(scale, scale, scale);
 	
	glRotatef(-anitheta, .0, .0, 1.); 

	glPushMatrix();  

	glPushMatrix(); 
			glTranslatef(.0, -.3, -2.5);
			Draw_L_leg2();
		glPopMatrix();

		glPushMatrix(); 
			glTranslatef(.0, -.3, -1.7);
			Draw_L_knee();
		glPopMatrix();

		glPushMatrix(); 
			glTranslatef(.0, -.3, -1.6);
			Draw_L_leg();
		glPopMatrix();

		glTranslatef(.0, -.3, -.7);
		Draw_L_pelvis();
	glPopMatrix(); 

	glPushMatrix();
		glPushMatrix();
			glTranslatef(.0, .3, -2.5);
			Draw_R_leg2();
		glPopMatrix();

		glPushMatrix(); 
			glTranslatef(.0, .3, -1.7);
			Draw_R_knee();
		glPopMatrix();

		glPushMatrix(); 
			glTranslatef(.0, .3, -1.6);
			Draw_R_leg();
		glPopMatrix();

		glTranslatef(.0, .3, -.7);
		Draw_R_pelvis();
	glPopMatrix();

	glTranslatef(.0, 0, .5);

	

	glPushMatrix();

		glPushMatrix();
			glRotatef(30, -1, .0, .0);
			glTranslatef(.0, -1., -0.4);
			Draw_L_arm_up();
		glPopMatrix();


		glPushMatrix();
			glTranslatef(0.0, -1.13, 0.04);
			Draw_L_elbow();
		glPopMatrix();
		
		
		glPushMatrix();
			glRotatef(30, -1., .0, .0);
			glTranslatef(.0, -1., -1.4);
			Draw_L_arm_down();
		glPopMatrix();


		glPushMatrix();
			glTranslatef(.0, -1.62, -0.8);
			Draw_L_shoulder();
		glPopMatrix();

		glTranslatef(.0, -.7, .77);
		Draw_L_shoulder();

	glPopMatrix(); 

		
	glPushMatrix();

		glPushMatrix();
			glPushMatrix();
			glRotatef(30, 1., .0, .0);
			glTranslatef(.0, 1., -0.4);
			Draw_R_arm_up();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0, 1.13, 0.04);
			Draw_L_elbow();
		glPopMatrix();

		glPushMatrix();
			glRotatef(30, 1., .0, .0);
			glTranslatef(.0, 1., -1.4);
			Draw_R_arm_down();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(.0, 1.62, -0.8);
			Draw_L_shoulder();
		glPopMatrix();

		glTranslatef(.0, .7, .77);
		Draw_R_shoulder();
	glPopMatrix(); 

	glPushMatrix();
		glTranslatef(0, 0, -1);
		Draw_Body();
	glPopMatrix(); 

	glTranslatef(0., 0., 1.4);
		Draw_Head();

	glutSwapBuffers();
    
}

void myLookAt(int key)
{
	if(key == GLUT_KEY_UP) {
		eye[2] = eye[2]-cos(theta)*eyeDelta;
		eye[0] = eye[0]+sin(theta)*eyeDelta;
	}
	else if(key == GLUT_KEY_DOWN) {
		eye[2] = eye[2]+cos(theta)*eyeDelta;
		eye[0] = eye[0]-sin(theta)*eyeDelta;
	}
		center[2] = eye[2]-cos(theta);
		center[0] = eye[0]+sin(theta);
}

void myResize (int width, int height){    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
	glViewport(0, 0, width, height);    
	glMatrixMode(GL_PROJECTION);   
	glLoadIdentity(); 

	if(projection) {
		glOrtho(-size, size, -size, size, -size, size); 
		eye[2] = 0.;
	}
	else {
		gluPerspective(60., (float)width/height, .1, 100.);
		eye[2] = 5.;
		myLookAt(0);
	}

	glEnable(GL_DEPTH_TEST);
	windowWidth=width;
	windowHeight=height;
}

void myIdle()
{
	anitheta = anitheta + anithetaDelta;

	glutPostRedisplay();
}

void myKeyboard (unsigned char key, int x, int y)
{ 
	switch (key) { 
	case ' ':
		aniOn = !aniOn;
		
		if(aniOn)
			glutIdleFunc(myIdle);
		else
			glutIdleFunc(NULL);
		break;

	case 'o': 
		openOn = !openOn;
		break;

	/*case 'f':
		fillOn = !fillOn;
		if(fillOn) 
			gluQuadricDrawStyle(c, GLU_FILL);
		else 
			gluQuadricDrawStyle(c, GLU_LINE);
	    break;*/

	case 'p':
		projection = !projection;
		myResize(windowWidth, windowHeight);
		break;

	case 'd':
		depthOn = !depthOn;
		if(depthOn) 
			glEnable(GL_DEPTH_TEST);
		else 
			glDisable(GL_DEPTH_TEST);
		break;

	case 'z':
		increase_flag = 1;
		decrease_flag = 0;
		break;

	case 'x':
		decrease_flag = 1;
		increase_flag = 0;
		break;

	case 'c':
		increase_flag = 0;
		decrease_flag = 0;
		break;

	}
  	glutPostRedisplay();
}

void mySKeyboard (int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP :
		rot[0] = rot[0]+5;
		break;
	case GLUT_KEY_DOWN :
		rot[0] = rot[0]-5;
		break;
	case GLUT_KEY_LEFT :
		theta-=thetaDelta;  
		break;
	case GLUT_KEY_RIGHT :
		theta+=thetaDelta; 
		break;
	default : 
		return;
	}

 	myLookAt(key);

	glutPostRedisplay();
}

void myMouse(int btn, int state, int x, int y)
{
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		/*if(aniOn)	
			glutIdleFunc(NULL);*/

		mouseState = state;
		mouseButton = btn;
		mouseX = x;
		mouseY = y;
	}
	else if(btn == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		/*if(aniOn)	
			glutIdleFunc(myIdle);*/

		mouseState = -1;
	}
	else
		return;

	glutPostRedisplay();
}

void myMotion(int x, int y)
{
	if(mouseButton == GLUT_LEFT_BUTTON && mouseState == GLUT_DOWN) {

		rot[1] -= (mouseX - x)/5.;
		rot[0] -= (mouseY - y)/5.;

		glutPostRedisplay();

		mouseX = x;
		mouseY = y;
	}
}

void myTimer(int Value)
{
	if(increase_flag == 1){
		scale = scale * scaleDelta;
	}

	if(decrease_flag == 1){
		scale = scale / scaleDelta;
	}

	glutPostRedisplay();
	glutTimerFunc(40,myTimer,1); 

}

void main (int argc,char** argv)
{
  	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(500,500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Youngmin_Shin OpenGL Project");

	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myResize);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySKeyboard);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);

	glutIdleFunc(myIdle);

	glutTimerFunc(40,myTimer,1);

	glutMainLoop();
}



