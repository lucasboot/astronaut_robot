/* Dan Gray
cs4410 HW #3
10-22-14 */

#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>
using namespace std;

 double horizAngle = 0.0;	//Viewing angle
 double vertAngle = 0.0;	//Viewing angle
 double limbAngle = 0.0; //Walking angle
 bool walk = false;	//For walking

//coordenadas de textura 2D
float textures[6][4][2]=
{
//coordenadas de textura da 1ª face 
0.0, 0.0,
1.0, 0.0,
1.0, 1.0, 
0.0, 1.0,
//coordenadas de textura da 2ª face
0.0, 0.0,
1.0, 0.0,
1.0, 1.0, 
0.0, 1.0,
//coordenadas de textura da 3ª face
0.0, 0.0,
1.0, 0.0,
1.0, 1.0, 
0.0, 1.0,
//coordenadas de textura da 4ª face
0.0, 0.0,
1.0, 0.0,
1.0, 1.0, 
0.0, 1.0,
//coordenadas de textura da 5ª face
0.0, 0.0,
1.0, 0.0,
1.0, 1.0, 
0.0, 1.0,
//coordenadas de textura da 6ª face
0.0, 0.0,
1.0, 0.0,
1.0, 1.0, 
0.0, 1.0,
};

//glScaled(2, 0.05, 2);
//Coordenadas dasfaces fazes do cubo
float cube[6][4][3]=
{
-6.0, -0.60, -6.0,
-6.0, -0.60, 6.0,
-6.0, -0.55, 6.0,
-6.0, -0.55, -6.0,

-6.0, -0.60, -6.0,
-6.0, -0.55, -6.0,
6.0, -0.55, -6.0,
6.0, -0.60, -6.0,

-6.0, -0.60, -6.0,
6.0, -0.60, -6.0,
6.0, -0.60, 6.0,
-6.0, -0.60, 6.0,

-6.0, -0.60, 6.0,
6.0, -0.60, 6.0,
6.0, -0.55, 6.0,
-6.0, -0.55, 6.0,

-6.0, -0.55, -6.0,
-6.0, -0.55, 6.0,
6.0, -0.55, 6.0,
6.0, -0.55, -6.0,

6.0, -0.60, -6.0,
6.0, -0.55, -6.0,
6.0, -0.55, 6.0,
6.0, -0.60, 6.0,
};

//desenhar um cubo por coordenadas
void drawCube()
{
int i,j;
glDisable(GL_COLOR);
glEnable(GL_TEXTURE_2D);
for(i = 0; i < 6; i++)
    {
    glBindTexture(GL_TEXTURE_2D, i+1);
    //se as texturas forem diferentes 
    //glBindTexture(GL_TEXTURE_2D, i);  
    glBegin(GL_QUADS);
    for(j = 0; j < 4; j++)
        {
        glTexCoord2f(textures[i][j][0], textures[i][j][1]);
        glVertex3f(cube[i][j][0], cube[i][j][1], cube[i][j][2]);
        }
    glEnd();
    }
glDisable(GL_TEXTURE_2D);
glEnable(GL_COLOR);
}

