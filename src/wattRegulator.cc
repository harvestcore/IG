//####################################################
//
//  Ángel Gómez Martín
//  agomezm@correo.ugr.es
//  3º A - Informática Gráfica 2017-18
//  GII - ETSIIT
//
//  file: wattRegulator.cc
//
//####################################################

#include "wattRegulator.h"

using namespace std;

Laterales::Laterales() {
    Ply_Static aux("/mnt/c/Users/Angel/Dropbox/Universidad/Tercero/modif/P2_2/ply/beethoven.ply");
    beethoven = aux;
}

void Laterales::draw(ViewMode mode) {
    comprobarMovimiento();

    tubo.generateByRevolution('y', false);

    // Brazo superior izq
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(-1.5,12,0);
    glRotatef(angulo_superior,0,0,1);
    glTranslatef(1.5,-12,0);

    glTranslatef(-5.5,12,0);
    glRotatef(90,0,0,1);
    glScalef(0.35,8,0.35);
    show(mode, CYLINDER);
    glPopMatrix();

    // Brazo superior der
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(1.5,12,0);
    glRotatef(360-angulo_superior,0,0,1);
    glTranslatef(-1.5,-12,0);

    glTranslatef(5.5,12,0);
    glRotatef(270,0,0,1);
    glScalef(0.35,8,0.35);
    show(mode, CYLINDER);
    glPopMatrix();

    // Brazo inferior izq
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(-1.5,altura_disco_central,0);
    glRotatef(360-angulo_inferior,0,0,1);
    glTranslatef(1.5,-altura_disco_central,0);

    glTranslatef(-4,altura_disco_central,0);
    glRotatef(90,0,0,1);
    glScalef(0.2,5.1,0.2);
    show(mode, CYLINDER);
    glPopMatrix();

    // Brazo inferior der
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(1.5,altura_disco_central,0);
    glRotatef(angulo_inferior,0,0,1);
    glTranslatef(-1.5,-altura_disco_central,0);

    glTranslatef(4,altura_disco_central,0);
    glRotatef(270,0,0,1);
    glScalef(0.2,5.1,0.2);
    show(mode, CYLINDER);
    glPopMatrix();

    // Disco central
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,altura_disco_central,0);
    glScalef(3.5,0.8,3.5);
    show(mode, CYLINDER);
    glPopMatrix();

    // Varilla central
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(1,altura_disco_central-2,0);
    glScalef(0.2,4,0.2);
    show(mode, CYLINDER);
    glPopMatrix();

    // Esfera izquierda
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(-1.5,12,0);
    glRotatef(angulo_superior,0,0,1);
    glTranslatef(1.5,-13,0);

    glTranslatef(-10,13,0);
    glScalef(0.009,0.009,0.009);
    show(mode, SPHERE);
    glPopMatrix();

    // Esfera derecha
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(1.5,12,0);
    glRotatef(360-angulo_superior,0,0,1);
    glTranslatef(-1.5,-13,0);

    glTranslatef(10,13,0);
    glScalef(0.009,0.009,0.009);
    show(mode, SPHERE);
    glPopMatrix();

    // Beethoven izquierda
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(-1.5,12,0);
    glRotatef(angulo_superior,0,0,1);
    glTranslatef(1.5,-13,0);

    glTranslatef(-10,15.8,0);
    glScalef(0.3,0.3,0.3);
    show(mode, PLY_STATIC);
    glPopMatrix();

    // Beethoven derecha
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(1.5,12,0);
    glRotatef(360-angulo_superior,0,0,1);
    glTranslatef(-1.5,-13,0);

    glTranslatef(10,15.8,0);
    glScalef(0.3,0.3,0.3);
    show(mode, PLY_STATIC);
    glPopMatrix();
}

void Laterales::show(ViewMode mode, TypeObject type) {
    if (type == CYLINDER) {
        switch (mode) {
            case MESH: tubo.drawMesh(); break;
            case EDGES: tubo.drawEdges(); break;
            case SOLID: tubo.drawSolid(); break;
            case CHESS: tubo.drawChess(); break;
        }
    }

    if (type == SPHERE) {
        switch (mode) {
            case MESH: bola.drawMesh(); break;
            case EDGES: bola.drawEdges(); break;
            case SOLID: bola.drawSolid(); break;
            case CHESS: bola.drawChess(); break;
        }
    }

    if (type == PLY_STATIC) {
        switch (mode) {
            case MESH: beethoven.drawMesh(); break;
            case EDGES: beethoven.drawEdges(); break;
            case SOLID: beethoven.drawSolid(); break;
            case CHESS: beethoven.drawChess(); break;
        }
    }
}

