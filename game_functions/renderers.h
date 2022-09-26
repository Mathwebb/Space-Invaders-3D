#ifndef RENDERERS_H
#define RENDERERS_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <string>
#include <vector>

#include "../game_classes/Object.h"

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
	glRasterPos3f(x, y, z);
	glColor3f(r, g, b);

	for (unsigned int i = 0; i < text.size(); i++) {
		glutBitmapCharacter(font, text.at(i));
	}

	glPopMatrix();
}

void renderMainMenu(int selectedMenuOption, float x, float y, float z, float optionsSpacing){
	glPushMatrix();
    
    glBegin(GL_BITMAP);
	if (selectedMenuOption == 0){
    	renderBitMapCharacter(x, y, z, GLUT_BITMAP_HELVETICA_18, "[ 0 ] - Start game", 1.0, 1.0, 1.0);
    	renderBitMapCharacter(x, y-optionsSpacing, z, GLUT_BITMAP_HELVETICA_18, "[ 1 ] - Exit", 0.0, 1.0, 1.0);
	} else if (selectedMenuOption == 1){
		renderBitMapCharacter(x, y-optionsSpacing, z, GLUT_BITMAP_HELVETICA_18, "[ 1 ] - Exit", 1.0, 1.0, 1.0);
		renderBitMapCharacter(x, y, z, GLUT_BITMAP_HELVETICA_18, "[ 0 ] - Start game", 0.0, 1.0, 1.0);
	}
    glEnd();
    
    glPopMatrix();
}

void renderGameOver(int selectedMenuOption, float x, float y, float z, float optionsSpacing){
	glPushMatrix();
    
    glBegin(GL_BITMAP);
    renderBitMapCharacter(x, y, z, GLUT_BITMAP_HELVETICA_18, " You Lost :( ", 1.0, 0.0, 0.0);
	if (selectedMenuOption == 0){
    	renderBitMapCharacter(x, y-optionsSpacing, z, GLUT_BITMAP_HELVETICA_18, "[ 0 ] - Try Again", 1.0, 1.0, 1.0);
    	renderBitMapCharacter(x, y-(2*(optionsSpacing)), z, GLUT_BITMAP_HELVETICA_18, "[ 1 ] - Give Up", 0.0, 1.0, 1.0);
	} else if (selectedMenuOption == 1){
		renderBitMapCharacter(x, y-(2*(optionsSpacing)), z, GLUT_BITMAP_HELVETICA_18, "[ 1 ] - Give Up", 1.0, 1.0, 1.0);
		renderBitMapCharacter(x, y-optionsSpacing, z, GLUT_BITMAP_HELVETICA_18, "[ 0 ] - Try Again", 0.0, 1.0, 1.0);
	}
    glEnd();
    
    glPopMatrix();
}

void renderVictory(int selectedMenuOption, float x, float y, float z, float optionsSpacing){
	glPushMatrix();
    
    glBegin(GL_BITMAP);
    renderBitMapCharacter(x, y, z, GLUT_BITMAP_HELVETICA_18, " Wow, congratulations!!! ", 1.0, 0.0, 0.0);
	if (selectedMenuOption == 0){
    	renderBitMapCharacter(x, y-optionsSpacing, z, GLUT_BITMAP_HELVETICA_18, "[ 0 ] - Play Again", 1.0, 1.0, 1.0);
    	renderBitMapCharacter(x, y-(2*(optionsSpacing)), z, GLUT_BITMAP_HELVETICA_18, "[ 1 ] - Exit", 0.0, 1.0, 1.0);
	} else if (selectedMenuOption == 1){
		renderBitMapCharacter(x, y-(2*(optionsSpacing)), z, GLUT_BITMAP_HELVETICA_18, "[ 1 ] - Exit", 1.0, 1.0, 1.0);
		renderBitMapCharacter(x, y-optionsSpacing, z, GLUT_BITMAP_HELVETICA_18, "[ 0 ] - Play Again", 0.0, 1.0, 1.0);
	}
    glEnd();
    
    glPopMatrix();
}

void renderHUD(float x, float y, float z, float optionsSpacing, int score, int lives){
}

// void renderObjects(vector<Object> sceneObjects) {
// 	for (unsigned int i = 0; i < sceneObjects.size(); i++){
// 		Object sceneObject = sceneObjects.at(i);
// 		glPushMatrix();
// 		glTranslatef(sceneObject.getCoordinateX(), sceneObject.getCoordinateY(), sceneObject.getCoordinateZ());
// 		glRotatef(sceneObject.getRotationAngle(), sceneObject.getRotationX(), sceneObject.getRotationY(), sceneObject.getRotationZ());
// 		glScalef(sceneObject.getScaleX(), sceneObject.getScaleY(), sceneObject.getScaleZ());
// 		glColor3f(0, 1, 0);
// 		for (unsigned int j = 0; j < sceneObject.getFaces().size(); j++){
// 			Face face = sceneObject.getFaces().at(j);
// 			vector <int> faceVertexIndices = face.getVerticesIndices();
// 			Vertex vertex1 = sceneObject.getVertices().at(faceVertexIndices.at(0));
// 			Vertex vertex2 = sceneObject.getVertices().at(faceVertexIndices.at(1));
// 			Vertex vertex3 = sceneObject.getVertices().at(faceVertexIndices.at(2));
// 			glBegin(GL_TRIANGLES);
// 			glNormal3fv(vertex1.getNormal());
// 			glVertex3f(vertex1.getCoordinateX(), vertex1.getCoordinateY(), vertex1.getCoordinateZ());
// 			glNormal3fv(vertex2.getNormal());
// 			glVertex3f(vertex2.getCoordinateX(), vertex2.getCoordinateY(), vertex2.getCoordinateZ());
// 			glNormal3fv(vertex3.getNormal());
// 			glVertex3f(vertex3.getCoordinateX(), vertex3.getCoordinateY(), vertex3.getCoordinateZ());
// 			glEnd();
// 		}
// 		glPopMatrix();
// 	}
// }
#endif
