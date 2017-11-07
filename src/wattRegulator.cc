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

Soportes::Soportes() {
}

void Soportes::draw() {
    soporte_izq.generateByRevolution('y', false);


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(-4.5,8,0);
    glRotatef(105,0,0,1);
    glTranslatef(4.5,-8,0);
    glTranslatef(-4.5,8,0);
    glRotatef(90,0,0,1);
    glScalef(0.3,6,0.3);
    //soporte_izq.drawMesh();
    //soporte_izq.drawEdges();
    soporte_izq.drawChess();
    glPopMatrix();

    soporte_der.generateByRevolution('y', false);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(4.5,8,0);
    glRotatef(270,0,0,1);
    glScalef(0.3,6,0.3);
    //soporte_der.drawMesh();
    //soporte_der.drawEdges();
    soporte_der.drawChess();
    glPopMatrix();
}

Anillo::Anillo() {
}

void Anillo::draw() {
    varilla.generateByRevolution('y', false);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(1,5.8,0);
    glScalef(0.2,4,0.2);
    //anillo_central.drawMesh();
    //anillo_central.drawEdges();
    varilla.drawChess();
    glPopMatrix();

    anillo_central.generateByRevolution('y', false);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,8,0);
    glScalef(3,0.8,3);
    //anillo_central.drawMesh();
    //anillo_central.drawEdges();
    anillo_central.drawChess();
    glPopMatrix();

    soportes_laterales.draw();
}

Esferas::Esferas() {
}

void Esferas::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(-8.5,12,0);
    glScalef(0.009,0.009,0.009);
    //bola_izq.drawMesh();
    //bola_izq.drawEdges();
    bola_izq.drawChess();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(8.5,12,0);
    glScalef(0.009,0.009,0.009);
    //bola_der.drawMesh();
    //bola_der.drawEdges();
    bola_der.drawChess();
    glPopMatrix();

    anillo_central.draw();
}

BrazosLaterales::BrazosLaterales() {
}

void BrazosLaterales::draw() {
    brazo_izq.generateByRevolution('y', false);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(-4.5,12,0);
    glRotatef(90,0,0,1);
    glScalef(0.3,6,0.3);
    //brazo_izq.drawMesh();
    //brazo_izq.drawEdges();
    brazo_izq.drawChess();
    glPopMatrix();

    brazo_der.generateByRevolution('y', false);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(4.5,12,0);
    glRotatef(270,0,0,1);
    glScalef(0.3,6,0.3);
    //brazo_der.drawMesh();
    //brazo_der.drawEdges();
    brazo_der.drawChess();
    glPopMatrix();

    bolas.draw();
}

Disco::Disco() {
}

void Disco::draw() {
    disco_sup.generateByRevolution('y', false);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,12,0);
    glScalef(3,0.8,3);
    //disco_sup.drawMesh();
    //disco_sup.drawEdges();
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
    glScalef(0.5,10,0.5);
    //brazo.drawMesh();
    //brazo.drawEdges();
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
    glScalef(7,2,7);
    //base.drawMesh();
    //base.drawEdges();
    base.drawChess();
    glPopMatrix();

    brazo.draw();
}
