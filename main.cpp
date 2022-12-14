//Autores: Matheus Luis Webber e Pedro Henryque Nery de Oliveira
//Link para Git Hub: https://github.com/Mathwebb/Space-Invaders-3D

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <Windows.h>
#include <MMSystem.h>

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

enum MenuOptions {
	START_GAME = 0,
	MAIN_MENU_EXIT = 1
};
enum GameOverOptions {
	TRY_AGAIN = 0,
	GIVE_UP = 1
};
enum VictoryOptions {
	PLAY_AGAIN = 0,
	VICTORY_EXIT = 1
};
enum PausedOptions {
	CONTINUE = 0,
	RESTART = 1,
	MAIN_MENU_PAUSED = 2
};
enum NextLevelOptions {
	CONTINUE_NEXT_LEVEL = 0,
	MAIN_MENU_NEXT_LEVEL = 1
};
enum GameStates {
	MAIN_MENU,
	GAME_RUNNING,
	GAME_PAUSED,
	GAME_OVER,
	NEXT_LEVEL,
	VICTORY
};
int windowWidth = 640, windowHeight = 480, angle = 0, selectedMenuOption = 0, gameState = 0;
int actualLevel = 1, counterResetPlayerShot = 0, counterEnemyShot = 0, counterSpawnEnemy = 0;
Level level;

void initGlut(const char *nome_janela, int argc, char** argv);
void reshapeCallback(int w, int h);
void displayCallback(void);
void keyboardCallback(unsigned char key, int x, int y);
void keyboardCallbackSpecial(int key, int x, int y);
void mouseCallback(int button, int state, int x, int y);
void mousePassiveMotionCallback(int x, int y);
void spawnEnemyAtRandomPosition(int n);
void resetPlayerShot(int n);
void enemyShot(int n);
void timerCallback(int n);
void enableLighting();
void disableLighting();

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
	glutTimerFunc(1000, timerCallback, 0);
	
    GLfloat light_position[] = {0.0, 500.0, 0.0, 0.0};
	GLfloat light_color[] = {1.0, 1.0, 1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

	
	GLfloat mat_ambient_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_diffuse);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
	
    glShadeModel(GL_SMOOTH);
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void spawnEnemyAtRandomPosition(int n){
	if (gameState == GAME_RUNNING){
		level.spawnEnemy();
	}
}

void enemyShot(int n){
	if (gameState == GAME_RUNNING){
		level.enemiesShot();
	}
}

void resetPlayerShot(int n){
	if (gameState == GAME_RUNNING){
		level.getPlayer()->resetShot();
	}
}

