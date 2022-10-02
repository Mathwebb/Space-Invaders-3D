#ifndef RENDERERS_H
#define RENDERERS_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <string>
#include <vector>

#include "../game_classes/Level.h"

using namespace std;

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
	glBegin(GL_BITMAP);
	glColor3f(r, g, b);
	glRasterPos3f(x, y, z);
	for (unsigned int i = 0; i < text.size(); i++) {
		glutBitmapCharacter(font, text.at(i));
	}
	glEnd();
	glPopMatrix();
}

void renderMainMenu(int selectedMenuOption, float x, float y, float z, float optionsSpacing){
	glPushMatrix();
    
    glBegin(GL_BITMAP);
    renderBitMapCharacter(0, 0, 0, GLUT_BITMAP_TIMES_ROMAN_24, "Space Invaders 3D", 1.0, 0.0, 0.0);
	if (selectedMenuOption == 0){
    	renderBitMapCharacter(x, y, z, GLUT_BITMAP_HELVETICA_18, "[ 0 ] - Start game", 0.0, 1.0, 1.0);
    	renderBitMapCharacter(x, y-optionsSpacing, z, GLUT_BITMAP_HELVETICA_18, "[ 1 ] - Exit", 1.0, 1.0, 1.0);
	} else if (selectedMenuOption == 1){
		renderBitMapCharacter(x, y, z, GLUT_BITMAP_HELVETICA_18, "[ 0 ] - Start game", 1.0, 1.0, 1.0);
    	renderBitMapCharacter(x, y-optionsSpacing, z, GLUT_BITMAP_HELVETICA_18, "[ 1 ] - Exit", 0.0, 1.0, 1.0);
	}
    glEnd();
    
    glPopMatrix();
}

void renderGameOver(int selectedMenuOption, float x, float y, float z, float optionsSpacing){
	glPushMatrix();
    
    glBegin(GL_BITMAP);
    renderBitMapCharacter(x, y, z, GLUT_BITMAP_HELVETICA_18, " You Lost :( ", 1.0, 0.0, 0.0);
	if (selectedMenuOption == 0){
    	renderBitMapCharacter(x, y-optionsSpacing, z, GLUT_BITMAP_HELVETICA_18, "[ 0 ] - Try Again", 0.0, 1.0, 1.0);
    	renderBitMapCharacter(x, y-(2*(optionsSpacing)), z, GLUT_BITMAP_HELVETICA_18, "[ 1 ] - Give Up", 1.0, 1.0, 1.0);
	} else if (selectedMenuOption == 1){
		renderBitMapCharacter(x, y-optionsSpacing, z, GLUT_BITMAP_HELVETICA_18, "[ 0 ] - Try Again", 1.0, 1.0, 1.0);
    	renderBitMapCharacter(x, y-(2*(optionsSpacing)), z, GLUT_BITMAP_HELVETICA_18, "[ 1 ] - Give Up", 0.0, 1.0, 1.0);
	}
    glEnd();
    
    glPopMatrix();
}

void renderVictory(int selectedMenuOption, float x, float y, float z, float optionsSpacing){
	glPushMatrix();
    
    glBegin(GL_BITMAP);
    renderBitMapCharacter(x, y, z, GLUT_BITMAP_HELVETICA_18, " Congratulations, you save the earth!!! ", 1.0, 0.0, 0.0);
	if (selectedMenuOption == 0){
    	renderBitMapCharacter(x, y-optionsSpacing, z, GLUT_BITMAP_HELVETICA_18, "[ 0 ] - Play Again", 0.0, 1.0, 1.0);
    	renderBitMapCharacter(x, y-(2*(optionsSpacing)), z, GLUT_BITMAP_HELVETICA_18, "[ 1 ] - Exit", 1.0, 1.0, 1.0);
	} else if (selectedMenuOption == 1){
		renderBitMapCharacter(x, y-optionsSpacing, z, GLUT_BITMAP_HELVETICA_18, "[ 0 ] - Play Again", 1.0, 1.0, 1.0);
    	renderBitMapCharacter(x, y-(2*(optionsSpacing)), z, GLUT_BITMAP_HELVETICA_18, "[ 1 ] - Exit", 0.0, 1.0, 1.0);
	}
    glEnd();
    
    glPopMatrix();
}

void renderNextLevel(int selectedMenuOption, float x, float y, float z, float optionsSpacing){
	glPushMatrix();
    
    glBegin(GL_BITMAP);
    renderBitMapCharacter(x, y, z, GLUT_BITMAP_HELVETICA_18, " Well Done ", 1.0, 0.0, 0.0);
	if (selectedMenuOption == 0){
    	renderBitMapCharacter(x, y-optionsSpacing, z, GLUT_BITMAP_HELVETICA_18, "[ 0 ] - Next Level", 0.0, 1.0, 1.0);
    	renderBitMapCharacter(x, y-(2*(optionsSpacing)), z, GLUT_BITMAP_HELVETICA_18, "[ 1 ] - Main Menu", 1.0, 1.0, 1.0);
	} else if (selectedMenuOption == 1){
		renderBitMapCharacter(x, y-optionsSpacing, z, GLUT_BITMAP_HELVETICA_18, "[ 0 ] - Next Level", 1.0, 1.0, 1.0);
    	renderBitMapCharacter(x, y-(2*(optionsSpacing)), z, GLUT_BITMAP_HELVETICA_18, "[ 1 ] - Main Menu", 0.0, 1.0, 1.0);
	}
    glEnd();
    
    glPopMatrix();
}

