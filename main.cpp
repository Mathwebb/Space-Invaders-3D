#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <string>
#include <vector>

#include "libraries/object loader.h"

using namespace std;

// ASCII key codes
#define ESCAPE 27
#define SPACEBAR 32
#define ENTER 13
#define BACKSPACE 8
#define TAB 9
#define NUMBER_0 48
#define NUMBER_1 49
#define NUMBER_2 50
#define NUMBER_3 51
#define NUMBER_4 52
#define NUMBER_5 53
#define NUMBER_6 54
#define NUMBER_7 55
#define NUMBER_8 56
#define NUMBER_9 57

// Main menu options
#define START_GAME_OPTION 0
#define EXIT_OPTION 1

// Game states
#define MAIN_MENU 0
#define GAME_RUNNING 1
#define GAME_PAUSED 2
#define GAME_OVER 3

int windowWidth = 640, windowHeight = 480, angle = 0, selectedMenuOption = 0, gameState = 0;
void initGlut(const char *nome_janela, int argc, char** argv);
void reshapeCallback(int w, int h);
void displayCallback(void);
void keyboardCallback(unsigned char key, int x, int y);
void keyboardCallbackSpecial(int key, int x, int y);
void mouseCallback(int button, int state, int x, int y);
void mousePassiveMotionCallback(int x, int y);
void renderObjects(vector<Object> sceneObjects);
void renderBitMapCharacter(float x, float y, float z, void *font, string text, float r, float g, float b);
void showMainMenu(float x, float y, float z, float optionsSpacing);

void initGlut(const char *nome_janela, int argc, char** argv){
    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowSize(windowWidth,windowHeight);
    glutInitWindowPosition(100,100);
    glutCreateWindow(nome_janela);

    glutReshapeFunc(reshapeCallback);
    glutDisplayFunc(displayCallback);
    glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(keyboardCallbackSpecial);
	glutMouseFunc(mouseCallback);
	glutPassiveMotionFunc(mousePassiveMotionCallback);
}

void reshapeCallback(int w, int h){
	windowWidth = w;
	windowHeight = h;
    if (gameState == MAIN_MENU){
		glMatrixMode(GL_PROJECTION);
	    glClearColor(0.0, 0.0, 0.0, 1.0);
		glLoadIdentity();
		
		glViewport(0, 0, (GLsizei) w, (GLsizei) h);
		
		glOrtho(-(w/2), (w/2), -(h/2), h/2, -1, 1);
		
		glMatrixMode(GL_MODELVIEW);		
	} else if (gameState == GAME_RUNNING){
	    glMatrixMode (GL_PROJECTION);
	    glClearColor(0.0, 0.0, 0.0, 1.0);
	    glLoadIdentity();
	
	    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	
	    gluPerspective(60, (float)w/(float)h, 1.0, 1000.0);
	
	    gluLookAt (0.0, 0.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	    glMatrixMode (GL_MODELVIEW);
	}
}

void displayCallback(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (gameState == MAIN_MENU){
		showMainMenu(-windowWidth/2+windowWidth*0.1, 0.0, 0.0, -20.0);
	} else if(gameState == GAME_RUNNING){
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glutSolidCube(50);
		glPopMatrix();
	}

    glutSwapBuffers();
}

void mouseCallback(int button, int state, int x, int y){

	glutPostRedisplay();
}

void mouseMotionCallback(int x, int y){
	
}

void mousePassiveMotionCallback(int x, int y){
	
}

void keyboardCallback(unsigned char key, int x, int y){
	switch (key){
		case ESCAPE:
			exit(0);
			break;
		case ENTER:
			if (gameState == MAIN_MENU){
				if (selectedMenuOption == START_GAME_OPTION){
					gameState = GAME_RUNNING;
					reshapeCallback(windowWidth, windowHeight);
					displayCallback();
				} else if (selectedMenuOption == EXIT_OPTION){
					exit(0);
				}
			}
			break;
		case NUMBER_0:
			if (gameState == MAIN_MENU){
				selectedMenuOption = 0;
				displayCallback();
			}
			break;
		case NUMBER_1:
			if (gameState == MAIN_MENU){
				selectedMenuOption = 1;
				displayCallback();
			}
			break;
	}	
}

void keyboardCallbackSpecial(int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP:
			break;
		case GLUT_KEY_DOWN:
			break;
		case GLUT_KEY_RIGHT:
			break;
		case GLUT_KEY_LEFT:
			break;
	}
    glutPostRedisplay();
}

