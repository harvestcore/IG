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
#include <utility>
#include "vertex.h"
#include "models.h"
#include "objects.h"
#include "manageView.h"
#include "types.h"
#include "3DObject.h"
#include "wattRegulator.h"
#include "button.h"
#include "fps.h"
#include "light.h"
#include "plank.h"

using namespace std;

Models modelos;
vector<ViewMode> modos = {NULL_,NULL_,NULL_,NULL_,NULL_,NULL_,NULL_};
TypeObject objeto = _NULL;
ViewMode current_mode = NULL_;

Texture foto("./texturas/google.jpg");
Plank tablero(10,20,6,4);
bool mostrarTablero = false;
bool mostrarimagen = false;

DrawMode drawmode;

ALLFIGURE cube_, tetraedro_, beethoven_, peon_, cilindro_, vaso_, vaso2_, cono_, tubo_, esfera_;
Watt watt_regulator;
bool drawWatt_ = false;

bool mas_material = false;
bool menos_material = false;
bool help_ = false;

Light luz, luz_inf;
bool luz_ = false;
bool luz_inf_ = false;

float alfa = 1, beta = 1;
float dist = 0.0;
float alfa2 = 1, beta2 = 1;

// Contador de FPS
FPScounter fps;
bool showFPS = false;

// Ventanas
int window_1, window_2;

bool sumar = false;
bool restar = false;

// tamaño de los ejes
const int AXIS_SIZE=15000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=900,UI_window_height=900;

//**************************************************************************
//	INICIALIZAR LUCES
//***************************************************************************
void initialize_ligths() {
    luz.setID(GL_LIGHT0);
    luz.setDirectional(true);
    luz.setAlpha(2.5);
    luz.setBeta(2.5);
    luz.setPosition(_vertex4f(0,0,40,1));
    luz.setAmbient(_vertex4f(0.2,0.2,0.2,1));
    luz.setDiffuse(_vertex4f(0.8,0.8,0.8,1));
    luz.setSpecular(_vertex4f(0.8,0.8,0.8,1));

    luz_inf.setID(GL_LIGHT1);
    luz_inf.setDirectional(true);
    luz_inf.setAlpha(2.5);
    luz_inf.setBeta(2.5);
    luz_inf.setPosition(_vertex4f(0,50,0,0));
    luz_inf.setAmbient(_vertex4f(0.2,0.2,0.2,1));
    luz_inf.setDiffuse(_vertex4f(0.8,0.8,0.8,1));
    luz_inf.setSpecular(_vertex4f(1,1,1,1));
}

void initialize_models() {
    cube_.createCube();
    cube_.calculateNormalTriangles();
    cube_.calculateNormalPoints();
    cube_.setMaterial(1);

    tetraedro_.createTetrahedron();
    tetraedro_.calculateNormalTriangles();
    tetraedro_.calculateNormalPoints();
    tetraedro_.setMaterial(1);

    beethoven_.readPly("./ply/beethoven.ply");
    beethoven_.calculateNormalTriangles();
    beethoven_.calculateNormalPoints();
    beethoven_.setMaterial(1);

    peon_.createPly_Revolution("./ply/peon.ply");
    peon_.calculateNormalTriangles();
    peon_.calculateNormalPoints();
    peon_.setMaterial(1);

    cilindro_.createCylinder(2.0, 4.0);
    cilindro_.calculateNormalTriangles();
    cilindro_.calculateNormalPoints();
    cilindro_.setMaterial(1);

    vaso_.createGlass(2.0, 1.0, 4.0);
    vaso_.calculateNormalTriangles();
    vaso_.calculateNormalPoints();
    vaso_.setMaterial(1);

    vaso2_.createGlass_Inverted(2.0, 1.0, 4.0);
    vaso2_.calculateNormalTriangles();
    vaso2_.calculateNormalPoints();
    vaso2_.setMaterial(1);

    cono_.createCone(2.0, 4.0);
    cono_.calculateNormalTriangles();
    cono_.calculateNormalPoints();
    cono_.setMaterial(1);

    tubo_.createTube(2.0, 4.0);
    tubo_.calculateNormalTriangles();
    tubo_.calculateNormalPoints();
    tubo_.setMaterial(1);

    esfera_.generateSphereProfile(2.0);
    esfera_.generateByRevolution('y', false);
    esfera_.calculateNormalTriangles();
    esfera_.calculateNormalPoints();
    esfera_.setMaterial(1);
}
//**************************************************************************
//	Entrada texto tablero
//**************************************************************************
pair<CoordenadasIMG, CoordenadasIMG> parsingCoord;

void initialize_parsingCoord() {
    parsingCoord.first.X_00 = 0;
    parsingCoord.first.Y_00 = 0;
    parsingCoord.first.X_01 = 0;
    parsingCoord.first.Y_01 = 1;
    parsingCoord.first.X_10 = 1;
    parsingCoord.first.Y_10 = 0;
    parsingCoord.first.X_11 = 1;
    parsingCoord.first.Y_11 = 1;
    parsingCoord.first.thicc = 0.5;

    parsingCoord.second.X_00 = 0;
    parsingCoord.second.Y_00 = 0;
    parsingCoord.second.X_01 = 0;
    parsingCoord.second.Y_01 = 1;
    parsingCoord.second.X_10 = 1;
    parsingCoord.second.Y_10 = 0;
    parsingCoord.second.X_11 = 1;
    parsingCoord.second.Y_11 = 1;
    parsingCoord.second.thicc = 0.5;
}