void Laterales::incrementarAnguloSuperior(double velocidad) {
    if (velocidad < 8.5) {
        angulo_superior += 0.105 * velocidad;
    }

    if (angulo_superior < 35)
        angulo_superior *=1.0008;
}

void Laterales::reducirAnguloSuperior(double velocidad) {
    if (velocidad < 8.5) {
        angulo_superior -= 0.105 * velocidad;
    }
    if (angulo_superior < 35)
        angulo_superior *=1.0008;
}

void Laterales::incrementarAnguloInferior(double velocidad) {
    if (velocidad < 8.5) {
        angulo_inferior += 0.09 * velocidad;
    }

    if (angulo_inferior < 41)
        angulo_inferior *=1.0008;
}

void Laterales::reducirAnguloInferior(double velocidad) {
    if (velocidad < 8.5) {
        angulo_inferior -= 0.09 * velocidad;
    }
    if (angulo_inferior < 41)
        angulo_inferior *=1.0008;
}

void Laterales::incrementarDiscoCentral(double velocidad) {
    if (velocidad < 8.5) {
        altura_disco_central += 0.015 * velocidad;
        reducirAnguloSuperior(velocidad);
        reducirAnguloInferior(velocidad);
        comprobarMovimiento();
    }
}

void Laterales::decrementarDiscoCentral(double velocidad) {
    if (velocidad < 8.5) {
        altura_disco_central -= 0.015 * velocidad;
        incrementarAnguloSuperior(velocidad);
        incrementarAnguloInferior(velocidad);
        comprobarMovimiento();
    }
}

void Laterales::comprobarMovimiento() {
    if (altura_disco_central < 0) {
        altura_disco_central = 0;
        angulo_superior = 35;
        angulo_inferior = 41;
    }

    if (altura_disco_central > 11.2) {
        altura_disco_central = 11.2;
        angulo_superior = -2.741; //-1.9075;
        angulo_inferior = 10;
    }
}

Brazo_Disco::Brazo_Disco() {
}

void Brazo_Disco::draw(ViewMode mode) {
    brazo_disco.generateByRevolution('y', false);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,7,0);
    glScalef(0.8,10,0.8);
    show(mode);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,12,0);
    glScalef(3.5,0.8,3.5);
    show(mode);
    glPopMatrix();
}

void Brazo_Disco::show(ViewMode mode) {
    switch (mode) {
        case MESH: brazo_disco.drawMesh(); break;
        case EDGES: brazo_disco.drawEdges(); break;
        case SOLID: brazo_disco.drawSolid(); break;
        case CHESS: brazo_disco.drawChess(); break;
    }
}


Pie::Pie() {
}

void Pie::draw(ViewMode mode) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,1,0);
    glScalef(7,2,7);
    show(mode);
    glPopMatrix();
}

void Pie::show(ViewMode mode) {
    switch (mode) {
        case MESH: pie.drawMesh(); break;
        case EDGES: pie.drawEdges(); break;
        case SOLID: pie.drawSolid(); break;
        case CHESS: pie.drawChess(); break;
    }
}

Watt::Watt() {
}

void Watt::draw(ViewMode mode) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(0,-5,0);
        pie.draw(mode);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glRotatef(angulo_giro,0,1,0);
        brazo_disco.draw(mode);
        laterales.draw(mode);
        glPopMatrix();
    glPopMatrix();
}

void Watt::incrementarAngulo() {
    laterales.incrementarAnguloSuperior(velocidad);
}

void Watt::decrementarAngulo() {
    laterales.reducirAnguloSuperior(velocidad);
}

void Watt::incrementarAnguloInf() {
    laterales.incrementarAnguloInferior(velocidad);
}

void Watt::decrementarAnguloInf() {
    laterales.reducirAnguloInferior(velocidad);
}

void Watt::aumentarVelocidad() {
    velocidad += 0.1;
    control();
    laterales.incrementarDiscoCentral(velocidad);
}

void Watt::decrementarVelocidad() {
    velocidad -= 0.1;
    control();
    laterales.decrementarDiscoCentral(velocidad);
}

void Watt::control() {
    if (velocidad < 1) velocidad = 1;
    if (velocidad > 25) velocidad = 25;
}

void Watt::giro() {
    control();
    angulo_giro += fmod((0.6 * velocidad),360);
}

void Watt::toggleSpinning() {
    girando = !girando;
}

bool Watt::isSpinning() {
    return girando;
}

double Watt::getSpeed() {
    return velocidad;
}
