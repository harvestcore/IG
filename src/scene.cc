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
#include "button.h"
#include "fps.h"
#include "light.h"
#include "plank.h"

using namespace std;

Models modelos;
vector<ViewMode> modos = {NULL_,NULL_,NULL_,NULL_,NULL_,NULL_,NULL_};
TypeObject objeto = _NULL;

vector<Materials> mat = {EMERALD,JADE,OBSIDIAN,PEARL,RUBY,TURQUOISE,BRASS,BRONCE,CHROME,COPPER,GOLD,SILVER,BLACK_PLASTIC,CYAN_PLASTIC,GREEN_PLASTIC,RED_PLASTIC,WHITE_PLASTIC,YELLOW_PLASTIC};
int mat_index = 0;

Texture foto("/mnt/c/Users/Angel/Dropbox/Universidad/Tercero/modif/P2_2/texturas/xd.jpg");
Plank tablero(25,25,25);
bool mostrarTablero = false;

ALLFIGURE cubo_, tetraedro_, beethoven_, peon_, cilindro_, vaso_, vaso2_, cono_, tubo_, esfera_;

bool drawflat = false;
bool drawsmooth = false;
bool mas_material = false;
bool menos_material = false;
bool help_ = false;

Light luz, luz_inf;
bool luz_ = false;
bool luz1_ = false;
float alfa = 1, beta = 1;

Plank p(30.0, 30.0, 2.0);

// Contador de FPS
FPScounter fps;
bool showFPS = false;

// Ventanas
int window_1, window_2;

bool sumar = false;
bool restar = false;

// tamaño de los ejes
const int AXIS_SIZE=10000;

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
    luz.setPosition(_vertex4f(0,0,10,1));
    luz.setAmbient(_vertex4f(0.2,0.2,0.2,1));
    luz.setDiffuse(_vertex4f(0.8,0.8,0.8,1));
    luz.setSpecular(_vertex4f(0.8,0.8,0.8,1));

    luz_inf.setID(GL_LIGHT1);
    luz_inf.setDirectional(false);
    luz_inf.setPosition(_vertex4f(0,20,0,0));
    luz_inf.setAmbient(_vertex4f(0.2,0.2,0.2,1));
    luz_inf.setDiffuse(_vertex4f(0.8,0.8,0.8,1));
    luz_inf.setSpecular(_vertex4f(1,1,1,1));
}

//**************************************************************************
//	INICIALIZAR OBJETOS
//***************************************************************************
void initialize_objects() {
    cubo_.createCube();
    cubo_.calculateNormalTriangles();
    cubo_.calculateNormalPoints();
    cubo_.setMaterial(1);

    tetraedro_.createTetrahedron();
    tetraedro_.calculateNormalTriangles();
    tetraedro_.calculateNormalPoints();
    tetraedro_.setMaterial(2);

    beethoven_.readPly("/mnt/c/Users/Angel/Dropbox/Universidad/Tercero/modif/P2_2/ply/beethoven.ply");
    beethoven_.calculateNormalTriangles();
    beethoven_.calculateNormalPoints();
    beethoven_.setMaterial(3);

    peon_.readPly("/mnt/c/Users/Angel/Dropbox/Universidad/Tercero/modif/P2_2/ply/peon.ply");
    peon_.setProfile(peon_.getVectorPoints());
    peon_.generateByRevolution('y', true);
    peon_.calculateNormalTriangles();
    peon_.calculateNormalPoints();
    peon_.setMaterial(4);

    cilindro_.createCylinder();
    cilindro_.generateByRevolution('y', false);
    cilindro_.calculateNormalTriangles();
    cilindro_.calculateNormalPoints();
    cilindro_.setMaterial(5);

    vaso_.createGlass();
    vaso_.generateByRevolution('y', false);
    vaso_.calculateNormalTriangles();
    vaso_.calculateNormalPoints();
    vaso_.setMaterial(6);

    vaso2_.createGlass_Inverted();
    vaso2_.generateByRevolution('y', false);
    vaso2_.calculateNormalTriangles();
    vaso2_.calculateNormalPoints();
    vaso2_.setMaterial(7);

    cono_.createCone();
    cono_.generateByRevolution('y', false);
    cono_.calculateNormalTriangles();
    cono_.calculateNormalPoints();
    cono_.setMaterial(8);

    tubo_.createTube();
    tubo_.generateByRevolution('y', false);
    tubo_.calculateNormalTriangles();
    tubo_.calculateNormalPoints();
    tubo_.setMaterial(9);

    esfera_.readPly("/mnt/c/Users/Angel/Dropbox/Universidad/Tercero/modif/P2_2/ply/sphere.ply");
    esfera_.calculateNormalTriangles();
    esfera_.calculateNormalPoints();
    esfera_.setMaterial(10);
}


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
    //float alto = glutGet(GLUT_WINDOW_WIDTH);
    //float ancho = glutGet(GLUT_WINDOW_HEIGHT);
    //float ratio = ancho/alto;
    //gluPerspective(60, ratio, 0.01, 100);
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
string objectToString(TypeObject obj) {
    switch (obj) {
        case CUBE:
        return "Cubo";
        case TETRAHEDRON:
        return "Tetraedro";
        case PLY_STATIC:
        return "Beethoven";
        case PLY_REVOLUTION:
        return "Peon";
        case CYLINDER:
        return "Cilindro";
        case GLASS:
        return "Vaso";
        case GLASS_INVERTED:
        return "Vaso Inv";
        case CONE:
        return "Cono";
        case TUBE:
        return "Tubo";
        case SPHERE:
        return "Esfera";
        case WATT:
        return "Watt";
        case _NULL:
        return "Off";
    }
}