void renderStrokeFontString(float x, float y, float z, void *font, string text) {
	glPushMatrix();
	glTranslatef(x, y,z);

	for (unsigned int i = 0; i < text.size(); i++) {
		glutStrokeCharacter(font, text.at(i));
	}

	glPopMatrix();
}

void renderBitMapCharacter(float x, float y, float z, void *font, string text, float r, float g, float b) {
	glPushMatrix();
	glRasterPos3f(x, y, z);
	glColor3f(r, g, b);
	cout << "Text: " << text << endl;
	cout << "Color: " << r << ", " << g << ", " << b << endl;

	for (unsigned int i = 0; i < text.size(); i++) {
		glutBitmapCharacter(font, text.at(i));
	}

	glPopMatrix();
}

void renderObjects(vector<Object> sceneObjects) {
	for (unsigned int i = 0; i < sceneObjects.size(); i++){
		Object sceneObject = sceneObjects.at(i);
		glPushMatrix();
		glTranslatef(sceneObject.posX, sceneObject.posY, sceneObject.posZ);
		glRotatef(sceneObject.angle, sceneObject.angleX, sceneObject.angleY, sceneObject.angleZ);
		glScalef(sceneObject.scaleX, sceneObject.scaleY, sceneObject.scaleZ);
		glColor3f(1, 1, 1);
		glBegin(GL_POINTS);
			for (unsigned int j = 0; j < sceneObject.faces.size(); j++){
				Face face = sceneObject.faces.at(j);
				glNormal3fv(face.normal);
				for (unsigned int k = 0; k < face.vertices.size(); k++){
					Vertex vertex = face.vertices.at(k);
					glVertex3f(vertex.posX, vertex.posY, vertex.posZ);
					glNormal3fv(vertex.normal);
				}
			}
		glEnd();
		glBegin(GL_TRIANGLES);
		for (unsigned int j = 0; j < sceneObject.faces.size(); j++){
			Face face = sceneObject.faces.at(j);
			glNormal3fv(face.normal);
			for (unsigned int k = 0; k < face.vertices.size(); k++){
				Vertex vertex = face.vertices.at(k);
				glVertex3f(vertex.posX, vertex.posY, vertex.posZ);
				glNormal3fv(vertex.normal);
			}
		}
		glEnd();
		glPopMatrix();
	}
}

void showMainMenu(float x, float y, float z, float optionsSpacing){
	glPushMatrix();
    
    glBegin(GL_BITMAP);
	if (selectedMenuOption == 0){
    	renderBitMapCharacter(x, y, z, GLUT_BITMAP_HELVETICA_18, "[ 0 ] - Start game", 0.0, 1.0, 1.0);
    	renderBitMapCharacter(x, y-optionsSpacing, z, GLUT_BITMAP_HELVETICA_18, "[ 1 ] - Exit", 1.0, 1.0, 1.0);
	} else if (selectedMenuOption == 1){
		renderBitMapCharacter(x, y-optionsSpacing, z, GLUT_BITMAP_HELVETICA_18, "[ 1 ] - Exit", 0.0, 1.0, 1.0);
		renderBitMapCharacter(x, y, z, GLUT_BITMAP_HELVETICA_18, "[ 0 ] - Start game", 1.0, 1.0, 1.0);
	}
    glEnd();
    
    glPopMatrix();
}



int main(int argc, char* argv[]){
    initGlut("Space Invaders 3D", argc, argv);
    glutMainLoop();
    return 0;
}
