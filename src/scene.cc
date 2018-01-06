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
#include "camera.h"

using namespace std;

vector<bool> selectItems(9, false);
bool pickItem = false;

TypeObject objeto = _NULL;
ViewMode current_mode = NULL_;

Texture foto("./texturas/google.jpg");
Plank tablero(10,20,6,4);
bool mostrarTablero = false;
bool mostrarimagen = false;

bool modoObjetos = false;
bool modoSeleccion = false;

DrawMode drawmode;

vector<ALLFIGURE* > vobjects;
bool addobject = false;
bool deleteobject = false;

ALLFIGURE* selected;
ALLFIGURE* actual_;

ALLFIGURE* cube_;
ALLFIGURE* tetraedro_;
ALLFIGURE* beethoven_;
ALLFIGURE* peon_;
ALLFIGURE* cilindro_;
ALLFIGURE* vaso_;
ALLFIGURE* vaso2_;
ALLFIGURE* cono_;
ALLFIGURE* tubo_;
ALLFIGURE* esfera_;

Watt watt_regulator;
bool drawWatt_ = false;

bool mas_material = false;
bool menos_material = false;
bool help_ = false;

Light luz, luz_inf;
bool luz_ = false;
bool luz_inf_ = false;

float alfa = 1, beta_ = 1;
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
    actual_ = nullptr;

    cube_ = new ALLFIGURE();
    cube_->createCube();
    cube_->calculateNormalTriangles();
    cube_->calculateNormalPoints();

    tetraedro_ = new ALLFIGURE();
    tetraedro_->createTetrahedron();
    tetraedro_->calculateNormalTriangles();
    tetraedro_->calculateNormalPoints();

    beethoven_ = new ALLFIGURE();
    beethoven_->readPly("./ply/beethoven.ply");
    beethoven_->calculateNormalTriangles();
    beethoven_->calculateNormalPoints();

    peon_ = new ALLFIGURE();
    peon_->createPly_Revolution("./ply/peon.ply");
    peon_->calculateNormalTriangles();
    peon_->calculateNormalPoints();

    cilindro_ = new ALLFIGURE();
    cilindro_->createCylinder(2.0, 4.0);
    cilindro_->calculateNormalTriangles();
    cilindro_->calculateNormalPoints();

    vaso_ = new ALLFIGURE();
    vaso_->createGlass(2.0, 1.0, 4.0);
    vaso_->calculateNormalTriangles();
    vaso_->calculateNormalPoints();

    vaso2_ = new ALLFIGURE();
    vaso2_->createGlass_Inverted(2.0, 1.0, 4.0);
    vaso2_->calculateNormalTriangles();
    vaso2_->calculateNormalPoints();

    cono_ = new ALLFIGURE();
    cono_->createCone(2.0, 4.0);
    cono_->calculateNormalTriangles();
    cono_->calculateNormalPoints();

    tubo_ = new ALLFIGURE();
    tubo_->createTube(2.0, 4.0);
    tubo_->calculateNormalTriangles();
    tubo_->calculateNormalPoints();

    esfera_ = new ALLFIGURE();
    esfera_->generateSphereProfile(2.0);
    esfera_->generateByRevolution('y', false);
    esfera_->calculateNormalTriangles();
    esfera_->calculateNormalPoints();
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
// Cámaras
//**************************************************************************
Camera* escena_cam;
Camera* objeto_cam;
bool proyeccionParalela = false;
bool proyeccionPerspectiva = true;