void renderPause(int selectedMenuOption, float x, float y, float z, float optionsSpacing){
	glPushMatrix();
    
    glBegin(GL_BITMAP);
    renderBitMapCharacter(x, y, z, GLUT_BITMAP_HELVETICA_18, " Game Paused ", 1.0, 0.0, 0.0);
	if (selectedMenuOption == 0){
    	renderBitMapCharacter(x, y-optionsSpacing, z, GLUT_BITMAP_HELVETICA_18, "[ 0 ] - Continue", 0.0, 1.0, 1.0);
    	renderBitMapCharacter(x, y-(2*(optionsSpacing)), z, GLUT_BITMAP_HELVETICA_18, "[ 1 ] - Restart Level", 1.0, 1.0, 1.0);
    	renderBitMapCharacter(x, y-(3*(optionsSpacing)), z, GLUT_BITMAP_HELVETICA_18, "[ 2 ] - Main Menu", 1.0, 1.0, 1.0);
	} else if (selectedMenuOption == 1){
		renderBitMapCharacter(x, y-optionsSpacing, z, GLUT_BITMAP_HELVETICA_18, "[ 0 ] - Continue", 1.0, 1.0, 1.0);
    	renderBitMapCharacter(x, y-(2*(optionsSpacing)), z, GLUT_BITMAP_HELVETICA_18, "[ 1 ] - Restart Level", 0.0, 1.0, 1.0);
    	renderBitMapCharacter(x, y-(3*(optionsSpacing)), z, GLUT_BITMAP_HELVETICA_18, "[ 2 ] - Main Menu", 1.0, 1.0, 1.0);
	} else if (selectedMenuOption == 2){
		renderBitMapCharacter(x, y-optionsSpacing, z, GLUT_BITMAP_HELVETICA_18, "[ 0 ] - Continue", 1.0, 1.0, 1.0);
    	renderBitMapCharacter(x, y-(2*(optionsSpacing)), z, GLUT_BITMAP_HELVETICA_18, "[ 1 ] - Restart Level", 1.0, 1.0, 1.0);
    	renderBitMapCharacter(x, y-(3*(optionsSpacing)), z, GLUT_BITMAP_HELVETICA_18, "[ 2 ] - Main Menu", 0.0, 1.0, 1.0);
	}
    glEnd();
    
    glPopMatrix();
}

void renderHUD(Level level){
	glMatrixMode(GL_PROJECTION);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_COLOR_MATERIAL);

	glPushMatrix();
    
    glBegin(GL_BITMAP);
    float xPlayer = level.getPlayer()->getCoordinateX();
    float yPlayer = level.getPlayer()->getCoordinateY();
    float zPlayer = level.getPlayer()->getCoordinateZ();
    glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(xPlayer-170+level.getPlayer()->getHealthPoints()*0.8, yPlayer+115, 0);
	glVertex3f(xPlayer-170+level.getPlayer()->getHealthPoints()*0.8, yPlayer+130, 0);
	glVertex3f(xPlayer-170, yPlayer+130, 0);
	glVertex3f(xPlayer-170, yPlayer+115, 0);
	glEnd();
    glPopMatrix();
    glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(xPlayer-170+level.getObjectiveHealthPoints()*0.8, yPlayer+95, 0);
	glVertex3f(xPlayer-170+level.getObjectiveHealthPoints()*0.8, yPlayer+110, 0);
	glVertex3f(xPlayer-170, yPlayer+110, 0);
	glVertex3f(xPlayer-170, yPlayer+95, 0);
	glEnd();
    glPopMatrix();
    char aux[30] = "Level ";
    char nivel[10];
	sprintf (nivel, "%d", level.getLevelNumber()); 
	strcat(aux, nivel);
	renderBitMapCharacter(xPlayer-30, yPlayer+140, zPlayer, GLUT_BITMAP_HELVETICA_18, aux, 1.0, 1.0, 1.0);
	char aux2[30] = "Enemies Left = ";
    char iniRes[10];
	sprintf (iniRes, "%d", level.getEnemiesToKill()); 
	strcat(aux2, iniRes);
	renderBitMapCharacter(xPlayer+100, yPlayer+120, zPlayer, GLUT_BITMAP_HELVETICA_18, aux2 , 1.0, 1.0, 1.0);
	char aux3[30]= "Enemies Killed = ";
    char iniMorto[10];
	sprintf (iniMorto, "%d", level.getEnemiesKilled()); 
	strcat(aux3, iniMorto);
	renderBitMapCharacter(xPlayer+100, yPlayer+100, zPlayer, GLUT_BITMAP_HELVETICA_18, aux3, 1.0, 1.0, 1.0);
	renderBitMapCharacter(xPlayer-205, yPlayer+120, zPlayer, GLUT_BITMAP_HELVETICA_18, "Ship", 1.0, 1.0, 1.0);
	renderBitMapCharacter(xPlayer-209, yPlayer+100, zPlayer, GLUT_BITMAP_HELVETICA_18, "Earth", 1.0, 1.0, 1.0);
	glEnd();
    
    glPopMatrix();
    
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_MODELVIEW);
}
#endif
