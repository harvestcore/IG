//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: 3DObject.cc
//
//####################################################

#include <GL/glut.h>
#include <vector>
#include <math.h>
#include "3DObject.h"
#include "vertex.h"
#include "models.h"
#include "wattRegulator.h"
#include <thread>
#include <chrono>

using namespace std;

Laterales::Laterales() {
}

void Laterales::draw() {
    comprobarMovimiento();

    tubo.generateByRevolution('y', false);

    // Brazo superior izq
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(-1.5,12,0);
    glRotatef(angulo_superior,0,0,1);
    glTranslatef(1.5,-12,0);     // origen

    glTranslatef(-5.5,12,0);
    glRotatef(90,0,0,1);
    glScalef(0.3,8,0.3);
    tubo.drawChess();
    glPopMatrix();

    // Brazo superior der
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(1.5,12,0);
    glRotatef(360 - angulo_superior,0,0,1);
    glTranslatef(-1.5,-12,0);     // origen

    glTranslatef(5,12,0);
    glRotatef(270,0,0,1);
    glScalef(0.3,8,0.3);
    tubo.drawChess();
    glPopMatrix();

    // Brazo inferior izq
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(-1.5,altura_disco_central,0);
    glRotatef(360-angulo_inferior,0,0,1);
    glTranslatef(1.5,-altura_disco_central,0);     // origen

    glTranslatef(-4,altura_disco_central,0);     // sitio
    glRotatef(90,0,0,1);
    glScalef(0.2,5,0.2);
    tubo.drawChess();
    glPopMatrix();

    // Brazo inferior der
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(1.5,altura_disco_central,0);
    glRotatef(angulo_inferior,0,0,1);
    glTranslatef(-1.5,-altura_disco_central,0);     // origen

    glTranslatef(4,altura_disco_central,0);
    glRotatef(270,0,0,1);
    glScalef(0.2,5,0.2);
    tubo.drawChess();
    glPopMatrix();

    // Disco central
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,altura_disco_central,0);
    glScalef(3.5,0.8,3.5);
    tubo.drawChess();
    glPopMatrix();

    // Varilla central
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(1,altura_disco_central-2,0);
    glScalef(0.2,4,0.2);
    tubo.drawChess();
    glPopMatrix();

    //cout << "angulo_superior: " << angulo_superior << endl;
    //cout << "angulo_inferior: " << angulo_inferior << endl;
    //cout << "-------------------" << endl;

}

void Laterales::incrementarAnguloSuperior() {
    angulo_superior += 0.95;
}

void Laterales::reducirAnguloSuperior() {
    angulo_superior -= 0.95;
}

void Laterales::incrementarAnguloInferior() {
    angulo_inferior += 0.75;
}

void Laterales::reducirAnguloInferior() {
    angulo_inferior -= 0.75;
}

void Laterales::incrementarDiscoCentral() {
    altura_disco_central += 0.13;
    reducirAnguloSuperior();
    reducirAnguloInferior();
}

void Laterales::reducirDiscoCentral() {
    altura_disco_central -= 0.13;
    incrementarAnguloSuperior();
    incrementarAnguloInferior();
}

void Laterales::comprobarMovimiento() {
    if (altura_disco_central < 6) {
        altura_disco_central = 6;
        angulo_superior = 35;
        angulo_inferior = 41;
    }

    if (altura_disco_central > 11.2) {
        altura_disco_central = 11.2;
        angulo_superior = -3;
        angulo_inferior = 11;
    }
}

Brazo_Disco::Brazo_Disco() {
}

void Brazo_Disco::draw() {
    brazo_disco.generateByRevolution('y', false);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,7,0);
    glScalef(0.5,10,0.5);
    brazo_disco.drawChess();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,12,0);
    glScalef(3.5,0.8,3.5);
    brazo_disco.drawChess();
    glPopMatrix();
}


Pie::Pie() {
}

void Pie::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,1,0);
    glScalef(7,2,7);
    pie.drawChess();
    glPopMatrix();
}

Watt::Watt() {
}

void Watt::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(0,-5,0);
        pie.draw();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glRotatef(angulo_giro,0,1,0);
        brazo_disco.draw();
        laterales.draw();
        glPopMatrix();
    glPopMatrix();
}

void Watt::incrementarAngulo() {
    laterales.incrementarAnguloSuperior();
}

void Watt::decrementarAngulo() {
    laterales.reducirAnguloSuperior();
}

void Watt::incrementarAnguloInf() {
    laterales.incrementarAnguloInferior();
}

void Watt::decrementarAnguloInf() {
    laterales.reducirAnguloInferior();
}

void Watt::incrementarDisco() {
    laterales.incrementarDiscoCentral();
    velocidad += 0.5;
}

void Watt::decrementarDisco() {
    laterales.reducirDiscoCentral();
    velocidad -= 0.5;
}

void Watt::giro() {
    if (velocidad < 1) velocidad = 1;
    if (velocidad > 5) velocidad = 5;


    angulo_giro += 0.7 * velocidad;
}
