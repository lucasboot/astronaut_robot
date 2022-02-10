#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>
using namespace std;

 double horizAngle = 180.0;	//Ângulo de visão
 double vertAngle = 0.0;	//Ângulo de visão
 double limbAngle = 0.0; //Ângulo da caminhada
 bool walk = false;	//Para caminhar

//coordenadas de textura 2D
float textures[6][4][2]=  //6 faces, 4 vértices, 2 coordenadas
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

//Coordenadas dasfaces fazes do cubo
float cube[6][4][3]=  //6 faces, 4 vértices, 3 coordenadas
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
//Desabilita a cor da figura para adicionar textura
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

//Carrega os arquivos de textura
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
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

//a textura é criada e, portanto, agora você pode
//livre memória da imagem carregada
free(data);
return 0;
}

//Desenha tronco e cabeça
void drawRobot(){
	//Cabeça - capacete
	glColor3f(1, 1, 0.9); //Seleção da cor
	glPushMatrix();  //Seta matriz atual na stack de matrizes
	glTranslated(0.0, 1.05, 0.0); //Multiplica a matriz atual por uma matriz de translação
	glScaled(1.0, 1.0, 1.0); //Configura a escala desenho
	glutSolidSphere(.30, 30, 30);  //Renderiza uma esfera sólida
	glPopMatrix(); //Remove a matriz atual da stack de matrizes

	//Cabeça - Viseira
	glColor3f(0.1, 0.1, 0.1);
	glPushMatrix();
	glTranslated(0.0, 1.05, 0.05);
	glScaled(1.0, 1.0, 1.05);
	glutSolidSphere(.29, 30, 30);
	glPopMatrix();

	//Corpo
	glColor3f(1, 1, 0.9);
	glPushMatrix();
	glTranslated(0.0, 0.40, 0.0);
	glScaled(1.0, 1.5, 0.30);
	glutSolidCube(.50); //Renderiza um cubo sólido
	glPopMatrix();

	//mochila
    glColor3f(1, 1, 0.9);
    glPushMatrix();
    glTranslated(0.0, 0.5, -0.1);
    glScaled(0.8, 1.5, 0.7);
    glutSolidCube(.4);
    glPopMatrix();

	//Bandeira
	//Verde
	glColor3f(0.3, 0.8, 0.1);
    glPushMatrix();
    glTranslated(0.0, 0.7, -0.11);
    glScaled(0.50, 0.37, 0.7);
    glutSolidCube(.4);
    glPopMatrix();
	//Amarelo
	glColor3f(1, 1, 0);
    glPushMatrix();
    glTranslated(0.0, 0.7, -0.24);
    glScaled(0.15, 0.15, 0.05);
    glutSolidSphere(.5, 4, 4);
    glPopMatrix();
	//Azul
	glColor3f(0, 0, 1);
    glPushMatrix();
    glTranslated(0.0, 0.7, -0.23);
    glScaled(0.1, 0.1, 0.1);
    glutSolidSphere(.4, 30, 30);
    glPopMatrix();

}
//Desenha o braço esquerdo
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
	//mão
	glColor3f(1, 1, 0.9);	
	glPushMatrix();
	glTranslated(-0.30, 0.17, 0.0);
	glScaled(0.80, 1.0, 1.0);
	glutSolidSphere(.08, 20, 20);
	glPopMatrix();
}
//Desenha o braço direito
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
	//mão
	glColor3f(1, 1, 0.9);	
	glPushMatrix();
	glTranslated(0.30, 0.17, 0.0);
	glScaled(0.80, 1.0, 1.0);
	glutSolidSphere(.08, 20, 20);
	glPopMatrix();
}
//Desenha a perna esquerda
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
	//Calçado
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
//Desenha a perna direita
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
	//Calçado
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

void myInit(){
	glClearColor(0.0, 0.0, 0.0, 0.0); //céu escuro
	glMatrixMode(GL_PROJECTION); //aplica operações de matrizes subsequentes à pilha
	glLoadIdentity(); //matriz identidade
	glOrtho(-2.0*(64/48.0), 2.0*(64/48.0), -2.0, 2.0, 0.1, 100.0); //ortogonalizar 
	glViewport(0, 0, 800, 640); //determina a janela de visualização
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

	//propriedades da superfície do material
    
	GLfloat mat_ambient[] = { 0.0f, 0.0f, 1.0f, 1.0f}; // reflectância do ambiente RGBA do material
	GLfloat mat_diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f}; //reflectância difusa RGBA do material
	GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f}; //reflectância especular RGBA do material
	GLfloat mat_shininess[] = {50.0f}; //brilho
	//Especificar os parâmetros do modelo de iluminação e as faces que serão atualizadas
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

	GLfloat lightIntensity[] = {1.0f, 1.0f, 1.0f, 1.0f}; // intensidade
	GLfloat light_position[] = {2.0f, 2.0f, 3.0f, 0.0f}; //posição da fonte
	//Configuração dos parâmetros da fonte de luz
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); //número de luzes,  posição 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity); //numero de luzes, intensidade

}
//sempre executa, pois controla o ângulo do movimento
void Walk (void)
{
	static float mf = 0.05;	//fator de movimento do membro
 
	limbAngle += mf; //variável utilizada no rotate
 
	if(limbAngle >  30.0){ //verifica se o ângulo do movimento é maior que 30 graus
		mf = -0.70;
	}
	if(limbAngle < -30.0){
		mf =  0.70;
	}
	glutPostRedisplay (); //marca a janela atual como necessitada de redisplay
}


