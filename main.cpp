#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

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
float playerX = 0, playerY = 0, playerZ = 0;
vector<Object> sceneObjects;

struct object{
	vector<struct vertex> v;
	vector<struct vertex> vn;
	vector<struct face> f;
};

struct vertex{
	float x;
	float y;
	float z;
};

struct face{
	int v1;
	int v2;
	int v3;
};

object loadOBJ(const char * path){
	FILE * file = fopen(path, "r");
	fstream debugFile("debug.txt", ios::out);
	struct object obj;
	vector<struct vertex> vertices;
	vector<struct vertex> vertices_normals;
	vector<struct face> faces;
	if( file == NULL ){
	    printf("Impossible to open the file !\n");
	    return obj;
	}
	while( 1 ){
	    char lineHeader[128];
	    // read the first word of the line
	    int res = fscanf(file, "%s", lineHeader);
	    if (res == EOF)
	        break; // EOF = End Of File. Quit the loop.
	
	    if ( strcmp( lineHeader, "v" ) == 0 ){
	    	vertex vert;
		    fscanf(file, "%f %f %f\n", &vert.x, &vert.y, &vert.z );
			debugFile << "Vertex: " << vert.x << " " << vert.y << " " << vert.z << endl;
		    vertices.push_back(vert);
	    }else if ( strcmp( lineHeader, "vn" ) == 0 ){
		    vertex normal;
		    fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			debugFile << "Normal: " << normal.x << " " << normal.y << " " << normal.z << endl;
		    vertices_normals.push_back(normal);
	    }
		else if ( strcmp( lineHeader, "f" ) == 0 ){
			face temp_face;
		    int matches = fscanf(file, "%d %d %d\n", &temp_face.v1, &temp_face.v2, &temp_face.v3);
		    if (matches == 3) {
				faces.push_back(temp_face);
				debugFile << "Face: " << temp_face.v1 << " " << temp_face.v2 << " " << temp_face.v3 << endl;
			}
		}
	}
	obj.v = vertices;
	obj.vn = vertices_normals;
	obj.f = faces;
	return obj;
}

object obj = loadOBJ("assets/models/porsche_clear.obj");

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
	Object loadedObject = loadObject("assets/models/porsche_clear.obj");
	sceneObjects.push_back(loadedObject);

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
	
	    gluLookAt (playerX, playerY+40, playerZ+500, playerX, playerY, playerZ, 0.0, 1.0, 0.0);
	
	    glMatrixMode (GL_MODELVIEW);
	}
}