void timerCallback(int n){
	if(gameState == GAME_RUNNING){
		counterResetPlayerShot+=50;
		counterEnemyShot+=50;
		counterSpawnEnemy+=50;
		level.moveEnemies();
		level.moveProjectiles();
		if(counterResetPlayerShot>=level.getPlayer()->getShotCooldownMiliseconds()){
			glutTimerFunc(level.getPlayer()->getShotCooldownMiliseconds(), resetPlayerShot, 0);
			counterResetPlayerShot=0;
		}
		if(level.getEnemies().size()!=0){
			if(counterEnemyShot>=level.getEnemies()[0].getShotCooldownMiliseconds()){
				glutTimerFunc(level.getPlayer()->getShotCooldownMiliseconds(), enemyShot, 0);
				counterEnemyShot=0;
			}
		}
		if(counterSpawnEnemy>=level.getEnemiesSpawnRateMiliseconds()){
			glutTimerFunc(level.getEnemiesSpawnRateMiliseconds(), spawnEnemyAtRandomPosition, 0);
			counterSpawnEnemy=0;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(100, timerCallback, 0);
}

void reshapeCallback(int w, int h){
	windowWidth = w;
	windowHeight = h;
    if (gameState == MAIN_MENU || gameState == GAME_OVER || gameState == VICTORY || gameState == GAME_PAUSED || gameState == NEXT_LEVEL){
		glMatrixMode(GL_PROJECTION);
		disableLighting();

	    glClearColor(0.0, 0.0, 0.0, 1.0);
		glLoadIdentity();
		
		glViewport(0, 0, (GLsizei) w, (GLsizei) h);
		
		glOrtho(-(w/2), (w/2), -(h/2), h/2, -1, 1);
		
		glMatrixMode(GL_MODELVIEW);		
	} else if (gameState == GAME_RUNNING){
	    glMatrixMode (GL_PROJECTION);
	    glClearColor(0.0, 0.0, 0.0, 1.0);

		enableLighting();
		
	    glLoadIdentity();
	
	    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	
	    gluPerspective(60, (float)w/(float)h, 1.0, 10000.0);
	
	    gluLookAt (level.getPlayer()->getCoordinateX(), level.getPlayer()->getCoordinateY()+60, level.getPlayer()->getCoordinateZ()+300,
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
		renderHUD(level);
		if (level.getStatus() == LEVEL_LOST){
			level.resetLevel();
			gameState = GAME_OVER;
			reshapeCallback(windowWidth, windowHeight);
		}
		if (level.getStatus() == LEVEL_WON){
			actualLevel++;
			if (actualLevel > 10){
				actualLevel = 1;
				gameState = VICTORY;
				sndPlaySound("assets/sounds/victory.wav", SND_ASYNC);
			}
			else{
				sndPlaySound("assets/sounds/levelWon.wav", SND_ASYNC);
				gameState = NEXT_LEVEL;
			}
			level = Level(actualLevel);
			reshapeCallback(windowWidth, windowHeight);
		}
	} else if (gameState == GAME_PAUSED){
		renderPause(selectedMenuOption, -windowHeight/2+windowWidth*0.1, 0.0, 0.0, 20.0);
	} else if (gameState == GAME_OVER){
		renderGameOver(selectedMenuOption, -windowHeight/2+windowWidth*0.1, 0.0, 0.0, 20.0);
	} else if (gameState == NEXT_LEVEL){
		renderNextLevel(selectedMenuOption, -windowWidth/2+windowWidth*0.1, 0.0, 0.0, 20.0);
	} else if (gameState == VICTORY){
		renderVictory(selectedMenuOption, -windowHeight/2+windowWidth*0.1, 0.0, 0.0, 20.0);
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
			if(gameState == GAME_RUNNING){
				gameState = GAME_PAUSED;
				reshapeCallback(windowWidth, windowHeight);
				displayCallback();
			} else if(gameState == GAME_PAUSED){
				gameState = GAME_RUNNING;
				reshapeCallback(windowWidth, windowHeight);
				displayCallback();
			}
			else{
				exit(0);
			}
			break;
		case ENTER:
			if (gameState == MAIN_MENU){
				sndPlaySound("assets/sounds/click.wav", SND_SYNC);
				if (selectedMenuOption == START_GAME){
					gameState = GAME_RUNNING;
					reshapeCallback(windowWidth, windowHeight);
					displayCallback();
				} else if (selectedMenuOption == MAIN_MENU_EXIT){
					exit(0);
				}
			}
			if (gameState == GAME_OVER){
				sndPlaySound("assets/sounds/click.wav", SND_SYNC);
				if (selectedMenuOption == TRY_AGAIN){
					gameState = GAME_RUNNING;
					level.resetLevel();
					reshapeCallback(windowWidth, windowHeight);
					displayCallback();
				} else if (selectedMenuOption == GIVE_UP){
					gameState = MAIN_MENU;
					selectedMenuOption=0;
					level.resetLevel();
					reshapeCallback(windowWidth, windowHeight);
					displayCallback();
				}
			}
			if (gameState == NEXT_LEVEL){
				sndPlaySound("assets/sounds/click.wav", SND_SYNC);
				if (selectedMenuOption == CONTINUE_NEXT_LEVEL){
					gameState = GAME_RUNNING;
					reshapeCallback(windowWidth, windowHeight);
					displayCallback();
				} else if (selectedMenuOption == MAIN_MENU_NEXT_LEVEL){
					gameState = MAIN_MENU;
					selectedMenuOption=0;
					level.resetLevel();
					reshapeCallback(windowWidth, windowHeight);
					displayCallback();
				}
			}
			if (gameState == VICTORY){
				sndPlaySound("assets/sounds/click.wav", SND_SYNC);
				if (selectedMenuOption == PLAY_AGAIN){
					gameState = GAME_RUNNING;
					level.resetLevel();
					reshapeCallback(windowWidth, windowHeight);
					displayCallback();
				} else if (selectedMenuOption == VICTORY_EXIT){
					gameState = MAIN_MENU;
					selectedMenuOption=0;
					level.resetLevel();
					reshapeCallback(windowWidth, windowHeight);
					displayCallback();
				}
			}
			if (gameState == GAME_PAUSED){
				sndPlaySound("assets/sounds/click.wav", SND_SYNC);
				if (selectedMenuOption == CONTINUE){
					gameState = GAME_RUNNING;
					reshapeCallback(windowWidth, windowHeight);
					displayCallback();
				} else if (selectedMenuOption == RESTART){
					gameState = GAME_RUNNING;
					level.resetLevel();
					reshapeCallback(windowWidth, windowHeight);
					displayCallback();
				} else if (selectedMenuOption == MAIN_MENU_PAUSED){
					gameState = MAIN_MENU;
					selectedMenuOption=0;
					level.resetLevel();
					reshapeCallback(windowWidth, windowHeight);
					displayCallback();
				}
			}
			break;
		case SPACEBAR:
			if (gameState == GAME_RUNNING){
				level.playerShoot();
			}
		case NUMBER_0:
			if (gameState == MAIN_MENU || gameState == GAME_OVER || gameState == VICTORY || gameState == GAME_PAUSED || gameState == NEXT_LEVEL){
				sndPlaySound("assets/sounds/swapOptions.wav", SND_ASYNC);
				selectedMenuOption = 0;
				displayCallback();
			}
			break;
		case NUMBER_1:
			if (gameState == MAIN_MENU || gameState == GAME_OVER || gameState == VICTORY || gameState == GAME_PAUSED || gameState == NEXT_LEVEL){
				sndPlaySound("assets/sounds/swapOptions.wav", SND_ASYNC);
				selectedMenuOption = 1;
				displayCallback();
			}
			break;
		case NUMBER_2:
			if (gameState == GAME_PAUSED){
				sndPlaySound("assets/sounds/swapOptions.wav", SND_ASYNC);
				selectedMenuOption = 2;
				displayCallback();
			}
			break;
		// case TAB:
		// 	if (gameState == GAME_RUNNING){
		// 		level.setLevelStatus(LEVEL_WON);
		// 	}
		// 	break;
	}	
}

void keyboardCallbackSpecial(int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP:
			if (gameState == MAIN_MENU || gameState == GAME_OVER || gameState == VICTORY || gameState == GAME_PAUSED || gameState == NEXT_LEVEL){
				sndPlaySound("assets/sounds/swapOptions.wav", SND_ASYNC);
				if (selectedMenuOption > 0){
					selectedMenuOption--;
					displayCallback();
				} else if(gameState == GAME_PAUSED){
					selectedMenuOption=2;
					displayCallback();
				}
				else {
					selectedMenuOption=1;
					displayCallback();
				}
			}else if (gameState == GAME_RUNNING){
				level.movePlayerUp();
				reshapeCallback(windowWidth, windowHeight);
				displayCallback();
			}
			break;
		
		case GLUT_KEY_DOWN:
			if (gameState == MAIN_MENU || gameState == GAME_OVER || gameState == VICTORY || gameState == NEXT_LEVEL){
				sndPlaySound("assets/sounds/swapOptions.wav", SND_ASYNC);
				if (selectedMenuOption < 1){
					selectedMenuOption++;
					displayCallback();
				}
				else {
					selectedMenuOption=0;
					displayCallback();
				}
			}else if (gameState == GAME_PAUSED){
				sndPlaySound("assets/sounds/swapOptions.wav", SND_ASYNC);
				if (selectedMenuOption < 2){
					selectedMenuOption++;
					displayCallback();
				}
				else {
					selectedMenuOption=0;
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

void enableLighting(){
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
}

void disableLighting(){
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_COLOR_MATERIAL);
}

int main(int argc, char* argv[]){
    initGlut("Space Invaders 3D", argc, argv);
    glutMainLoop();
    return 0;
}
