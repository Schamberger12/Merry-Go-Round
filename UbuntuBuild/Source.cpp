//Gregory Schamberger, gscham2
//Merry-Go-Round

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/GL.h>
#endif

#include <stdio.h>
#include <math.h>


#define KEY_ESC 27
#define KEY_A 65
#define KEY_D 68
#define KEY_H 72
#define KEY_R 82
#define KEY_S 83
#define KEY_W 87
#define KEY_I 73
#define KEY_J 74
#define KEY_K 75
#define KEY_L 76
#define KEY_U 85
#define KEY_O 79

bool isPossessingMerry(); 
bool isPossessingCars();

//Define initial size of the window
GLint width = 800;
GLint height = 600;

//Define Colors
GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat yellow_t[] = { 1.0, 1.0, 0.0, 0.7 };
GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat green_t[] = { 0.0, 1.0, 0.0, 0.7 };
GLfloat darkGreen[] = { 0.0, 0.3, 0.0, 1.0 };
GLfloat darkGreen_t[] = { 0.0, 0.3, 0.0, 0.7 };
GLfloat brown[] = { 0.5, 0.35, 0.05, 1.0 };
GLfloat brown_t[] = { 0.5, 0.35, 0.05, 0.7 };
GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat white_t[] = { 1.0, 1.0, 1.0, 0.7 };
GLfloat blue[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat blue_t[] = { 0.0, 0.0, 1.0, 0.7 };
GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat red_t[] = { 1.0, 0.0, 0.0, 0.7 };
GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat black_t[] = { 0.0, 0.0, 0.0, 0.7 }; 
GLfloat ghost[] = { 0.5, 0.5, 0.5, 0.5 };

// Variables for rotation.
GLfloat treeRotate = 0;
GLfloat teapotRotate = 0;

//Variable for sin wave/cos wave
GLfloat sinWave = 0; 
GLfloat timeWave = 0;
GLfloat cosWave = 0;

//Variables for cars
GLfloat car1x = -7.0f;
GLfloat car1z = 7.0f;
GLfloat car2x = 4.0f;
GLfloat car2z = 7.0f;
GLfloat car3x = 4.0f;
GLfloat car3z = 3.0f;
GLfloat car4x = -7.0f;
GLfloat car4z = 3.0f;
GLfloat carDirection = 0;
GLfloat carDirection2 = 0;
GLfloat carDirection3 = 0;
GLfloat carDirection4 = 0;

//Variables for Ghost
GLfloat ghost_x = 0.0f; 
GLfloat ghost_y = 5.0f; 
GLfloat ghost_z = 0.0f; 

// Variable for zoom in/out.
GLfloat zoom_distance = 0;

// Variable for pan
GLfloat pan_angle = 0;

//Functions
void init();
void idle();
void display();
void reshape(GLint, GLint);
GLvoid keyboard(unsigned char, int, int);


bool isPossessingMerry() {

	if ((ghost_x >= 0.0 && ghost_x <= 6.0) && (ghost_y >= 0.0 && ghost_y <= 5.5)
		&& (ghost_z >= -7.5 && ghost_z <= -2.5)) {
		return true;
	}
	else
		return false; 
	
}

bool isPossessingCars() {

	if ((ghost_x >= -7.0 && ghost_x <= 4.0) && (ghost_y >= 0.0 && ghost_y <= 3.0)
		&& (ghost_z >= 3.0 && ghost_z <= 7.0)) {
		return true;
	}
	else
		return false;

}

//------------------------------------------------------------------------ main
int main(int argc, char** argv) {
	// Initialize glut, passing along command-line parameters  
	glutInit(&argc, argv);

	// Initialize the display mode, double buffered with RGBA color, enables the usage of the depth buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Set the window's position (Pixels on screen).
	glutInitWindowPosition(80, 80);

	// Initialize the physical window size (Pixels on screen).
	glutInitWindowSize(width, height);

	// Set the title of the window.
	glutCreateWindow("Tree and Teapot");


	//Register the callback event handlers
	glutReshapeFunc(reshape); //When the window is reshaped/resized
	glutDisplayFunc(display); // To redraw the screen as needed
	glutIdleFunc(idle);	//When there is nothing else to do
	glutKeyboardFunc(keyboard); //Add  keyboard input to program


	init(); //Set light sources
	glutMainLoop();
}

//------------------------------------------------------------------------ Init
// Initializing the lighting 
// Setting the position of the light and the color of ambient, diffuse, specular.
void init() {

	//Setting lighting parameters for light source GL_LIGHT0
	GLfloat direction[] = { 1.0f, 1.0f, 1.0f, 0.0f }; //light in homogeneous object coordinates

	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glLightfv(GL_LIGHT0, GL_POSITION, direction);

	               // the renderer considers light                 // turn LIGHT0 on


	GLfloat l_position[] = { -1.0f, 1.0f, 6.0f, 1.0f };
	GLfloat mat_spec[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shine[] = { 50.0f };


	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shine);
	glLightfv(GL_LIGHT1, GL_AMBIENT, red);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, red);
	glLightfv(GL_LIGHT1, GL_SPECULAR, red);
	glLightfv(GL_LIGHT1, GL_POSITION, l_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);              // the renderer considers depth. If it is not enabled, the depth buffer is not updated.

}