void drawRobot(){
	//head - capacete
	glColor3f(1, 1, 0.9);
	glPushMatrix();
	glTranslated(0.0, 1.05, 0.0);
	glScaled(1.0, 1.0, 1.0);
	glutSolidSphere(.30, 30, 30);
	glPopMatrix();

	//head - Viseira
	glColor3f(0.1, 0.1, 0.1);
	glPushMatrix();
	glTranslated(0.0, 1.05, 0.05);
	glScaled(1.0, 1.0, 1.05);
	glutSolidSphere(.29, 30, 30);
	glPopMatrix();

	//body
	glColor3f(1, 1, 0.9);
	glPushMatrix();
	glTranslated(0.0, 0.40, 0.0);
	glScaled(1.0, 1.5, 0.30);
	glutSolidCube(.50);
	glPopMatrix();

	//mochila
    glColor3f(1, 1, 0.9);
    glPushMatrix();
    glTranslated(0.0, 0.5, -0.1);
    glScaled(0.8, 1.5, 0.7);
    glutSolidCube(.4);
    glPopMatrix();

	//bandeira
	//Vermelho
	glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslated(0.0, 0.7, -0.11);
    glScaled(0.3, 0.1, 0.7);
    glutSolidCube(.4);
    glPopMatrix();
	//Branco
	glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslated(0.0, 0.66, -0.11);
    glScaled(0.3, 0.1, 0.7);
    glutSolidCube(.4);
    glPopMatrix();
	//Azul
	glColor3f(0, 0, 1);
    glPushMatrix();
    glTranslated(0.0, 0.62, -0.11);
    glScaled(0.3, 0.1, 0.7);
    glutSolidCube(.4);
    glPopMatrix();

}
//Draw left arm
void leftArm(){
	glColor3f(1, 1, 0.9);	
	glPushMatrix();
	glTranslated(-0.30, 0.50, 0.0);
	glScaled(0.20, 1.0, 0.20);
	glutSolidCube(.50);
	glPopMatrix();	
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslated(-0.30, 0.50, 0.0);
	glScaled(0.21, 0.1, 0.21);
	glutSolidCube(.50);
	glPopMatrix();
	//hand
	glColor3f(1, 1, 0.9);	
	glPushMatrix();
	glTranslated(-0.30, 0.17, 0.0);
	glScaled(0.80, 1.0, 1.0);
	glutSolidSphere(.08, 20, 20);
	glPopMatrix();
}
//Draw right arm
void rightArm(){
	glColor3f(1, 1, 0.9);	
	glPushMatrix();
	glTranslated(0.30, 0.50, 0.0);
	glScaled(0.20, 1.0, 0.20);
	glutSolidCube(.50);
	glPopMatrix();	
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslated(0.30, 0.50, 0.0);
	glScaled(0.21, 0.1, 0.21);
	glutSolidCube(.50);
	glPopMatrix();
	//hand
	glColor3f(1, 1, 0.9);	
	glPushMatrix();
	glTranslated(0.30, 0.17, 0.0);
	glScaled(0.80, 1.0, 1.0);
	glutSolidSphere(.08, 20, 20);
	glPopMatrix();
}
//Draw left leg
void leftLeg(){
	glColor3f(1, 1, 0.9);
	glPushMatrix();	
	glTranslated(-0.20, -0.220, 0.0);
	glScaled(0.20, 1.0, 0.20);
	glutSolidCube(.50);
	glPopMatrix();
	glColor3f(1, 0, 0);
	glPushMatrix();	
	glTranslated(-0.20, -0.220, 0.0);
	glScaled(0.21, 0.1, 0.21);
	glutSolidCube(.50);
	glPopMatrix();
	//shoe
	glColor3f(0.05, 0.05, 0.05);
	glPushMatrix();
	glTranslated(-0.20, -0.50, 0.15);
	glScaled(1.0, 0.60, 1.50);
	glutSolidSphere(.1, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-0.20, -0.485, 0.0);
	glScaled(1.0, 0.65, 1.0);
	glutSolidSphere(.1, 20, 20);
	glPopMatrix();
}
//Draw right leg
void rightLeg(){
	glColor3f(1, 1, 0.9);
	glPushMatrix();	
	glTranslated(0.20, -0.220, 0.0);
	glScaled(0.20, 1.0, 0.20);
	glutSolidCube(.50);
	glPopMatrix();
	glColor3f(1, 0, 0);
	glPushMatrix();	
	glTranslated(0.20, -0.220, 0.0);
	glScaled(0.21, 0.1, 0.21);
	glutSolidCube(.50);
	glPopMatrix();
	//shoe
	glColor3f(0.05, 0.05, 0.05);
	glPushMatrix();
	glTranslated(0.20, -0.50, 0.15);
	glScaled(1.0, 0.60, 1.50);
	glutSolidSphere(.1, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.20, -0.485, 0.0);
	glScaled(1.0, 0.65, 1.0);
	glutSolidSphere(.1, 20, 20);
	glPopMatrix();
}

GLuint LoadTexture(GLuint tex, const char * filename, int width, int height)
{
//bmp padrão 24 bits
unsigned char * data;
unsigned char R,G,B;
FILE * file;

//carregando imagem do arquivo .bmp
file = fopen(filename, "rb");

if(file == NULL)return 0;
//alocar memória para variável de dados
data =(unsigned char *)malloc(width * height * 3);
//deslocamento de salto de sobrecarga
fseek(file,128,0);
//leia todo o arquivo de arquivo em uma variável de dados
fread(data, width * height * 3, 1, file);
//feche o arquivo
fclose(file);

//reorganize os valores R, G, B ​​​​para exibir a cor corretamente
int index;
for(int i = 0; i < width * height ; ++i)
	{
	index = i*3;
	B = data[index]; G = data[index+1]; R = data[index+2];
	data[index] = R; data[index+1] = G; data[index+2] = B;
	}

//criar textura a partir da imagem carregada
glGenTextures(1, &tex);
glBindTexture(GL_TEXTURE_2D, tex);

// filtragem de textura

gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

//a textura é criada e, portanto, agora você pode
//livre memória da imagem carregada
free(data);
return 0;
}


