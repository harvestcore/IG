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

BrazoLateral::BrazoLateral() {
}

void BrazoLateral::draw() {
    //brazo_lat.generateByRevolution('y', false);
    //brazo_lat.drawMesh();
    /*
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,14,0);
    glScalef(1,6,1);
    glRotatef(45,1,1,1);
    brazo_lat.drawMesh();
    brazo_lat.drawEdges();
    glPopMatrix();
    */
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
    glPopMatrix();

    lat_1.draw();
    //lat_2.draw();
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
    base.drawEdges();
    glPopMatrix();

    brazo.draw();
}