//--------------------------------------------------------------------- display
// This function is called each time the screen is to be drawn
void display() {

	//Setting Camera view
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(60, (float)width / (float)height, 1.0, 50.0);

	gluLookAt(0.0f, 10.0f, 15.0f - zoom_distance,   // eye 
		pan_angle, 0.0f, 0.0f,   // center
		0.0f, 1.0f, 0.0f);  // up

							// Clear the screen to the clear colour
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Subsequent transformations will apply to the modelview transformation.
	//The modelview matrix transforms directly from object coordinates to eye coordinates.
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();						//1


	// Set current matrix on the stack 


	//Draw Objects on the scene
	//Plane
	//Should be in a counter-clockwise order. 

	glPushMatrix();						//2
	glNormal3f(0, 1, 0); 
	glBegin(GL_QUADS);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
		glVertex3f(20, 0, -20);
		glVertex3f(-20, 0, -20);
		glVertex3f(-20, 0, 20);
		glVertex3f(20, 0, 20);
	glEnd();
	glPopMatrix();						//1
	

//--------------Merry-Go-Round--------------------

	//Top of Merry-Go-Round

	glPushMatrix();						//2
	glTranslatef(3.0f, 0.0f, -5.0f);
	glPushMatrix();						//3
	glRotatef(treeRotate, 0.0f, 1.0f, 0.0f);
	glTranslatef(00.0f, 5.0f, 0.0f);
	glBegin(GL_TRIANGLES);
		//Front
		glNormal3f(0, 1, 1);
		if (isPossessingMerry()) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, red_t);
		}
		else {
			glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
		}
		glVertex3f(0.0f, 1.5f, 0.0f);
		glVertex3f(-2.5f, -1.5f, 2.5f);
		glVertex3f(2.5f, -1.5f, 2.5f);
		//right
		glNormal3f(1, 1, 0);
		if (isPossessingMerry()) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, white_t);
		}
		else {
			glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
		}
		glVertex3f(0.0f, 1.5f, 0.0f);
		glVertex3f(2.5f, -1.5f, 2.5f);
		glVertex3f(2.5f, -1.5f, -2.5f);
		//back
		glNormal3f(0, 1, -1);
		if (isPossessingMerry()) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, red_t);
		}
		else {
			glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
		}
		glVertex3f(0.0f, 1.5f, 0.0f);
		glVertex3f(2.5f, -1.5f, -2.5f);
		glVertex3f(-2.5f, -1.5f, -2.5f);
		//left
		glNormal3f(-1, 1, 0);
		if (isPossessingMerry()) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, white_t);
		}
		else {
			glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
		}
		glVertex3f(0.0f, 1.5f, 0.0f);
		glVertex3f(-2.5f, -1.5f, -2.5f);
		glVertex3f(-2.5f, -1.5f, 2.5f);
	glEnd(); 
	glDisable(GL_BLEND); 
	glPopMatrix();						//2

	//Base of Merry-Go-Round
	//Cylinder
	GLUquadricObj *quadratic = gluNewQuadric();
	glPushMatrix();						//3
	if (isPossessingMerry()) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, brown_t);
	}
	else {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, brown);
	}
	glRotatef(treeRotate, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, .5f, -0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	//void gluCylinder(	GLUquadric* quad, GLdouble base, GLdouble top, GLdouble height, GLint slices,GLint stacks);
	gluCylinder(quadratic, 4.0f, 4.0f, 0.5f, 8, 8);
	glDisable(GL_BLEND); 
	glPopMatrix();						//2

	//Disc on top
	GLUquadricObj *discQuad = gluNewQuadric();
	glPushMatrix();						//3
	if (isPossessingMerry()) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, brown_t);
	}
	else {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, brown);
	}
	glRotatef(treeRotate, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, .5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluDisk(discQuad, 0.0f, 4.0f, 8, 8);
	glDisable(GL_BLEND); 
	glPopMatrix();						//2

	//Horse poles
	GLUquadricObj *frontRight = gluNewQuadric();
	glPushMatrix();						//3
	if (isPossessingMerry()) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow_t);
	}
	else {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
	}
	glRotatef(treeRotate, 0.0f, 1.0f, 0.0f);
	glTranslatef(2.0f, 4.0f, -2.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(frontRight, 0.1f, 0.1f, 4.0f, 8, 8);
	glPushMatrix();						//4
	if (isPossessingMerry()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blue_t);
	}
	else {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
	}
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); 
	glTranslatef(0.0f, -2.0f, 0.0f); 
	glTranslatef(0.0f, sinWave, 0.0f);
	glutSolidSphere(0.5f, 8, 8);
	glPopMatrix();						//3
	glPopMatrix();						//2

	GLUquadricObj *quadratic1 = gluNewQuadric();
	glPushMatrix();						//3
	if (isPossessingMerry()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow_t);
	}
	else {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
	}
	glRotatef(treeRotate, 0.0f, 1.0f, 0.0f);
	glTranslatef(2.0f, 4.0f, 2.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	//void gluCylinder(	GLUquadric* quad, GLdouble base, GLdouble top, GLdouble height, GLint slices,GLint stacks);
	gluCylinder(quadratic1, 0.1f, 0.1f, 4.0f, 8, 8);
	glPushMatrix();						//4
	if (isPossessingMerry()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, green_t);
	}
	else {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
	}
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -2.0f, 0.0f);
	glTranslatef(0.0f, cosWave, 0.0f);
	glutSolidSphere(0.5f, 8, 8);
	glPopMatrix();						//3
	glPopMatrix();						//2


	GLUquadricObj *quadratic2 = gluNewQuadric();
	glPushMatrix();						//3
	if (isPossessingMerry()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow_t);
	}
	else {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
	}
	glRotatef(treeRotate, 0.0f, 1.0f, 0.0f);
	glTranslatef(-2.0f, 4.0f, -2.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	//void gluCylinder(	GLUquadric* quad, GLdouble base, GLdouble top, GLdouble height, GLint slices,GLint stacks);
	gluCylinder(quadratic2, 0.1f, 0.1f, 4.0f, 8, 8);
	glPushMatrix();						//4
	if (isPossessingMerry()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, red_t);
	}
	else {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	}
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -2.0f, 0.0f);
	glTranslatef(0.0f, cosWave, 0.0f);
	glutSolidSphere(0.5f, 8, 8);
	glPopMatrix();						//3
	glPopMatrix();						//2

	GLUquadricObj *quadratic3 = gluNewQuadric();
	glPushMatrix();						//3
	if (isPossessingMerry()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow_t);
	}
	else {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
	}
	glRotatef(treeRotate, 0.0f, 1.0f, 0.0f);
	glTranslatef(-2.0f, 4.0f, 2.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	//void gluCylinder(	GLUquadric* quad, GLdouble base, GLdouble top, GLdouble height, GLint slices,GLint stacks);
	gluCylinder(quadratic3, 0.1f, 0.1f, 4.0f, 8, 8);
	glPushMatrix();						//4
	if (isPossessingMerry()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, white_t);
	}
	else {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	}
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -2.0f, 0.0f);
	glTranslatef(0.0f, sinWave, 0.0f);
	glutSolidSphere(0.5f, 8, 8);
	glDisable(GL_BLEND);
	glPopMatrix();						//3
	glPopMatrix();						//2
	glPopMatrix();						//1
	//------------End of Merry-Go-Round--------------

	//-------------Start of "Cars" ----------------

	//body of car
	glPushMatrix();						//2
	if (isPossessingCars()) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow_t); 
	}
	else
		glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
	glTranslatef(car1x, 1.0f, car1z);
	glRotatef(carDirection, 0.0f, 1.0f, 0.0f); 
	glutSolidTeapot(1.0f);
	//Wheels of car
	glPushMatrix();						//3
	if (isPossessingCars()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black_t);
	}
	else
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black); 
	glTranslatef(0.7f, -0.7f, 0.8f);
	glRotatef(treeRotate, 0.0f, 0.0f, 1.0f);
	glutSolidTorus(0.15f, 0.3f, 8, 8); 
	glPopMatrix();						//2
	glPushMatrix();						//3
	if (isPossessingCars()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black_t);
	}
	else
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glTranslatef(0.7f, -0.7f, -0.8f);
	glRotatef(treeRotate, 0.0f, 0.0f, 1.0f);
	glutSolidTorus(0.15f, 0.3f, 8, 8);
	glPopMatrix();						//2
	glPushMatrix();						//3
	if (isPossessingCars()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black_t);
	}
	else
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glTranslatef(-0.7f, -0.7f, 0.8f);
	glRotatef(treeRotate, 0.0f, 0.0f, 1.0f);
	glutSolidTorus(0.15f, 0.3f, 8, 8);
	glPopMatrix();						//2
	glPushMatrix();						//3
	if (isPossessingCars()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black_t);
	}
	else
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glTranslatef(-0.7f, -0.7f, -0.8f);
	glRotatef(treeRotate, 0.0f, 0.0f, 1.0f);
	glutSolidTorus(0.15f, 0.3f, 8, 8);
	glPopMatrix();						//2
	glPopMatrix();						//1
	//body of car
	glPushMatrix();						//2
	if (isPossessingCars()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blue_t);
	}
	else
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
	glTranslatef(car2x, 1.0f, car2z);
	glRotatef(carDirection2, 0.0f, 1.0f, 0.0f);
	glutSolidTeapot(1.0f);
	//Wheels of car
	glPushMatrix();						//3
	if (isPossessingCars()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black_t);
	}
	else
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glTranslatef(0.7f, -0.7f, 0.8f);
	glRotatef(treeRotate, 0.0f, 0.0f, 1.0f);
	glutSolidTorus(0.15f, 0.3f, 8, 8);
	glPopMatrix();						//2
	glPushMatrix();						//3
	if (isPossessingCars()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black_t);
	}
	else
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glTranslatef(0.7f, -0.7f, -0.8f);
	glRotatef(treeRotate, 0.0f, 0.0f, 1.0f);
	glutSolidTorus(0.15f, 0.3f, 8, 8);
	glPopMatrix();						//2
	glPushMatrix();						//3
	if (isPossessingCars()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black_t);
	}
	else
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glTranslatef(-0.7f, -0.7f, 0.8f);
	glRotatef(treeRotate, 0.0f, 0.0f, 1.0f);
	glutSolidTorus(0.15f, 0.3f, 8, 8);
	glPopMatrix();						//2
	glPushMatrix();						//3
	if (isPossessingCars()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black_t);
	}
	else
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glTranslatef(-0.7f, -0.7f, -0.8f);
	glRotatef(treeRotate, 0.0f, 0.0f, 1.0f);
	glutSolidTorus(0.15f, 0.3f, 8, 8);
	glPopMatrix();						//2
	glPopMatrix();						//1
	//body of car
	glPushMatrix();						//2
	if (isPossessingCars()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, white_t);
	}
	else
		glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glTranslatef(car3x, 1.0f, car3z);
	glRotatef(carDirection3, 0.0f, 1.0f, 0.0f);
	glutSolidTeapot(1.0f);
	//Wheels of car
	glPushMatrix();						//3
	if (isPossessingCars()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black_t);
	}
	else
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glTranslatef(0.7f, -0.7f, 0.8f);
	glRotatef(treeRotate, 0.0f, 0.0f, 1.0f);
	glutSolidTorus(0.15f, 0.3f, 8, 8);
	glPopMatrix();						//2
	glPushMatrix();						//3
	if (isPossessingCars()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black_t);
	}
	else
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glTranslatef(0.7f, -0.7f, -0.8f);
	glRotatef(treeRotate, 0.0f, 0.0f, 1.0f);
	glutSolidTorus(0.15f, 0.3f, 8, 8);
	glPopMatrix();						//2
	glPushMatrix();						//3
	if (isPossessingCars()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black_t);
	}
	else
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glTranslatef(-0.7f, -0.7f, 0.8f);
	glRotatef(treeRotate, 0.0f, 0.0f, 1.0f);
	glutSolidTorus(0.15f, 0.3f, 8, 8);
	glPopMatrix();						//2
	glPushMatrix();						//3
	if (isPossessingCars()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black_t);
	}
	else
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glTranslatef(-0.7f, -0.7f, -0.8f);
	glRotatef(treeRotate, 0.0f, 0.0f, 1.0f);
	glutSolidTorus(0.15f, 0.3f, 8, 8);
	glPopMatrix();						//2
	glPopMatrix();						//1
		//body of car
	glPushMatrix();						//2
	if (isPossessingCars()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, red_t);
	}
	else
		glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glTranslatef(car4x, 1.0f, car4z);
	glRotatef(carDirection4, 0.0f, 1.0f, 0.0f);
	glutSolidTeapot(1.0f);
	//Wheels of car
	glPushMatrix();						//3
	if (isPossessingCars()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black_t);
	}
	else
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glTranslatef(0.7f, -0.7f, 0.8f);
	glRotatef(treeRotate, 0.0f, 0.0f, 1.0f);
	glutSolidTorus(0.15f, 0.3f, 8, 8);
	glPopMatrix();						//2
	glPushMatrix();						//3
	if (isPossessingCars()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black_t);
	}
	else
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glTranslatef(0.7f, -0.7f, -0.8f);
	glRotatef(treeRotate, 0.0f, 0.0f, 1.0f);
	glutSolidTorus(0.15f, 0.3f, 8, 8);
	glPopMatrix();						//2
	glPushMatrix();						//3
	if (isPossessingCars()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black_t);
	}
	else
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glTranslatef(-0.7f, -0.7f, 0.8f);
	glRotatef(treeRotate, 0.0f, 0.0f, 1.0f);
	glutSolidTorus(0.15f, 0.3f, 8, 8);
	glPopMatrix();						//2
	glPushMatrix();						//3
	if (isPossessingCars()) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black_t);
	}
	else
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glTranslatef(-0.7f, -0.7f, -0.8f);
	glRotatef(treeRotate, 0.0f, 0.0f, 1.0f);
	glutSolidTorus(0.15f, 0.3f, 8, 8);
	glPopMatrix();						//2
	glDisable(GL_BLEND); 
	glPopMatrix();						//1

	// ----------Ghost!------------

	glPushMatrix();						//2
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); 
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ghost);
	glTranslatef(ghost_x, ghost_y, ghost_z); 
	glutSolidSphere(0.5f, 8, 8);
	glPushMatrix();						//3
	GLUquadricObj *ghostQuad = gluNewQuadric();
	glRotatef(90.0f, 1.0, 0.0, 0.0); 
	gluCylinder(ghostQuad, 0.5, 1.0f, 2.0f, 8, 8);
	glDisable(GL_BLEND);
	glPopMatrix();						//2
	glPushMatrix();						//3
	glTranslatef(-0.25f, 0.1f, 0.4f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black);
	glutSolidSphere(0.1f, 8, 8); 
	glPopMatrix();						//2
	glPushMatrix();						//3
	glTranslatef(0.25f, 0.1f, 0.4f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black);
	glutSolidSphere(0.1f, 8, 8);
	glPopMatrix();						//2
	glPushMatrix();						//3
	glTranslatef(0.0f, -0.1f, 0.5f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black);
	glutSolidSphere(0.1f, 8, 8);
	glPopMatrix();						//2
	glPopMatrix();						//1



	glPopMatrix();						//0
	glutSwapBuffers();
}


