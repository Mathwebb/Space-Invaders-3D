#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "game_functions/renderers.h"
#include "game_classes/Player.h"
#include "game_classes/Enemy.h"
#include "game_classes/Projectile.h"
#include "game_classes/Level.h"

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

enum MainMenuOptions {
	START_GAME = 0,
	EXIT = 1
};
enum GameStates {
	MAIN_MENU,
	GAME_RUNNING,
	GAME_PAUSED,
	GAME_OVER
};
int windowWidth = 640, windowHeight = 480, angle = 0, selectedMenuOption = 0, gameState = 0;
int actualLevel = 1;
// vector<Object> sceneObjects;
// Player player;
// vector<Enemy> enemies;
Level level;

void initGlut(const char *nome_janela, int argc, char** argv);
void reshapeCallback(int w, int h);
void displayCallback(void);
void keyboardCallback(unsigned char key, int x, int y);
void keyboardCallbackSpecial(int key, int x, int y);
void mouseCallback(int button, int state, int x, int y);
void mousePassiveMotionCallback(int x, int y);

void initGlut(const char *nome_janela, int argc, char** argv){

    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowSize(windowWidth,windowHeight);
    glutInitWindowPosition(100,100);
    glutCreateWindow(nome_janela);

	glEnable(GL_DEPTH_TEST);
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
	
	    gluPerspective(60, (float)w/(float)h, 1.0, 10000.0);
	
	    gluLookAt (level.getPlayer()->getCoordinateX(), level.getPlayer()->getCoordinateY()+100, level.getPlayer()->getCoordinateZ()+350,
				   level.getPlayer()->getCoordinateX(), level.getPlayer()->getCoordinateY(), level.getPlayer()->getCoordinateZ(),
				   0.0, 1.0, 0.0);
	
	    glMatrixMode (GL_MODELVIEW);
	}
}

void displayCallback(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (gameState == MAIN_MENU){
		renderMainMenu(selectedMenuOption, -windowWidth/2+windowWidth*0.1, 0.0, 0.0, 20.0);
	} else if(gameState == GAME_RUNNING){
		level.renderLevel();
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
				if (selectedMenuOption == START_GAME){
					gameState = GAME_RUNNING;
					reshapeCallback(windowWidth, windowHeight);
					displayCallback();
				} else if (selectedMenuOption == EXIT){
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
			if (gameState == MAIN_MENU){
				if (selectedMenuOption > 0){
					selectedMenuOption--;
					displayCallback();
				}
			}else if (gameState == GAME_RUNNING){
				level.movePlayerUp();
				reshapeCallback(windowWidth, windowHeight);
				displayCallback();
			}

			break;
		case GLUT_KEY_DOWN:
			if (gameState == MAIN_MENU){
				if (selectedMenuOption < 1){
					selectedMenuOption++;
					displayCallback();
				}
			}else if (gameState == GAME_RUNNING){
				level.movePlayerDown();
				reshapeCallback(windowWidth, windowHeight);
				displayCallback();
			}
			break;
		case GLUT_KEY_RIGHT:
			if (gameState == GAME_RUNNING){
				level.movePlayerRight();
				reshapeCallback(windowWidth, windowHeight);
				displayCallback();
			}
			break;
		case GLUT_KEY_LEFT:
			if (gameState == GAME_RUNNING){
				level.movePlayerLeft();
				reshapeCallback(windowWidth, windowHeight);
				displayCallback();
			}
			break;
	}
    glutPostRedisplay();
}

int main(int argc, char* argv[]){
    initGlut("Space Invaders 3D", argc, argv);
    glutMainLoop();
    return 0;
}