void initialize_cameras() {
    escena_cam = new Camera();
    escena_cam->setType(PERSPECTIVE);
    escena_cam->setPlanes(Front_plane, Back_plane);
    escena_cam->setCoordinates(-Window_width, Window_width, -Window_height, Window_height);
    escena_cam->setObserverAngle({Observer_angle_x, Observer_angle_y});
    escena_cam->setObserverDistance(Observer_distance);

    objeto_cam = escena_cam;
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
    float aspect = GLfloat(glutGet(GLUT_WINDOW_WIDTH)) / GLfloat(glutGet(GLUT_WINDOW_HEIGHT));

    escena_cam->setCoordinates(-Window_width*aspect, Window_width*aspect, -Window_height, Window_height);
    escena_cam->project();
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//**************************************************************************

void change_observer() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    if (modoSeleccion)
        objeto_cam->move();
    else
        escena_cam->move();

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
    if (actual_ != nullptr)
        actual_->getMaterialID();
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
        printText(20, 170, "Material: " + materialIDtostring(actual_->getMaterialID()));
    else
        printText(20, 170, "Material: Off");

    printText(20, 190, "Tablero: " + booltostring(mostrarTablero));
    printText(20, 210, "Modo objetos: " + booltostring(modoObjetos));
    printText(20, 230, "Modo seleccion: " + booltostring(modoSeleccion));
    
    if (modoSeleccion)
        printText(20, 250, "Proyeccion: " + cameratypetostring(objeto_cam->getType()));
    if (modoObjetos)
        printText(20, 250, "Proyeccion: " + cameratypetostring(escena_cam->getType()));

    if (help_) {
        printText(20, 700, "Menu raton: (Right Click)");
        printText(20, 720, "(De)Seleccionar objeto: (Left Click)");
        printText(20, 740, "Leer coordenadas: (Terminal)");
        printText(20, 760, "Acercar luz 1: (R)");
        printText(20, 780, "Alejar luz 1: (F)");
        printText(20, 800, "Mover luz 1: (WASD/MouseWheelClick+Mouse)");
        printText(20, 820, "Mover luz inf: (UHJK)");
        printText(20, 840, "Mover camara: (Mouse/Arrows)");
        printText(20, 860, "Zoom+ : (AVPag/Wheel)");
        printText(20, 880, "Zoom- : (REPag/Wheel)");
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

}

void drawobjmode() {
    if (drawmode.mesh)
        actual_->drawMesh();
    if (drawmode.edges)
        actual_->drawEdges();
    if (drawmode.solid)
        actual_->drawSolid();
    if (drawmode.chess)
        actual_->drawChess();
    if (drawmode.flat)
        actual_->drawFlatSmoothing();
    if (drawmode.smooth)
        actual_->drawGouraudSmoothing();
}

//**************************************************************************
// Funcion que dibuja los objetos
//**************************************************************************
void draw_objects_names() {
    glMatrixMode(GL_MODELVIEW);
    glInitNames();
    glPushName(0);
    
    for(int i=0; i < 3; ++i) {
        for(int j=0; j < 3; ++j) {
            glPushMatrix();
            glLoadName(i*3+j+1);
            if(selectItems[i*3+j]) {
                glTranslatef(7*j-7,0,7*i-7);
                glScalef(0.5,0.5,0.5);
                if (actual_ != nullptr) {
                    actual_->calculateNormalTriangles();
                    actual_->calculateNormalPoints();
                    actual_->setColorSolid(255, 255, 0);
                    actual_->setMaterial(5);
                    actual_->setColorChess(255, 0, 255, 0, 0, 0);
                    drawobjmode();
                }
            } else {
                glTranslatef(7*j-7,0,7*i-7);
                glScalef(0.5,0.5,0.5);
                if (actual_ != nullptr) {
                    actual_->calculateNormalTriangles();
                    actual_->calculateNormalPoints();
                    actual_->setColorSolid(0, 128, 255);
                    actual_->setMaterial(1);
                    actual_->setColorChess(255, 0, 0, 0, 255, 0);
                    drawobjmode();
                }
            }
            glPopMatrix();
        }
    }
    
    glPopName();
}

void draw_objects() {
	glPointSize(3);
	glLineWidth(1);

    if (modoObjetos) {
        if (sumar) {
            if (actual_ != nullptr) {
                actual_->moreSteps();
                actual_->generateByRevolution('y', false);
                actual_->calculateNormalTriangles();
                actual_->calculateNormalTriangles();
                sumar = false;
            }
        }

        if (restar) {
            if (actual_ != nullptr) {
                actual_->lessSteps();
                actual_->generateByRevolution('y', false);
                actual_->calculateNormalTriangles();
                actual_->calculateNormalTriangles();
                restar = false;
            }
        }

        if (watt_regulator.isSpinning()){
            watt_regulator.giro();
            glutPostRedisplay();
        }

        if (mas_material) {
            if (actual_ != nullptr) {
                actual_->incrementMaterialID();
                mas_material = false;
            }
        }

        if (menos_material) {
            if (actual_ != nullptr) {
                actual_->decrementMaterialID();
                menos_material = false;
            }
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

        if (actual_ != nullptr) {
            drawobjmode();
        }
    }

    if (modoSeleccion) {
        /*
        for (unsigned int i = 0; i < vobjects.size(); ++i) {
            if (vobjects[i] != nullptr) {
                if (drawmode.mesh)
                    vobjects[i]->drawMesh();
                if (drawmode.edges)
                    vobjects[i]->drawEdges();
                if (drawmode.solid)
                    vobjects[i]->drawSolid();
                if (drawmode.chess)
                    vobjects[i]->drawChess();
                if (drawmode.flat)
                    vobjects[i]->drawFlatSmoothing();
                if (drawmode.smooth)
                    vobjects[i]->drawGouraudSmoothing();
            }
        }

        if (addobject) {
            ALLFIGURE* aux = actual_;
            aux->generateRandomColor();
            vobjects.push_back(aux);
            addobject = false;
            glutPostRedisplay();
        }

        if (deleteobject) {
            if (selected != nullptr) {
                GLint r = selected->getR();
                GLint g = selected->getG();
                GLint b = selected->getB();

                for (unsigned int i = 0; i < vobjects.size(); ++i) {
                    if (vobjects[i] != nullptr) {
                        if (vobjects[i]->compareColor(r, g, b)) {
                            vobjects[i] = nullptr;
                        } 
                    }
                }
            }
        
            deleteobject = false;
        }
        */

        draw_objects_names();
    }

    luz.setAlpha(alfa);
    luz.setBeta(beta_);
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

	glutPostRedisplay();
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

void draw_hidden_scene(void) {
	clear_window();
	change_observer();
	draw_axis();
	draw_objects();
	fps.calculateFPS();
}

void draw_scene_names(void) {
    if (modoSeleccion) {
        clear_window();
        change_observer();
        draw_axis();
        draw_objects_names();
        glutSwapBuffers();
        fps.calculateFPS();
    }
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

Button modo_objetos, modo_seleccion;
Button add_objeto, delete_objeto;

Button proyeccion;

void exit_program() {
	exit(0);
}

void toggle_proyeccion() {
    proyeccionParalela = !proyeccionParalela;
    proyeccionPerspectiva = !proyeccionPerspectiva;

    if (proyeccionParalela) {
        escena_cam->setType(ORTHOGONAL);
        objeto_cam->setType(ORTHOGONAL);
    }

    if (proyeccionPerspectiva) {
        escena_cam->setType(PERSPECTIVE);
        objeto_cam->setType(PERSPECTIVE);
    }

    glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_add_objeto() {
    addobject = true;
}

void toggle_delete_objeto() {
    deleteobject = true;
}

void toggle_modo_objetos() {
    modoObjetos = !modoObjetos;
    modoSeleccion = false;
    glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_modo_seleccion() {
    modoSeleccion = !modoSeleccion;
    modoObjetos = false;
    glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
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
	actual_ = changeObject(actual_, cube_);
    objeto = changeCurrentObject(objeto, CUBE);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_tetrahedron() {
    mostrarTablero = false;
    drawWatt_ = false;
	actual_ = changeObject(actual_, tetraedro_);
    objeto = changeCurrentObject(objeto, TETRAHEDRON);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_ply_static() {
    mostrarTablero = false;
    drawWatt_ = false;
	actual_ = changeObject(actual_, beethoven_);
    objeto = changeCurrentObject(objeto, PLY_STATIC);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_ply_revolution() {
    mostrarTablero = false;
    drawWatt_ = false;
	actual_ = changeObject(actual_, peon_);
    objeto = changeCurrentObject(objeto, PLY_REVOLUTION);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_cylinder() {
    mostrarTablero = false;
    drawWatt_ = false;
	actual_ = changeObject(actual_, cilindro_);
    objeto = changeCurrentObject(objeto, CYLINDER);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_glass() {
    mostrarTablero = false;
    drawWatt_ = false;
	actual_ = changeObject(actual_, vaso_);
    objeto = changeCurrentObject(objeto, GLASS);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_glass_inverted() {
    mostrarTablero = false;
    drawWatt_ = false;
	actual_ = changeObject(actual_, vaso2_);
    objeto = changeCurrentObject(objeto, GLASS_INVERTED);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_cone() {
    mostrarTablero = false;
    drawWatt_ = false;
	actual_ = changeObject(actual_, cono_);
    objeto = changeCurrentObject(objeto, CONE);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_tube() {
    mostrarTablero = false;
    drawWatt_ = false;
	actual_ = changeObject(actual_, tubo_);
    objeto = changeCurrentObject(objeto, TUBE);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_sphere() {
    mostrarTablero = false;
    drawWatt_ = false;
	actual_ = changeObject(actual_, esfera_);
    objeto = changeCurrentObject(objeto, SPHERE);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_watt() {
    drawWatt_ = !drawWatt_;
    mostrarTablero = false;
    actual_ = changeObject(actual_, nullptr);
    objeto = changeCurrentObject(objeto, WATT);
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
    actual_ = changeObject(actual_, nullptr);
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

    modo_objetos.display();
    modo_seleccion.display();
    add_objeto.display();
    delete_objeto.display();

    proyeccion.display();
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

    modo_objetos.handlemotion(x,y);
    modo_seleccion.handlemotion(x,y);
    add_objeto.handlemotion(x,y);
    delete_objeto.handlemotion(x,y);

    proyeccion.handlemotion(x,y);
}

void handle_mouse_buttons(int button, int state, int x, int y) {
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

    modo_objetos.handlemouse(button,state,x,y);
    modo_seleccion.handlemouse(button,state,x,y);
    add_objeto.handlemouse(button,state,x,y);
    delete_objeto.handlemouse(button,state,x,y);

    proyeccion.handlemouse(button,state,x,y);
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

    modo_objetos.setpos(-0.05,-0.55);
    modo_objetos.setsize(0.4,0.15);
    modo_objetos.setlabel("Objetos");
    modo_objetos.setaction(toggle_modo_objetos);
    modo_objetos.setactive(true);

    modo_seleccion.setpos(-0.05,-0.7);
    modo_seleccion.setsize(0.4,0.15);
    modo_seleccion.setlabel("Seleccion");
    modo_seleccion.setaction(toggle_modo_seleccion);
    modo_seleccion.setactive(true);

    add_objeto.setpos(-0.05,-0.85);
    add_objeto.setsize(0.4,0.15);
    add_objeto.setlabel("++Obj");
    add_objeto.setaction(toggle_add_objeto);
    add_objeto.setactive(false);

    delete_objeto.setpos(-0.05,-1);
    delete_objeto.setsize(0.4,0.15);
    delete_objeto.setlabel("--Obj");
    delete_objeto.setaction(toggle_delete_objeto);
    delete_objeto.setactive(false);

    proyeccion.setpos(-0.95,-1);
    proyeccion.setsize(0.4,0.15);
    proyeccion.setlabel("Proyec");
    proyeccion.setaction(toggle_proyeccion);
    proyeccion.setactive(true);
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

        case 'A': alfa -= 1; break;
        case 'D': alfa += 1; break;
        case 'W': beta_ -= 1; break;
        case 'S': beta_ += 1; break;

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
	}

    escena_cam->setObserverAngle({Observer_angle_x, Observer_angle_y});
    escena_cam->setObserverDistance(Observer_distance);
	glutPostRedisplay();
}

//***************************************************************************
// Funcion del ratón
//***************************************************************************
bool left_button_pressed = false;
bool middle_button_pressed = false;
#define BUFFER_SIZE 100

void colorpick(int x, int y) {
    unsigned char pixel[3] = {0};
    draw_hidden_scene();
    glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    draw_scene();

    for (unsigned int i = 0; i < vobjects.size(); ++i) {
        if (vobjects[i] != nullptr) {
            if (vobjects[i]->compareColor((int)pixel[0], (int)pixel[1], (int)pixel[2])) {
                selected = vobjects[i];
            }
        }
    }

    if (((int)pixel[0] == 255) && ((int)pixel[1] == 255) && ((int)pixel[2] == 255))
        selected = nullptr;
}

#define BUFFER_SIZE 100
#define MAX_SELECTION 64
int seleccionado;

void restoreoffset() {
    objeto_cam = escena_cam;
    objeto_cam->setOffset({0,0,0});
}

void glpick(int x, int y) {
    GLuint Hits, Selection_buffer[BUFFER_SIZE];
    GLint Viewport[4];

    glGetIntegerv(GL_VIEWPORT, Viewport);
    glSelectBuffer(BUFFER_SIZE, Selection_buffer);
    glRenderMode(GL_SELECT);

    glInitNames();
    glPushName(0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPickMatrix(x, Viewport[3] - y, 1, 1, Viewport);
    if (modoObjetos)
        escena_cam->project();
    if (modoSeleccion)
        objeto_cam->project();
    glMatrixMode(GL_MODELVIEW);
    draw_scene_names();
    Hits = glRenderMode(GL_RENDER);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (modoObjetos)
        escena_cam->project();
    if (modoSeleccion)
        objeto_cam->project();

    int seleccionado = -1;

    if (Hits > 0) {
        int auxprof;
        seleccionado = Selection_buffer[(0*4)+3];

        int prof = Selection_buffer[(0*4)+1];

        for(int i = 0; i < Hits; ++i) {
            auxprof = Selection_buffer[(i*4)+1];
            if (auxprof < prof) {
                prof = auxprof;
                seleccionado = Selection_buffer[(i*4)+3];
            }
        }

    } else {
        seleccionado = 0;
    }

    switch(seleccionado) {
        case 1:
            if (selectItems[0]) {
                selectItems[0] = false;
                restoreoffset();
            } else {
                selectItems[0] = true;
                objeto_cam = escena_cam;
                objeto_cam->setOffset({7,0,7});
            }
            break;

        case 2:
            if (selectItems[1]) {
                selectItems[1] = false;
                restoreoffset();
            } else {
                selectItems[1] = true;
                objeto_cam = escena_cam;
                objeto_cam->setOffset({0,0,7});
            }
            break;

        case 3:
            if (selectItems[2]) {
                selectItems[2] = false;
                restoreoffset();
            } else {
                selectItems[2] = true;
                objeto_cam = escena_cam;
                objeto_cam->setOffset({-7,0,7});
            }
            break;

        case 4:
            if (selectItems[3]) {
                selectItems[3] = false;
                restoreoffset();
            } else {
                selectItems[3] = true;
                objeto_cam = escena_cam;
                objeto_cam->setOffset({7,0,0});
            }
            break;

        case 5:
            if (selectItems[4]) {
                selectItems[4] = false;
                restoreoffset();
            } else {
                selectItems[4] = true;
                objeto_cam = escena_cam;
                objeto_cam->setOffset({0,0,0});
            }
            break;

        case 6:
            if (selectItems[5]) {
                selectItems[5] = false;
                restoreoffset();
            } else {
                selectItems[5] = true;
                objeto_cam = escena_cam;
                objeto_cam->setOffset({-7,0,0});
            }
            break;

        case 7:
            if (selectItems[6]) {
                selectItems[6] = false;
                restoreoffset();
            } else {
                selectItems[6] = true;
                objeto_cam = escena_cam;
                objeto_cam->setOffset({7,0,-7});
            }
            break;

        case 8:
            if (selectItems[7]) {
                selectItems[7] = false;
                restoreoffset();
            } else {
                selectItems[7] = true;
                objeto_cam = escena_cam;
                objeto_cam->setOffset({0,0,-7});
            }
            break;

        case 9:
            if (selectItems[8]) {
                selectItems[8] = false;
                restoreoffset();
            } else {
                selectItems[8] = true;
                objeto_cam = escena_cam;
                objeto_cam->setOffset({-7,0,-7});
            }
            break;
    }
}

void handle_mouse(int button, int state, int x, int y) {
    if (state = GLUT_UP) {
        if (button == 3) {
            Observer_distance /= 1.03;
            glutPostRedisplay();

            if (proyeccionParalela) {
                escena_cam->moveBackward();
                objeto_cam->moveBackward();
            }
        }        
        else if(button == 4) {
            Observer_distance *= 1.03;
            glutPostRedisplay();

            if (proyeccionParalela) {
                escena_cam->moveForward();
                objeto_cam->moveForward();
            }
        }
    }     

    if (button == GLUT_LEFT_BUTTON) {
        left_button_pressed = true;
        pickItem = !pickItem;
    }
    else
        left_button_pressed = false;

    if (button == GLUT_MIDDLE_BUTTON)
        middle_button_pressed = true;
    else
        middle_button_pressed = false;

    if (pickItem)
        glpick(x, y);

    escena_cam->setObserverDistance(Observer_distance);
    glutPostRedisplay();
}

int lastx = 0;
int lasty = 0;

void handle_mouse_movement(int x, int y) {
    if (left_button_pressed) {
        if (x > lastx)
            Observer_angle_y += 0.6;
        if (x < lastx)
            Observer_angle_y -= 0.6;    
        
        if (y > lasty)
            Observer_angle_x += 0.6;
        if (y < lasty)
            Observer_angle_x -= 0.6;
        
        lastx = x;
        lasty = y;
        
        escena_cam->setObserverAngle({Observer_angle_x, Observer_angle_y});
        glutPostRedisplay();
    }

    if (middle_button_pressed) {
        if (x > lastx)
            alfa += 0.25;
        if (x < lastx)
            alfa -= 0.25;    
        
        if (y > lasty)
            beta_ += 0.25;
        if (y < lasty)
            beta_ -= 0.25;

        lastx = x;
        lasty = y;
        
        glutPostRedisplay();
    }
}


//***************************************************************************
// Funcion de incializacion
//***************************************************************************
void initialize(void) {
	// se inicalizan la ventana y los planos de corte
	Window_width=5;
	Window_height=5;
	Front_plane=10;
	Back_plane=10000;

	// se inicia la posicion del observador, en el eje z
	Observer_distance=2*Front_plane;
	Observer_angle_x=0;
	Observer_angle_y=0;

    initialize_cameras();
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

static int value = 0; 

void menu(int num){
    if(num == 0){
        exit(0);
    }else{
        value = num;
    }

    switch (value) {
        case -2: toggle_proyeccion(); break;
        case -1: toggle_help(); break;
        case 1: glutPostRedisplay(); break;
        case 2: toggle_cube(); break;
        case 3: toggle_tetrahedron(); break;
        case 4: toggle_ply_static(); break;
        case 5: toggle_ply_revolution(); break;
        case 6: toggle_cylinder(); break;
        case 7: toggle_glass(); break;
        case 8: toggle_glass_inverted(); break;
        case 9: toggle_cone(); break;
        case 10: toggle_tube(); break;
        case 11: toggle_sphere(); break;
        case 12: toggle_watt(); break;
        case 13: toggle_mesh(); break;
        case 14: toggle_edges(); break;
        case 15: toggle_solid(); break;
        case 16: toggle_chess(); break;
        case 17: toggle_flat(); break;
        case 18: toggle_smooth(); break;
        case 19: toggle_modo_objetos(); break;
        case 20: toggle_modo_seleccion(); break;
        case 21: toggle_luz(); break;
        case 22: toggle_luz1(); break;
        case 23: toggle_masMaterial(); break;
        case 24: toggle_menosMaterial(); break;
        case 25: toggle_tablero(); break;
        case 26: toggle_mostrarimagen(); break;
        case 27: toggle_leerCoordenadas(); break;
        case 28: toggle_leerCoordenadasTextura(); break;
        case 29: toggle_masVel(); break;
        case 30: toggle_menosVel(); break;
        case 31: toggle_spin(); break;
    }

    glutPostRedisplay();
}

static int menu_id;
static int submenu_obj, submenu_viewmode, submenu_mode, submenu_lights, submenu_material, submenu_tablero, submenu_watt;

void createMenu(void){
    submenu_obj = glutCreateMenu(menu);
    glutAddMenuEntry("Cubo", 2);
    glutAddMenuEntry("Tetraedro", 3);
    glutAddMenuEntry("Ply", 4);
    glutAddMenuEntry("Ply Rev", 5);
    glutAddMenuEntry("Cilindro", 6);
    glutAddMenuEntry("Vaso", 7);
    glutAddMenuEntry("Vaso Inv", 8);
    glutAddMenuEntry("Cono", 9);
    glutAddMenuEntry("Tubo", 10);
    glutAddMenuEntry("Esfera", 11);
    glutAddMenuEntry("Watt", 12);
    
    submenu_viewmode = glutCreateMenu(menu);
    glutAddMenuEntry("Puntos", 13);
    glutAddMenuEntry("Lineas", 14);
    glutAddMenuEntry("Solido", 15);
    glutAddMenuEntry("Ajedrez", 16);
    glutAddMenuEntry("Flat", 17);
    glutAddMenuEntry("Smooth", 18);

    submenu_mode = glutCreateMenu(menu);
    glutAddMenuEntry("Objetos", 19);
    glutAddMenuEntry("Seleccion", 20);

    submenu_lights = glutCreateMenu(menu);
    glutAddMenuEntry("Luz 1", 21);
    glutAddMenuEntry("Luz inf", 22);

    submenu_material = glutCreateMenu(menu);
    glutAddMenuEntry("++Mat", 23);
    glutAddMenuEntry("--Mat", 24);

    submenu_tablero = glutCreateMenu(menu);
    glutAddMenuEntry("On/Off", 25);
    glutAddMenuEntry("On/Off Img", 26);
    glutAddMenuEntry("Leer Tab", 27);
    glutAddMenuEntry("Leer Img", 28);

    submenu_watt = glutCreateMenu(menu);
    glutAddMenuEntry("On/Off", 12);
    glutAddMenuEntry("++Vel", 29);
    glutAddMenuEntry("--Vel", 30);
    glutAddMenuEntry("Spin", 31);

    menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Proyeccion", -2);
    glutAddSubMenu("Mode", submenu_mode);
    glutAddSubMenu("Draw", submenu_obj);
    glutAddSubMenu("Viewmode", submenu_viewmode);
    glutAddSubMenu("Lights", submenu_lights);
    glutAddSubMenu("Material", submenu_material);
    glutAddSubMenu("Tablero", submenu_tablero);
    glutAddSubMenu("Watt", submenu_watt);
    glutAddMenuEntry("Help", -1);
    glutAddMenuEntry("Redisplay", 1);    
    glutAddMenuEntry("Quit", 0);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
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
	window_1 = glutCreateWindow("Practica 5. Angel Gomez Martin");

	// asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw_scene);
	// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
	glutReshapeFunc(change_window_size);
	// asignación de la funcion llamada "tecla_normal" al evento correspondiente
	glutKeyboardFunc(normal_keys);
	// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_keys);
    // menu
    createMenu();
    
    // Raton
    glutMouseFunc(handle_mouse);
    glutMotionFunc(handle_mouse_movement);

    // funcion de inicialización
	initialize();

	glutInitWindowSize(500,UI_window_height);
	glutInitWindowPosition(950,50);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	window_2 = glutCreateWindow("Buttons");
	glutDisplayFunc(draw_scene_button);
	glutPassiveMotionFunc(handle_motion);
	glutMouseFunc(handle_mouse_buttons);
	initialize2();

	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}