int objectTomaterialID(TypeObject obj) {
    switch (obj) {
        case CUBE:
        return cubo_.getMaterialID();
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

string booltostring(bool bts) {
    if (bts)
        return "On";
    else
        return "Off";
}

string materialIDtostring(int mat) {
    switch (mat) {
        case 0:
            return "Off";
        case 1:
            return "EMERALD";
        case 2:
            return "JADE";
        case 3:
            return "OBSIDIAN";
        case 4:
            return "PEARL";
        case 5:
            return "RUBY";
        case 6:
            return "TURQUOISE";
        case 7:
            return "BRASS";
        case 8:
            return "BRONCE";
        case 9:
            return "CHROME";
        case 10:
            return "COPPER";
        case 11:
            return "GOLD";
        case 12:
            return "SILVER";
        case 13:
            return "BLACK_PLASTIC";
        case 14:
            return "CYAN_PLASTIC";
        case 15:
            return "GREEN_PLASTIC";
        case 16:
            return "RED_PLASTIC";
        case 17:
            return "WHITE_PLASTIC";
        case 18:
            return "YELLOW_PLASTIC";
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

    string data;

	if (objeto == WATT) printText(30, 30, "V: " + dts(modelos.v_Watt.getSpeed()));
    printText(30, 50, "FPS: " + dts(fps.getFPS()));
    printText(30, 70, "Objeto: " + objectToString(objeto));
    printText(30, 90, "Flat: " + booltostring(drawflat));
    printText(30, 110, "Smooth: " + booltostring(drawsmooth));
    printText(30, 130, "Luz: " + booltostring(luz_));
    printText(30, 150, "Luz inf: " + booltostring(luz1_));
    printText(30, 170, "Spin: " + booltostring(modelos.v_Watt.isSpinning()));

    if (drawflat || drawsmooth)
        printText(30, 190, "Material: " + materialIDtostring(objectTomaterialID(objeto)));
    else
        printText(30, 190, "Material: Off");

    if (help_) {
        printText(30, 830, "Mover luz: (WASD)");
        printText(30, 850, "Mover camara: (Arrows)");
        printText(30, 870, "Zoom: (AV/RE Pag)");
    }

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

	if (modelos.v_Watt.isSpinning()){
		modelos.v_Watt.giro();
		glutPostRedisplay();
	}

    if (luz_) {
        luz.enable();
    } else {
        luz.disable();
    }

    if (luz1_) {
        luz_inf.enable();
    } else {
        luz_inf.disable();
    }

    drawModels(modelos, objeto, modos);

    if (mostrarTablero) {
        tablero.generatePlank();
        foto.drawTexture(tablero.getCoordenadas());
    }

    if (drawflat) {
        switch (objeto) {
            case CUBE:
                cubo_.drawFlatSmoothing();
                break;

            case TETRAHEDRON:
                tetraedro_.drawFlatSmoothing();
                break;

            case PLY_STATIC:
                beethoven_.drawFlatSmoothing();
                break;

            case PLY_REVOLUTION:
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glScalef(0.6,0.6,0.6);
                peon_.drawFlatSmoothing();
                glPopMatrix();
                break;

            case CYLINDER:
                cilindro_.drawFlatSmoothing();
                break;

            case GLASS:
                vaso_.drawFlatSmoothing();
                break;

            case GLASS_INVERTED:
                vaso2_.drawFlatSmoothing();
                break;

            case CONE:
                cono_.drawFlatSmoothing();
                break;

            case TUBE:
                tubo_.drawFlatSmoothing();
                break;

            case SPHERE:
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glScalef(0.8,0.8,0.8);
                esfera_.drawFlatSmoothing();
                glPopMatrix();
                break;
        }
    }

    if (drawsmooth) {
        switch (objeto) {
            case CUBE:
                cubo_.drawGouraudSmoothing();
                break;

            case TETRAHEDRON:
                tetraedro_.drawGouraudSmoothing();
                break;

            case PLY_STATIC:
                beethoven_.drawGouraudSmoothing();
                break;

            case PLY_REVOLUTION:
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glScalef(0.6,0.6,0.6);
                peon_.drawGouraudSmoothing();
                glPopMatrix();
                break;

            case CYLINDER:
                cilindro_.drawGouraudSmoothing();
                break;

            case GLASS:
                vaso_.drawGouraudSmoothing();
                break;

            case GLASS_INVERTED:
                vaso2_.drawGouraudSmoothing();
                break;

            case CONE:
                cono_.drawGouraudSmoothing();
                break;

            case TUBE:
                tubo_.drawGouraudSmoothing();
                break;

            case SPHERE:
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glScalef(0.8,0.8,0.8);
                esfera_.drawGouraudSmoothing();
                glPopMatrix();
                break;
        }
    }

    if (mas_material) {
        switch (objeto) {
            case CUBE:
                cubo_.incrementMaterialID();
                cubo_.updateMaterial();
                break;

            case TETRAHEDRON:
                tetraedro_.incrementMaterialID();
                tetraedro_.updateMaterial();
                break;

            case PLY_STATIC:
                beethoven_.incrementMaterialID();
                beethoven_.updateMaterial();
                break;

            case PLY_REVOLUTION:
                peon_.incrementMaterialID();
                peon_.updateMaterial();
                break;

            case CYLINDER:
                cilindro_.incrementMaterialID();
                cilindro_.updateMaterial();
                break;

            case GLASS:
                vaso_.incrementMaterialID();
                vaso_.updateMaterial();
                break;

            case GLASS_INVERTED:
                vaso2_.incrementMaterialID();
                vaso2_.updateMaterial();
                break;

            case CONE:
                cono_.incrementMaterialID();
                cono_.updateMaterial();
                break;

            case TUBE:
                tubo_.incrementMaterialID();
                tubo_.updateMaterial();
                break;

            case SPHERE:
                esfera_.incrementMaterialID();
                esfera_.updateMaterial();
                break;
        }
        mas_material = false;
    }

    if (menos_material) {
        switch (objeto) {
            case CUBE:
                cubo_.decrementMaterialID();
                cubo_.updateMaterial();
                break;

            case TETRAHEDRON:
                tetraedro_.decrementMaterialID();
                tetraedro_.updateMaterial();
                break;

            case PLY_STATIC:
                beethoven_.decrementMaterialID();
                beethoven_.updateMaterial();
                break;

            case PLY_REVOLUTION:
                peon_.decrementMaterialID();
                peon_.updateMaterial();
                break;

            case CYLINDER:
                cilindro_.decrementMaterialID();
                cilindro_.updateMaterial();
                break;

            case GLASS:
                vaso_.decrementMaterialID();
                vaso_.updateMaterial();
                break;

            case GLASS_INVERTED:
                vaso2_.decrementMaterialID();
                vaso2_.updateMaterial();
                break;

            case CONE:
                cono_.decrementMaterialID();
                cono_.updateMaterial();
                break;

            case TUBE:
                tubo_.decrementMaterialID();
                tubo_.updateMaterial();
                break;

            case SPHERE:
                esfera_.decrementMaterialID();
                esfera_.updateMaterial();
                break;
        }
        menos_material = false;
    }

    luz.setAlpha(alfa);
    luz.setBeta(beta);

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

Button help;

void exit_program() {
	exit(0);
}

void toggle_help() {
    help_ = !help_;
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_mesh() {
	modos = changeMode(modos, MESH, 0);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_edges() {
	modos = changeMode(modos, EDGES, 1);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_solid() {
	modos = changeMode(modos, SOLID, 2);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_chess() {
	modos = changeMode(modos, CHESS, 3);
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
	modelos.v_Watt.aumentarVelocidad();
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_menosVel() {
	modelos.v_Watt.decrementarVelocidad();
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_spin() {
	modelos.v_Watt.toggleSpinning();
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

////////////

void toggle_cube() {
	objeto = changeObject(objeto, CUBE);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_tetrahedron() {
	objeto = changeObject(objeto, TETRAHEDRON);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_ply_static() {
	objeto = changeObject(objeto, PLY_STATIC);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_ply_revolution() {
	objeto = changeObject(objeto, PLY_REVOLUTION);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_cylinder() {
	objeto = changeObject(objeto, CYLINDER);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_glass() {
	objeto = changeObject(objeto, GLASS);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_glass_inverted() {
	objeto = changeObject(objeto, GLASS_INVERTED);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_cone() {
	objeto = changeObject(objeto, CONE);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_tube() {
	objeto = changeObject(objeto, TUBE);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_sphere() {
	objeto = changeObject(objeto, SPHERE);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

void toggle_watt() {
	objeto = changeObject(objeto, WATT);
	glutSetWindow(window_1);
	draw_scene();
	glutSetWindow(window_2);
}

	/////////////////

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

	////////////////////

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
    luz1_ = !luz1_;
    glutSetWindow(window_1);
    draw_scene();
    glutSetWindow(window_2);
}

void toggle_flat() {
    drawflat = !drawflat;
    drawsmooth = false;
    glutSetWindow(window_1);
    draw_scene();
    glutSetWindow(window_2);
}

void toggle_smooth() {
    drawsmooth = !drawsmooth;
    drawflat = false;
    glutSetWindow(window_1);
    draw_scene();
    glutSetWindow(window_2);
}

void toggle_tablero() {
    mostrarTablero = !mostrarTablero;
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
    if (tablero.getCubes() > 0)
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
}

void handle_motion(int x, int y) {
	salir.handlemotion(x,y);
    help.handlemotion(x,y);

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
    vaso_invertido.setlabel("Vaso Inv");
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

    tab.setpos(0.4,0.8);
    tab.setsize(0.4,0.15);
    tab.setlabel("Tablero");
    tab.setaction(toggle_tablero);
    tab.setactive(true);

    masCubo.setpos(0.4,0.65);
    masCubo.setsize(0.4,0.15);
    masCubo.setlabel("++Cube");
    masCubo.setaction(toggle_masCubo);
    masCubo.setactive(true);

    menosCubo.setpos(0.4,0.5);
    menosCubo.setsize(0.4,0.15);
    menosCubo.setlabel("--Cube");
    menosCubo.setaction(toggle_menosCubo);
    menosCubo.setactive(true);

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
        case 'A': modelos.v_Watt.toggleSpinning(); break;
        case 'G': luz_ = !luz_; break;
        case 'H': luz1_ = !luz1_; break;
        case 'B': tablero.incrementSide(); break;
        case 'N': tablero.decrementSide(); break;
        case 'J': tablero.incrementWidth(); break;
        case 'K': tablero.decrementWidth(); break;
        case 'S': tablero.incrementHeight(); break;
        case 'D': tablero.decrementHeight(); break;
        case '1': mostrarTablero = !mostrarTablero; break;
		case 'X': modelos.v_Watt.aumentarVelocidad(); break;
		case 'Z': modelos.v_Watt.decrementarVelocidad(); break;
*/

        case 'A': alfa -= 1; break;
        case 'D': alfa += 1; break;
        case 'W': beta -= 1; break;
        case 'S': beta += 1; break;
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
	Front_plane=5;
	Back_plane=10000;

	// se inicia la posicion del observador, en el eje z
	Observer_distance=2*Front_plane;
	Observer_angle_x=0;
	Observer_angle_y=0;

    initialize_ligths();
    initialize_objects();

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