void displayCallback(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (gameState == MAIN_MENU){
		showMainMenu(-windowWidth/2+windowWidth*0.1, 0.0, 0.0, 20.0);
	} else if(gameState == GAME_RUNNING){
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(playerX, playerY, playerZ);
		glutSolidCube(50);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(0.0, 0.0, -100.0);
		glutSolidCube(50);
		glPopMatrix();

		// glPushMatrix();
		// glColor3f(0.0, 1.0, 0.0);
		// glTranslatef(100.0, 100.0, 0.0);
		// // Create a new object with the format of a cube
		// Object cube;
		// // Create the cube vertices
		// vector<Vertex> cubeVertices;
		// cubeVertices.push_back(Vertex(0.0, 0.0, 0.0));
		// cubeVertices.push_back(Vertex(0.0, 0.0, 50.0));
		// cubeVertices.push_back(Vertex(0.0, 50.0, 0.0));
		// cubeVertices.push_back(Vertex(0.0, 50.0, 50.0));
		// cubeVertices.push_back(Vertex(50.0, 0.0, 0.0));
		// cubeVertices.push_back(Vertex(50.0, 0.0, 50.0));
		// cubeVertices.push_back(Vertex(50.0, 50.0, 0.0));
		// cubeVertices.push_back(Vertex(50.0, 50.0, 50.0));
		// // Create the cube faces
		// vector<Face> cubeFaces;
		// cubeFaces.push_back(Face(0, 1, 3));
		// cubeFaces.push_back(Face(0, 3, 2));
		// cubeFaces.push_back(Face(0, 2, 6));
		// cubeFaces.push_back(Face(0, 6, 4));
		// cubeFaces.push_back(Face(0, 4, 5));
		// cubeFaces.push_back(Face(0, 5, 1));
		// cubeFaces.push_back(Face(1, 5, 7));
		// cubeFaces.push_back(Face(1, 7, 3));
		// cubeFaces.push_back(Face(2, 3, 7));
		// cubeFaces.push_back(Face(2, 7, 6));
		// cubeFaces.push_back(Face(4, 6, 7));
		// cubeFaces.push_back(Face(4, 7, 5));
		// // Set the cube vertices and faces		
		// cube.setVertices(cubeVertices);
		// cube.setFaces(cubeFaces);
		// // Render the cube
		// vector<Object> sceneObjects;
		// sceneObjects.push_back(cube);
		// renderObjects(sceneObjects);
		// glPopMatrix();

		// glPushMatrix();
		// glColor3f(0.0, 1.0, 0.0);
		// glTranslatef(0.0, 100.0, 0.0);
		// vector<struct face> faces = obj.f;
		// vector<struct vertex> vertices = obj.v;
		// glBegin(GL_TRIANGLES);
		// for (unsigned int i = 0; i < faces.size(); i++){
		// 	for (int j = 0; j < 3; j++){
		// 		glVertex3f(vertices[faces.at(i).v1].x, vertices[faces.at(i).v1].y, vertices[faces.at(i).v1].z);
		// 		glVertex3f(vertices[faces.at(i).v2].x, vertices[faces.at(i).v2].y, vertices[faces.at(i).v2].z);
		// 		glVertex3f(vertices[faces.at(i).v3].x, vertices[faces.at(i).v3].y, vertices[faces.at(i).v3].z);
		// 	}
		// }
		// glEnd();
		// glPopMatrix();

		glPushMatrix();
		glColor3f(0.0, 0.0, 1.0);
		glTranslatef(0.0, 200.0, 0.0);
		renderObjects(sceneObjects);
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
			if (gameState == MAIN_MENU){
				if (selectedMenuOption > 0){
					selectedMenuOption--;
					displayCallback();
				}
			}else if (gameState == GAME_RUNNING){
				playerY += 10;
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
				playerY -= 10;
				reshapeCallback(windowWidth, windowHeight);
				displayCallback();
			}
			break;
		case GLUT_KEY_RIGHT:
			if (gameState == GAME_RUNNING){
				playerX += 10;
				reshapeCallback(windowWidth, windowHeight);
				displayCallback();
			}
			break;
		case GLUT_KEY_LEFT:
			if (gameState == GAME_RUNNING){
				playerX -= 10;
				reshapeCallback(windowWidth, windowHeight);
				displayCallback();
			}
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

	for (unsigned int i = 0; i < text.size(); i++) {
		glutBitmapCharacter(font, text.at(i));
	}

	glPopMatrix();
}

void renderObjects(vector<Object> sceneObjects) {
	for (unsigned int i = 0; i < sceneObjects.size(); i++){
		Object sceneObject = sceneObjects.at(i);
		glPushMatrix();
		glTranslatef(sceneObject.getCoordinateX(), sceneObject.getCoordinateY(), sceneObject.getCoordinateZ());
		glRotatef(sceneObject.getRotationAngle(), sceneObject.getRotationX(), sceneObject.getRotationY(), sceneObject.getRotationZ());
		glScalef(sceneObject.getScaleX(), sceneObject.getScaleY(), sceneObject.getScaleZ());
		glColor3f(0, 1, 0);
		for (unsigned int j = 0; j < sceneObject.getFaces().size(); j++){
			Face face = sceneObject.getFaces().at(j);
			vector <int> faceVertexIndices = face.getVerticesIndices();
			Vertex vertex1 = sceneObject.getVertices().at(faceVertexIndices.at(0));
			Vertex vertex2 = sceneObject.getVertices().at(faceVertexIndices.at(1));
			Vertex vertex3 = sceneObject.getVertices().at(faceVertexIndices.at(2));
			glBegin(GL_TRIANGLES);
			glNormal3fv(vertex1.getNormal());
			glVertex3f(vertex1.getCoordinateX(), vertex1.getCoordinateY(), vertex1.getCoordinateZ());
			glNormal3fv(vertex2.getNormal());
			glVertex3f(vertex2.getCoordinateX(), vertex2.getCoordinateY(), vertex2.getCoordinateZ());
			glNormal3fv(vertex3.getNormal());
			glVertex3f(vertex3.getCoordinateX(), vertex3.getCoordinateY(), vertex3.getCoordinateZ());
			glEnd();
		}
		glPopMatrix();
	}
	cout << "Objects Rendered" << endl;
}

void showMainMenu(float x, float y, float z, float optionsSpacing){
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

int main(int argc, char* argv[]){
    initGlut("Space Invaders 3D", argc, argv);
    glutMainLoop();
    return 0;
}