void myDisplay(void){
	glMatrixMode(GL_MODELVIEW); // Específica qual matriz é a matriz atual
	// GL_MODELVIEW é a matriz que recebe as operações feitas em seguida
	glLoadIdentity(); // Substitui a matriz atual pela identidade da mesma
	gluLookAt(0.0, 0.50, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Define uma transformação de visualização
	// Os 3 primeiros, define a posição de visualização
	// 3 do meio a posição referente ao ponto
	// 3 últimos especificam a direçãod e cima do vetor
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa a janela de fato

	//Rotating around Robot
	glPushMatrix(); // Adiciona a matriz atual na stack de matrizes
	glRotated(vertAngle, 1.0, 0.0, 0.0f); // Multiplica a matriz atual por uma de rotação, recebendo como parâmetro o angulo e as coordenadas
	glRotated(horizAngle, 0.0, 1.0, 0.0f); // Permite rotacionar a câmera ao redor do objeto
	drawRobot(); // Desenha o objeto
	drawCube(); // Desenha o cubo

	if(walk == true){
	glPopMatrix();
	// Movimento de animação do braço esquerdo
	glPushMatrix();
	glRotated(vertAngle, 1.0, 0.0, 0.0f);
	glRotated(horizAngle, 0.0, 1.0, 0.0f);
	glTranslated(-0.30, 1.0, 0.0);
	glRotated(limbAngle, 1.0, 0.0, 0.0f);
	glTranslated(0.30, -1.0, 0.0);
	leftArm();
	glPopMatrix();
	//Movimento de animação do braço direito
	glPushMatrix();
	glRotated(vertAngle, 1.0, 0.0, 0.0f);
	glRotated(horizAngle, 0.0, 1.0, 0.0f);
	glTranslated(0.30, 1.0, 0.0);
	glRotated(-limbAngle, 1.0, 0.0, 0.0f);
	glTranslated(-0.30, -1.0, 0.0);
	rightArm();
	glPopMatrix();
	//Movimento de animação do perna esquerdo
	glPushMatrix();
	glRotated(vertAngle, 1.0, 0.0, 0.0f);
	glRotated(horizAngle, 0.0, 1.0, 0.0f);
	glRotated(-limbAngle, 1.0, 0.0, 0.0f);
	leftLeg();
	glPopMatrix();
	//Movimento de animação do perna direita
	glPushMatrix();
	glRotated(vertAngle, 1.0, 0.0, 0.0f);
	glRotated(horizAngle, 0.0, 1.0, 0.0f);
	glRotated(limbAngle, 1.0, 0.0, 0.0f);
	rightLeg();
	}
	else {
	//Rotaciona ao redor do objeto sem animação do movimento
	leftArm();
	rightArm();
	leftLeg();
	rightLeg();
	}
	glPopMatrix();

	// Cada nova imagem é desenhada pelo buffer e quando cada um é desenhado é desenhado o display é trocado para o novo
	glutSwapBuffers();
}


 
void myKeyboard(unsigned char key, int x, int y){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	static double zoomFactor = 1.0;	//Fator de zoom out e in 
	static double zoomFactor2 = 1.0;

	switch (key)
    {
    case 's': //movimentar-se ou não
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
		glViewport(1.0 * zoomFactor2, 1.0 * zoomFactor2, 800*zoomFactor, 640*zoomFactor); //aplicar o fator de zoom na janela
	break;
	case 'Z':
		zoomFactor += 0.02;
		zoomFactor2 -= 7.7;
		glViewport(1.0 * zoomFactor2, 1.0 * zoomFactor2, 800*zoomFactor, 640*zoomFactor); //aplicar o fator de zoom na janela
	break;
	case 'd':
		vertAngle = 0.0;
		horizAngle = 0.0;
		walk = false; //reseta a janela de visão e para o movimento do robô
	break;
    case 'e':
		exit(0);			// fechar o programa
    }
	
	glutPostRedisplay();		//marca a janela atual como necessitada de redisplay
}

// Essa função lida com as teclas especiais de seta, direcionando o ângulo de visão
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

    glutPostRedisplay(); // Redesenha a imagem
}


int main(int argc, char **argv){

	glutInit(&argc, argv);  //kit de utilidade OpenGL
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  //buffering duplo para animação
	glutInitWindowSize(1024, 720);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Marcos Pontes Android");
	glutDisplayFunc(myDisplay);
	glutIdleFunc(Walk);		//Mantem a função 'walk' funcionando enquanto nada está acontecendo

	glutKeyboardFunc(myKeyboard);	//a função myKeyboard trata as teclas normais
	glutSpecialFunc(arrowKeyPress);	//arrowKeyPress vai tratar os casos de telcas especiais

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable (GL_COLOR_MATERIAL);	//Material color match vertex color specified

	myInit();
	glutMainLoop();
}