//--------------------------------------------------------------------- idle
//updating rotation angles for tree and teapot
void idle() {
	teapotRotate += 0.05f;
	treeRotate -= 0.1f; 
	timeWave += 0.001f; 
	sinWave = 0.8f * sin(timeWave);
	cosWave = 0.8f * cos(timeWave);

	
	//car1
	if (car1x <= 4.0f && car1z == 7.0f) {
		carDirection = 0.0f;
		car1x += 0.01f;
	}
	if (car1x >= 4.0f && car1z > 3.0f) {
		car1z -= 0.01f;
		carDirection = 90.0f;
	}
	if (car1x >= -7.0f && car1z <= 3.0f){
		car1x -= 0.01f;
		carDirection = 180.0f;
	}
	if (car1x <= -7.0f && car1z <= 7.0f) {
		car1z += 0.01f; 
		carDirection = 270.0f; 
	}
	//car2
	if (car2x <= 4.0f && car2z == 7.0f) {
		carDirection2 = 0.0f;
		car2x += 0.01f;
	}
	if (car2x >= 4.0f && car2z > 3.0f) {
		car2z -= 0.01f;
		carDirection2 = 90.0f;
	}
	if (car2x >= -7.0f && car2z <= 3.0f) {
		car2x -= 0.01f;
		carDirection2 = 180.0f;
	}
	if (car2x <= -7.0f && car2z <= 7.0f) {
		car2z += 0.01f;
		carDirection2 = 270.0f;
	}
	//car3
	if (car3x <= 4.0f && car3z >= 7.0f) {
		carDirection3 = 0.0f;
		car3x += 0.01f;
	}
	if (car3x >= 4.0f && car3z >= 3.0f) {
		car3z -= 0.01f;
		carDirection3 = 90.0f;
	}
	if (car3x >= -7.0f && car3z <= 3.0f) {
		car3x -= 0.01f;
		carDirection3 = 180.0f;
	}
	if (car3x <= -7.0f && car3z <= 7.0f) {
		car3z += 0.01f;
		carDirection3 = 270.0f;
	}
	//car4
	if (car4x <= 4.0f && car4z >= 7.0f) {
		carDirection4 = 0.0f;
		car4x += 0.01f;
	}
	if (car4x >= 4.0f && car4z >= 3.0f) {
		car4z -= 0.01f;
		carDirection4 = 90.0f;
	}
	if (car4x >= -7.0f && car4z <= 3.0f) {
		car4x -= 0.01f;
		carDirection4 = 180.0f;
	}
	if (car4x <= -7.0f && car4z <= 7.0f) {
		car4z += 0.01f;
		carDirection4 = 270.0f;
	}


	glutPostRedisplay();
}