void myInit(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0*(64/48.0), 2.0*(64/48.0), -2.0, 2.0, 0.1, 100.0); //left, right, bottom, top, near, far Parallel Projection
	glViewport(0, 0, 800, 640);
	//permitir sombras borradas
	glShadeModel(GL_SMOOTH);
	//cor da tela preta
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//permitir texturas
	glEnable(GL_TEXTURE_2D);
	//carregando textura de bmp 24 bits
	LoadTexture(1, "lua.bmp", 1024, 602);
	LoadTexture(2, "lua.bmp", 1024, 602);
	LoadTexture(3, "lua.bmp", 1024, 602);
	LoadTexture(4, "lua.bmp", 1024, 602);
	LoadTexture(5, "lua.bmp", 1024, 602);
	LoadTexture(6, "lua.bmp", 1024, 602);

	//set properties of the surface material
    
	GLfloat mat_ambient[] = { 0.0f, 0.0f, 1.0f, 1.0f}; // 
	GLfloat mat_diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat mat_shininess[] = {50.0f};

	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

	GLfloat lightIntensity[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat light_position[] = {2.0f, 2.0f, 3.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

}
//If nothing else happening, do walking motion
void Walk (void)
{
	static float mf = 0.05;	//limb movement factor
 
	limbAngle += mf;
 
	if(limbAngle >  30.0){
		mf = -0.70;
	}
	if(limbAngle < -30.0){
		mf =  0.70;
	}
	glutPostRedisplay ();
}


void myDisplay(void){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.50, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(walk == true){
	//Rotating around Robot
	glPushMatrix();
	glRotated(vertAngle, 1.0, 0.0, 0.0f);
	glRotated(horizAngle, 0.0, 1.0, 0.0f);
	drawRobot();
	drawCube();
	glPopMatrix();
	//Left arm walking movement
	glPushMatrix();
	glRotated(vertAngle, 1.0, 0.0, 0.0f);
	glRotated(horizAngle, 0.0, 1.0, 0.0f);
	glTranslated(-0.30, 1.0, 0.0);
	glRotated(limbAngle, 1.0, 0.0, 0.0f);
	glTranslated(0.30, -1.0, 0.0);
	leftArm();
	glPopMatrix();
	//Right arm walking movement
	glPushMatrix();
	glRotated(vertAngle, 1.0, 0.0, 0.0f);
	glRotated(horizAngle, 0.0, 1.0, 0.0f);
	glTranslated(0.30, 1.0, 0.0);
	glRotated(-limbAngle, 1.0, 0.0, 0.0f);
	glTranslated(-0.30, -1.0, 0.0);
	rightArm();
	glPopMatrix();
	//Left leg walking movement
	glPushMatrix();
	glRotated(vertAngle, 1.0, 0.0, 0.0f);
	glRotated(horizAngle, 0.0, 1.0, 0.0f);
	glRotated(-limbAngle, 1.0, 0.0, 0.0f);
	leftLeg();
	glPopMatrix();
	//Right leg walking movement
	glPushMatrix();
	glRotated(vertAngle, 1.0, 0.0, 0.0f);
	glRotated(horizAngle, 0.0, 1.0, 0.0f);
	glRotated(limbAngle, 1.0, 0.0, 0.0f);
	rightLeg();
	glPopMatrix();
	}
	else if(walk == false){
	//Rotating around Robot and no Walking
	glPushMatrix();
	glRotated(vertAngle, 1.0, 0.0, 0.0f);
	glRotated(horizAngle, 0.0, 1.0, 0.0f);
	drawRobot();
	drawCube();
	leftArm();
	rightArm();
	leftLeg();
	rightLeg();
	glPopMatrix();
	}

	/*Each new picture is drawn in the invisible buffer, and when the drawing is
	complete the display switches to it.*/
	glutSwapBuffers();
}



void myKeyboard(unsigned char key, int x, int y){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	static double zoomFactor = 1.0;	//Zooming in/out 
	static double zoomFactor2 = 1.0;

	switch (key)
    {
    case 's':
		if(walk == false){
			walk = true;
		}
		else if(walk == true){
			walk = false;
		}
	break;
	case 'z':
		zoomFactor -= 0.02;
		zoomFactor2 += 7.7;
		glViewport(1.0 * zoomFactor2, 1.0 * zoomFactor2, 800*zoomFactor, 640*zoomFactor);
	break;
	case 'Z':
		zoomFactor += 0.02;
		zoomFactor2 -= 7.7;
		glViewport(1.0 * zoomFactor2, 1.0 * zoomFactor2, 800*zoomFactor, 640*zoomFactor);
	break;
	case 'd':
		vertAngle = 0.0;
		horizAngle = 0.0;
		walk = false;
	break;
    case 'e':
		exit(0);			// exit
    }
	
	/*sets a flag so that when the mainloop is ready it will call the real "display" callback once per mainloop iteration*/
	glutPostRedisplay();		//refresh the display, redraw the image now
}

void arrowKeyPress(int key, int x, int y){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch(key){
	case GLUT_KEY_RIGHT:
		horizAngle += 2;
	break;
	case GLUT_KEY_LEFT:
		horizAngle -= 2;
	break;
	case GLUT_KEY_UP:
		vertAngle -= 2;
	break;
	case GLUT_KEY_DOWN:
		vertAngle += 2;
	break;
    }

    glutPostRedisplay();		// redraw the image now
}


int main(int argc, char **argv){

	glutInit(&argc, argv);  //OpenGL utility kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  //double buffering for animation
	glutInitWindowSize(1024, 720);
	glutInitWindowPosition(1024, 720);
	glutCreateWindow("Oh Ceus!!!");
	glutDisplayFunc(myDisplay);
	glutIdleFunc(Walk);		//Ongoing walking function for when nothing else happening

	glutKeyboardFunc(myKeyboard);	//myKeyboard will handle normal keys
	glutSpecialFunc(arrowKeyPress);	//arrowKeyPress will handle special keys

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable (GL_COLOR_MATERIAL);	//Material color match vertex color specified

	myInit();
	glutMainLoop();
}