void readPlankCoords() {
    double anchoizq, anchoder, altoabajo, altoarriba;

    cout << endl << "~~Lectura coordenadas tablero~~" << endl;
    cout << "[Ancho],[Izq] -> ";
    cin >> anchoizq;
    cout << "[Ancho],[Der] -> ";
    cin >> anchoder;
    cout << "[Alto],[Abajo] -> ";
    cin >> altoabajo;
    cout << "[Alto],[Arriba] -> ";
    cin >> altoarriba;
    cout << endl;

    parsingCoord.first.X_00 = anchoizq*2;
    parsingCoord.first.Y_00 = altoabajo*2;
    parsingCoord.first.X_01 = anchoizq*2;
    parsingCoord.first.Y_01 = altoarriba;
    parsingCoord.first.X_10 = anchoder;
    parsingCoord.first.Y_10 = altoabajo*2;
    parsingCoord.first.X_11 = anchoder;
    parsingCoord.first.Y_11 = altoarriba;
    parsingCoord.first.thicc = 0.5;
}

void readTextureCoords() {
    double anchoizq, anchoder, altoabajo, altoarriba;

    cout << endl << "~~Lectura coordenadas textura~~" << endl;
    cout << "[Ancho],[Izq] -> ";
    cin >> anchoizq;
    cout << "[Ancho],[Der] -> ";
    cin >> anchoder;
    cout << "[Alto],[Abajo] -> ";
    cin >> altoabajo;
    cout << "[Alto],[Arriba] -> ";
    cin >> altoarriba;

    parsingCoord.second.X_00 = anchoizq;
    parsingCoord.second.Y_00 = altoabajo;
    parsingCoord.second.X_01 = anchoizq;
    parsingCoord.second.Y_01 = altoarriba;
    parsingCoord.second.X_10 = anchoder;
    parsingCoord.second.Y_10 = altoabajo;
    parsingCoord.second.X_11 = anchoder;
    parsingCoord.second.Y_11 = altoarriba;
    parsingCoord.second.thicc = 0.5;
}


//**************************************************************************
//	ClearWindow
//**************************************************************************
void clear_window() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//**************************************************************************

