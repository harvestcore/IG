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

using namespace std;

BrazosLaterales::BrazosLaterales() {
}

void BrazosLaterales::draw() {
    brazo_izq.generateByRevolution('y', false);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(-4,10,0);
    glRotatef(135,0,0,1);
    glScalef(0.5,6,0.5);
    brazo_izq.drawMesh();
    brazo_izq.drawEdges();
    brazo_izq.drawChess();
    glPopMatrix();

    brazo_der.generateByRevolution('y', false);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(4,10,0);
    glRotatef(225,0,0,1);
    glScalef(0.5,6,0.5);
    brazo_der.drawMesh();
    brazo_der.drawEdges();
    brazo_der.drawChess();
    glPopMatrix();
}

Disco::Disco() {
}

void Disco::draw() {
    disco_sup.generateByRevolution('y', false);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,12,0);
    glScalef(3,1,3);
    disco_sup.drawMesh();
    disco_sup.drawEdges();
    disco_sup.drawChess();
    glPopMatrix();

    laterales.draw();
}

BrazoPrincipal::BrazoPrincipal() {
}

void BrazoPrincipal::draw() {
    brazo.generateByRevolution('y', false);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,7,0);
    glScalef(1,10,1);
    brazo.drawMesh();
    brazo.drawEdges();
    brazo.drawChess();
    glPopMatrix();

    disco_sup.draw();
}

WattRegulator::WattRegulator() {
}

void WattRegulator::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,1,0);
    glScalef(5,2,5);
    base.drawMesh();
    //base.drawEdges();
    base.drawChess();
    glPopMatrix();

    brazo.draw();
}