//--------------------------------------------------------------------- reshape
// To avoid distortion when the window size changes, we need a reshape callback. 
void reshape(GLint w, GLint h) {

	width = w;
	height = h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(60, (float)w / (float)h, 1.0f, 50.0f);

	gluLookAt(0.0f, 10.0f, 15.0f - zoom_distance,   // eye
		pan_angle, 0.0f, 0.0f,   // center
		0.0f, 1.0f, 0.0f);  // up
}



//-------------------------------------------------------------------- keyboard
// Add the keyboard input to the program (which is non-case sensitive).  
GLvoid keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case KEY_ESC:
		exit(1);
		break;

	case KEY_A:		 // A
	case KEY_A + 32: // a
		pan_angle -= 0.5f;
		break;

	case KEY_D:		 // D
	case KEY_D + 32: // d
		pan_angle += 0.5f;
		break;

		// zoom-out
	case KEY_S:		 // S
	case KEY_S + 32: // s
		zoom_distance -= 0.5f;
		break;

		// zoom-in
	case KEY_W:		 // W
	case KEY_W + 32: // w
		zoom_distance += 0.5f;
		break;

		// reset
	case KEY_R:		 // R
	case KEY_R + 32: // r
		zoom_distance = 0.0f;
		pan_angle = 0.0f;
		break;

	case KEY_I:
	case KEY_I + 32:
		ghost_z -= 0.5f;
		break;

	case KEY_J:
	case KEY_J + 32:
		ghost_x -= 0.5f;
		break;

	case KEY_K:
	case KEY_K + 32:
		ghost_z += 0.5f;
		break;

	case KEY_L:
	case KEY_L + 32:
		ghost_x += 0.5f;
		break;

	case KEY_U:
	case KEY_U + 32:
		ghost_y -= 0.5f;
		break;

	case KEY_O:
	case KEY_O + 32:
		ghost_y += 0.5f;
		break;
	

		// Print Help (instruction) on console
	case KEY_H:		 // H
	case KEY_H + 32: // h
		printf("------------HELP------------ \n");
		printf("Key A: Pan left \n");
		printf("Key D: Pan right \n");
		printf("Key W: Zoom in \n");
		printf("Key S: Zoom out \n");
		printf("Key R: Reset \n");
		printf("Key I: Ghost Forward\n");
		printf("Key J: Ghost Left\n");
		printf("Key K: Ghost Backward\n");
		printf("Key L: Ghost Right\n");
		printf("Key U: Ghost Down\n");
		printf("Key O: Ghost Up\n"); 
		break;

	}
}