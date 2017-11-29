//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <string>
#include "vertex.h"
#include "models.h"
#include "objects.h"
#include "manageView.h"
#include "types.h"
#include "3DObject.h"
#include "wattRegulator.h"
#include "sceneButtons.h"
#include "fps.h"

using namespace std;

Models modelos;
vector<ViewMode> modos(4, NULL_);
TypeObject objeto = _NULL;
sceneButtons botones;
FPScounter fps;


// Contador de FPS
bool showFPS = false;
double tiempo;
int frames = 0, fps = 0;
double base_time = 0;

int window_1, window_2;

bool sumar = false;
bool restar = false;

// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=900,UI_window_height=900;

//**************************************************************************
//	ClearWindow
//***************************************************************************
void clear_window() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
	//  Front_plane>0  Back_plane>PlanoDelantero)
	glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer() {
	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-Observer_distance);
	glRotatef(Observer_angle_x,1,0,0);
	glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************
void draw_axis() {
	glBegin(GL_LINES);
	// eje X, color rojo
	glColor3f(1,0,0);
	glVertex3f(-AXIS_SIZE,0,0);
	glVertex3f(AXIS_SIZE,0,0);
	// eje Y, color verde
	glColor3f(0,1,0);
	glVertex3f(0,-AXIS_SIZE,0);
	glVertex3f(0,AXIS_SIZE,0);
	// eje Z, color azul
	glColor3f(0,0,1);
	glVertex3f(0,0,-AXIS_SIZE);
	glVertex3f(0,0,AXIS_SIZE);
	glEnd();
}
//**************************************************************************
// Texto en pantalla
//***************************************************************************
string dts(double i){
	stringstream out;
	out << i;
	return out.str();
}

void printText(int x, int y, string text) {
    glRasterPos2f(x,y);

    for (int i=0; i<text.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
    }
}

void drawHUD() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, UI_window_width, UI_window_height, 0.0, -1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_DEPTH_BUFFER_BIT);
    glColor3f(1,0,0);

	printText(50, 50, "FPS: " + dts(fps.getFPS()));
	if (objeto == WATT) printText(50, 70, "V: " + dts(modelos.v_Watt.getSpeed()));

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

}

//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************
void draw_objects() {
	glPointSize(3);
	glLineWidth(1);

	if (!modelos.getModelsAreGenerated()) {
		modelos.initializeModels();
		modelos.setModelsAreGenerated(true);
	}

	if (sumar) {
		modelos.addStep(objeto);
		sumar = false;
	}

	if (restar) {
		modelos.reduceStep(objeto);
		restar = false;
	}

	drawModels(modelos, objeto, modos);

	if (modelos.v_Watt.isSpinning()){
		//glutIdleFunc(modelos.v_Watt.giro());
		modelos.v_Watt.giro();
		glutPostRedisplay();
	}

	fps.incrementFrames();

	drawHUD();
}


//**************************************************************************
// DRAW ESCENA
//***************************************************************************
void draw_scene(void) {
	clear_window();
	change_observer();
	draw_axis();
	draw_objects();
	glutSwapBuffers();

	fps.calculateFPS();
}

//**************************************************************************
//	BOTONES
//***************************************************************************
void draw_scene_button(void) {
	clear_window();
	if (botones.getButtonsGenerated()) {
		botones.generateButtons();
		botones.setButtonsGenerated();
	}

	botones.draw_buttons();
	glutSwapBuffers();
}
//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1) {
	change_projection();
	glViewport(0,0,Ancho1,Alto1);
	glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y) {
	switch (toupper(Tecla1)) {
		case 'Q': exit(0); break;

		case 'P': modos = changeMode(modos, MESH, 0); break;
		case 'L': modos = changeMode(modos, EDGES, 1); break;
		case 'F': modos = changeMode(modos, SOLID, 2); break;
		case 'C': modos = changeMode(modos, CHESS, 3); break;

		case 'T': restar = true; break;
		case 'Y': sumar = true; break;

		case 'X': modelos.v_Watt.aumentarVelocidad(); break;
		case 'Z': modelos.v_Watt.decrementarVelocidad(); break;

		case 'A': modelos.v_Watt.toggleSpinning(); break;
	}

	draw_scene();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y) {
	switch (Tecla1){
		case GLUT_KEY_LEFT:Observer_angle_y--;break;
		case GLUT_KEY_RIGHT:Observer_angle_y++;break;
		case GLUT_KEY_UP:Observer_angle_x--;break;
		case GLUT_KEY_DOWN:Observer_angle_x++;break;
		case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
		case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;

		case GLUT_KEY_F1: objeto = changeObject(objeto, CUBE); break;
		case GLUT_KEY_F2: objeto = changeObject(objeto, TETRAHEDRON); break;
		case GLUT_KEY_F3: objeto = changeObject(objeto, PLY_STATIC); break;
		case GLUT_KEY_F4: objeto = changeObject(objeto, PLY_REVOLUTION); break;
		case GLUT_KEY_F5: objeto = changeObject(objeto, CYLINDER); break;
		case GLUT_KEY_F6: objeto = changeObject(objeto, GLASS); break;
		case GLUT_KEY_F7: objeto = changeObject(objeto, GLASS_INVERTED); break;
		case GLUT_KEY_F8: objeto = changeObject(objeto, CONE); break;
		case GLUT_KEY_F9: objeto = changeObject(objeto, TUBE); break;
		case GLUT_KEY_F10: objeto = changeObject(objeto, SPHERE); break;
		case GLUT_KEY_F11: objeto = changeObject(objeto, WATT); break;
	}
	glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void) {
	// se inicalizan la ventana y los planos de corte
	Window_width=5;
	Window_height=5;
	Front_plane=10;
	Back_plane=1000;

	// se inicia la posicion del observador, en el eje z
	Observer_distance=2*Front_plane;
	Observer_angle_x=0;
	Observer_angle_y=0;

	// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	glClearColor(1,1,1,1);

	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);
	//
	change_projection();
	//
	glViewport(0,0,UI_window_width,UI_window_height);
}

void initialize2(void) {

	glClearColor(1,1,1,1);

}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv) {
	// se llama a la inicialización de glut
	glutInit(&argc, argv);

	// se indica las caracteristicas que se desean para la visualización con OpenGL
	// Las posibilidades son:
	// GLUT_SIMPLE -> memoria de imagen simple
	// GLUT_DOUBLE -> memoria de imagen doble
	// GLUT_INDEX -> memoria de imagen con color indizado
	// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
	// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
	// GLUT_DEPTH -> memoria de profundidad o z-bufer
	// GLUT_STENCIL -> memoria de estarcido
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// posicion de la esquina inferior izquierdad de la ventana
	glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

	// tamaño de la ventana (ancho y alto)
	glutInitWindowSize(UI_window_width,UI_window_height);

	// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
	// al bucle de eventos)
	window_1 = glutCreateWindow("Practica 3. Angel Gomez Martin");

	// asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw_scene);
	// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
	glutReshapeFunc(change_window_size);
	// asignación de la funcion llamada "tecla_normal" al evento correspondiente
	glutKeyboardFunc(normal_keys);
	// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_keys);
	// funcion de inicialización
	initialize();

	glutInitWindowSize(500,750);
	glutInitWindowPosition(950,50);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	window_2 = glutCreateWindow("Buttons");
	glutDisplayFunc(draw_scene_button);
	glutPassiveMotionFunc(botones.handle_motion);
	glutMouseFunc(botones.handle_mouse);
	//glutKeyboardFunc(normal_keys);
	//glutSpecialFunc(special_keys);
	initialize2();

	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}
