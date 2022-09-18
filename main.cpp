#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

int windowSize[2] = {640, 480}, angle = 0;

void initGlut(const char *nome_janela, int argc, char** argv);
void reshapeCallback(int w, int h);
void displayCallback(void);
void keyboardCallback(unsigned char key, int x, int y);
void keyboardCallbackSpecial(int key, int x, int y);
void mouseCallback(int button, int state, int x, int y);
void mouseMenu();
void showMainMenu();

void initGlut(const char *nome_janela, int argc, char** argv){
    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowSize(windowSize[0],windowSize[1]);
    glutInitWindowPosition(100,100);
    glutCreateWindow(nome_janela);

    glutReshapeFunc(reshapeCallback);
    glutDisplayFunc(displayCallback);
    glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(keyboardCallbackSpecial);
	glutMouseFunc(mouseCallback);
}

void reshapeCallback(int w, int h){
    glMatrixMode (GL_PROJECTION);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glLoadIdentity();

    glViewport (0, 0, (GLsizei) w, (GLsizei) h);

    gluPerspective(60, (float)w/(float)h, 1.0, 100.0);

    gluLookAt (0, 0.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glMatrixMode (GL_MODELVIEW);

}

void displayCallback(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    showMainMenu();

    glutSwapBuffers();
}

void mouseCallback(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN)
			if (angle >= 10)	angle -= 5;
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN)
			if (angle <= 130)	angle += 5;
	glutPostRedisplay();
}

void keyboardCallback(unsigned char key, int x, int y){
	switch (key){
		case 27: // ESC
			exit(0);
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

void reshapeView(){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();

    gluLookAt(0.0, 0.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glMatrixMode (GL_MODELVIEW);	
}

void renderStrokeFontString(float x, float y, float z, void *font, char *string) {
	char *c;
	glPushMatrix();
	glTranslatef(x, y,z);

	for (c=string; *c != '\0'; c++) {
		glutStrokeCharacter(font, *c);
	}

	glPopMatrix();
}

void showMainMenu(){
	
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 0, 0);
    glPushMatrix();
    // renderStrokeFontString(0, 0, 0, GLUT_STROKE_ROMAN, "dias");
    glutSolidCube(20);
    glPopMatrix();
}

int main(int argc, char* argv[]){
    initGlut("Space Invaders 3D", argc, argv);
    glutMainLoop();
    return 0;
}