void change_projection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    //gluPerspective(60, ratio, 0.01, 100);
	// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
	//  Front_plane>0  Back_plane>PlanoDelantero)
    float aspect = GLfloat(glutGet(GLUT_WINDOW_WIDTH)) / GLfloat(glutGet(GLUT_WINDOW_HEIGHT));
    glFrustum(-Window_width*aspect, Window_width*aspect, -Window_height, Window_height, Front_plane, Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//**************************************************************************

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
//**************************************************************************
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
//**************************************************************************
int objectTomaterialID(TypeObject obj) {
    switch (obj) {
        case CUBE:
        return cube_.getMaterialID();
        case TETRAHEDRON:
        return tetraedro_.getMaterialID();
        case PLY_STATIC:
        return beethoven_.getMaterialID();
        case PLY_REVOLUTION:
        return peon_.getMaterialID();
        case CYLINDER:
        return cilindro_.getMaterialID();
        case GLASS:
        return vaso_.getMaterialID();
        case GLASS_INVERTED:
        return vaso2_.getMaterialID();
        case CONE:
        return cono_.getMaterialID();
        case TUBE:
        return tubo_.getMaterialID();
        case SPHERE:
        return esfera_.getMaterialID();
        default:
        return 0;
    }
}

string dts(double i){
	stringstream out;
	out << i;
	return out.str();
}

void printText(int x, int y, string text) {
    glRasterPos2f(x,y);

    for (int i=0; i<text.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
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
    glColor3f(0,0,0);

	if (objeto == WATT)
        printText(20, 30, "Vel: " + dts(watt_regulator.getSpeed()));

    printText(20, 50, "FPS: " + dts(fps.getFPS()));
    printText(20, 70, "Objeto: " + objectToString(objeto));
    printText(20, 90, "Modo: " + modotoString(current_mode));
    printText(20, 110, "Luz: " + booltostring(luz_));
    printText(20, 130, "Luz inf: " + booltostring(luz_inf_));
    printText(20, 150, "Spin: " + booltostring(watt_regulator.isSpinning()));

    if (current_mode == FLAT || current_mode == SMOOTH)
        printText(20, 170, "Material: " + materialIDtostring(objectTomaterialID(objeto)));
    else
        printText(20, 170, "Material: Off");

    printText(20, 190, "Tablero: " + booltostring(mostrarTablero));

    if (help_) {
        printText(20, 740, "Leer coordenadas: (Terminal)");
        printText(20, 760, "Acercar luz 1: (R)");
        printText(20, 780, "Alejar luz 1: (F)");
        printText(20, 800, "Mover luz 1: (WASD)");
        printText(20, 820, "Mover luz inf: (UHJK)");
        printText(20, 840, "Mover camara: (Arrows)");
        printText(20, 860, "Zoom+ : (AVPag)");
        printText(20, 880, "Zoom- : (REPag)");
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

}

//**************************************************************************
// Funcion que dibuja los objetos
//**************************************************************************
void draw_objects() {
	glPointSize(3);
	glLineWidth(1);

    if (!modelos.getModelsAreGenerated()) {
        modelos.initializeModels();
        modelos.setModelsAreGenerated(true);
    }

	if (sumar) {
		switch (objeto) {
            case PLY_REVOLUTION:
                peon_.moreSteps();
                peon_.generateByRevolution('y', false);
                peon_.calculateNormalTriangles();
                peon_.calculateNormalTriangles();
                break;
            case CYLINDER:
                cilindro_.moreSteps();
                cilindro_.generateByRevolution('y', false);
                cilindro_.calculateNormalTriangles();
                cilindro_.calculateNormalTriangles();
                break;
            case GLASS:
                vaso_.moreSteps();
                vaso_.generateByRevolution('y', false);
                vaso_.calculateNormalTriangles();
                vaso_.calculateNormalTriangles();
                break;
            case GLASS_INVERTED:
                vaso2_.moreSteps();
                vaso2_.generateByRevolution('y', false);
                vaso2_.calculateNormalTriangles();
                vaso2_.calculateNormalTriangles();
                break;
            case CONE:
                cono_.moreSteps();
                cono_.generateByRevolution('y', false);
                cono_.calculateNormalTriangles();
                cono_.calculateNormalTriangles();
                break;
            case TUBE:
                tubo_.moreSteps();
                tubo_.generateByRevolution('y', false);
                tubo_.calculateNormalTriangles();
                tubo_.calculateNormalTriangles();
                break;
            case SPHERE:
                esfera_.moreSteps();
                esfera_.generateSphereProfile(2.0);
                esfera_.generateByRevolution('y', false);
                esfera_.calculateNormalTriangles();
                esfera_.calculateNormalTriangles();
        }
		sumar = false;
	}

	if (restar) {
		switch (objeto) {
            case PLY_REVOLUTION:
                peon_.lessSteps();
                peon_.generateByRevolution('y', false);
                peon_.calculateNormalTriangles();
                peon_.calculateNormalTriangles();
                break;
            case CYLINDER:
                cilindro_.lessSteps();
                cilindro_.generateByRevolution('y', false);
                cilindro_.calculateNormalTriangles();
                cilindro_.calculateNormalTriangles();
                break;
            case GLASS:
                vaso_.lessSteps();
                vaso_.generateByRevolution('y', false);
                vaso_.calculateNormalTriangles();
                vaso_.calculateNormalTriangles();
                break;
            case GLASS_INVERTED:
                vaso2_.lessSteps();
                vaso2_.generateByRevolution('y', false);
                vaso2_.calculateNormalTriangles();
                vaso2_.calculateNormalTriangles();
                break;
            case CONE:
                cono_.lessSteps();
                cono_.generateByRevolution('y', false);
                cono_.calculateNormalTriangles();
                cono_.calculateNormalTriangles();
                break;
            case TUBE:
                tubo_.lessSteps();
                tubo_.generateSphereProfile(2.0);
                tubo_.generateByRevolution('y', false);
                tubo_.calculateNormalTriangles();
                tubo_.calculateNormalTriangles();
                break;
            case SPHERE:
                esfera_.lessSteps();
                esfera_.generateSphereProfile(2.0);
                esfera_.generateByRevolution('y', false);
                esfera_.calculateNormalTriangles();
                esfera_.calculateNormalTriangles();
        }
		restar = false;
	}

	if (watt_regulator.isSpinning()){
		watt_regulator.giro();
		glutPostRedisplay();
	}

    if (mas_material) {
        switch (objeto) {
            case CUBE:
                cube_.incrementMaterialID();
                break;
            case TETRAHEDRON:
                tetraedro_.incrementMaterialID();
                break;
            case PLY_STATIC:
                beethoven_.incrementMaterialID();
                break;
            case PLY_REVOLUTION:
                peon_.incrementMaterialID();
                break;
            case CYLINDER:
                cilindro_.incrementMaterialID();
                break;
            case GLASS:
                vaso_.incrementMaterialID();
                break;
            case GLASS_INVERTED:
                vaso2_.incrementMaterialID();
                break;
            case CONE:
                cono_.incrementMaterialID();
                break;
            case TUBE:
                tubo_.incrementMaterialID();
                break;
            case SPHERE:
                esfera_.incrementMaterialID();
                break;
        }
        mas_material = false;
    }

    if (menos_material) {
        switch (objeto) {
            case CUBE:
                cube_.decrementMaterialID();
                break;
            case TETRAHEDRON:
                tetraedro_.decrementMaterialID();
                break;
            case PLY_STATIC:
                beethoven_.decrementMaterialID();
                break;
            case PLY_REVOLUTION:
                peon_.decrementMaterialID();
                break;
            case CYLINDER:
                cilindro_.decrementMaterialID();
                break;
            case GLASS:
                vaso_.decrementMaterialID();
                break;
            case GLASS_INVERTED:
                vaso2_.decrementMaterialID();
                break;
            case CONE:
                cono_.decrementMaterialID();
                break;
            case TUBE:
                tubo_.decrementMaterialID();
                break;
            case SPHERE:
                esfera_.decrementMaterialID();
                break;
        }
        menos_material = false;
    }

    if (mostrarTablero) {
        switch (current_mode) {
            case MESH:
                tablero.generatePlank(MESH, parsingCoord.first);
                if (mostrarimagen)
                    foto.drawTexture(tablero.getCoordenadas(), parsingCoord.second);
                glutPostRedisplay();
                break;

            case SOLID:
                tablero.generatePlank(SOLID, parsingCoord.first);
                if (mostrarimagen)
                    foto.drawTexture(tablero.getCoordenadas(), parsingCoord.second);
                glutPostRedisplay();
                break;

            case CHESS:
                tablero.generatePlank(CHESS, parsingCoord.first);
                if (mostrarimagen)
                    foto.drawTexture(tablero.getCoordenadas(), parsingCoord.second);
                glutPostRedisplay();
                break;

            case FLAT:
                tablero.generatePlank(FLAT, parsingCoord.first);
                if (mostrarimagen)
                    foto.drawTexture(tablero.getCoordenadas(), parsingCoord.second);
                glutPostRedisplay();
                break;

            case SMOOTH:
                tablero.generatePlank(SMOOTH, parsingCoord.first);
                if (mostrarimagen)
                    foto.drawTexture(tablero.getCoordenadas(), parsingCoord.second);
                glutPostRedisplay();
                break;
        }
    }

    luz.setAlpha(alfa);
    luz.setBeta(beta);
    luz.setPosition(_vertex4f(0,0,40 + dist,1));

    luz_inf.setAlpha(alfa2);
    luz_inf.setBeta(beta2);

    if (luz_)
        luz.enable();
    else
        luz.disable();

    if (luz_inf_)
        luz_inf.enable();
    else
        luz_inf.disable();

    if (drawWatt_) {
        if (drawmode.mesh)
            watt_regulator.draw(MESH);
        if (drawmode.edges)
            watt_regulator.draw(EDGES);
        if (drawmode.solid)
            watt_regulator.draw(SOLID);
        if (drawmode.chess)
            watt_regulator.draw(CHESS);
        if (drawmode.flat)
            watt_regulator.draw(FLAT);
        if (drawmode.smooth)
            watt_regulator.draw(SMOOTH);
    }


    switch (objeto) {
        case CUBE:
            if (drawmode.mesh)
                cube_.drawMesh();
            if (drawmode.edges)
                cube_.drawEdges();
            if (drawmode.solid)
                cube_.drawSolid();
            if (drawmode.chess)
                cube_.drawChess();
            if (drawmode.flat)
                cube_.drawFlatSmoothing();
            if (drawmode.smooth)
                cube_.drawGouraudSmoothing();
            break;
        case TETRAHEDRON:
            if (drawmode.mesh)
                tetraedro_.drawMesh();
            if (drawmode.edges)
                tetraedro_.drawEdges();
            if (drawmode.solid)
                tetraedro_.drawSolid();
            if (drawmode.chess)
                tetraedro_.drawChess();
            if (drawmode.flat)
                tetraedro_.drawFlatSmoothing();
            if (drawmode.smooth)
                tetraedro_.drawGouraudSmoothing();
            break;
        case PLY_STATIC:
            if (drawmode.mesh)
                beethoven_.drawMesh();
            if (drawmode.edges)
                beethoven_.drawEdges();
            if (drawmode.solid)
                beethoven_.drawSolid();
            if (drawmode.chess)
                beethoven_.drawChess();
            if (drawmode.flat)
                beethoven_.drawFlatSmoothing();
            if (drawmode.smooth)
                beethoven_.drawGouraudSmoothing();
            break;
        case PLY_REVOLUTION:
            if (drawmode.mesh)
                peon_.drawMesh();
            if (drawmode.edges)
                peon_.drawEdges();
            if (drawmode.solid)
                peon_.drawSolid();
            if (drawmode.chess)
                peon_.drawChess();
            if (drawmode.flat)
                peon_.drawFlatSmoothing();
            if (drawmode.smooth)
                peon_.drawGouraudSmoothing();
            break;
        case CYLINDER:
            if (drawmode.mesh)
                cilindro_.drawMesh();
            if (drawmode.edges)
                cilindro_.drawEdges();
            if (drawmode.solid)
                cilindro_.drawSolid();
            if (drawmode.chess)
                cilindro_.drawChess();
            if (drawmode.flat)
                cilindro_.drawFlatSmoothing();
            if (drawmode.smooth)
                cilindro_.drawGouraudSmoothing();
            break;
        case GLASS:
            if (drawmode.mesh)
                vaso_.drawMesh();
            if (drawmode.edges)
                vaso_.drawEdges();
            if (drawmode.solid)
                vaso_.drawSolid();
            if (drawmode.chess)
                vaso_.drawChess();
            if (drawmode.flat)
                vaso_.drawFlatSmoothing();
            if (drawmode.smooth)
                vaso_.drawGouraudSmoothing();
            break;
        case GLASS_INVERTED:
            if (drawmode.mesh)
                vaso2_.drawMesh();
            if (drawmode.edges)
                vaso2_.drawEdges();
            if (drawmode.solid)
                vaso2_.drawSolid();
            if (drawmode.chess)
                vaso2_.drawChess();
            if (drawmode.flat)
                vaso2_.drawFlatSmoothing();
            if (drawmode.smooth)
                vaso2_.drawGouraudSmoothing();
            break;
        case CONE:
            if (drawmode.mesh)
                cono_.drawMesh();
            if (drawmode.edges)
                cono_.drawEdges();
            if (drawmode.solid)
                cono_.drawSolid();
            if (drawmode.chess)
                cono_.drawChess();
            if (drawmode.flat)
                cono_.drawFlatSmoothing();
            if (drawmode.smooth)
                cono_.drawGouraudSmoothing();
            break;
        case TUBE:
            if (drawmode.mesh)
                tubo_.drawMesh();
            if (drawmode.edges)
                tubo_.drawEdges();
            if (drawmode.solid)
                tubo_.drawSolid();
            if (drawmode.chess)
                tubo_.drawChess();
            if (drawmode.flat)
                tubo_.drawFlatSmoothing();
            if (drawmode.smooth)
                tubo_.drawGouraudSmoothing();
            break;
        case SPHERE:
            if (drawmode.mesh)
                esfera_.drawMesh();
            if (drawmode.edges)
                esfera_.drawEdges();
            if (drawmode.solid)
                esfera_.drawSolid();
            if (drawmode.chess)
                esfera_.drawChess();
            if (drawmode.flat)
                esfera_.drawFlatSmoothing();
            if (drawmode.smooth)
                esfera_.drawGouraudSmoothing();
            break;
    }

    fps.incrementFrames();
	drawHUD();
}


//**************************************************************************
// DRAW ESCENA
//**************************************************************************
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
//**************************************************************************
bool buttons_generated = false;
Button mesh, lines, solid, chess, masDiv, menosDiv, masVel, menosVel, spin;
Button cubo, tetraedro, ply_estatico, ply_revolucion, cilindro, vaso, vaso_invertido, cono, tubo, esfera, watt;
Button flecha_up, flecha_down, flecha_left, flecha_right;
Button zoom_in, zoom_out;
Button salir;

Button luz1, luz2;
Button flat, smooth;
Button tab, masCubo, menosCubo, masAncho, menosAncho, masAlto, menosAlto;
Button masMaterial, menosMaterial;

Button leerCoordenadas, leerCoordenadasTextura;
Button help;

Button mostrar_imagen;

void exit_program() {
	exit(0);
}

void toggle_mostrarimagen() {
	mostrarimagen = !mostrarimagen;
}

void toggle_leerCoordenadas() {
    readPlankCoords();
    glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_leerCoordenadasTextura() {
    readTextureCoords();
    glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_help() {
    help_ = !help_;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_mesh() {
    current_mode = currentMode(current_mode, MESH);
	drawmode.mesh = !drawmode.mesh;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_edges() {
    current_mode = currentMode(current_mode, EDGES);
	drawmode.edges = !drawmode.edges;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_solid() {
    current_mode = currentMode(current_mode, SOLID);
	drawmode.solid = !drawmode.solid;
    drawmode.chess = false;
    drawmode.flat = false;
    drawmode.smooth = false;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_chess() {
    current_mode = currentMode(current_mode, CHESS);
	drawmode.chess = !drawmode.chess;
    drawmode.solid = false;
    drawmode.flat = false;
    drawmode.smooth = false;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_flat() {
    current_mode = currentMode(current_mode, FLAT);
    drawmode.flat = !drawmode.flat;
    drawmode.chess = false;
    drawmode.solid = false;
    drawmode.smooth = false;
    glutSetWindow(window_1);
    draw_scene();
    glutSetWindow(window_2);
}

void toggle_smooth() {
    current_mode = currentMode(current_mode, SMOOTH);
    drawmode.smooth = !drawmode.smooth;
    drawmode.chess = false;
    drawmode.solid = false;
    drawmode.flat = false;
    glutSetWindow(window_1);
    draw_scene();
    glutSetWindow(window_2);
}

void toggle_masDiv() {
	sumar = true;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_menosDiv() {
	restar = true;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_masVel() {
	watt_regulator.aumentarVelocidad();
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_menosVel() {
	watt_regulator.decrementarVelocidad();
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_spin() {
	watt_regulator.toggleSpinning();
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_cube() {
    mostrarTablero = false;
    drawWatt_ = false;
	objeto = changeObject(objeto, CUBE);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_tetrahedron() {
    mostrarTablero = false;
    drawWatt_ = false;
	objeto = changeObject(objeto, TETRAHEDRON);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_ply_static() {
    mostrarTablero = false;
    drawWatt_ = false;
	objeto = changeObject(objeto, PLY_STATIC);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_ply_revolution() {
    mostrarTablero = false;
    drawWatt_ = false;
	objeto = changeObject(objeto, PLY_REVOLUTION);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_cylinder() {
    mostrarTablero = false;
    drawWatt_ = false;
	objeto = changeObject(objeto, CYLINDER);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_glass() {
    mostrarTablero = false;
    drawWatt_ = false;
	objeto = changeObject(objeto, GLASS);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_glass_inverted() {
    mostrarTablero = false;
    drawWatt_ = false;
	objeto = changeObject(objeto, GLASS_INVERTED);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_cone() {
    mostrarTablero = false;
    drawWatt_ = false;
	objeto = changeObject(objeto, CONE);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_tube() {
    mostrarTablero = false;
    drawWatt_ = false;
	objeto = changeObject(objeto, TUBE);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_sphere() {
    mostrarTablero = false;
    drawWatt_ = false;
	objeto = changeObject(objeto, SPHERE);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_watt() {
    drawWatt_ = !drawWatt_;
    mostrarTablero = false;
    objeto = changeObject(objeto, WATT);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}


void toggle_up() {
	Observer_angle_x--;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_down() {
	Observer_angle_x++;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_left() {
	Observer_angle_y--;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_right() {
	Observer_angle_y++;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_zoom_in() {
	Observer_distance/=1.2;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_zoom_out() {
	Observer_distance*=1.2;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_luz() {
    luz_ = !luz_;
    glutSetWindow(window_1);
    draw_scene();
    glutSetWindow(window_2);
}

void toggle_luz1() {
    luz_inf_ = !luz_inf_;
    glutSetWindow(window_1);
    draw_scene();
    glutSetWindow(window_2);
}

void toggle_tablero() {
    mostrarTablero = !mostrarTablero;
    drawmode.allFalse();
    objeto = changeObject(objeto, _NULL);
    glutSetWindow(window_1);
    draw_scene();
    glutSetWindow(window_2);
}

void toggle_masCubo() {
    tablero.incrementSide();
    glutSetWindow(window_1);
    draw_scene();
    glutSetWindow(window_2);
}

void toggle_menosCubo() {
    if (tablero.getCubesx() > 1)
        tablero.decrementSide();
    glutSetWindow(window_1);
    draw_scene();
    glutSetWindow(window_2);
}

void toggle_masAncho() {
    tablero.incrementWidth();
    glutSetWindow(window_1);
    draw_scene();
    glutSetWindow(window_2);
}

void toggle_menosAncho() {
    tablero.decrementWidth();
    glutSetWindow(window_1);
    draw_scene();
    glutSetWindow(window_2);
}

void toggle_masAlto() {
    tablero.incrementHeight();
    glutSetWindow(window_1);
    draw_scene();
    glutSetWindow(window_2);
}

void toggle_menosAlto() {
    tablero.decrementHeight();
    glutSetWindow(window_1);
    draw_scene();
    glutSetWindow(window_2);
}

void toggle_masMaterial() {
    mas_material = true;
    glutSetWindow(window_1);
    glutPostRedisplay();
    draw_scene();
    glutSetWindow(window_2);
}

void toggle_menosMaterial() {
    menos_material = true;
    glutSetWindow(window_1);
    glutPostRedisplay();
    draw_scene();
    glutSetWindow(window_2);
}

void draw_buttons() {
	salir.display();
    help.display();
    leerCoordenadas.display();
    leerCoordenadasTextura.display();

	mesh.display();
	lines.display();
	solid.display();
	chess.display();
	masDiv.display();
	menosDiv.display();
	masVel.display();
	menosVel.display();
	spin.display();

	cubo.display();
	tetraedro.display();
	ply_estatico.display();
	ply_revolucion.display();
	cilindro.display();
	vaso.display();
	vaso_invertido.display();
	cono.display();
	tubo.display();
	esfera.display();
	watt.display();

	flecha_up.display();
	flecha_down.display();
	flecha_left.display();
	flecha_right.display();

	zoom_in.display();
	zoom_out.display();

    luz1.display();
    luz2.display();
    flat.display();
    smooth.display();
    masMaterial.display();
    menosMaterial.display();

    tab.display();
    masCubo.display();
    menosCubo.display();
    masAncho.display();
    menosAncho.display();
    masAlto.display();
    menosAlto.display();

    mostrar_imagen.display();
}

void handle_motion(int x, int y) {
	salir.handlemotion(x,y);
    help.handlemotion(x,y);
    leerCoordenadas.handlemotion(x,y);
    leerCoordenadasTextura.handlemotion(x,y);
    mostrar_imagen.handlemotion(x,y);

	mesh.handlemotion(x,y);
	lines.handlemotion(x,y);
	solid.handlemotion(x,y);
	chess.handlemotion(x,y);
	masDiv.handlemotion(x,y);
	menosDiv.handlemotion(x,y);
	masVel.handlemotion(x,y);
	menosVel.handlemotion(x,y);
	spin.handlemotion(x,y);

	cubo.handlemotion(x,y);
	tetraedro.handlemotion(x,y);
	ply_estatico.handlemotion(x,y);
	ply_revolucion.handlemotion(x,y);
	cilindro.handlemotion(x,y);
	vaso.handlemotion(x,y);
	vaso_invertido.handlemotion(x,y);
	cono.handlemotion(x,y);
	tubo.handlemotion(x,y);
	esfera.handlemotion(x,y);
	watt.handlemotion(x,y);

	flecha_up.handlemotion(x,y);
	flecha_down.handlemotion(x,y);
	flecha_left.handlemotion(x,y);
	flecha_right.handlemotion(x,y);

	zoom_in.handlemotion(x,y);
	zoom_out.handlemotion(x,y);

    luz1.handlemotion(x,y);
    luz2.handlemotion(x,y);
    flat.handlemotion(x,y);
    smooth.handlemotion(x,y);
    masMaterial.handlemotion(x,y);
    menosMaterial.handlemotion(x,y);

    tab.handlemotion(x,y);
    masCubo.handlemotion(x,y);
    menosCubo.handlemotion(x,y);
    masAncho.handlemotion(x,y);
    menosAncho.handlemotion(x,y);
    masAlto.handlemotion(x,y);
    menosAlto.handlemotion(x,y);
}

void handle_mouse(int button, int state, int x, int y) {
	salir.handlemouse(button,state,x,y);
    help.handlemouse(button,state,x,y);
    leerCoordenadas.handlemouse(button, state, x, y);
    leerCoordenadasTextura.handlemouse(button, state, x, y);
    mostrar_imagen.handlemouse(button,state,x,y);

	mesh.handlemouse(button,state,x,y);
	lines.handlemouse(button,state,x,y);
	solid.handlemouse(button,state,x,y);
	chess.handlemouse(button,state,x,y);
	masDiv.handlemouse(button,state,x,y);
	menosDiv.handlemouse(button,state,x,y);
	masVel.handlemouse(button,state,x,y);
	menosVel.handlemouse(button,state,x,y);
	spin.handlemouse(button,state,x,y);

	cubo.handlemouse(button,state,x,y);
	tetraedro.handlemouse(button,state,x,y);
	ply_estatico.handlemouse(button,state,x,y);
	ply_revolucion.handlemouse(button,state,x,y);
	cilindro.handlemouse(button,state,x,y);
	vaso.handlemouse(button,state,x,y);
	vaso_invertido.handlemouse(button,state,x,y);
	cono.handlemouse(button,state,x,y);
	tubo.handlemouse(button,state,x,y);
	esfera.handlemouse(button,state,x,y);
	watt.handlemouse(button,state,x,y);

	flecha_up.handlemouse(button,state,x,y);
	flecha_down.handlemouse(button,state,x,y);
	flecha_left.handlemouse(button,state,x,y);
	flecha_right.handlemouse(button,state,x,y);

	zoom_in.handlemouse(button,state,x,y);
	zoom_out.handlemouse(button,state,x,y);

    luz1.handlemouse(button,state,x,y);
    luz2.handlemouse(button,state,x,y);
    flat.handlemouse(button,state,x,y);
    smooth.handlemouse(button,state,x,y);
    masMaterial.handlemouse(button,state,x,y);
    menosMaterial.handlemouse(button,state,x,y);

    tab.handlemouse(button,state,x,y);
    masCubo.handlemouse(button,state,x,y);
    menosCubo.handlemouse(button,state,x,y);
    masAncho.handlemouse(button,state,x,y);
    menosAncho.handlemouse(button,state,x,y);
    masAlto.handlemouse(button,state,x,y);
    menosAlto.handlemouse(button,state,x,y);
}

void generate_buttons() {
    salir.setpos(0.55,-0.95);
    salir.setsize(0.4,0.2);
    salir.setlabel("Salir");
    salir.setaction(exit_program);
    salir.setactive(true);

    help.setpos(0.55,-0.7);
    help.setsize(0.4,0.2);
    help.setlabel("Help");
    help.setaction(toggle_help);
    help.setactive(true);

    leerCoordenadas.setpos(0.4,-0.25);
    leerCoordenadas.setsize(0.4,0.15);
    leerCoordenadas.setlabel("LeerTab");
    leerCoordenadas.setaction(toggle_leerCoordenadas);
    leerCoordenadas.setactive(true);

    leerCoordenadasTextura.setpos(0.4,-0.4);
    leerCoordenadasTextura.setsize(0.4,0.15);
    leerCoordenadasTextura.setlabel("LeerTex");
    leerCoordenadasTextura.setaction(toggle_leerCoordenadasTextura);
    leerCoordenadasTextura.setactive(true);

    mesh.setpos(-0.5,0.8);
    mesh.setsize(0.4,0.15);
    mesh.setlabel("Puntos");
    mesh.setaction(toggle_mesh);
    mesh.setactive(true);

    lines.setpos(-0.5,0.65);
    lines.setsize(0.4,0.15);
    lines.setlabel("Lineas");
    lines.setaction(toggle_edges);
    lines.setactive(true);

    solid.setpos(-0.5,0.5);
    solid.setsize(0.4,0.15);
    solid.setlabel("Solido");
    solid.setaction(toggle_solid);
    solid.setactive(true);

    chess.setpos(-0.5,0.35);
    chess.setsize(0.4,0.15);
    chess.setlabel("Ajedrez");
    chess.setaction(toggle_chess);
    chess.setactive(true);

    masDiv.setpos(-0.5,0.2);
    masDiv.setsize(0.4,0.15);
    masDiv.setlabel("++Div");
    masDiv.setaction(toggle_masDiv);
    masDiv.setactive(true);

    menosDiv.setpos(-0.5,0.05);
    menosDiv.setsize(0.4,0.15);
    menosDiv.setlabel("--Div");
    menosDiv.setaction(toggle_menosDiv);
    menosDiv.setactive(true);

    masVel.setpos(-0.5,-0.1);
    masVel.setsize(0.4,0.15);
    masVel.setlabel("++Vel");
    masVel.setaction(toggle_masVel);
    masVel.setactive(true);

    menosVel.setpos(-0.5,-0.25);
    menosVel.setsize(0.4,0.15);
    menosVel.setlabel("--Vel");
    menosVel.setaction(toggle_menosVel);
    menosVel.setactive(true);

    spin.setpos(-0.5,-0.4);
    spin.setsize(0.4,0.15);
    spin.setlabel("Spin");
    spin.setaction(toggle_spin);
    spin.setactive(true);

    zoom_in.setpos(0.1,-1);
    zoom_in.setsize(0.25,0.15);
    zoom_in.setlabel("++Z");
    zoom_in.setaction(toggle_zoom_in);
    zoom_in.setactive(true);

    zoom_out.setpos(-0.35,-1);
    zoom_out.setsize(0.25,0.15);
    zoom_out.setlabel("--Z");
    zoom_out.setaction(toggle_zoom_out);
    zoom_out.setactive(true);

    flecha_up.setpos(-0.1,-0.75);
    flecha_up.setsize(0.2,0.15);
    flecha_up.setlabel("^");
    flecha_up.setaction(toggle_up);
    flecha_up.setactive(true);

    flecha_down.setpos(-0.1,-0.90);
    flecha_down.setsize(0.2,0.15);
    flecha_down.setlabel("v");
    flecha_down.setaction(toggle_down);
    flecha_down.setactive(true);

    flecha_left.setpos(-0.3,-0.825);
    flecha_left.setsize(0.2,0.15);
    flecha_left.setlabel("<");
    flecha_left.setaction(toggle_left);
    flecha_left.setactive(true);

    flecha_right.setpos(0.1,-0.825);
    flecha_right.setsize(0.2,0.15);
    flecha_right.setlabel(">");
    flecha_right.setaction(toggle_right);
    flecha_right.setactive(true);

    cubo.setpos(-0.95,0.80);
    cubo.setsize(0.4,0.15);
    cubo.setlabel("Cubo");
    cubo.setaction(toggle_cube);
    cubo.setactive(true);

    tetraedro.setpos(-0.95,0.65);
    tetraedro.setsize(0.4,0.15);
    tetraedro.setlabel("Tetraedro");
    tetraedro.setaction(toggle_tetrahedron);
    tetraedro.setactive(true);

    ply_estatico.setpos(-0.95,0.5);
    ply_estatico.setsize(0.4,0.15);
    ply_estatico.setlabel("Ply Est");
    ply_estatico.setaction(toggle_ply_static);
    ply_estatico.setactive(true);

    ply_revolucion.setpos(-0.95,0.35);
    ply_revolucion.setsize(0.4,0.15);
    ply_revolucion.setlabel("Ply Rev");
    ply_revolucion.setaction(toggle_ply_revolution);
    ply_revolucion.setactive(true);

    cilindro.setpos(-0.95,0.2);
    cilindro.setsize(0.4,0.15);
    cilindro.setlabel("Cilindro");
    cilindro.setaction(toggle_cylinder);
    cilindro.setactive(true);

    vaso.setpos(-0.95,0.05);
    vaso.setsize(0.4,0.15);
    vaso.setlabel("Vaso");
    vaso.setaction(toggle_glass);
    vaso.setactive(true);

    vaso_invertido.setpos(-0.95,-0.1);
    vaso_invertido.setsize(0.4,0.15);
    vaso_invertido.setlabel("VasoInv");
    vaso_invertido.setaction(toggle_glass_inverted);
    vaso_invertido.setactive(true);

    cono.setpos(-0.95,-0.25);
    cono.setsize(0.4,0.15);
    cono.setlabel("Cono");
    cono.setaction(toggle_cone);
    cono.setactive(true);

    tubo.setpos(-0.95,-0.4);
    tubo.setsize(0.4,0.15);
    tubo.setlabel("Tubo");
    tubo.setaction(toggle_tube);
    tubo.setactive(true);

    esfera.setpos(-0.95,-0.55);
    esfera.setsize(0.4,0.15);
    esfera.setlabel("Esfera");
    esfera.setaction(toggle_sphere);
    esfera.setactive(true);

    watt.setpos(-0.95,-0.7);
    watt.setsize(0.4,0.15);
    watt.setlabel("Watt");
    watt.setaction(toggle_watt);
    watt.setactive(true);

    /////////////////////////

    luz1.setpos(-0.05,0.8);
    luz1.setsize(0.4,0.15);
    luz1.setlabel("Luz");
    luz1.setaction(toggle_luz);
    luz1.setactive(true);

    luz2.setpos(-0.05,0.65);
    luz2.setsize(0.4,0.15);
    luz2.setlabel("Luz Inf");
    luz2.setaction(toggle_luz1);
    luz2.setactive(true);

    flat.setpos(-0.05,0.5);
    flat.setsize(0.4,0.15);
    flat.setlabel("Flat");
    flat.setaction(toggle_flat);
    flat.setactive(true);

    smooth.setpos(-0.05,0.35);
    smooth.setsize(0.4,0.15);
    smooth.setlabel("Smooth");
    smooth.setaction(toggle_smooth);
    smooth.setactive(true);

    masMaterial.setpos(-0.05,0.2);
    masMaterial.setsize(0.4,0.15);
    masMaterial.setlabel("++Mat");
    masMaterial.setaction(toggle_masMaterial);
    masMaterial.setactive(true);

    menosMaterial.setpos(-0.05,0.05);
    menosMaterial.setsize(0.4,0.15);
    menosMaterial.setlabel("--Mat");
    menosMaterial.setaction(toggle_menosMaterial);
    menosMaterial.setactive(true);

    mostrar_imagen.setpos(-0.05,-0.1);
    mostrar_imagen.setsize(0.4,0.15);
    mostrar_imagen.setlabel("Img");
    mostrar_imagen.setaction(toggle_mostrarimagen);
    mostrar_imagen.setactive(true);

    tab.setpos(0.4,0.8);
    tab.setsize(0.4,0.15);
    tab.setlabel("Tablero");
    tab.setaction(toggle_tablero);
    tab.setactive(true);

    masCubo.setpos(0.4,0.65);
    masCubo.setsize(0.4,0.15);
    masCubo.setlabel("++Cube");
    masCubo.setaction(toggle_masCubo);
    masCubo.setactive(false);

    menosCubo.setpos(0.4,0.5);
    menosCubo.setsize(0.4,0.15);
    menosCubo.setlabel("--Cube");
    menosCubo.setaction(toggle_menosCubo);
    menosCubo.setactive(false);

    masAncho.setpos(0.4,0.35);
    masAncho.setsize(0.4,0.15);
    masAncho.setlabel("++W");
    masAncho.setaction(toggle_masAncho);
    masAncho.setactive(true);

    menosAncho.setpos(0.4,0.2);
    menosAncho.setsize(0.4,0.15);
    menosAncho.setlabel("--W");
    menosAncho.setaction(toggle_menosAncho);
    menosAncho.setactive(true);

    masAlto.setpos(0.4,0.05);
    masAlto.setsize(0.4,0.15);
    masAlto.setlabel("++H");
    masAlto.setaction(toggle_masAlto);
    masAlto.setactive(true);

    menosAlto.setpos(0.4,-0.1);
    menosAlto.setsize(0.4,0.15);
    menosAlto.setlabel("--H");
    menosAlto.setaction(toggle_menosAlto);
    menosAlto.setactive(true);
}

void draw_scene_button(void) {
	clear_window();
	if (!buttons_generated) {
        generate_buttons();
        buttons_generated = true;
	}

	draw_buttons();
	glutSwapBuffers();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************
void change_window_size(GLsizei width, GLsizei height) {
	change_projection();
	glViewport(0, 0, width,height);
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
/*
		case 'P': modos = changeMode(modos, MESH, 0); break;
		case 'L': modos = changeMode(modos, EDGES, 1); break;
		case 'F': modos = changeMode(modos, SOLID, 2); break;
		case 'C': modos = changeMode(modos, CHESS, 3); break;
        case '2': drawflat = !drawflat; drawsmooth = false; modos = changeMode(modos, NULL_, 6); break;
        case '3': drawsmooth = !drawsmooth; drawflat = false; modos = changeMode(modos, NULL_, 6); break;
		case 'T': restar = true; break;
        case 'Y': sumar = true; break;
        case 'A': watt_regulator.toggleSpinning(); break;
        case 'G': luz_ = !luz_; break;
        case 'H': luz1_ = !luz1_; break;
        case 'B': tablero.incrementSide(); break;
        case 'N': tablero.decrementSide(); break;
        case 'J': tablero.incrementWidth(); break;
        case 'K': tablero.decrementWidth(); break;
        case 'S': tablero.incrementHeight(); break;
        case 'D': tablero.decrementHeight(); break;
        case '1': mostrarTablero = !mostrarTablero; break;
		case 'X': watt_regulator.aumentarVelocidad(); break;
		case 'Z': watt_regulator.decrementarVelocidad(); break;
*/

        case 'A': alfa -= 1; break;
        case 'D': alfa += 1; break;
        case 'W': beta -= 1; break;
        case 'S': beta += 1; break;

        case 'H': alfa2 -= 1; break;
        case 'K': alfa2 += 1; break;
        case 'U': beta2 -= 1; break;
        case 'J': beta2 += 1; break;

        case 'R': dist -= 1.0; break;
        case 'F': dist += 1.0; break;
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

    /*
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
    */
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
	Front_plane=5;
	Back_plane=10000;

	// se inicia la posicion del observador, en el eje z
	Observer_distance=2*Front_plane;
	Observer_angle_x=0;
	Observer_angle_y=0;

    initialize_ligths();
    initialize_models();
    initialize_parsingCoord();

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
	window_1 = glutCreateWindow("Practica 4. Angel Gomez Martin");

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
	glutPassiveMotionFunc(handle_motion);
	glutMouseFunc(handle_mouse);
	//glutKeyboardFunc(normal_keys);
	//glutSpecialFunc(special_keys);
	initialize2();

	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}
